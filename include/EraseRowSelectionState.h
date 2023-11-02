#ifndef ERASEROWSELECTIONSTATE
#define ERASEROWSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class EraseRowSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        EraseRowSelectionState(View* v, GameGrid& grid);

        GameState* manage_user_input();
};

#endif // ERASEROWSELECTIONSTATE