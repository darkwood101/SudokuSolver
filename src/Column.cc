#include "Column.hh"

/**
 * Covers the column, as defined by Algorithm X.
 **/
void Column::cover() {
    // Unlink the column from its neighboring columns
    right_->left_ = left_;
    left_->right_ = right_;

    // Completely remove each row that intersects with the column
    // that is being covered
    for (Cell* row = down_; row != this; row = row->down_) {
        for (Cell* cell = row->right_; cell != row; cell = cell->right_) {
            cell->up_->down_ = cell->down_;
            cell->down_->up_ = cell->up_;
            --cell->column_->size_;
        }
    }
}

/**
 * Uncovers the column, as defined by Algorithm X.
 * 
 * It's very important that the order of operations is reversed
 * compared to covering the column, in order to maintain the consistent
 * state of the linked lists.
 **/
void Column::uncover() {
    // Re-insert each row that intersects with the colum
    // that is being uncovered
    for (Cell* row = up_; row != this; row = row->up_) {
        for (Cell* cell = row->left_; cell != row; cell = cell->left_) {
            cell->up_->down_ = cell;
            cell->down_->up_ = cell;
            ++cell->column_->size_;
        }
    }

    // Re-link the column with its neighbors
    right_->left_ = this;
    left_->right_ = this;
}
