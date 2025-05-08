# name of the program (Minix service)
PROG=proj

# source code files to be compiled

VPATH = drivers

SRCS = game.c graphics.c keyboard.c timer.c utils.c mouse.c kbc.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
