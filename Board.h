#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <set>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class Board {
public:
    Board();
    bool constructBoard(int index, sf::RenderWindow& window, sf::Font& font, sf::Text& header, const float& gridStartX, const float& gridStartY, const float& cellSize,  const float& gridSize, const float& cellCenter);
    bool isValid(int r, int c, int value);
    int getValue(int row, int col) const;
    void resetBoard();
    void drawCell(sf::RenderWindow& window, sf::Font& font, const float& gridStartX, const float& gridStartY, const float& cellSize);
    void drawGrid(sf::RenderWindow& window, const float& gridStartX, const float& gridStartY, const float& gridSize, const float& cellSize, const float& cellCenter);
    void drawHeader(sf::RenderWindow& window, sf::Font& font, sf::Text& header);
    void drawButtons(sf::RenderWindow& window, sf::Font& font);

    // help with animation
    bool isConstructing = false;
    int animationDelay = 50;
    sf::Clock animationClock;

    std::vector< std::vector<int> > board;
};

#endif