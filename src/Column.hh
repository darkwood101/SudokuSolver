#ifndef COLUMN_HH
#define COLUMN_HH

#include "Cell.hh"
#include <cstdlib>

struct Column : public Cell {
    size_t size_;
    int row_;
    int column_;
    int digit_;

    inline Column();

    void cover();
    void uncover();
};

inline Column::Column() : size_(0),
                          row_(-1),
                          column_(-1),
                          digit_(-1) {
}

#endif
