#include <vector>
#include "RowSelectionState.h"
#include "ColSelectionState.h"
#include "MainMenuState.h"

RowSelectionState::RowSelectionState(View* v){
    this->v = v;
    this->current_menu = MenuType::ROWSELECTION;
    this->row_idx = 0;
    this->col_idx = 0;
    this->val = 0;
}

void RowSelectionState::print_menu() const{
    std::stringstream sstream;

    sstream << "Insert a row index or 'q' to go back to main menu:" << std::endl;

    v->draw();
    v->print(sstream.str());
}

GameState* RowSelectionState::go_back() const{
    return new MainMenuState(v);
}

GameState* RowSelectionState::manage_user_input(){
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
            row_idx = n;
            return new ColSelectionState(v, row_idx);
        }
    }

    return this;
}