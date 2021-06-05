#ifndef COLUMN_HH
#define COLUMN_HH

#include "Cell.hh"
#include <cstdlib>

class Column : public Cell {

private:
    size_t size_;
    int row_;
    int column_;
    int digit_;

public:
    Column();

    void cover();
    void uncover();

    inline size_t& size();
    inline int& row();
    inline int& column();
    inline int& digit();

};

inline size_t& Column::size() {
    return size_;
}

inline int& Column::row() {
    return row_;
}

inline int& Column::column() {
    return column_;
}

inline int& Column::digit() {
    return digit_;
}

#endif
