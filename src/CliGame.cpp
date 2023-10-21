#include "CliView.h"
#include "Grid.h"
#include "Solver.h"
#include "PathGridInitializer.h"
#include "RandomGridInitializer.h"

int play(){
    return 0;
}

int main(int argc, char* argv[]){
    unsigned block_width = 3;

    Grid grid(block_width);    
    CliView v(grid);
    grid.set_view(v);
    IGridInitializer* initializer = new RandomGridInitializer(&v);
    initializer->init(grid);
    v.draw();

    return play();
}