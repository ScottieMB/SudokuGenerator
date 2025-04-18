#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class SFML;

class Board {
public:
    Board();
    bool constructBoard(SFML& sfml, int index, sf::RenderWindow& window, sf::Font& font, sf::Text& header, sf::Text& generate, sf::Text& reset, const float& gridStartX, const float& gridStartY, const float& cellSize,  const float& gridSize, const float& cellCenter);
    bool isValid(int r, int c, int value);
    int getValue(int row, int col) const;
    void resetBoard();
    void redrawBoard(SFML& sfml, sf::RenderWindow& window, sf::Font& font, int row, int col, Board& board, sf::Text& header, sf::Text& generate, sf::Text& reset, const float& gridStartX, const float& gridStartY, const float& gridSize, const float& cellSize, const float& cellCenter);

    std::vector< std::vector<int> > board;
};

#endif