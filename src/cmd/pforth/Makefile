# makefile for pForth
# Portable Forth written in 'C'
# by Phil Burk
# For more info visit http://www.softsynth.com/pforth/
#
# Use 'make all' to build standalone pForth executable.
# PForth can be built in several stages using these targets:
# - pfdicapp = executable pForth with minimal dictionary. All from 'C'.
# - pfdicdat = image of full dictionary build by compiling Forth code.
# - pforthapp = executable with embedded dictionary image. DEFAULT 'all' target.
#
# The file 'pfdicdat.h' is generated by pForth. It contains a binary image of the Forth dictionary.
# It allows pForth to work as a standalone image that does not need to load a dictionary file.

TOPSRC		= $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk
#include $(TOPSRC)/cross.mk

# Options include: PF_SUPPORT_FP PF_NO_MALLOC PF_NO_INIT PF_DEBUG
# See "docs/pf_ref.htm" file for more info.

CFLAGS		+= -Wall -Os
#CFLAGS		+= -DPF_SUPPORT_FP
CFLAGS          += -DPF_STATIC_DIC
LIBS            += -lm

OBJS            = pf_cglue.o pf_clib.o pf_core.o pf_inner.o \
                  pf_io.o pf_io_none.o pf_main.o pf_mem.o pf_save.o \
                  pf_text.o pf_words.o pfcompil.o pfcustom.o
#OBJS            += pf_io_posix.o
OBJS            += pf_io_stdio.o

all:            ../pforth ../../lib/pforth.dic

../pforth:      ${OBJS}
		${LD} ${LDFLAGS} -o pforth.elf ${OBJS} ${LIBS}
		${OBJDUMP} -S pforth.elf > pforth.dis
		${SIZE} pforth.elf
		${ELF2AOUT} pforth.elf $@

pfdicdat.h pforth.dic:
		(cd fth; ../pforth.elf -i system.fth)
		mv fth/pforth.dic pforth.dic
		mv fth/pfdicdat.h $@

../../lib/pforth.dic: pforth.dic
		cp -p $< $@

clean:
		rm -f *.o ${MAN} ../id ../groups ../whoami *.elf *.dis tags *~
