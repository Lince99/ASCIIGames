#Copyright (c) 2019 Lince99 under MIT license

CC=gcc -Wall -Os -O3
CC+= -faggressive-loop-optimizations -fcombine-stack-adjustments
CC+= -fexpensive-optimizations -falign-functions -falign-jumps
CC+= -falign-labels -falign-loops -floop-nest-optimize
CC+= -foptimize-strlen -ftree-loop-optimize

CC+= -fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
CC+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
CC+= -freorder-functions

# name of the source (include folders if the source isn't in the current dir)
SRC=askli_art.c
# name of the executable
EXC=askliart

all: clean_screen compile run clean

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

clean:
	@rm $(EXC)

clean_screen:
	@reset && clear

run:
	@./$(EXC)
