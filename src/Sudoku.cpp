#include "Sudoku.hpp"

bool validCell(int row, int col)
{
    return 0 <= row && row < Sudoku::BOARD_SIZE &&
           0 <= col && col < Sudoku::BOARD_SIZE;
}

bool validValue(int value)
{
    return 1 <= value && value <= Sudoku::BOARD_SIZE;
}

void Sudoku::setValue(int row, int col, int value)
{
    if(validCell(row, col) && validValue(value))
        m_board[row][col] = value;
}

std::optional<int> Sudoku::getValue(int row, int col) const
{
    if(validCell(row, col))
        return m_board[row][col];
    else
        return -1;
}

void Sudoku::clearValue(int row, int col)
{
    if(validCell(row, col))
        m_board[row][col].reset();
}

void Sudoku::clear()
{
    for(int row = 0; row < Sudoku::BOARD_SIZE; row++)
    {
        for(int col = 0; col < Sudoku::BOARD_SIZE; col++)
            clearValue(row, col);
    }
}