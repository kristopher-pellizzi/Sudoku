#include <vector>
#include "EraseColSelectionState.h"
#include "EraseRowSelectionState.h"
#include "MainMenuState.h"

EraseColSelectionState::EraseColSelectionState(View* v, GameGrid& grid, unsigned row_idx) : GameState(grid){
    this->v = v;
    this->current_menu = MenuType::COLSELECTION;
    this->row_idx = row_idx;
    this->col_idx = 0;
    this->val = 0;
}

void EraseColSelectionState::print_menu() const{
    std::stringstream sstream;

    sstream << "Row idx: " << row_idx << std::endl;
    sstream << "Insert a col index or 'q' to go back to row index selection:" << std::endl;

    v->draw(&grid);
    v->print(sstream.str());
}

GameState* EraseColSelectionState::go_back() const{
    return new EraseRowSelectionState(v, grid);
}

GameState* EraseColSelectionState::manage_user_input(){
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

        if (n < grid_width){
            input_ok = true;
            col_idx = n;
            std::stringstream sstream;
            if (grid.erase(row_idx, col_idx)){
                sstream << "Cannot erase fixed cell (" << row_idx << ", " << col_idx << ")";
            }
            else{
                sstream << "Erased cell (" << row_idx << ", " << col_idx << ")";
            }
            v->print(sstream.str());

            return new MainMenuState(v, grid);
        }
        else{
            std::stringstream sstream;
            sstream << "Please insert an index between 0 and " << grid_width - 1;
            v->print(sstream.str());
        }
    }

    return this;
}