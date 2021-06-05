#ifndef PARSER_HH
#define PARSER_HH

#include <cstdlib>
#include <chrono>
#include <thread>

struct Parser {
    bool help_;
    bool animate_;
    bool time_;
    std::chrono::high_resolution_clock::time_point start_;

    inline Parser();
    void parse(int argc, char** argv);
    static void usage(const char* prog_name);
    static void clear();
    inline void start_timing();
    inline double end_timing();
};

inline Parser::Parser() : help_(false),
                          animate_(false),
                          time_(false) {
}

inline void Parser::start_timing() {
    start_ = std::chrono::high_resolution_clock::now();
}

inline double Parser::end_timing() {
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
}

#endif