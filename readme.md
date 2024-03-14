# Sudoku Solver
Sudoku puzzle solver using simple backtracking and [SFML](https://www.sfml-dev.org/) for GUI.

![Solved puzzle](.github/solved.png)

## Building
1. Download the latest version of [SFML](https://www.sfml-dev.org/download.php). Make sure to download the right SFML version for your system.
2. Clone this repo
```
$ git clone https://github.com/ChrisRzech/SudokuSolver.git
```
3. Edit the `SFML_DIR` variable in the `makefile` to the location where SFML is on your system.
4. Build
```
$ make
```
5. Run
```
$ make run
```

## Controls
There is a cursor that shows the current square that will be edited. Pressing 1-9 will overwrite the current square, and the cursor will advance. In addition, you can press space to advance the cursor. Pressing backspace will erase the square behind the cursor. For convenience, you can click on a square to move the cursor there for quick edits. Finally, pressing enter will attempt to solve the sudoku puzzle.