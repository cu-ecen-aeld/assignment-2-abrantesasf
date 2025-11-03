# Simple Makefile for assignment 2
# By: Abrantes Araújo Silva Filho

# Define CROSS_COMPILE to gcc, if not defined.
# NOTE: we expect that CROSS_COMPILE have a trailing hifem, like:
#                 "aarch64-none-linux-gnu-"
#
# This variable could be passed to make through 2 ways:
#    1) make CROSSS_COMPILE=aarch64-none-linux-gnu- all
#    2) export CROSSS_COMPILE=aarch64-none-linux-gnu-; make all
CROSS_COMPILE ?= gcc

# If CROSS_COMPILE is not gcc, we are using the cross-compiler
ifneq ($(CROSS_COMPILE), gcc)
    CC := $(CROSS_COMPILE)gcc
else
    CC := gcc
endif

# Other configurations:
CSTD ?= c11
CFLAGS := -std=$(CSTD) -Wall -Wpedantic -Wextra -Werror -Wconversion \
          -Wunused-result
LDFLAGS :=
LIBS :=

.PHONY: all clean

all: writer

writer: writer.c
	$(CC) $(CFLAGS) -o writer writer.c $(LDFLAGS) $(LIBS)

clean:
	rm -f writer.o
	rm -f writer
	rm -f writer*~
	rm -f Makefile~
