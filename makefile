ROOT_DIR := $(shell dirname '$(realpath $(firstword $(MAKEFILE_LIST)))')
SRC_DIR := $(ROOT_DIR)/src/
OBJ_DIR := $(ROOT_DIR)/obj/
BIN_DIR := $(ROOT_DIR)/bin/
MKDIR := @mkdir -p 
CXX := g++
COMP_FLAGS := -std=c++17 -Wall -Werror -Iinclude -c $(ADD_COMP_FLAGS)

.PHONY: all
all: game

.PHONY: clean
clean:
	-rm -r obj
	$(MAKE) -C CppArgumentParser clean

.PHONY: test
test:
	@echo ROOT_DIR: $(ROOT_DIR)
	@echo SRC_DIR: $(SRC_DIR)
	@echo OBJ_DIR: $(OBJ_DIR)

$(OBJ_DIR): 
	$(MKDIR) $@
	@echo "Created folder $@"

$(OBJ_DIR)CliMain.o: $(SRC_DIR)CliMain.cpp $(ROOT_DIR)/CppArgumentParser/lib/libArgumentParser.so | $(OBJ_DIR)
	$(CXX) $(COMP_FLAGS) -I$(ROOT_DIR)/CppArgumentParser/include $< -o $@

$(ROOT_DIR)/SudokuSolver/solver:
	$(MAKE) -C SudokuSolver

.PHONY: solver
solver: $(ROOT_DIR)/SudokuSolver/solver


game: $(OBJ_DIR)CliView.o $(OBJ_DIR)Grid.o $(OBJ_DIR)View.o $(OBJ_DIR)CliTest.o $(OBJ_DIR)Cell.o $(OBJ_DIR)Coordinates.o $(ROOT_DIR)/SudokuSolver/solver
	$(CXX) -L$(ROOT_DIR)/CppArgumentParser/lib -lArgumentParser $^ -o $@