#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <argp.h>

#include "emu.h"
#include "elf.h"
#include "traceback.h"
#include "asm/context.h"

const char* argp_program_version = "urv86t 0.1";
const char* argp_program_bug_address = "<mindaugas.taujanskas@proton.me>";

static char doc[] = "The Ultimate RV-x86 Transpiler";
static char args_doc[] = "RISCV-BINARY";

static struct argp_option options[] = {
  {NULL, 'S', "PATH", OPTION_ARG_OPTIONAL, "Output disassembly to file", 0},
  {0}
};

struct arguments
{
  char *input_file;
  int is_disasm;
  char *disasm_path;
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;
  switch (key)
  {
    case 'S':
      arguments->is_disasm = 1;
      if (arg)
        arguments->disasm_path = arg;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        argp_usage (state);
      arguments->input_file = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
        argp_usage (state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};

void
bkpt_user_loop (rvstate_t state, struct rvbkpt_ev* ev)
{
  (void)ev;
  printf ("Breakpoint hit at 0x%" PRIx32 "\n", state->pc);
  while (1)
  {
    char cmd[32];
    printf ("> ");
    if (fgets (cmd, sizeof (cmd), stdin) == NULL)
      break;
    cmd[strcspn (cmd, "\n")] = 0;
    for (char *p = cmd; *p; p++)
      *p = tolower(*p);
    
    if (!strcmp (cmd, "c") || !strcmp (cmd, "continue"))
      break;
    else if (!strcmp (cmd, "s") || !strcmp (cmd, "step"))
    {
      rvemu_step (state);
      continue;
    }
    else if (!strcmp (cmd, "r") || !strcmp (cmd, "regs"))
    {
      rvtrbk_print_dump (state);
    }
    else
      printf ("Commands: c/continue, s/step, r/regs\n");
  }
}

int
main (int argc, char** argv)
{
  struct arguments arguments = {0};
  
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  elfctx_t elf_ctx = NULL;
  u8* emu_code = NULL;
  rvstate_t state = NULL;

  auto fd = fopen (arguments.input_file, "rb");
  if (fd == NULL)
    rvtrbk_fatal ("Failed to open binary file\n");

  fseek (fd, 0, SEEK_END);
  size_t fd_size = ftell (fd);
  rewind (fd);

  if ((emu_code = calloc (1, fd_size)) == NULL)
    rvtrbk_fatal ("Failed to allocate memory region for code\n");

  size_t nread;
  if ((nread = fread (emu_code, 1, fd_size, fd)) != fd_size)
    rvtrbk_fatal ("Failed to read from binary file\n");

  elf_ctx = elf_init (emu_code, nread);
  if (elf_ctx == NULL)
    rvtrbk_fatal ("Failed to parse ELF file\n");
  else if (!elf_ctx->bp)
    rvtrbk_fatal ("Failed to allocate stack/heap\n");

  state = rvstate_init (elf_ctx);
  if (state == NULL)
    rvtrbk_fatal ("Failed to allocate emulation context\n");

  if (arguments.is_disasm)
  {
    size_t path_len;
    if (arguments.disasm_path != NULL)
      path_len = strlen (arguments.disasm_path);
    else
      path_len = strlen (arguments.input_file) + 2;
    
    char disasm_path[path_len + 1];
    if (arguments.disasm_path != NULL)
      strcpy (disasm_path, arguments.disasm_path);
    else
    {
      strcpy (disasm_path, arguments.input_file);
      strcat (disasm_path, ".S");
    }
    rvtrbk_debug ("Disassembly will be saved to %s\n", disasm_path);
    if ((state->gen_ctx.disasm = rvasm_init (disasm_path)) == NULL)
      rvtrbk_fatal ("Failed to open file for disassembly context\n");
  }

#if RV32_HAS(BKPT)
  rvtrbk_debug (
    "Setting breakpoint at pc: 0x%" PRIx32 "\n", elf_ctx->entry_point);
  struct rvbkpt_ev entry_bkpt = {
    .pc_cond = {
      .val = 0x10954,
      .comp = BKPTCOMP_EQ,
    },
    .one_shot = true, .active = true
  };
  rvbkpt_add (state, &entry_bkpt);
#endif

  while (rvemu_step (state))
  {
#if RV32_HAS(BKPT)
    struct rvbkpt_ev* which = NULL;
    if ((which = rvbkpt_poll (state)) == NULL)
      continue;
    bkpt_user_loop (state, which);
#endif
  }

  rvtrbk_print_dump (state);
  if (state->gen_ctx.disasm != NULL)
    rvasm_free (state->gen_ctx.disasm);
  rvstate_free (state);
  elf_free (elf_ctx);
  free (emu_code);
  fclose (fd);

  return EXIT_SUCCESS;
}