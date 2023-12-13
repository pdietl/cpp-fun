CURRENT_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

METALANG99_INC_PATH := $(CURRENT_DIR)metalang99/include

CPPFLAGS := -ftrack-macro-expansion=0 -I$(METALANG99_INC_PATH)
CFLAGS   := -Wall -Wextra -O2
CC       := gcc
SHELL    := bash

.PHONY: all
all: main main.i

main: main.c

# Inspect main.i to see macro expansion.
main.i: main.c
	$(CC) $(CPPFLAGS) -P -E $< -o $@

.PHONY: preproc
preproc: main.i
	@printf '\nPreprocessor output:\n\n' && cat $<

.PHONY: run
run: main
	./$<

.PHONY: clean
clean:
	$(RM) main *.o *.i
