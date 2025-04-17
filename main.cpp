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
    header.setString("Sudoku");
    header.setCharacterSize(24);
    header.setFillColor(sf::Color::Blue);
    header.setStyle(sf::Text::Bold);
    
    // Position the header in the correct center
    sf::FloatRect bounds = header.getLocalBounds(); 
    sf::Vector2f origin;
    origin.x = bounds.position.x + bounds.size.x / 2.f;
    origin.y = bounds.position.y + bounds.size.y / 2.f;
    header.setOrigin(origin);
    sf::Vector2f pos(window.getSize().x / 2.0f, 40.f);
    header.setPosition(pos);

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
    
    // Create our lines
    sf::VertexArray rows(sf::PrimitiveType::Lines, 20);
    sf::VertexArray cols(sf::PrimitiveType::Lines, 20);
    sf::VertexArray thickLinesRows(sf::PrimitiveType::Lines, 10);
    sf::VertexArray thickLinesCols(sf::PrimitiveType::Lines, 10);

    for (int i = 0; i < 20; i += 2)
    {
        // rows
        float x = gridStartX + i * cellSize;
        cols[i].position = sf::Vector2f(x, gridStartY);
        cols[i + 1].position = sf::Vector2f(x, gridStartY + gridSize);
        cols[i].color = sf::Color::Blue;
        cols[i + 1].color = sf::Color::Blue;

        // cols
        float y = gridStartY + i * cellSize;
        rows[i].position = sf::Vector2f(gridStartX, y);
        rows[i + 1].position = sf::Vector2f(gridStartX + gridSize, y);
        rows[i].color = sf::Color::Blue;
        rows[i + 1].color = sf::Color::Blue;
    }

    sf::Clock animationClock;
    float animationSpeed = 0.05f;

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
                    myBoard.constructBoard(0);
                }

                // reset it back to 0s
                if (resetBounds.contains(mousePos))
                {
                    myBoard.resetBoard();
                }
            }
        }

        // Color and clear the window
        window.clear(sf::Color(240, 240, 240));

        // Draw the grid and text
        window.draw(rows);
        window.draw(cols);
        window.draw(header);
        window.draw(reset);
        window.draw(generate);
        window.draw(genButton);
        window.draw(resetButton);

        for (int row = 0; row < 9; ++row) 
        {
            for (int col = 0; col < 9; ++col) 
            {
                int value = myBoard.getValue(row, col);

                sf::Text cellText(font, std::to_string(value));
                cellText.setCharacterSize(18);
                cellText.setFillColor(sf::Color::Black);

                // Center the origin of the text
                sf::FloatRect textBounds = cellText.getLocalBounds();
                sf::Vector2f textOrigin;
                textOrigin.x = textBounds.position.x + textBounds.size.x / 2.f;
                textOrigin.y = textBounds.position.y + textBounds.size.y / 2.f;
                cellText.setOrigin(textOrigin);

                // Position the text in the center of the cell
                float x = gridStartX + col * 2 * cellSize + cellSize;
                float y = gridStartY + row * 2 * cellSize + cellSize;
                sf::Vector2f nums(x, y);
                cellText.setPosition(nums);

                window.draw(cellText);
            }
        }

        // Display the contents of the window
        window.display();
    }

    myBoard.printBoard();

    /* remove values
    Remover remover(myBoard);
    remover.Remove(0);
    remover.printUnsolved();*/

    return 0;
}