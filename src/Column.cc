#include "Column.hh"

Column::Column() : size_(0) {}

void Column::cover() {
    right()->left() = left();
    left()->right() = right();

    for (Cell* row = down(); row != this; row = row->down()) {
        for (Cell* cell = row->right(); cell != row; cell = row->right()) {
            cell->up()->down() = cell->down();
            cell->down()->up() = cell->up();
            --cell->column()->size_;
        }
    }
}

void Column::uncover() {
    for (Cell* row = up(); row != this; row = row->up()) {
        for (Cell* cell = row->left(); cell != row; cell = cell->left()) {
            cell->up()->down() = cell;
            cell->down()->up() = cell;
            ++cell->column()->size_;
        }
    }

    right()->left() = this;
    left()->right() = this;
}
