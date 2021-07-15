/**
 * Solver.hh
 * 
 * This header file contains the declaration of the `Solver` class, which
 * abstracts the Algorithm X and Dancing Links implementation.
 **/

#ifndef SOLVER_HH
#define SOLVER_HH

#include "Column.hh"
#include "Cell.hh"
#include "Sudoku.hh"
#include <cstdio>
#include <vector>

class Solver {

private:
    Column* root_;                  // Points to the root column header
    std::vector<Column> cols_;      // Stores all column headers
    std::vector<Cell*> sols_;       // Vector of solutions 
    std::vector<Cell*> allocs_;     // Vector of all rows that were allocated
    Sudoku& s_;                     // Reference to the underlying sudoku board
    bool animate_;                  // Set to true if the solution should be animated
    size_t iter_;

    enum constraint {               // Enumerate different constraints for Algorithm X
        c_cell,     // The cell is taken
        c_row,      // A digit can't repeat in the same row twice
        c_column,   // A digit can't repeat in the same column twice
        c_box       // A digit can't repeat in the same box twice
    };

    int constraint_to_col(constraint c, int row, int col, int digit = 0);   // Convert the given constraint to column index
    constraint col_to_constraint(int col);                                  // Convert the given column index to constraint
    void init_columns();                                                    // Initialize all columns
    void insert_row(int row, int col, int digit);                           // Insert a row in the dancing links grid
    void search();                                                          // Search for the solution
    void decode();                                                          // Convert the solution to readable form

public:
    static constexpr int board_size = Sudoku::sudoku_size;                  // Size of the board
    static constexpr int num_cols = 4 * board_size * board_size + 1;        // Number of constraint columns

    Solver(Sudoku& s, bool animate);
    ~Solver();
    Column* choose_next_column();                                           // Choose the next column to cover
    void run();                                                             // Run the solving algorithm


};

static_assert(Solver::board_size == 9, "Only 9x9 Sudokus are supported!");
static_assert(Solver::num_cols == 325, "Number of columns is miscalculated!");

#endif
