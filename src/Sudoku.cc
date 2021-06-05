#include "Sudoku.hh"

#include <cstdio>
#include <stdexcept>

Sudoku::Sudoku(std::vector<std::vector<char>>& grid) {
    if (grid.size() != sudoku_size) {
        throw std::invalid_argument("Board size invalid");
    }
    for (size_t i = 0; i < sudoku_size; ++i) {
        if (grid[i].size() != sudoku_size) {
            throw std::invalid_argument("Board size invalid");
        }
    }

    for (size_t i = 0; i < sudoku_size; ++i) {
        for (size_t j = 0; j < sudoku_size; ++j) {
            if ((grid[i][j] - '0' < 1 || grid[i][j] - '0' > 9) && (grid[i][j] != '.')) {
                fprintf(stderr, "Illegal character %c at row %lu, column %lu\n", grid[i][j], i, j);
                throw std::invalid_argument("Illegal character");
            }
        }
    }

    grid_ = grid;
}

Sudoku::Sudoku() {
    grid_.resize(sudoku_size);
    for (size_t i = 0; i < sudoku_size; ++i) {
        grid_[i].resize(sudoku_size, '.');
    }
}

void Sudoku::init(std::string s) {
    if (s.length() != sudoku_size * sudoku_size) {
        throw std::invalid_argument("Invalid string length");
    }
    for (size_t i = 0; i < sudoku_size; ++i) {
        for (size_t j = 0; j < sudoku_size; ++j) {
            if ((s.at(i * sudoku_size + j) - '0' < 1 || s.at(i * sudoku_size + j) - '0' > 9) && (s.at(i * sudoku_size + j) != '.')) {
                fprintf(stderr, "Illegal character %c at row %lu, column %lu\n", s.at(i * sudoku_size + j), i, j);
                throw std::invalid_argument("Illegal character");
            }
            grid_[i][j] = s.at(i * sudoku_size + j);
        }
    }
}

void Sudoku::print_line() {
    printf("+-------+-------+-------+\n");
}

void Sudoku::print_row(size_t row) {
    for (size_t i = 0; i < sudoku_size; ++i) {
        if (i % 3 == 0) {
            printf("| ");
        }
        printf("%c ", grid_[row][i]);
    }
    printf("|\n");
}

void Sudoku::print() {
    for (size_t i = 0; i < sudoku_size; ++i) {
        if (i % 3 == 0) {
            print_line();
        }
        print_row(i);
    }
    print_line();
}
