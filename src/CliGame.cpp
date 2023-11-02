#include "CliView.h"
#include "Grid.h"
#include "Solver.h"
#include "PathGridInitializer.h"
#include "RandomGridInitializer.h"
#include "MainMenuState.h"
#include "FillRowSelectionState.h"
#include "FillColSelectionState.h"
#include "ValSelectionState.h"
#include "GameGrid.h"

int play(View* v, GameGrid& grid){
    GameState* state = new MainMenuState(v, grid);

    while (true){
        state = state->manage_user_input();
    }
}

int main(int argc, char* argv[]){
    unsigned block_width = 3;

    Grid grid(block_width);    
    CliView v(grid);
    grid.set_view(v);
    IGridInitializer* initializer = new RandomGridInitializer(&v);
    initializer->init(grid);
    GameGrid game_grid(grid);

    return play(&v, game_grid);
}