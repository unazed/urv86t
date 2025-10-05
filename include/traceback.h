#pragma once

#include <inttypes.h>
#include <stdio.h>

#include "emu.h"

#ifdef DEBUG
# define rvtrbk_debug(fmt, ...) printf ("d: "fmt,##__VA_ARGS__)
#else
# define rvtrbk_debug(fmt, ...)
#endif

#define rvtrbk_error(fmt, ...) fprintf (stderr, "e: "fmt,##__VA_ARGS__)

__attribute__ (( noreturn ))
void rvtrbk_fatal (const char* const msg);

void rvtrbk_diagn (rvstate_t state, const char* const msg);
void rvtrbk_print_dump (rvstate_t state);