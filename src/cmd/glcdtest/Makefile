#
# Public Domain.  1995/03/13 - Steven Schultz
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

CFLAGS		+= -Werror -I../../../sys/include

SRCS            = glcdtest.c
OBJS            = glcdtest.o

all:            glcdtest

glcdtest:    ${OBJS}
		${LD} ${LDFLAGS} -o glcdtest.elf ${OBJS} ${LIBS}
		${OBJDUMP} -S glcdtest.elf > glcdtest.dis
		${SIZE} glcdtest.elf
		${ELF2AOUT} glcdtest.elf $@

.SUFFIXES:      .0 .1

clean:
		rm -f *.o *.elf *.elf *.dis tags *~ glcdtest

depend:         ${SRCS}
		mkdep ${CFLAGS} ${SRCS}

install:        all
		install -m 755 glcdtest ${DESTDIR}/bin

lint:           ${SRCS}
		lint -hax ${SRCS}

tags:           ${SRCS}
		ctags ${SRCS}
