#include <vector>
#include "MainMenuState.h"
#include "RowSelectionState.h"

MainMenuState::MainMenuState(View* v){
    this->v = v;
    this->current_menu = MenuType::MAINMENU;
    this->row_idx = 0;
    this->col_idx = 0;
    this->val = 0;
}

void MainMenuState::print_menu() const{
    std::vector<string> choices {
        "Fill Cell",
        "Submit Grid",
        "Exit"
    };

    std::stringstream sstream;

    sstream << "Select a choice:" << std::endl;
    for (unsigned i = 0; i < choices.size(); ++i){
        sstream << i + 1 << ") " << choices[i] << std::endl;
    }

    v->draw();
    v->print(sstream.str());
}

GameState* MainMenuState::go_back() const{
    v->print("Goodbye\n");
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
                return new RowSelectionState(v);
            case 2:
                v->print("Submission not yet implemented\n");
                break;
            case 3:
                return go_back();
                break;
            default:
                input_ok = false;
        }
    }

    return this;
}