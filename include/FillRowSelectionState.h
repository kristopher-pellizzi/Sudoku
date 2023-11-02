#ifndef FILLROWSELECTIONSTATE
#define FILLROWSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class FillRowSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        FillRowSelectionState(View* v, GameGrid& grid);

        GameState* manage_user_input();
};

#endif // FILLROWSELECTIONSTATE