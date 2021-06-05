#include "Solver.hh"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "Sudoku.hh"
#include <stdexcept>

int main() {
	
	try {
		Sudoku s;
		s.print();
		return 0;
	} catch (std::invalid_argument& err) {
		printf("Error: %s\n", err.what());
		return 0;
	}

	std::vector<std::vector<int>> grid;
	grid.resize(9);
	for (int i = 0; i < 9; ++i) {
		grid[i].resize(9);
	}
	const char* str = ".845.3...5...1.....3...9....679.....1.5.68....4..3..1............9...76.4.8...53.";
	const char* sln = "984523176526417983731689254367941825195268347842735619653872491219354768478196532";

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (str[i * 9 + j] != '.') {
				grid[i][j] = str[i * 9 + j] - '0';
			} else{
				grid[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			printf("%d ", grid[i][j]);
			//assert(sol[i][j] == sln[i * 9 + j] - '0');
		}
		printf("\n");
	}

	printf("\n");	

	Solver solver(grid);

	std::vector<std::vector<int>> sol;
	sol.resize(9);
	for (int i = 0; i < 9; ++i) {
		sol[i].resize(9);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			sol[i][j] = -2;
		}
	}

	solver.run(sol);

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			printf("%d ", sol[i][j]);
			assert(sol[i][j] == sln[i * 9 + j] - '0');
		}
		printf("\n");
	}

	return 0;

}