#include "SudokuSolver.hpp"
#include "SudokuDrawer.hpp"
#include "Input.hpp"

void nextCell(int& row, int& col)
{
    if(col < Sudoku::BOARD_SIZE && row < Sudoku::BOARD_SIZE)
    {
        col++;
        
        if(col == Sudoku::BOARD_SIZE)
        {
            col = 0;
            row++;
        }
    }
}

void prevCell(int& row, int& col)
{
    if(col >= 0 && row >= 0)
    {
        if(col == 0)
        {
            if(row > 0)
            {
                col = Sudoku::BOARD_SIZE - 1;
                row--;
            }
        }
        else
        {
            col--;
        }
    }
}

void fillCell(Sudoku& sudoku, int& row, int& col, int value)
{
    if(col < Sudoku::BOARD_SIZE && row < Sudoku::BOARD_SIZE)
    {
        sudoku.setValue(row, col, value);
        
        nextCell(row, col);
    }
}

void clearPreviousCell(Sudoku& sudoku, int& row, int& col)
{
    if(col >= 0 && row >= 0)
    {
        prevCell(row, col);
        
        sudoku.clearValue(row, col);
    }
}

void clearSudoku(Sudoku& sudoku, int& row, int& col)
{
    row = 0;
    col = 0;
    sudoku.clear();
}

void solveSudoku(Sudoku& sudoku, int& row, int& col)
{
    row = Sudoku::BOARD_SIZE - 1;
    col = Sudoku::BOARD_SIZE;
    sudoku = solveSudoku(sudoku);
}

int main()
{
    sf::VideoMode windowVideoMode(600, 600);
    sf::RenderWindow window(windowVideoMode, "Sudoku Solver", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Image windowIcon;
    windowIcon.loadFromFile("res/window_icon.png");
    window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
    bool windowIsFocused = true;
    
    const std::vector<Input::Key> polledInputs =
    {
        Input::Key::Num1, Input::Key::Num2, Input::Key::Num3,
        Input::Key::Num4, Input::Key::Num5, Input::Key::Num6,
        Input::Key::Num7, Input::Key::Num8, Input::Key::Num9,
        Input::Key::Space,
        Input::Key::Backspace,
        Input::Key::Enter,
        Input::Key::Escape,
        Input::Key::LeftClick
    };
    Input input(window, 10, polledInputs);
    
    Sudoku sudoku;
    int row = 0;
    int col = 0;
    SudokuDrawer sudokuDrawer(sudoku, row, col, sf::Vector2f{0, 0}, sf::Vector2u{600, 600});
    
    while(window.isOpen())
    {
        /* Window event */
        sf::Event windowEvent;
        while(window.pollEvent(windowEvent))
        {
            switch(windowEvent.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                
                case sf::Event::LostFocus:
                {
                    windowIsFocused = false;
                    break;
                }
                
                case sf::Event::GainedFocus:
                {
                    windowIsFocused = true;
                    break;
                }
                
                default:
                {
                    break;
                }
            }
        }
        
        /* Input */
        if(windowIsFocused)
            input.poll();
        
        /* Logic */
        if(input.isPressed(Input::Key::Num1))
            fillCell(sudoku, row, col, 1);
        else if(input.isPressed(Input::Key::Num2))
            fillCell(sudoku, row, col, 2);
        else if(input.isPressed(Input::Key::Num3))
            fillCell(sudoku, row, col, 3);
        else if(input.isPressed(Input::Key::Num4))
            fillCell(sudoku, row, col, 4);
        else if(input.isPressed(Input::Key::Num5))
            fillCell(sudoku, row, col, 5);
        else if(input.isPressed(Input::Key::Num6))
            fillCell(sudoku, row, col, 6);
        else if(input.isPressed(Input::Key::Num7))
            fillCell(sudoku, row, col, 7);
        else if(input.isPressed(Input::Key::Num8))
            fillCell(sudoku, row, col, 8);
        else if(input.isPressed(Input::Key::Num9))
            fillCell(sudoku, row, col, 9);
        else if(input.isPressed(Input::Key::Space))
            nextCell(row, col);
        else if(input.isPressed(Input::Key::Backspace))
            clearPreviousCell(sudoku, row, col);
        else if(input.isPressed(Input::Key::Escape))
            clearSudoku(sudoku, row, col);
        else if(input.isPressed(Input::Key::Enter))
            solveSudoku(sudoku, row, col);
        else if(input.isPressed(Input::Key::LeftClick))
        {
            std::pair<int, int> cell = sudokuDrawer.convertPointToCell(static_cast<sf::Vector2f>(input.mousePosition()));
            row = cell.first;
            col = cell.second;
        }
        
        /* Render */
        window.clear();
        window.draw(sudokuDrawer);
        window.display();
    }
}