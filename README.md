# Sudoku Solver #

This is a [sudoku] solving command line program, written in C++. The Sudoku Solver uses Algorithm X, in combination with the Dancing Links implementation, to efficiently solve 9x9 sudokus.

After running `./sudokusolver` from the terminal, the program will wait for input. The sudoku board should be input as a string of length 81, with dots in places of empty cells. The input is perhaps best explained through an example:
+-------+-------+-------+
| . . . | 2 4 . | . 1 . |
| 7 . . | . . . | 8 . . |
| . 1 . | . 8 . | 3 . . |
+-------+-------+-------+
| . . 8 | 3 . . | . . . |
| 3 . . | 6 2 4 | 7 . 9 |
| . . . | . . . | . 6 . |
+-------+-------+-------+
| . . . | . 3 . | . 4 2 |
| 8 . . | 7 . 2 | 9 . . |
| . 6 . | . . . | . . . |
+-------+-------+-------+
should be input as 
...24..1.7.....8...1..8.3....83.....3..6247.9.......6.....3..428..7.29...6.......

The 

## Build ##

The default compiler is `GCC`. You can also use `clang`, in which case you need to replace the first line in `makefile`, which is currently `CC=g++`, with `CC=clang++`. Regardless of which compiler you use, it needs to support at least `C++11`. Sudoku Solver is written using standard C++, so it should, in principle, be able to run on any platform, although it has only been tested on Linux.

Download the files from this repository and open the terminal in the main directory. Type `make` and hit enter. If everything goes okay, you should see the message `Build successful!` displayed on the screen. Then, you can run the program from the terminal.

## Demo ##

Check the screenshots in the `demo` folder!

## References ##

Both Dancing Links and Algorithm X were created by Donald Knuth. The original paper, which this Sudoku Solver is based on, can be found [here].

The list of additional sources which were used as references:
- https://www.cs.mcgill.ca/~aassaf9/python/algorithm_x.html
- https://www.kth.se/social/files/58861771f276547fe1dbf8d1/HLaestanderMHarrysson_dkand14.pdf
- https://github.com/ShivanKaul/Sudoku-DLX
- https://github.com/KarlHajal/DLX-Sudoku-Solver

[sudoku]: https://en.wikipedia.org/wiki/Sudoku
[here]: https://www.ocf.berkeley.edu/~jchu/publicportal/sudoku/0011047.pdf
