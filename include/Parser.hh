/** Parser.hh 
 * 
 * This header file contains the declaration of the `Parser` struct,
 * which is used to parse the command line input, as well as for some general
 * helper functions.
 **/

#ifndef PARSER_HH
#define PARSER_HH

#include <cstdlib>
#include <chrono>
#include <thread>

struct Parser {
    bool help_;                                             // Set to true if -h is supplied
    bool animate_;                                          // Set to true if -a is supplied
    bool time_;                                             // Set to true if -t is supplied
    std::chrono::high_resolution_clock::time_point start_;  // Used to measure the starting time stamp

    inline Parser();
    void parse(int argc, char** argv);

    // Printout functions
    static void usage(const char* prog_name);
    static void clear();

    // Timing functions
    inline void start_timing();
    inline double end_timing();
};

inline Parser::Parser() : help_(false),
                          animate_(false),
                          time_(false) {
}

/** 
 * Records the timestamp in the `start_` variable
 **/
inline void Parser::start_timing() {
    start_ = std::chrono::high_resolution_clock::now();
}

/**
 * Measures the time since `start_` and returns the number
 * of elapsed microseconds as a double.
 **/
inline double Parser::end_timing() {
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
}

#endif
