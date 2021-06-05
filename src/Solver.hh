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
    std::vector<Cell*> allocs_;

    enum constraint {
        c_cell,
        c_row,
        c_column,
        c_box
    };

    int constraint_to_col(constraint c, int row, int col, int digit = 0);
    constraint col_to_constraint(int col);
    void init_columns();
    void insert_row(int row, int col, int digit);
    bool search(int depth, std::vector<std::vector<int>>& sol);
    void decode(std::vector<std::vector<int>>& sol);



public:
    static constexpr int board_size = 9;
    static constexpr int board_size_sqr = 81;
    static constexpr int num_cols = 4 * board_size * board_size + 1;

    Solver(std::vector<std::vector<int>>& grid);
    ~Solver();
    Column* choose_next_column();
    void run(std::vector<std::vector<int>>& sol);


};

static_assert(Solver::board_size == 9, "Only 9x9 Sudokus are supported!");
static_assert(Solver::num_cols == 325, "Number of columns is miscalculated!");
static_assert(Solver::board_size_sqr == Solver::board_size * Solver::board_size, "81 != 9^2");

#endif