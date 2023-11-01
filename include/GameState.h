#ifndef GAMESTATE
#define GAMESTATE

#include <sstream>
#include "MenuType.h"
#include "View.h"

class GameState{
    protected:
        View* v;
        unsigned grid_width;
        MenuType current_menu;
        unsigned row_idx;
        unsigned col_idx;
        unsigned val;


        virtual void print_menu() const = 0;
        virtual GameState* go_back() const = 0;

    public:
        virtual GameState* manage_user_input() = 0;
};

#endif // GAMESTATE