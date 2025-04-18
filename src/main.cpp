#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Board.h"
#include "SFML.h"

int main() 
{
    // create window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Sudoku");
    SFML sfml(window);
    
    // Set up header
    sf::Font font("assets/SpecialGothicCondensedOne-Regular.ttf");
    sf::Text generate(font);
    sf::Text reset(font);
    sf::Text header(font);

    // Generate the 9x9 board and declare the SFML object
    srand(time(NULL));
    Board myBoard;

    const float gridSize = 450.0f;
    const float gridStartX = 75.0f;
    const float gridStartY = 75.0f;
    const float cellSize = gridSize / 18.0f;
    const float cellCenter = cellSize / 2.0f;

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
                    myBoard.constructBoard(sfml, 0, window, font, header, generate, reset, gridStartX, gridStartY, cellSize, gridSize, cellCenter);
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
        sfml.drawGrid(window, gridStartX, gridStartY, gridSize, cellSize, cellCenter);
        sfml.drawButtons(window, font, generate, reset);
        sfml.drawCell(window, font, gridStartX, gridStartY, cellSize, myBoard);

        // Display the contents of the window
        window.display();
    }

    return 0;
}