#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Board.h"
#include "Remover.h"

int main() 
{
    // create window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Sudoku");
    
    // Set up header
    sf::Font font("assets/SpecialGothicCondensedOne-Regular.ttf");
    sf::Text header(font);

    // Set up buttons
    sf::Text generate(font);
    sf::Text reset(font);
    generate.setString("Generate a Board");
    reset.setString("Reset Board");
    generate.setCharacterSize(22);
    reset.setCharacterSize(22);
    generate.setFillColor(sf::Color::Green);
    generate.setStyle(sf::Text::Bold);
    reset.setFillColor(sf::Color::Red);
    reset.setStyle(sf::Text::Bold);

    // Position the buttons correctly
    // TODO
    sf::FloatRect genBounds = generate.getLocalBounds();
    sf::FloatRect resetBounds = reset.getLocalBounds();
    sf::Vector2f genOrigin;
    sf::Vector2f resetOrigin;
    genOrigin.x = genBounds.position.x + genBounds.size.x / 2.0f;
    genOrigin.y = genBounds.position.y + genBounds.size.y / 2.0f;
    resetOrigin.x = resetBounds.position.x + resetBounds.size.x / 2.0f;
    resetOrigin.y = resetBounds.position.y + resetBounds.size.y / 2.0f;
    generate.setOrigin(genOrigin);
    reset.setOrigin(resetOrigin);
    sf::Vector2f genPos(window.getSize().x / 2.0f - 100.0f, 570.f);
    generate.setPosition(genPos);
    sf::Vector2f resetPos(window.getSize().x / 2.0f + 100.0f, 570.0f);
    reset.setPosition(resetPos);

    // Padding for spacing around the text
    float padding = 10.f;

    // Create a rectangle around the text
    sf::FloatRect genTextBounds = generate.getGlobalBounds();
    sf::RectangleShape genButton;
    genButton.setSize(sf::Vector2f(genTextBounds.size.x + padding * 2, genTextBounds.size.y + padding * 2));
    genButton.setOrigin(genButton.getSize() / 2.f);
    genButton.setPosition(generate.getPosition());
    genButton.setFillColor(sf::Color(200, 200, 200, 100));
    genButton.setOutlineColor(sf::Color::Black);
    genButton.setOutlineThickness(2.f);

    sf::FloatRect resetTextBounds = reset.getGlobalBounds();
    sf::RectangleShape resetButton;
    resetButton.setSize(sf::Vector2f(resetTextBounds.size.x + padding * 2, resetTextBounds.size.y + padding * 2));
    resetButton.setOrigin(resetButton.getSize() / 2.f);
    resetButton.setPosition(reset.getPosition());
    resetButton.setFillColor(sf::Color(200, 200, 200, 100));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(2.f);

    // Generate the 9x9 board filled with 0s
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
                sf::FloatRect genBounds = genButton.getGlobalBounds();
                sf::FloatRect resetBounds = resetButton.getGlobalBounds();

                // generate the board
                if (genBounds.contains(mousePos))
                {
                    myBoard.constructBoard(0, window, font, header, gridStartX, gridStartY, cellSize, gridSize, cellCenter);
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
        myBoard.drawHeader(window, font, header);
        myBoard.drawGrid(window, gridStartX, gridStartY, gridSize, cellSize, cellCenter);
        myBoard.drawButtons(window, font);
        myBoard.drawCell(window, font, gridStartX, gridStartY, cellSize);

        // Display the contents of the window
        window.display();
    }

    return 0;
}