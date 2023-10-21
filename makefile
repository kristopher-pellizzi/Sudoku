ROOT_DIR := $(shell dirname '$(realpath $(firstword $(MAKEFILE_LIST)))')
SRC_DIR := $(ROOT_DIR)/src/
OBJ_DIR := $(ROOT_DIR)/obj/
BIN_DIR := $(ROOT_DIR)/bin/
SOLVER_OBJ_DIR := $(ROOT_DIR)/SudokuSolver/obj/
MKDIR := @mkdir -p 
CXX := g++
COMP_FLAGS := -std=c++17 -Wall -Werror -Iinclude -ISudokuSolver/include -c $(ADD_COMP_FLAGS)

.PHONY: all
all: $(BIN_DIR)game

.PHONY: clean
clean:
	-rm -r obj
	-rm -r bin
	$(MAKE) -C SudokuSolver clean

.PHONY: test
test:
	@echo ROOT_DIR: $(ROOT_DIR)
	@echo SRC_DIR: $(SRC_DIR)
	@echo OBJ_DIR: $(OBJ_DIR)

$(OBJ_DIR): 
	$(MKDIR) $@
	@echo "Created folder $@"

$(BIN_DIR): 
	$(MKDIR) $@
	@echo "Created folder $@"

$(ROOT_DIR)/SudokuSolver/CppArgumentParser/lib/libArgumentParser.so: argparse
	@echo 
.PHONY: argparse
argparse:
	$(MAKE) -C $(ROOT_DIR)/SudokuSolver/CppArgumentParser

# NOTE: it is REQUIRED to put something in this recipe, otherwise the prerequisite is not always consedered newer than target
# if anything changes in the SudokuSolver submodule
$(ROOT_DIR)/SudokuSolver/solver: solver
	@echo 

.PHONY: solver
solver:
	$(MAKE) -C $(ROOT_DIR)/SudokuSolver

$(OBJ_DIR)CliGame.o: $(SRC_DIR)CliGame.cpp $(ROOT_DIR)/SudokuSolver/solver $(ROOT_DIR)/SudokuSolver/CppArgumentParser/lib/libArgumentParser.so | $(OBJ_DIR)
	$(CXX) $(COMP_FLAGS) -I$(ROOT_DIR)/SudokuSolver/CppArgumentParser/include $< -o $@

$(BIN_DIR)game: $(OBJ_DIR)CliGame.o $(SOLVER_OBJ_DIR)Checkpoint.o $(SOLVER_OBJ_DIR)LockedCandidateIndex.o $(SOLVER_OBJ_DIR)Solver.o $(SOLVER_OBJ_DIR)Grid.o $(SOLVER_OBJ_DIR)PathGridInitializer.o $(SOLVER_OBJ_DIR)RandomGridInitializer.o $(SOLVER_OBJ_DIR)RandomNumberGenerator.o $(SOLVER_OBJ_DIR)View.o $(SOLVER_OBJ_DIR)CliView.o $(SOLVER_OBJ_DIR)Cell.o $(SOLVER_OBJ_DIR)Coordinates.o | $(BIN_DIR)
	$(CXX) -L$(ROOT_DIR)/SudokuSolver/CppArgumentParser/lib -lArgumentParser $^ -o $@