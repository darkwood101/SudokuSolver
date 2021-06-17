#include "Solver.hh"
#include "Parser.hh"
#include "Sudoku.hh"
#include <iostream>

/**
 * The global parser object used for processing command line input.
 **/
Parser parser;

int main(int argc, char** argv) {

    // Parse the arguments and catch any errors.
    // Print usage on error.
    try {
        parser.parse(argc, argv);
    } catch (std::invalid_argument& err) {
        fprintf(stderr, "Error: Unrecognized command %s\n\n", err.what());
        parser.usage(argv[0]);
        return 0;
    }

    // If `-h` was supplied, terminate the program.
    if (parser.help_) {
        return 0;
    }

    // Get a line from standard input
    std::string input;
    std::getline(std::cin, input);

    // Time if requested
    if (parser.time_) {
        parser.start_timing();
    }
    
    // Try initializing the sudoku board, and catch any errors.
    Sudoku s;
    try {
        s.init(input);
    } catch (std::invalid_argument& err) {
        fprintf(stderr, "Error: %s\n", err.what());
        fprintf(stderr, "Run %s -h for an input example\n", argv[0]);
        return 0;
    }

    // Save a copy of the old board, so we can print the user's input
    Sudoku old(s);

    // Solution 
    Solver sol(s, parser.animate_);
    try {
        sol.run();
    } catch (std::bad_alloc& err) {
        fprintf(stderr, "Error: %s\n", err.what());
        return EXIT_FAILURE;
    }

    // If we were animating, clear the screen.
    if (parser.animate_) {
        parser.clear();
    }

    // Print the input and the solution
    printf("Your input\n");
    old.print();

    if (s.solved_) {
        printf("Solution:\n");
        s.print();
    } else {
        printf("The sudoku has no solution\n");
    }

    // Print timing result
    if (parser.time_) {
        printf("Time taken: %.2f milliseconds\n", parser.end_timing() / 1000.00);
    }

    return 0;
}
