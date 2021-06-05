#include "Parser.hh"
#include "Sudoku.hh"

#include <cstring>
#include <cstdio>
#include <stdexcept>

void Parser::parse(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) {
            usage(argv[0]);
            help_ = true;
        } else if (strcmp(argv[i], "-a") == 0) {
            animate_ = true;
        } else if (strcmp(argv[i], "-t") == 0) {
            time_ = true;
        } else {
            throw std::invalid_argument(argv[i]);
        }
    }
}

void Parser::usage(const char* prog_name) {
    fprintf(stderr, "Usage: %s [OPTIONS]\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "\t-h \t\t Print this message\n");
    fprintf(stderr, "\t-a \t\t Animate the solution\n");
    fprintf(stderr, "\t-t \t\t Measure execution time\n");
    fprintf(stderr, "Input example: \n");
    static const char* example_sudoku = "...24..1.7.....8...1..8.3....83.....3..6247.9.......6.....3..428..7.29...6.......";
    Sudoku s;
    s.init(std::string(example_sudoku));
    s.print();
    fprintf(stderr, "should be input as \n%s\n", example_sudoku);
}

void Parser::clear() {
    for (int i = 0; i < 100; ++i) {
        printf("\n");
    }
}
