#include "SudokuDrawer.hpp"
#include "Resources.hpp"

SudokuDrawer::SudokuDrawer(const Sudoku& sudoku, const int& row, const int& col)
    : SudokuDrawer{sudoku, row, col, sf::Vector2f{0, 0}, sf::Vector2u{0, 0}}
{
    //Do nothing
}

SudokuDrawer::SudokuDrawer(const Sudoku& sudoku, const int& row, const int& col, sf::Vector2f position, sf::Vector2u size)
    : position{position}, size{size}, m_sudoku{sudoku}, m_row{row}, m_col{col}
{
    //Do nothing
}

std::pair<int, int> SudokuDrawer::convertPointToCell(sf::Vector2f point) const
{
    float spacingX = size.x / Sudoku::BOARD_SIZE;
    float spacingY = size.y / Sudoku::BOARD_SIZE;
    
    point -= position;
    
    //return (row, col)
    return std::make_pair(point.y / spacingY, point.x / spacingX);
}

void SudokuDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    /* Draw board */
    sf::VertexArray lines(sf::Lines, (Sudoku::BOARD_SIZE - 1) * 2);
    float spacingX = size.x / Sudoku::BOARD_SIZE;
    float spacingY = size.y / Sudoku::BOARD_SIZE;
    float startingX = spacingX + position.x;
    float startingY = spacingY + position.y;
    
    for(int i = 0; i < Sudoku::BOARD_SIZE - 1; i++)
    {
        sf::Color color = (i % Sudoku::BOX_SIZE == Sudoku::BOX_SIZE - 1 ? sf::Color::White : sf::Color{50, 50, 50});
        
        /* Vertical line */
        lines.append(sf::Vertex{sf::Vector2f{startingX + spacingX * i, position.y}, color});
        lines.append(sf::Vertex{sf::Vector2f{startingX + spacingX * i, position.y + size.y}, color});
        
        /* Horizontal line */
        lines.append(sf::Vertex{sf::Vector2f{position.x, startingY + spacingY * i}, color});
        lines.append(sf::Vertex{sf::Vector2f{position.x + size.x, startingY + spacingY * i}, color});
    }
    
    target.draw(lines, states);
    
    /* Draw numbers */
    sf::Text text;
    text.setFont(Resources::getResources().font);
    for(int row = 0; row < Sudoku::BOARD_SIZE; row++)
    {
        for(int col = 0; col < Sudoku::BOARD_SIZE; col++)
        {
            std::optional<int> cellValueOptional = m_sudoku.getValue(row, col);
            
            if(cellValueOptional.has_value())
            {
                text.setString(std::to_string(cellValueOptional.value()));
                
                /* Center text in cell */
                float textWidth = text.getLocalBounds().width;
                float textHeight = text.getLocalBounds().height;
                float offsetX = spacingX / 2 - textWidth / 2;
                float offsetY = spacingY / 2 - textHeight / 2;
                text.setPosition(spacingX * col + offsetX, spacingY * row + offsetY);
                
                target.draw(text, states);
            }
        }
    }
    
    /* Draw cursor */
    sf::VertexArray cursor(sf::Lines, 2);
    float cursorLength = spacingX * 0.5;
    float offsetX = spacingX / 2 - cursorLength / 2;
    float offsetY = spacingY * 0.85;
    cursor.append(sf::Vertex{sf::Vector2f{spacingX * m_col + offsetX, spacingY * m_row + offsetY}, sf::Color::White});
    cursor.append(sf::Vertex{sf::Vector2f{spacingX * m_col + offsetX + cursorLength, spacingY * m_row + offsetY}, sf::Color::White});
    target.draw(cursor);
}