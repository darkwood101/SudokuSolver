/** Column.hh 
 * 
 * This header file contains the declaration of the `Column` struct,
 * which is used to represent a column header in the Dancing Links algorithm.
 * 
 * The `Column` struct is derived from the `Cell` struct, and thus also contains pointers
 * to 4 neighboring cells. The left and right cells are, in this case, the 2 neighboring
 * column headers. Up and down cells might point to the column itself, since the linked list
 * is toroidal.
 **/

#ifndef COLUMN_HH
#define COLUMN_HH

#include "Cell.hh"
#include <cstdlib>

struct Column : public Cell {
    size_t size_;       // How many cells in this column
    int row_;           // Which sudoku row does this constraint column correspond to
    int column_;        // Which sudoku column does this constraint column correspond to
    int digit_;         // Which sudoku digit does this constraint column correspond to

    inline Column();

    // Cover/uncover methods from algorithm X
    void cover();
    void uncover();
};

inline Column::Column() : size_(0),
                          row_(-1),
                          column_(-1),
                          digit_(-1) {
}

#endif
