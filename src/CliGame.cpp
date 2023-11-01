#include "CliView.h"
#include "Grid.h"
#include "Solver.h"
#include "PathGridInitializer.h"
#include "RandomGridInitializer.h"
#include "MainMenuState.h"
#include "RowSelectionState.h"
#include "ColSelectionState.h"
#include "ValSelectionState.h"

int play(View* v){
    GameState* state = new MainMenuState(v);

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
    v.draw();

    return play(&v);
}