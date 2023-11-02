#include <vector>
#include "MainMenuState.h"
#include "FillRowSelectionState.h"
#include "EraseRowSelectionState.h"

MainMenuState::MainMenuState(View* v, Grid& solution, GameGrid& grid) : GameState(solution, grid){
    this->v = v;
    this->row_idx = 0;
    this->col_idx = 0;
    this->val = 0;
}

void MainMenuState::print_menu() const{
    std::vector<string> choices {
        "Fill Cell",
        "Erase Cell",
        "Submit Grid",
        "Exit"
    };

    std::stringstream sstream;

    sstream << "Select a choice:" << std::endl;
    for (unsigned i = 0; i < choices.size(); ++i){
        sstream << i + 1 << ") " << choices[i] << std::endl;
    }

    v->draw(&grid);
    v->print(sstream.str());
}

GameState* MainMenuState::go_back() const{
    v->print("Goodbye\n");
    exit(0);
}

void MainMenuState::submit() const{
    for (unsigned i = 0; i < grid_width; ++i){
        for (unsigned j = 0; j < grid_width; ++j){
            if (grid.get(i, j) == 0){
                v->print("Grid is not completely filled yet. You can't submit an incomplete grid.");
                return;
            }
        }
    }

    for (unsigned i = 0; i < grid_width; ++i){
        for (unsigned j = 0; j < grid_width; ++j){
            if(grid.get(i, j) != solution.get(i, j)){
                v->print("Something's wrong. Check your grid and try again");
                return;
            }

        }
    }

    v->print("You successfully completed the Sudoku grid!");
    v->print("Congratulations!!!");
    exit(0);
}

GameState* MainMenuState::manage_user_input(){
    auto max_size = std::numeric_limits<std::streamsize>::max();
    unsigned n = 0;

    std::istream& istream = v->get_input_stream();
    bool input_ok = false;

    while (!input_ok){
        print_menu();

        if (istream.peek() == '\n'){
            istream.get();
            continue;
        }

        istream >> n;

        if (istream.peek() != '\n' || istream.fail()){
            istream.clear();
            istream.ignore(max_size, '\n');
            v->print("Please insert a valid selection\n");
            continue;
        }

        istream.ignore(max_size, '\n');
        input_ok = true;
        
        switch (n){
            case 1:
                return new FillRowSelectionState(v, solution, grid);
            case 2:
                return new EraseRowSelectionState(v, solution, grid);
            case 3:
                submit();
                break;
            case 4:
                return go_back();
                break;
            default:
                input_ok = false;
        }
    }

    return this;
}