#ifndef ERASECOLSELECTIONSTATE
#define ERASECOLSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class EraseColSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        EraseColSelectionState(View* v, Grid& solution, GameGrid& grid, unsigned row_idx);

        GameState* manage_user_input();
};

#endif // ERASECOLSELECTIONSTATE