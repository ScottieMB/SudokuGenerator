#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Board.h"
#include "SFML.h"
#include "Data.h"

int main() 
{
    // create window and set up text
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Sudoku");
    sf::Font font("assets/SpecialGothicCondensedOne-Regular.ttf");
    sf::Text generate(font);
    sf::Text reset(font);
    sf::Text header(font);

    // Generate the 9x9 board and declare objects
    srand(time(NULL));
    Board myBoard;
    SFML sfml;
    Data data;

    const float gridSize = 450.0f;
    const float gridStartX = 75.0f;
    const float gridStartY = 75.0f;
    const float cellSize = gridSize / 18.0f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) 
        {
            auto leftClick = event->is<sf::Event::MouseButtonPressed>();

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (leftClick) 
            {
                // check position of the mouse
                sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos(static_cast<float>(mousePosInt.x), static_cast<float>(mousePosInt.y));

                // define the bounds of the buttons
                sf::FloatRect genBounds = sfml.getGenerateButton().getGlobalBounds();
                sf::FloatRect resetBounds = sfml.getResetButton().getGlobalBounds();

                // generate the board
                if (genBounds.contains(mousePos))
                {
                    myBoard.constructBoard(sfml, 0, window, font, header, generate, reset, data);
                }

                // reset it back to 0s
                if (resetBounds.contains(mousePos))
                {
                    myBoard.resetBoard();
                }
            }
        }

        // Color the window
        window.clear(sf::Color(240, 240, 240));

        // Draw everything
        sfml.drawHeader(window, font, header);
        sfml.drawGrid(window, data);
        sfml.drawButtons(window, font, generate, reset);
        sfml.drawCell(window, font, gridStartX, gridStartY, cellSize, myBoard);

        // Display the contents of the window
        window.display();
    }
    return 0;
}