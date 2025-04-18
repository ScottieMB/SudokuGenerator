#ifndef SFML_H
#define SFML_H

#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

class Board;

class SFML
{
public:
    SFML() = default;

    void drawCell(sf::RenderWindow& window, sf::Font& font, const float& gridStartX, const float& gridStartY, const float& cellSize, Board& board);
    void drawGrid(sf::RenderWindow& window, const float& gridStartX, const float& gridStartY, const float& gridSize, const float& cellSize, const float& cellCenter);
    void drawHeader(sf::RenderWindow& window, sf::Font& font, sf::Text& header);
    void drawButtons(sf::RenderWindow& window, sf::Font& font, sf::Text& generate, sf::Text& reset);
    void highlightCell(sf::RenderWindow& window, int row, int col, const float& gridStartX, const float& gridStartY, const float& cellSize);

    sf::RectangleShape getGenerateButton() const;
    sf::RectangleShape getResetButton() const;

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape genButton;
    sf::RectangleShape resetButton;
};

#endif