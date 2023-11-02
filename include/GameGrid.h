#ifndef GAMEGRID
#define GAMEGRID

#include <set>
#include "Grid.h"
#include "IGrid.h"

class GameGrid : public IGrid{
    private:
        unsigned** grid;
        unsigned grid_width;
        std::set<unsigned> empty_set;
        std::set<Coordinates> fixed_cells;

    public:
        GameGrid(Grid& grid);
        GameGrid(const GameGrid& other);
        GameGrid& operator=(const GameGrid& other);

        ~GameGrid();

        unsigned get_grid_width() const;
        unsigned get(unsigned x, unsigned y) const;
        unsigned get(const Coordinates& c) const;
        std::set<Coordinates>& get_fixed_cells();
        std::set<unsigned>& get_available_vals(unsigned x, unsigned y);
        int set(unsigned x, unsigned y, unsigned val);
        int set(const Coordinates& c, unsigned val);
        int erase(unsigned x, unsigned y);
        int erase(const Coordinates& c);
};

#endif // GAMEGRID