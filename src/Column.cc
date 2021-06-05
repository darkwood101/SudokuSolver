#include "Column.hh"

void Column::cover() {
    right_->left_ = left_;
    left_->right_ = right_;

    for (Cell* row = down_; row != this; row = row->down_) {
        for (Cell* cell = row->right_; cell != row; cell = cell->right_) {
            cell->up_->down_ = cell->down_;
            cell->down_->up_ = cell->up_;
            --cell->column_->size_;
        }
    }
}

void Column::uncover() {
    for (Cell* row = up_; row != this; row = row->up_) {
        for (Cell* cell = row->left_; cell != row; cell = cell->left_) {
            cell->up_->down_ = cell;
            cell->down_->up_ = cell;
            ++cell->column_->size_;
        }
    }

    right_->left_ = this;
    left_->right_ = this;
}
