#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <set>
#include <vector>
#include <SFML/System.hpp>

class Board {
public:
    Board();
    bool constructBoard(int index);
    bool isValid(int r, int c, int value);
    void printBoard() const;
    int getValue(int row, int col) const;
    void resetBoard();

    // help with animation
    bool isConstructing = false;
    int animationDelay = 50;
    sf::Clock animationClock;

    std::vector< std::vector<int> > board;
};

#endif