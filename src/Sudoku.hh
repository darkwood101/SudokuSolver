#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <vector>
#include <cstdlib>
#include <string>

class Sudoku {

private:
    std::vector<std::vector<char>> grid_;

    void print_line();
    void print_row(size_t row);

public:
    static constexpr size_t sudoku_size = 9;
    bool multiple_;
    bool solved_;

    Sudoku(std::vector<std::vector<char>>& grid);
    Sudoku();
    void init(std::string s);
    inline char& get(size_t row, size_t column);
    void print();

};

inline char& Sudoku::get(size_t row, size_t column) {
    return grid_[row][column];
}

#endif
