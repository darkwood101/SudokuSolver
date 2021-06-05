#ifndef CELL_HH
#define CELL_HH

class Column;

struct Cell {
    Cell* up_;
    Cell* down_;
    Cell* right_;
    Cell* left_;
    Column* column_;

    inline Cell();
};

inline Cell::Cell() : up_(nullptr),
                      down_(nullptr),
                      right_(nullptr),
                      left_(nullptr),
                      column_(nullptr) {
}

#endif
