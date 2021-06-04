#include "Solver.hh"
#include <cassert>
#include <limits>

int Solver::get_constraint_col(constraint c, int row, int col, int digit) {
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
            break;

        case c_column:
            assert(digit > 0 && digit <= 9);
            ret = 2 * board_size_sqr + col * board_size + digit;
            assert(ret >= 163 && 243);
            break;

        case c_box:
            assert(digit > 0 && digit <= 9);
            int box = 3 * row + col % 3;
            assert(box >= 0 && box <= 8);
            ret = 3 * board_size_sqr + box * board_size + digit;
            assert(ret >= 244 && ret <= 324);
            break;
    }

    return ret;
}

void Solver::init_columns() {
    cols_.resize(num_cols);
    root_ = &cols_[0];

    for (size_t i = 0; i < num_cols; ++i) {
        cols_[i].right() = &cols_[(i + 1) % num_cols];
        cols_[i].left() = (i == 0) ? &cols_[num_cols - 1] : &cols_[i - 1];
        cols_[i].index() = i;
    }
}

void Solver::insert_row(int row, int col, int digit) {
    int col_indices[4] = {get_constraint_col(c_cell, row, col),
                          get_constraint_col(c_row, row, col, digit),
                          get_constraint_col(c_column, row, col, digit),
                          get_constraint_col(c_box, row, col, digit)};
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

bool Solver::search(int depth) {
    if (root_->right() == root_) {
        return true;
    }

    Column* col = choose_next_column();
    col->cover();
    for (Cell* cell = col->down(); cell != col; cell = cell->down()) {
        sols_.push_back(cell);
        for (Cell* row = cell->right(); row != cell; row = row->right()) {
            row->column()->cover();
        }
        search(++depth);
        Cell* fail_cell = sols_.back();
        sols_.pop_back();
        for (Cell* fail_row = fail_cell->left(); fail_row != fail_cell; fail_row = fail_row->left()) {
            fail_row->column()->uncover();
        }
    }
    col->uncover();

    return false;
}

Solver::Solver(std::vector<std::vector<int>> grid) {
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

    return ret;
}

void Solver::run(std::vector<std::vector<int>> sol) {
    if (search(0)) {
        // solution
    } else {
        // no solution
    }
}
