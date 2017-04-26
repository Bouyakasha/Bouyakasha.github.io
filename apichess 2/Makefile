# Simple Makefile

# Vars
CC= gcc 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Werror -Wall -Wextra -std=c99 -O0 -g3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL -lSDL_image -lSDL_ttf

SRC= main.c chessBoard.c pieces.c arbitrator.c moveRules.c tree_and_values.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END of Makefile

