#include "ArgumentParser.h"
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

using AP::ArgumentParser;
using AP::ArgumentsMap;

ArgumentsMap parse_args(int argc, char* argv[]){
    ArgumentParser parser(argc, argv);

    parser.add_argument(
        NamedArgument<string>("name", "--grid-path"),
        NamedArgument<string>("abbreviation", "-p"),
        NamedArgument<string>("help_string", "Path of a text file describing the initial state of the Sudoku grid (see files in folder \"grids\" for reference). If a path is not provided, a random grid will be generated"),
        NamedArgument<string>("dest", "path"),
        NamedArgument<string*>("default_val", new string(""))
    );

    return parser.parse_args();
}

int play(View* v, Grid& solution, GameGrid& grid){
    GameState* state = new MainMenuState(v, solution, grid);

    while (true){
        state = state->manage_user_input();
    }
}

int main(int argc, char* argv[]){
    ArgumentsMap args = parse_args(argc, argv);
    unsigned block_width = 3;
    string grid_path;

    args["path"]->get_value(&grid_path);

    Grid grid(block_width);    
    CliView v(grid);
    grid.set_view(v);
    
    IGridInitializer* initializer;
    if (grid_path != "")
        initializer = new PathGridInitializer(grid_path, &v);
    else   
        initializer = new RandomGridInitializer(&v);

    initializer->init(grid);
    GameGrid game_grid(grid);
    Solver solver(grid, v, true);
    solver.solve();

    return play(&v, grid, game_grid);
}