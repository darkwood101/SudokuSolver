#ifndef COLUMN_HH
#define COLUMN_HH

#include "Cell.hh"
#include <cstdlib>

class Column : public Cell {

private:
    size_t size_;
    int index_;

public:
    Column();

    void cover();
    void uncover();

    inline size_t& size();
    inline int& index();

};

inline size_t& Column::size() {
    return size_;
}

inline int& Column::index() {
    return index_;
}

#endif
