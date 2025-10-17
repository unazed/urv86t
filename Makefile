CC = gcc
OBJCOPY = objcopy

COMMON_CFLAGS = -Wall -Werror -Wextra -Iinclude/ -I/usr/include/ -ggdb \
								-Wno-error=switch -Wno-error=strict-aliasing -std=gnu23 -O0

CFG_DEFS := $(foreach cfg,$(filter CFG_%,$(.VARIABLES)),-D$(cfg))
LDFLAGS = -largp -lm

CFLAGS ?= $(COMMON_CFLAGS) $(CFG_DEFS)

OBJ = $(SOURCES:src/%.c=build/%.o)
SOURCES = $(wildcard src/*.c) $(wildcard src/insn/*.c) \
					$(wildcard src/asm/*.c) $(wildcard src/ext/*.c)

all: build/urv86t

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/urv86t: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

-include $(OBJ:.o=.d)