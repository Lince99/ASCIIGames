#Basso Nicola
#aka Lince99

CC=gcc
RM=rm -f

#name of the source (include folders if the source isn't in the current dir)
SRC=style_checker.c
#add params after the name of the executable
EXC=style_checker

all: compile run

help:
	@echo "\n- - use make [option]: - -\n"
	@echo "\thelp \n\t\tshow this help"
	@echo "\tcompile \n\t\tcompile from the source and strip it"
	@echo "\tclean \n\t\tremove the executable file and reset the terminal"
	@echo "\trun \n\t\trun the program (if already compiled)\n"

compile:
	@echo " - - Compiling... - -"
	$(CC) -o $(EXC) $(SRC)
	@strip $(EXC)
	@echo " - - Memory occupied by this program: - -"
	@size $(EXC)

clean:
	@echo " - - Cleaning all files... - -"
	@clear
	$(RM) $(EXC)

run:
	@find $(EXC)
	@./$(EXC)
