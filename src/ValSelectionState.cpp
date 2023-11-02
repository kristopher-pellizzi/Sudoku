#include <vector>
#include "ValSelectionState.h"
#include "FillColSelectionState.h"
#include "MainMenuState.h"

ValSelectionState::ValSelectionState(View* v, Grid& solution, GameGrid& grid, unsigned row_idx, unsigned col_idx) : GameState(solution, grid){
    this->v = v;
    this->row_idx = row_idx;
    this->col_idx = col_idx;
    this->val = 0;
}

void ValSelectionState::print_menu() const{
    std::stringstream sstream;

    sstream << "Row idx: " << row_idx << std::endl;
    sstream << "Col idx: " << col_idx << std::endl;
    sstream << "Insert a value for the cell or 'q' to go back to column index selection:" << std::endl;

    v->draw(&grid);
    v->print(sstream.str());
}

GameState* ValSelectionState::go_back() const{
    return new FillColSelectionState(v, solution, grid, row_idx);
}

GameState* ValSelectionState::manage_user_input(){
    auto max_size = std::numeric_limits<std::streamsize>::max();
    unsigned n = 0;

    std::istream& istream = v->get_input_stream();
    bool input_ok = false;

    while (!input_ok){
        print_menu();

        if (istream.peek() == '\n')
            continue;

        if (istream.peek() == 'q'){
            istream.get();
            if (istream.get() == '\n'){
                input_ok = true;
                return go_back();
            }
        }

        istream >> n;

        if (!input_ok && (istream.peek() != '\n' || istream.fail())){
            istream.clear();
            istream.ignore(max_size, '\n');
            v->print("Please insert a valid index or 'q' to go to main menu\n");
            continue;
        }

        istream.ignore(max_size, '\n');

        if (n > 0 && n <= grid_width){
            input_ok = true;
            val = n;
            std::stringstream sstream;
            if (grid.set(row_idx, col_idx, val)){
                sstream << "Cannot set value for fixed cell (" << row_idx << ", " << col_idx << ")";
            }
            else{
                sstream << "Inserted value " << val << " into cell (" << row_idx << ", " << col_idx << ")";
            }
            v->print(sstream.str());
            

            return new MainMenuState(v, solution, grid);
        }
        else{
            std::stringstream sstream;
            sstream << "Please insert a value between 1 and " << grid_width;
            v->print(sstream.str());
        }
    }

    return this;
}