#include <stdlib.h>
#include <string.h>

#include "elf.h"
#include "traceback.h"

u8*
elf_vma_to_mem (elfctx_t ctx, u32 ptr)
{
  for (size_t i = 0; i < ctx->nr_regions; ++i)
  {
    auto region = &ctx->load_regions[i];
    if ((region->vma_base > ptr) || (ptr >= region->vma_base + region->size))
      continue;
    u8* mem_addr = region->mem_base + (ptr - region->vma_base);
    // rvtrbk_debug ("VMA (#%zu) 0x%" PRIx32 " to MEM %p\n", i, ptr, mem_addr);
    return mem_addr;
  }
  return NULL;
}

u32
elf_mem_to_vma (elfctx_t ctx, u8* ptr)
{
  for (size_t i = 0; i < ctx->nr_regions; ++i)
  {
    auto region = &ctx->load_regions[i];
    if ((region->mem_base > ptr) || (ptr >= region->mem_base + region->size))
      continue;
    word_t vma_addr = region->vma_base + (ptr - region->mem_base);
    rvtrbk_debug ("MEM %p to VMA (#%zu) 0x%" PRIx32 "\n", ptr, i, vma_addr);
    return vma_addr;
  }
  rvtrbk_debug ("MEM %p has no associated LOAD region\n", ptr);
  return 0;
}

elfctx_t
elf_init (u8* const bytes, size_t length)
{
  elfctx_t ctx = calloc (1, sizeof (struct elf_context));
  if (ctx == NULL)
    rvtrbk_fatal ("failed to allocate ELF parsing context\n");

  auto ehdr = (Elf32_Ehdr *)bytes;
  if (length < sizeof (Elf32_Ehdr))
  {
    rvtrbk_debug ("invalid length to form ELF header\n");
    return ctx;
  }

  rvtrbk_debug ("ELF file information:\n");

  if ((ehdr->e_ident[0] != EI_MAG0) || (ehdr->e_ident[1] != EI_MAG1)
      || (ehdr->e_ident[2] != EI_MAG2) ||(ehdr->e_ident[3] != EI_MAG3))
  {
    rvtrbk_debug ("\tinvalid ELF magic number\n");
    return ctx;
  }

  switch (ehdr->e_ident[4])
  {
    case EI_ELFCLASSNONE:
      rvtrbk_debug ("\tFile class: unspecified\n");
      return ctx;
    case EI_ELFCLASS32:
      rvtrbk_debug ("\tFile class: 32 bit\n");
      break;
    case EI_ELFCLASS64:
      rvtrbk_debug ("\tFile class: 64 bit\n");
      break;
    default:
      rvtrbk_debug ("\tFile class: unrecognised class\n");
      return ctx;
  }

  switch (ehdr->e_ident[5])
  {
    case EI_ELFDATANONE:
      rvtrbk_debug ("\tData encoding: unspecified\n");
      return ctx;
    case EI_ELFDATA2LSB:
      rvtrbk_debug ("\tData encoding: little-endian\n");
      break;
    case EI_ELFDATA2MSB:
      rvtrbk_debug ("\tData encoding: big-endian\n");
      break;
    default:
      rvtrbk_debug ("\tData encoding: unrecognised\n");
      return ctx;
  }

  switch (ehdr->e_ident[6])
  {
    case EI_EV_NONE:
      rvtrbk_debug ("\tFile version: none\n");
      return ctx;
    case EI_EV_CURRENT:
      rvtrbk_debug ("\tFile version: current\n");
      break;
    default:
      rvtrbk_debug ("\tFile version: unrecognised\n");
      return ctx;
  }

  rvtrbk_debug ("\tOS/ABI identification: %" PRIu8 "\n", ehdr->e_ident[7]);
  rvtrbk_debug ("\tABI version: %" PRIu8 "\n", ehdr->e_ident[8]);

  switch (ehdr->e_machine)
  {
    case ET_NONE:
      rvtrbk_debug ("No machine architecture specified\n");
      return ctx;
    case EM_M32:
      rvtrbk_debug ("Machine architecture: AT&T WE 32100\n");
      break;
    case EM_SPARC:
      rvtrbk_debug ("Machine architecture: SPARC\n");
      break;
    case EM_386:
      rvtrbk_debug ("Machine architecture: Intel Architecture\n");
      break;
    case EM_68K:
      rvtrbk_debug ("Machine architecture: Motorola 68000\n");
      break;
    case EM_88K:
      rvtrbk_debug ("Machine architecture: Motorola 88000\n");
      break;
    case EM_860:
      rvtrbk_debug ("Machine architecture: Intel 80860\n");
      break;
    case EM_MIPS:
      rvtrbk_debug ("Machine architecture: MIPS RS3000 BE\n");
      break;
    case EM_MIPS_RS4_BE:
      rvtrbk_debug ("Machine architecture: MIPS RS4000 BE\n");
      break;
    case EM_RISCV:
      rvtrbk_debug ("Machine architecture: RISC-V\n");
      break;
    default:
      rvtrbk_debug ("Machine architecture: Unknown (%" PRIu32 ")\n",
        ehdr->e_machine);
      break;
  }

  rvtrbk_debug ("File version: %" PRIu8 "\n", ehdr->e_version);
  if (!ehdr->e_phoff)
  {
    rvtrbk_debug ("File contains no program header\n");
    return ctx;
  }

  rvtrbk_debug ("Entry-point at 0x%" PRIx32 "\n", ehdr->e_entry);

  rvtrbk_debug (
    "We have %" PRIu16 " section header(s), %" PRIu16 " bytes each\n",
    ehdr->e_shnum, ehdr->e_shentsize);

  auto strtab_ent
    = (Elf32_Shdr *)(
        bytes + ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize);
  u8* strtab = bytes + strtab_ent->sh_offset;
  u32 bss_start = 0, bss_size = 0;

  for (size_t sh_idx = 0; sh_idx < ehdr->e_shnum; ++sh_idx)
  {
    auto sh_ent
      = (Elf32_Shdr *)(bytes + ehdr->e_shoff + sh_idx * ehdr->e_shentsize);
    if (!sh_ent->sh_addr)
      continue;
    const char* shstr_ent = &((char *)strtab)[sh_ent->sh_name];
    rvtrbk_debug (
      "\t0x%08" PRIx32 " - 0x%08" PRIx32 ": %s\n",
      sh_ent->sh_addr, sh_ent->sh_addr + sh_ent->sh_size, shstr_ent);
    if (!strcmp (shstr_ent, ".bss"))
    {
      bss_start = sh_ent->sh_addr;
      bss_size = sh_ent->sh_size;
    }
  }

  rvtrbk_debug (
    "We have %" PRIu16 " program header(s), %" PRIu16 " bytes each\n",
    ehdr->e_phnum, ehdr->e_phentsize);

  /* +2 for heap/stack */
  size_t ph_count = 2;

  ctx->load_regions = calloc (
    ehdr->e_phnum + ph_count, sizeof (struct elf_load_region));
  if (ctx->load_regions == NULL)
    rvtrbk_fatal ("failed to allocate ELF LOAD region array\n");

  for (size_t ph_idx = 0; ph_idx < ehdr->e_phnum; ++ph_idx)
  {
    auto phdr
      = (Elf32_Phdr *)(bytes + ehdr->e_phoff + ph_idx * ehdr->e_phentsize);
    if (!phdr->p_memsz)
    {
      rvtrbk_debug ("\tSegment #%zu non-LOAD, skipping...\n", ph_idx);
      continue;
    }
    if (phdr->p_offset + phdr->p_filesz > length)
    {
      rvtrbk_debug (
        "\tSegment #%zu specifies region outside of file\n", ph_idx);
      continue;
    }
    rvtrbk_debug (
      "\tLOAD segment #%zu (in file +0x%" PRIx32 ") loading %" PRIu32
      " bytes to VMA 0x%" PRIx32 " (in file %" PRIu32 " bytes)\n",
      ph_idx, phdr->p_offset, phdr->p_memsz, phdr->p_vaddr, phdr->p_filesz);
    auto region = &ctx->load_regions[ph_count - 2];
    region->vma_base = phdr->p_vaddr;
    region->size = phdr->p_memsz;
    if ((region->mem_base = calloc (1, region->size)) == NULL)
      rvtrbk_fatal ("failed to allocate context LOAD region\n");
    region->mem_base = memcpy (
      region->mem_base, bytes + phdr->p_offset, phdr->p_filesz);
    region->tag = "LOAD";
    rvtrbk_debug (
      "\t-\tallocated %" PRIu32" byte region to %p\n", region->size,
      region->mem_base);
    ph_count++;
  }

  ctx->nr_regions = ph_count;
  ctx->entry_point = ehdr->e_entry;
  ctx->load_regions = realloc (
    ctx->load_regions, ph_count * sizeof (struct elf_load_region));

  if (ctx->load_regions == NULL)
    rvtrbk_fatal ("failed to realloc-downsize LOAD regions\n");

  if (!bss_start)
  {
    rvtrbk_debug (
      "Failed to find program break, no heap/stack will be allocated");
    return ctx;
  }
  else
  {
    rvtrbk_debug (
      "Program break at 0x08%" PRIx32 ", allocating 0x%" PRIx32 "/0x%" PRIx32
      " byte stack/heap\n", bss_start, PROG_STACK_SIZE, PROG_HEAP_SIZE);
  }

  auto heap = &ctx->load_regions[ph_count - 2];
  heap->size = PROG_HEAP_SIZE;
  heap->mem_base = calloc (1, heap->size);
  heap->vma_base = bss_start + bss_size;
  heap->tag = "HEAP";

  auto stack = &ctx->load_regions[ph_count - 1];
  stack->mem_base = calloc (1, PROG_STACK_SIZE);
  stack->size = PROG_STACK_SIZE;
  stack->vma_base = heap->vma_base + PROG_HEAP_SIZE;
  stack->tag = "STACK";
  ctx->bp = stack->vma_base;
  ctx->sp = stack->vma_base + stack->size - 1; 

  return ctx;
}

void
elf_free (elfctx_t ctx)
{
  free (ctx->load_regions);
  free (ctx);
}