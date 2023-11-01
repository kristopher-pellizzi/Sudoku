#ifndef COLSELECTIONSTATE
#define COLSELECTIONSTATE

#include "GameState.h"
#include "View.h"

class ColSelectionState : public GameState{
    protected:
        void print_menu() const;
        GameState* go_back() const;

    public:
        ColSelectionState(View* v, unsigned row_idx);

        GameState* manage_user_input();
};

#endif // COLSELECTIONSTATE