#include "GameGrid.h"

GameGrid::GameGrid(Grid& grid){
    grid_width = grid.get_grid_width();
    this->grid = new unsigned*[grid_width];

    for (unsigned i = 0; i < grid_width; ++i){
        this->grid[i] = new unsigned[grid_width];
    }

    for (unsigned i = 0; i < grid_width; ++i){
        for (unsigned j = 0; j < grid_width; ++j){
            this->grid[i][j] = grid.get(i, j);
            
            if (this->grid[i][j] != 0){
                fixed_cells.insert(Coordinates(i, j));
            }
        }
    }
}

GameGrid::GameGrid(const GameGrid& other){
    grid_width = other.grid_width;

    grid = new unsigned*[grid_width];

    for (unsigned i = 0; i < grid_width; ++i){
        grid[i] = new unsigned[grid_width];
    }

    for (unsigned i = 0; i < grid_width; ++i){
        for (unsigned j = 0; j < grid_width; ++j){
            grid[i][j] = other.grid[i][j];
        }
    }

    for (auto iter = other.fixed_cells.begin(); iter != other.fixed_cells.end(); ++iter){
        fixed_cells.insert(*iter);
    }
}

GameGrid& GameGrid::operator=(const GameGrid& other){
    grid_width = other.grid_width;

    grid = new unsigned*[grid_width];

    for (unsigned i = 0; i < grid_width; ++i){
        grid[i] = new unsigned[grid_width];
    }

    for (unsigned i = 0; i < grid_width; ++i){
        for (unsigned j = 0; j < grid_width; ++j){
            grid[i][j] = other.grid[i][j];
        }
    }

    for (auto iter = other.fixed_cells.begin(); iter != other.fixed_cells.end(); ++iter){
        fixed_cells.insert(*iter);
    }

    return *this;
}

GameGrid::~GameGrid(){
    for (unsigned i = 0; i < grid_width; ++i){
        delete[] grid[i];
    }

    delete[] grid;
}

unsigned GameGrid::get_grid_width() const{
    return grid_width;
}

unsigned GameGrid::get(unsigned x, unsigned y) const{
    return grid[x][y];
}

unsigned GameGrid::get(const Coordinates& c) const{
    return grid[c.get_x()][c.get_y()];
}

std::set<Coordinates>& GameGrid::get_fixed_cells(){
    return fixed_cells;
}

std::set<unsigned>& GameGrid::get_available_vals(unsigned x, unsigned y) {
    return empty_set;
}

int GameGrid::set(const Coordinates& c, unsigned val){
    auto found = fixed_cells.find(c);

    if (found != fixed_cells.end())
        return -1;

    grid[c.get_x()][c.get_y()] = val;

    return 0;
}

int GameGrid::set(unsigned x, unsigned y, unsigned val){
    Coordinates c(x, y);

    return set(c, val);
}

int GameGrid::erase(const Coordinates& c){
    return set(c, 0);
}

int GameGrid::erase(unsigned x, unsigned y){
    return set(x, y, 0);
}
