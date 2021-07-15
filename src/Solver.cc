#include "Solver.hh"
#include "Parser.hh"
#include <limits>
#include <cstdio>
#include <stdexcept>
#include <thread>
#include <chrono>

/**
 * Converts the given constraint to the index of a constraint column.
 **/
int Solver::constraint_to_col(constraint c, int row, int col, int digit) {
    int ret = -1;
    switch (c) {
        case c_cell:
            // `digit` is irrelevant here
            // This is because we are talking about the constraint that
            // the cell is taken by any digit, so the exact digit doesn't
            // matter
            ret = 1 + row * board_size + col;
            break;

        case c_row:
            ret = board_size * board_size + row * board_size + digit;
            cols_[ret].row_ = row;
            cols_[ret].digit_ = digit;
            break;

        case c_column:
            ret = 2 * board_size * board_size + col * board_size + digit;
            cols_[ret].column_ = col;
            cols_[ret].digit_ = digit;
            break;

        case c_box:
            // The index of the box. They look like this:
            /**
             *   0    1    2
             *   3    4    5
             *   6    7    8
             * 
             * Each digit is a 3x3 grid of cells (that's what we mean when
             * we say "box")
             **/
            int box = 3 * (row / 3) + (col / 3) % 3;
            ret = 3 * board_size * board_size + box * board_size + digit;
            break;
    }

    return ret;
}

/**
 * Convert the index of the constraint column to a constraint.
 * 
 * This essentially reverses the operation above.
 **/
Solver::constraint Solver::col_to_constraint(int col) {
    if (col <= board_size * board_size) {
        return c_cell;
    } else if (col <= 2 * board_size * board_size) {
        return c_row;
    } else if (col <= 3 * board_size * board_size) {
        return c_column;
    } else {
        return c_box;
    }
}

/**
 * Initialize all column headers. Called only once.
 **/
void Solver::init_columns() {
    // Pre-allocate the vector of collumns
    cols_.resize(num_cols);
    root_ = &cols_[0];

    // Set up all pointers properly
    for (size_t i = 0; i < num_cols; ++i) {
        // Point to the next one; if at the end, point to the
        // first one
        cols_[i].right_ = &cols_[(i + 1) % num_cols];

        // If the first column, point to the last one, otherwise just
        // to the lefts
        // We can't use the same syntax as above because the behavior of
        // mod of negative numbers is not guaranteed by the standard
        cols_[i].left_ = (i == 0) ? &cols_[num_cols - 1] : &cols_[i - 1];

        // Up and down point to themselves (toroidal list)
        cols_[i].up_ = &cols_[i];
        cols_[i].down_ = &cols_[i];
    }
}

/**
 * Insert the row corresponding to sudoku row `row`, sudoku column `col`,
 * and sudoku digit `digit` into the Dancing Links board.
 * 
 * This method is not called during solving, but during the initialization
 * of the Dancing Links board.
 * 
 * The row is always inserted at the bottom of the board (the order of the rows
 * is not important for Algorithm X)
 **/
void Solver::insert_row(int row, int col, int digit) {
    // Get the column indices for the 4 different constraints
    int col_indices[4] = {constraint_to_col(c_cell, row, col),
                          constraint_to_col(c_row, row, col, digit),
                          constraint_to_col(c_column, row, col, digit),
                          constraint_to_col(c_box, row, col, digit)};
    // Allocate the 4 cells for the 4 constraints
    Cell* cells = new Cell[4];
    allocs_.push_back(cells);

    // Insert all 4 cells
    for (int i = 0; i < 4; ++i) {
        Column* column = &cols_[col_indices[i]];
        Cell* cell = &cells[i];

        // We are inserting at the bottom
        cell->up_ = column->up_;
        cell->down_ = column;
        cell->up_->down_ = cell;
        column->up_ = cell;

        // Link it to the other cells that we just allocated
        cell->left_ = (i == 0) ? &cells[3] : &cells[i - 1];
        cell->right_ = &cells[(i + 1) % 4];

        cell->column_ = column;
        ++column->size_;
    }
}

/**
 * Searches for the solution using Algorithm X.
 **/
void Solver::search() {
    ++iter_;

    // Done; decode the solution and return
    if (root_->right_ == root_) {
        s_.solved_ = true;
        decode();
        return;
    }

    // If animation was requested, then we want to decode and print out
    // on every step
    if (animate_) {
        decode();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Parser::clear();
        printf("Iteration: %lu\n", iter_);
        s_.print();
    }

    Column* col = choose_next_column();
    col->cover();

    for (Cell* cell = col->down_; cell != col; cell = cell->down_) {
        // Insert the cell into the solutions list
        sols_.push_back(cell);

        // Cover all columns that intersect with this row
        for (Cell* row = cell->right_; row != cell; row = row->right_) {
            row->column_->cover();
        }

        // Recursively search
        search();

        // We are done; return. We don't want to search for multiple solutions.
        if (s_.solved_) {
            return;
        }

        // Didn't work: remove the cell from the solutions list,
        // uncover the columns in reverse order and continue the algorithm
        Cell* fail_cell = sols_.back();
        sols_.pop_back();
        for (Cell* fail_row = fail_cell->left_; fail_row != fail_cell; fail_row = fail_row->left_) {
            fail_row->column_->uncover();
        }
    }
    col->uncover();
}

/**
 * Decodes the current solution (complete or partial)
 * and updated the sudoku board.
 **/
void Solver::decode() {
    for (size_t i = 0; i < sols_.size(); ++i) {
        int row = -1;
        int col = -1;
        int digit = -1;
        Cell* cell = sols_[i];
        // Each cell has at most 4 neighbors
        for (int j = 0; j < 4; ++j) {
            // If any information is not -1, then it was
            // found by algorithm X
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
        // At this point, we are guaranteed to have `row`, `col`, and `digit`
        // correct
        s_.get(row, col) = digit + '0';
    }
}

/**
 * Initializes columns and initialize the board by encoding the sudoku board to
 * the Dancing Links board.
 **/
Solver::Solver(Sudoku& s, bool animate) : s_(s), animate_(animate), iter_(0) {
    init_columns();

    for (size_t row = 0; row < board_size; ++row) {
        for (size_t column = 0; column < board_size; ++column) {
            // If the cell is non-empty, we only need one row
            if (s.get(row, column) != '.') {
                insert_row(row, column, s.get(row, column) - '0');
            } else {
                // If the cell is empty, we need 9 rows (one for each
                // possibility)
                for (int digit = 1; digit <= 9; ++digit) {
                    insert_row(row, column, digit);
                } 
            }
        }
    }
}

/**
 * Frees up the memory that we used to allocate the cells in `Solver::insert_row`.
 **/
Solver::~Solver() {
    for (size_t i = 0; i < allocs_.size(); ++i) {
        delete[] allocs_[i];
    }
}

/**
 * Returns the next column to be covered. Knuth suggests the heuristic of picking
 * a column with the smallest size.
 **/
Column* Solver::choose_next_column() {
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
    return ret;
}

/**
 * A public interface method to start the solver.
 **/
void Solver::run() {
    search();
}
