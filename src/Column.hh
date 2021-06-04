#ifndef COLUMN_HH
#define COLUMN_HH

#include "Cell.hh"
#include <cstdlib>

class Column : public Cell {

private:
    size_t size_;

public:
    Column();

    void cover();
    void uncover();

    inline size_t size() const;

};

inline size_t Column::size() const {
    return size_;
}

#endif
