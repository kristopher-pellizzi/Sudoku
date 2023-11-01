#ifndef MAINMENUSTATE
#define MAINMENUSTATE

#include "GameState.h"
#include "View.h"

class MainMenuState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        MainMenuState(View* v);

        GameState* manage_user_input();
};

#endif // MAINMENUSTATE