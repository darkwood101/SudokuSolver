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
            cols_[ret].row() = row;
            cols_[ret].digit() = digit;
            break;

        case c_column:
            assert(digit > 0 && digit <= 9);
            ret = 2 * board_size_sqr + col * board_size + digit;
            assert(ret >= 163 && 243);
            cols_[ret].column() = col;
            cols_[ret].digit() = digit;
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
        cols_[i].right() = &cols_[(i + 1) % num_cols];
        cols_[i].left() = (i == 0) ? &cols_[num_cols - 1] : &cols_[i - 1];
        cols_[i].up() = &cols_[i];
        cols_[i].down() = &cols_[i];
        cols_[i].index() = i;
    }
}

void Solver::insert_row(int row, int col, int digit) {
    int col_indices[4] = {constraint_to_col(c_cell, row, col),
                          constraint_to_col(c_row, row, col, digit),
                          constraint_to_col(c_column, row, col, digit),
                          constraint_to_col(c_box, row, col, digit)};
    Cell* cells = new Cell[4];
    for (int i = 0; i < 4; ++i) {
        Column* column = &cols_[col_indices[i]];
        Cell* cell = &cells[i];
        cell->up() = column->up();
        cell->down() = column;
        cell->up()->down() = cell;
        column->up() = cell;

        cell->left() = (i == 0) ? &cells[3] : &cells[i - 1];
        cell->right() = &cells[(i + 1) % 4];

        cell->column() = column;
        ++column->size();
    }
}

bool Solver::search(int depth, std::vector<std::vector<int>>& sol) {
    if (root_->right() == root_) {
        decode(sol);
        return true;
    }

    Column* col = choose_next_column();
    col->cover();
    for (Cell* cell = col->down(); cell != col; cell = cell->down()) {
        sols_.push_back(cell);

        for (Cell* row = cell->right(); row != cell; row = row->right()) {
            row->column()->cover();
        }
        search(++depth, sol);
        Cell* fail_cell = sols_.back();
        sols_.pop_back();
        for (Cell* fail_row = fail_cell->left(); fail_row != fail_cell; fail_row = fail_row->left()) {
            fail_row->column()->uncover();
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
            if (cell->column()->digit() != -1) {
                digit = cell->column()->digit();
            }
            if (cell->column()->row() != -1) {
                row = cell->column()->row();
            }
            if (cell->column()->column() != -1) {
                col = cell->column()->column();
            }
            cell = cell->right();
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

}

Column* Solver::choose_next_column() {
    assert(root_ != nullptr);

    Column* ret = nullptr;
    size_t sz = std::numeric_limits<size_t>::max();

    for (Column* temp = reinterpret_cast<Column*>(root_->right());
        temp != root_;
        temp = reinterpret_cast<Column*>(temp->right())) {
        if (temp->size() < sz) {
            sz = temp->size();
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
