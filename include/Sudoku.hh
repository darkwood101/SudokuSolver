/**
 * Sudoku.hh
 * 
 * This header file contains the declaration of the `Sudoku` class, which
 * abstracts the `Sudoku` board.
 **/

#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <vector>
#include <cstdlib>
#include <string>

class Sudoku {

private:
    std::vector<std::vector<char>> grid_;               // The 9x9 matrix of characters
                                                        // Empty cells are represented as '.'

    // Printing helper functions
    void print_line();
    void print_row(size_t row);

public:
    static constexpr size_t sudoku_size = 9;
    bool solved_;                                       // True if the sudoku has been solved

    Sudoku();
    void init(std::string s);                           // Initialize the sudoku board using the string `s`
    inline char& get(size_t row, size_t column);        // Return the character at position (`row`, `column`)
    void print();                                       // Print the board nicely

};

/**
 * Returns the specified character in the board.
 * The rows and columns are indexed starting from 0.
 **/
inline char& Sudoku::get(size_t row, size_t column) {
    return grid_[row][column];
}

#endif
