#Lince99

CC=gcc
RM=rm -f

# name of the source (include folders if the source isn't in the current dir)
SRC=gameofcells.c
# name of the executable
EXC=releases/gameofcells
# params used in the program
PARAMS=
# compile params like optimization or other platform targeting
C_PAR=-Os -Wall

C_INFO=-fdiagnostics-color=auto

C_OPT=-faggressive-loop-optimizations -fcombine-stack-adjustments
C_OPT+= -fexpensive-optimizations -falign-functions -falign-jumps
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize

C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions



all: clean_reset compile run

all_opt: clean_reset compile_optimize run_less

help:
	@echo "\nUse make [option]:\n"
	@echo "help \n\tshow this help"
	@echo "compile \n\tcompile from the source and strip it"
	@echo "compile_info \n\tcompile and show compilation/linking stuffs"
	@echo "compile_optimize \n\tcompile and try to use built-in optimizers"
	@echo "cron_time \n\trun the program under time to cronometrate it"
	@echo "clean \n\tremove executable"
	@echo "clean_reset \n\tremove executable and clear terminal"
	@echo "run \n\trun the program"
	@echo "run \n\trun the program under less for a better visualization"

compile:
	@$(CC) -o $(EXC) $(SRC) -lncurses
	@strip $(EXC)

compile_info:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_INFO) -lncurses
	@strip $(EXC)

compile_optimize:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT) -lncurses
	@strip $(EXC)

cron_time:
	@time -p $(CC) -o $(EXC) $(SRC) $(C_PAR) -lncurses
	@time -p ./$(EXC) $(PARAMS)

clean:
	@$(RM) $(EXC)

clean_reset:
	@$(RM) $(EXC)
	@reset && clear

run:
	@./$(EXC) $(PARAMS)

run_less:
	@./$(EXC) $(PARAMS) | less -Cqrs
