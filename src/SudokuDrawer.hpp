#pragma once
#include "Sudoku.hpp"
#include <SFML/Graphics.hpp>

class SudokuDrawer : public sf::Drawable
{
public:
    SudokuDrawer(const Sudoku&, const int& row, const int& col);
    SudokuDrawer(const Sudoku&, const int& row, const int& col, sf::Vector2f position, sf::Vector2u size);
    
    std::pair<int, int> convertPointToCell(sf::Vector2f) const;
    
    void draw(sf::RenderTarget&, sf::RenderStates states) const override;
    
    sf::Vector2f position;
    sf::Vector2u size;

private:
    const Sudoku& m_sudoku;
    const int& m_row;
    const int& m_col;
};