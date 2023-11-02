#ifndef GAMESTATE
#define GAMESTATE

#include <sstream>
#include "MenuType.h"
#include "View.h"
#include "GameGrid.h"

class GameState{
    protected:
        View* v;
        Grid& solution;
        GameGrid& grid;
        unsigned grid_width;
        unsigned row_idx;
        unsigned col_idx;
        unsigned val;


        virtual void print_menu() const = 0;
        virtual GameState* go_back() const = 0;

    public:
        GameState(Grid& solution, GameGrid& grid);

        virtual GameState* manage_user_input() = 0;
};

#endif // GAMESTATE