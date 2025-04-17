#include "Board.h"
#include <iostream>
#include <set>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>

// populate board with 0s
Board::Board() : board(9, std::vector<int>(9, 0))
{

}

// construct valid sudoku board
bool Board::constructBoard(int index)
{
    if (index >= 81) 
    {
        return true;
    }
    
    int row = index / 9;
    int col = index % 9;

    // possible values in the row
    int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Fisher-Yates shuffle (O(n) time complexity to shuffle each row)
    for (int i = 8; i > 0; i--) 
    {
        // assign a random integer (will be used as an index) between 0 and i to j
        int j = rand() % (i + 1);
        // swap the value at index i with the value at index j
        std::swap(values[i], values[j]);
        // this moves the struck numbers to the END of the list, shuffling the list and avoiding repeats
    }

    // try each value, backtrack if not valid
    for (int i = 0; i < 9; i++)
    {
        int val = values[i];
        if (isValid(row, col, val))
        {
            board[row][col] = val;

            if (constructBoard(index + 1))
            {
                return true;
            }
            // backtrack
            board[row][col] = 0;
        }
    }
    return false;
}

// make sure it is valid
bool Board::isValid(int r, int c, int value)
{
    // row checker
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i] == value)
        {
            return false;
        }
    }

    // col checker
    for (int i = 0; i < 9; i++)
    {
        if (board[i][c] == value)
        {
            return false;
        }
    }

    // 3x3 checker
    int startRow = (r / 3) * 3;
    int startCol = (c / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (board[i][j] == value)
            {
                return false;
            }
        }
    }
    return true;
}

// Print board (just for debugging)
void Board::printBoard() const 
{
    for (int i = 0; i < board.size(); i++) 
    {
        for (int j = 0; j < board.size(); j++) 
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// For SFML rendering
int Board::getValue(int row, int col) const
{
    if (row < 0 || row >= 9 || col < 0 || col >= 9) 
    {
        return -1;
    }
    return board[row][col];
}

// Just to reset the board back to 0
void Board::resetBoard()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = 0;
        }
    }
}