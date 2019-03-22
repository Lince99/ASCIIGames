#Lince99

CC=gcc
RM=rm -f

# name of the source (include folders if the source isn't in the current dir)
SRC=Game_of_cells.c
#other libraries
LDFLAGS=-lncurses
# name of the executable
EXC=Game_of_cells
# params used in the program
PARAMS=
# compile params like optimization or other platform targeting
C_PAR=-Os -Wall -fdiagnostics-color=auto
# - - - warnings - - -
#-Wextra -Wall

C_INFO=-fdiagnostics-color=auto
# - - - infoes - - -
#-ftime-report
#-fopt-info
#-fdump-statistics -fstack-usage ( -fstats for C++)
#-aux-info signatures.txt
#-fdiagnostics-color=auto
#-fdiagnostics-parseable-fixits -fdiagnostics-generate-patch

C_OPT=-faggressive-loop-optimizations -fcombine-stack-adjustments
C_OPT+= -fexpensive-optimizations -falign-functions -falign-jumps
C_OPT+= -falign-labels -falign-loops -floop-nest-optimize
C_OPT+= -foptimize-strlen -ftree-loop-optimize
# - - - optimizations - - -
#-Os
#-fpredictive-commoning
#-faggressive-loop-optimizations -fcombine-stack-adjustments -fexpensive-optimizations
#-falign-functions -falign-jumps -falign-labels -falign-loops
#-fconserve-stack
#-floop-nest-optimize -foptimize-strlen -ftree-loop-optimize

C_FOLD_OPT=-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference
C_FOLD_OPT+= -fipa-pta -foptimize-sibling-calls -freorder-blocks
C_FOLD_OPT+= -freorder-functions
# - - - folding optimizations - - -
#-fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-reference -fipa-pta
#-foptimize-sibling-calls -freorder-blocks -freorder-functions


all: clean_reset compile

all_opt: clean_reset compile_optimize run_less

help:
	@echo "\nUse make [option]:\n"
	@echo "help \n\tshow this help"
	@echo "compile \n\tcompile from the source and strip it"
	@echo "compile_info \n\tcompile and show compilation/linking stuffs"
	@echo "compile_optimize \n\tcompile and try to use built-in optimizers"

compile:
	@$(CC) -o $(EXC) $(SRC)
	@strip $(EXC)

compile_info:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_INFO)
	@strip $(EXC)

compile_optimize:
	@$(CC) -o $(EXC) $(SRC) $(C_PAR) $(C_OPT) $(C_FOLD_OPT)
	@strip $(EXC)

cron_time:
	@time -p $(CC) -o $(EXC) $(SRC) $(C_PAR)
	@time -p ./$(EXC) $(PARAMS)

debug:
	@gdb $(EXC)

clean:
	@$(RM) $(EXC)

clean_reset:
	@$(RM) $(EXC)
	@reset && clear

run:
	@./$(EXC) $(PARAMS)

run_less:
	@./$(EXC) $(PARAMS) | less -Cqrs
