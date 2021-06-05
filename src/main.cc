#include "Solver.hh"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "Sudoku.hh"
#include <stdexcept>
#include <iostream>

int main() {

	std::string	input;
	std::getline(std::cin, input);
	
	Sudoku s;
	try {
		s.init(input);
	} catch (std::invalid_argument& err) {
		printf("Error: %s\n", err.what());
		return 0;
	}

	printf("Your input:\n");
	s.print();
	Solver sol(s);
	try {
		sol.run();
	} catch (std::runtime_error& err) {
		printf("Error: %s\n", err.what());
		return 0;
	}
	printf("Solution:\n");
	s.print();

	return 0;

}