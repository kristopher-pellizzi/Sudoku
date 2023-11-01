#include <vector>
#include "ColSelectionState.h"
#include "RowSelectionState.h"
#include "ValSelectionState.h"

ColSelectionState::ColSelectionState(View* v, unsigned row_idx){
    this->v = v;
    this->current_menu = MenuType::COLSELECTION;
    this->row_idx = row_idx;
    this->col_idx = 0;
    this->val = 0;
}

void ColSelectionState::print_menu() const{
    std::stringstream sstream;

    sstream << "Row idx: " << row_idx << std::endl;
    sstream << "Insert a col index or 'q' to go back to row index selection:" << std::endl;

    v->draw();
    v->print(sstream.str());
}

GameState* ColSelectionState::go_back() const{
    return new RowSelectionState(v);
}

GameState* ColSelectionState::manage_user_input(){
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
            return new ValSelectionState(v, row_idx, col_idx);
        }
    }

    return this;
}