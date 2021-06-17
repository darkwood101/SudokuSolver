#include "Sudoku.hh"

#include <cstdio>
#include <stdexcept>

/**
 * Initialize an empty sudoku.
 **/
Sudoku::Sudoku() : solved_(false) {
    grid_.resize(sudoku_size);
    for (size_t i = 0; i < sudoku_size; ++i) {
        grid_[i].resize(sudoku_size, '.');
    }
}

/**
 * Initialize sudoku by parsing the string `s`.
 * Will throw `std::invalid_argument` if the length of the string is not 81
 * or if there's an invalid character in the string (anything besides 0-9 and
 * dots).
 **/
void Sudoku::init(std::string s) {
    if (s.length() != sudoku_size * sudoku_size) {
        throw std::invalid_argument("Invalid string length");
    }
    for (size_t i = 0; i < sudoku_size; ++i) {
        for (size_t j = 0; j < sudoku_size; ++j) {
            if ((s.at(i * sudoku_size + j) - '0' < 1 || s.at(i * sudoku_size + j) - '0' > 9) && (s.at(i * sudoku_size + j) != '.')) {
                throw std::invalid_argument("Illegal character");
            }
            grid_[i][j] = s.at(i * sudoku_size + j);
        }
    }
}

/**
 * A helper function for printing. Prints a horizontal line.
 **/
void Sudoku::print_line() {
    printf("+-------+-------+-------+\n");
}

/**
 * Another helper function for printing. Prints the row number `row`.
 * The rows are indexed starting from 0.
 **/
void Sudoku::print_row(size_t row) {
    for (size_t i = 0; i < sudoku_size; ++i) {
        if (i % 3 == 0) {
            printf("| ");
        }
        printf("%c ", grid_[row][i]);
    }
    printf("|\n");
}

/**
 * Prints the entire board nicely.
 **/
void Sudoku::print() {
    for (size_t i = 0; i < sudoku_size; ++i) {
        if (i % 3 == 0) {
            print_line();
        }
        print_row(i);
    }
    print_line();
}
