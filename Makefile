CC = gcc
OBJCOPY = objcopy

COMMON_CFLAGS = -Wall -Werror -Wextra -Os -Iinclude/ -ggdb 

CFG_DEFS := $(foreach cfg,$(filter CFG_%,$(.VARIABLES)),-D$(cfg))

CFLAGS ?= $(COMMON_CFLAGS) $(CFG_DEFS) -DENABLE_RV32I -DDEBUG

OBJ = $(SOURCES:src/%.c=build/%.o)
SOURCES = $(wildcard src/*.c)

all: build/urv86t

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/urv86t: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

-include $(OBJ:.o=.d)