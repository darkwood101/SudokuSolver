#include "Solver.hh"
#include <cassert>
#include <limits>
#include <cstdio>

int Solver::constraint_to_col(constraint c, int row, int col, int digit) {
    int ret = -1;
    switch (c) {
        case c_cell:
            assert(digit == 0);
            ret = 1 + row * board_size + col;
            assert(ret >= 1 && ret <= 81);
            break;

        case c_row:
            assert(digit > 0 && digit <= 9);
            ret = board_size_sqr + row * board_size + digit;
            assert(ret >= 82 && ret <= 162);
            cols_[ret].row_ = row;
            cols_[ret].digit_ = digit;
            break;

        case c_column:
            assert(digit > 0 && digit <= 9);
            ret = 2 * board_size_sqr + col * board_size + digit;
            assert(ret >= 163 && 243);
            cols_[ret].column_ = col;
            cols_[ret].digit_ = digit;
            break;

        case c_box:
            assert(digit > 0 && digit <= 9);
            int box = 3 * (row / 3) + (col / 3) % 3;
            assert(box >= 0 && box <= 8);
            ret = 3 * board_size_sqr + box * board_size + digit;
            assert(ret >= 244 && ret <= 324);
            break;
    }

    return ret;
}

Solver::constraint Solver::col_to_constraint(int col) {
    if (col <= board_size_sqr) {
        return c_cell;
    } else if (col <= 2 * board_size_sqr) {
        return c_row;
    } else if (col <= 3 * board_size_sqr) {
        return c_column;
    } else {
        return c_box;
    }
}

void Solver::init_columns() {
    cols_.resize(num_cols);
    root_ = &cols_[0];

    for (size_t i = 0; i < num_cols; ++i) {
        cols_[i].right_ = &cols_[(i + 1) % num_cols];
        cols_[i].left_ = (i == 0) ? &cols_[num_cols - 1] : &cols_[i - 1];
        cols_[i].up_ = &cols_[i];
        cols_[i].down_ = &cols_[i];
    }
}

void Solver::insert_row(int row, int col, int digit) {
    int col_indices[4] = {constraint_to_col(c_cell, row, col),
                          constraint_to_col(c_row, row, col, digit),
                          constraint_to_col(c_column, row, col, digit),
                          constraint_to_col(c_box, row, col, digit)};
    Cell* cells = new Cell[4];
    allocs_.push_back(cells);
    for (int i = 0; i < 4; ++i) {
        Column* column = &cols_[col_indices[i]];
        Cell* cell = &cells[i];
        cell->up_ = column->up_;
        cell->down_ = column;
        cell->up_->down_ = cell;
        column->up_ = cell;

        cell->left_ = (i == 0) ? &cells[3] : &cells[i - 1];
        cell->right_ = &cells[(i + 1) % 4];

        cell->column_ = column;
        ++column->size_;
    }
}

bool Solver::search(int depth, std::vector<std::vector<int>>& sol) {
    if (root_->right_ == root_) {
        decode(sol);
        return true;
    }

    Column* col = choose_next_column();
    col->cover();
    for (Cell* cell = col->down_; cell != col; cell = cell->down_) {
        sols_.push_back(cell);

        for (Cell* row = cell->right_; row != cell; row = row->right_) {
            row->column_->cover();
        }
        search(++depth, sol);
        Cell* fail_cell = sols_.back();
        sols_.pop_back();
        for (Cell* fail_row = fail_cell->left_; fail_row != fail_cell; fail_row = fail_row->left_) {
            fail_row->column_->uncover();
        }
    }
    col->uncover();

    return false;
}

void Solver::decode(std::vector<std::vector<int>>& sol) {
    for (size_t i = 0; i < sols_.size(); ++i) {
        int row = -1;
        int col = -1;
        int digit = -1;
        Cell* cell = sols_[i];
        for (int j = 0; j < 4; ++j) {
            if (cell->column_->digit_ != -1) {
                digit = cell->column_->digit_;
            }
            if (cell->column_->row_ != -1) {
                row = cell->column_->row_;
            }
            if (cell->column_->column_ != -1) {
                col = cell->column_->column_;
            }
            cell = cell->right_;
        }
        assert(row >= 0 && row < 9);
        assert(col >= 0 && col < 9);
        //assert(digit > 0 && digit <= 9);
        //assert(sol[row][col] == -2);
        sol[row][col] = digit;
    }
}

Solver::Solver(std::vector<std::vector<int>>& grid) {
    init_columns();

    for (size_t row = 0; row < board_size; ++row) {
        for (size_t column = 0; column < board_size; ++column) {
            if (grid[row][column] != 0) {
                insert_row(row, column, grid[row][column]);
            } else {
                for (int digit = 1; digit <= 9; ++digit) {
                    insert_row(row, column, digit);
                } 
            }
        }
    }
}

Solver::~Solver() {
    for (size_t i = 0; i < allocs_.size(); ++i) {
        delete[] allocs_[i];
    }
}

Column* Solver::choose_next_column() {
    assert(root_ != nullptr);

    Column* ret = nullptr;
    size_t sz = std::numeric_limits<size_t>::max();

    for (Column* temp = reinterpret_cast<Column*>(root_->right_);
        temp != root_;
        temp = reinterpret_cast<Column*>(temp->right_)) {
        if (temp->size_ < sz) {
            sz = temp->size_;
            ret = temp;
        }
    }

    assert(ret != root_);
    return ret;
}

void Solver::run(std::vector<std::vector<int>>& sol) {
    if (search(0, sol)) {
        // solution
    } else {
        //assert(false);
    }
}
