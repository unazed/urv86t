# The Ultimate RV-x86 Transpiler

## Overview

Work in progress RISC-V emulator and (soon to support) transpiler, with goals to support the basic ISA extensions (multiplication/division, single/double-precision floating point, and CSRs,) alongside supporting the Linux syscall ABI.

## Installation

Using a simple `Makefile` build-system with no necessary prerequisites outside of a relatively recent version of GCC, and optionally the RISC-V cross-compilation suite to build applications for testing. Running `make` with no parameters will produce the release binary in `build/`

## Usage

`./urv86t [-t <output>] <path-to-file>`, `-t` toggles transpilation mode (not yet functional,) and otherwise begins emulation of the file provided.

## Configuration

Compilation flags to toggle certain features and extensions are listed under `include/feature.h`, a further `-DDEBUG` build flag in the `Makefile` can be toggled to provide further traceback information at the cost of significantly deteriorated performance.