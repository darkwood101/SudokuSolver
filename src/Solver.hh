#ifndef SOLVER_HH
#define SOLVER_HH

#include <cstdio>
#include <vector>
#include "Column.hh"
#include "Cell.hh"

class Solver {

private:
    Column* root_;
    std::vector<Column> cols_;
    std::vector<Cell*> sols_;

    enum constraint {
        c_cell,
        c_row,
        c_column,
        c_box
    };

    int get_constraint_col(constraint c, int row, int col, int digit = 0);
    void init_columns();
    void insert_row(int row, int col, int digit);
    bool search(int depth);



public:
    static constexpr size_t board_size = 9;
    static constexpr size_t board_size_sqr = 81;
    static constexpr size_t num_cols = 4 * board_size * board_size + 1;

    Solver(std::vector<std::vector<int>> grid);
    ~Solver();
    Column* choose_next_column();
    void run(std::vector<std::vector<int>> sol);


};

static_assert(Solver::board_size == 9, "Only 9x9 Sudokus are supported!");
static_assert(Solver::num_cols == 325, "Number of columns is miscalculated!");
static_assert(Solver::board_size_sqr == Solver::board_size * Solver::board_size, "81 != 9^2");

#endif