#ifndef MAINMENUSTATE
#define MAINMENUSTATE

#include "GameState.h"
#include "View.h"

class MainMenuState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;
        void submit() const;

    public:
        MainMenuState(View* v, Grid& solution, GameGrid& grid);

        GameState* manage_user_input();
};

#endif // MAINMENUSTATE