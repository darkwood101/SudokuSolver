/** Cell.hh 
 * 
 * This header file contains the declaration of the `Cell` struct,
 * which is used to represent a cell in the Dancing Links algorithm.
 * 
 * Each cell contains 5 pointers: 4 to the neighboring cells, and 1
 * to the column header. Since the list is toroidal, the cell might point
 * to itself.
 **/

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
