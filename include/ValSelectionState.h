#ifndef VALSELECTIONSTATE
#define VALSELECTIONSTATE

#include "GameState.h"
#include "View.h"


class ValSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        ValSelectionState(View* v, unsigned row_idx, unsigned col_idx);

        GameState* manage_user_input();
};

#endif // VALSELECTIONSTATE