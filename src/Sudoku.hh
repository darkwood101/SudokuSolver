#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <vector>
#include <cstdlib>

class Sudoku {

private:
    void print_line();
    void print_row(size_t row);

    static constexpr size_t sudoku_size = 9;
    std::vector<std::vector<char>> grid_;

public:

    Sudoku(std::vector<std::vector<char>>& grid);
    Sudoku();
    inline char get(size_t row, size_t column);
    void print();

};

inline char Sudoku::get(size_t row, size_t column) {
    return grid_[row][column];
}

#endif
