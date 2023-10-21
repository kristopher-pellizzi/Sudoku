#include "CliView.h"
#include "Grid.h"
#include "Solver.h"
#include "PathGridInitializer.h"

int play(){
    return 0;
}

int main(int argc, char* argv[]){
    string grid_path("./SudokuSolver/Grids/beginner1.txt");
    unsigned block_width = 3;

    Grid grid(block_width);    
    CliView v(grid);
    grid.set_view(v);
    GridInitializer* initializer = new PathGridInitializer(grid_path, &v);
    initializer->init(grid);
    v.draw();

    return play();
}