#include "GameState.h"

GameState::GameState(Grid& solution, GameGrid& grid) : solution(solution), grid(grid), grid_width(grid.get_grid_width())
{}