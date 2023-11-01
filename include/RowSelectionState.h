#ifndef ROWSELECTIONSTATE
#define ROWSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class RowSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        RowSelectionState(View* v);

        GameState* manage_user_input();
};

#endif // ROWSELECTIONSTATE