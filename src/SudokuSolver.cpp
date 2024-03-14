#include "SudokuSolver.hpp"
#include "UndirectedGraph.hpp"

UndirectedGraph<int> getSudokuGraph()
{
    //NOTE this will always make the same graph, only need to call once
    
    UndirectedGraph<int> graph;
    
    /* Each cell of the sudoku board is a vertex */
    for(int row = 0; row < Sudoku::BOARD_SIZE; row++)
    {
        for(int col = 0; col < Sudoku::BOARD_SIZE; col++)
        {
            int fromCell = row * Sudoku::BOARD_SIZE + col;
            int boxRow = row / Sudoku::BOX_SIZE;
            int boxCol = col / Sudoku::BOX_SIZE;
            
            for(int i = 0; i < Sudoku::BOARD_SIZE; i++)
            {
                /* Row cells */
                int toCell = i * Sudoku::BOARD_SIZE + col;
                if(fromCell != toCell)
                    graph.addEdge(fromCell, toCell);
                
                /* Column cells */
                toCell = row * Sudoku::BOARD_SIZE + i;
                if(fromCell != toCell)
                    graph.addEdge(fromCell, toCell);
            }
            
            /* Box cells */
            int startCellRow = boxRow * Sudoku::BOX_SIZE;
            int startCellCol = boxCol * Sudoku::BOX_SIZE;
            int boxStartCell = startCellRow * Sudoku::BOARD_SIZE + startCellCol;
            for(int i = 0; i < Sudoku::BOX_SIZE; i++)
            {
                for(int j = 0; j < Sudoku::BOX_SIZE; j++)
                {
                    int toCell = boxStartCell + i * Sudoku::BOARD_SIZE + j;
                    
                    /* Don't add self-loop */
                    if(fromCell != toCell)
                        graph.addEdge(fromCell, toCell);
                }
            }
        }
    }
    
    return graph;
}

std::map<int, int> getSudokuFixedColorings(const Sudoku& sudoku)
{
    std::map<int, int> fixedColorings;
    
    for(int row = 0; row < Sudoku::BOARD_SIZE; row++)
    {
        for(int col = 0; col < Sudoku::BOARD_SIZE; col++)
        {
            int cell = row * Sudoku::BOARD_SIZE + col;
            std::optional<int> cellValue = sudoku.getValue(row, col);
            
            if(cellValue.has_value())
                fixedColorings[cell] = cellValue.value();
        }
    }
    
    return fixedColorings;
}

std::map<int, int> colorSudokuGraphBacktracking(const UndirectedGraph<int>& graph, std::map<int, int> colorings, const std::map<int, int> fixedColorings, int cell)
{
    constexpr int MIN_COLOR = 1;
    constexpr int MAX_COLOR = 9;
    
    /* Is filling this cell valid? */
    auto isValidColoring =
    [&graph, &colorings](int cell, int color)
    {
        const UndirectedGraph<int>::EdgeList& neighbors = graph.getEdgeList(cell);
        
        /* Check if the cell has the same color as its neighbor */
        for(int neighbor : neighbors)
        {
            if(colorings.count(neighbor) != 0 && color == colorings.at(neighbor))
                return false;
        }
        
        return true;
    };
    
    /* Stop if previous cell was last cell */
    if(cell >= Sudoku::BOARD_SIZE * Sudoku::BOARD_SIZE)
        return colorings;
    
    /* Is this cell fixed? */
    if(fixedColorings.count(cell) != 0)
        return colorSudokuGraphBacktracking(graph, colorings, fixedColorings, cell + 1);
    
    /* Try every color for this cell */
    for(int color = MIN_COLOR; color <= MAX_COLOR; color++)
    {
        if(isValidColoring(cell, color))
        {
            colorings[cell] = color;
            
            std::map<int, int> newColorings = colorSudokuGraphBacktracking(graph, colorings, fixedColorings, cell + 1);
            
            if(!newColorings.empty())
                return newColorings;
        }
    }
    
    //Return empty map
    return std::map<int, int>{};
}

std::map<int, int> colorSudokuGraph(const UndirectedGraph<int>& graph, std::map<int, int> fixedCells)
{
    return colorSudokuGraphBacktracking(graph, fixedCells, fixedCells, 0);
}

void fillSudokuWithColorings(Sudoku& sudoku, std::map<int, int> colorings)
{
    for(auto [cell, coloring] : colorings)
    {
        int row = cell / Sudoku::BOARD_SIZE;
        int col = cell % Sudoku::BOARD_SIZE;
        
        sudoku.setValue(row, col, coloring);
    }
}

Sudoku solveSudoku(Sudoku sudoku)
{
    UndirectedGraph<int> graph = getSudokuGraph();
    std::map<int, int> fixedColorings = getSudokuFixedColorings(sudoku);
    
    std::map<int, int> colorings = colorSudokuGraph(graph, fixedColorings);
    fillSudokuWithColorings(sudoku, colorings);
    
    return sudoku;
}