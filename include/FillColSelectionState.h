#ifndef FILLCOLSELECTIONSTATE
#define FILLCOLSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class FillColSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        FillColSelectionState(View* v, Grid& solution, GameGrid& grid, unsigned row_idx);

        GameState* manage_user_input();
};

#endif // FILLCOLSELECTIONSTATE