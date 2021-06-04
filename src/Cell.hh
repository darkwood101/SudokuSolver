#ifndef CELL_HH
#define CELL_HH

class Column;

class Cell {

private:
    Cell* up_;
    Cell* down_;
    Cell* right_;
    Cell* left_;
    Column* column_;

public:
    Cell();

    inline Cell*& up();
    inline Cell*& down();
    inline Cell*& right();
    inline Cell*& left();
    inline Column* column() const;
};


inline Cell*& Cell::up() {
    return up_;
}

inline Cell*& Cell::down() {
    return down_;
}

inline Cell*& Cell::right() {
    return right_;
}

inline Cell*& Cell::left() {
    return left_;
}

inline Column* Cell::column() const {
    return column_;
}


#endif
