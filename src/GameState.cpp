#include "GameState.h"

GameState::GameState(GameGrid& grid) : grid(grid), grid_width(grid.get_grid_width())
{}