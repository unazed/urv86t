#pragma once

#include "types.h"

#define EI_NIDENT (16)

#define EI_MAG0 (0x7f)
#define EI_MAG1 ('E')
#define EI_MAG2 ('L')
#define EI_MAG3 ('F')
#define EI_ELFCLASSNONE (0)
#define EI_ELFCLASS32   (1)
#define EI_ELFCLASS64   (2)
#define EI_ELFDATANONE (0)
#define EI_ELFDATA2LSB (1)
#define EI_ELFDATA2MSB (2)
#define EI_EV_NONE    (0)
#define EI_EV_CURRENT (1)

#define ET_NONE   (0)
#define ET_REL    (1)
#define ET_EXEC   (2)
#define ET_DYN    (3)
#define ET_CORE   (4)
#define ET_LOPROC (0xff00)
#define ET_HIPROC (0xffff)

#define EM_M32          (1)
#define EM_SPARC        (2)
#define EM_386          (3)
#define EM_68K          (4)
#define EM_88K          (5)
#define EM_860          (7)
#define EM_MIPS         (8)
#define EM_MIPS_RS4_BE  (10)
#define EM_RISCV        (243)

#define PT_NULL             (0)
#define PT_LOAD             (1)
#define PT_DYNAMIC          (2)
#define PT_INTERP           (3)
#define PT_NOTE             (4)
#define PT_SHLIB            (5)
#define PT_PHDR             (6)
#define PT_LOPROC           (0x70000000)
#define PT_HIPROC           (0x7fffffff)
#define PT_RISCV_ATTRIBUTES (0x70000003)
#define PT_GNU_EH_FRAME	    (0x6474e550)
#define PT_GNU_STACK	      (0x6474e551)
#define PT_GNU_RELRO	      (0x6474e552)

#define PROG_STACK_SIZE (1024 * 1024)
#define PROG_HEAP_SIZE  (1024 * 1024)

typedef u32 Elf32_Addr;
typedef u16 Elf32_Half;
typedef u32 Elf32_Off;
typedef i32 Elf32_Sword;
typedef u32 Elf32_Word;

typedef struct
{
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
 } Elf32_Ehdr;

typedef struct
{
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_Shdr;

typedef struct
{
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_Phdr;

struct elf_load_region
{
  u32 vma_base;
  u8* mem_base;
  u32 size;
  const char* tag;
};

typedef struct elf_context
{
  struct elf_load_region* load_regions;
  size_t nr_regions;
  u32 entrypoint;
  u32 bp, sp;
} *elfctx_t;

elfctx_t elf_init (u8* const bytes, size_t length);
u8* elf_vma_to_mem (elfctx_t ctx, u32 ptr);
u32 elf_mem_to_vma (elfctx_t ctx, u8* ptr);
void elf_free (elfctx_t ctx);