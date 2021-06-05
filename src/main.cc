#include "Solver.hh"
#include <cstdio>
#include <cstdlib>
#include "Sudoku.hh"
#include <stdexcept>
#include <iostream>
#include "Parser.hh"

Parser parser;

int main(int argc, char** argv) {

    try {
        parser.parse(argc, argv);
    } catch (std::invalid_argument& err) {
        fprintf(stderr, "Unrecognized command %s\n\n", err.what());
        parser.usage(argv[0]);
        return 0;
    }

    if (parser.help_) {
        return 0;
    }

    std::string input;
    std::getline(std::cin, input);

    if (parser.time_) {
        parser.start_timing();
    }
    
    Sudoku s;
    try {
        s.init(input);
    } catch (std::invalid_argument& err) {
        printf("Error: %s\n", err.what());
        return 0;
    }

    Sudoku old(s);
    Solver sol(s, parser.animate_);
    try {
        sol.run();
    } catch (std::runtime_error& err) {
        printf("%s\n", err.what());
        return 0;
    }

    if (parser.animate_) {
        parser.clear();
    }

    printf("Your input\n");
    old.print();

    printf("Solution:\n");
    s.print();

    if (parser.time_) {
        printf("Time taken: %.2f milliseconds\n", parser.end_timing() / 1000.00);
    }

    return 0;

}