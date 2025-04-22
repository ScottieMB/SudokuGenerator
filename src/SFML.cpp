#include "Board.h"
#include "SFML.h"
#include "Data.h"

void SFML::drawCell(sf::RenderWindow& window, sf::Font& font, const float& gridStartX, const float& gridStartY, const float& cellSize, Board& board)
{
    for (int row = 0; row < 9; ++row) 
    {
        for (int col = 0; col < 9; ++col) 
        {
            int value = board.getValue(row, col);
            if (value == 0) continue;

            // Set up text style
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
}

void SFML::drawGrid(sf::RenderWindow& window, const Data& data)
{   
    // Create our lines
    sf::VertexArray rows(sf::PrimitiveType::Lines, 20);
    sf::VertexArray cols(sf::PrimitiveType::Lines, 20);
    std::vector<sf::RectangleShape> thickLinesRows;
    std::vector<sf::RectangleShape> thickLinesCols;

    for (int i = 0; i < 20; i += 2)
    {
        float x = data.gridStartX + i * data.cellSize;
        float y = data.gridStartY + i * data.cellSize;
        
        if (i % 3 == 0)
        {
            sf::RectangleShape thickRow(sf::Vector2f(data.gridSize + 1.5f, 2.0f));
            thickRow.setFillColor(sf::Color::Blue);
            thickRow.setPosition(sf::Vector2f(data.gridStartX, data.gridStartY + (i * data.cellSize)));
            thickLinesRows.push_back(thickRow);

            sf::RectangleShape thickCol(sf::Vector2f(2.0f, data.gridSize + 1.5f));
            thickCol.setFillColor(sf::Color::Blue);
            thickCol.setPosition(sf::Vector2f(data.gridStartX + (i * data.cellSize), data.gridStartY));
            thickLinesCols.push_back(thickCol);
        }
        else
        {
            cols[i].position = sf::Vector2f(x, data.gridStartY);
            cols[i + 1].position = sf::Vector2f(x, data.gridStartY + data.gridSize);
            cols[i].color = sf::Color::Blue;
            cols[i + 1].color = sf::Color::Blue;

            rows[i].position = sf::Vector2f(data.gridStartX, y);
            rows[i + 1].position = sf::Vector2f(data.gridStartX + data.gridSize, y);
            rows[i].color = sf::Color::Blue;
            rows[i + 1].color = sf::Color::Blue;
        }
    }

    window.draw(rows);
    window.draw(cols);

    for (auto& thickRow : thickLinesRows) 
    {
        window.draw(thickRow);
    }

    for (auto& thickCol : thickLinesCols) 
    {
        window.draw(thickCol);
    }
}

void SFML::drawButtons(sf::RenderWindow& window, sf::Font& font, sf::Text& generate, sf::Text& reset)
{
    float padding = 10.0f;

    // Set up button style
    generate.setString("Generate a Board");
    generate.setCharacterSize(22);
    generate.setFillColor(sf::Color::Green);
    generate.setStyle(sf::Text::Bold);

    reset.setString("Reset Board");
    reset.setCharacterSize(22);
    reset.setFillColor(sf::Color::Red);
    reset.setStyle(sf::Text::Bold);

    // Set origin to the center of text and place it on screen
    sf::FloatRect genBounds = generate.getLocalBounds();
    sf::Vector2f genOrigin;
    genOrigin.x = genBounds.position.x + genBounds.size.x / 2.0f;
    genOrigin.y = genBounds.position.y + genBounds.size.y / 2.0f;
    generate.setOrigin(genOrigin);
    sf::Vector2f genPos(window.getSize().x / 2.0f - 100.0f, 570.f);
    generate.setPosition(genPos);

    // Same thing as above
    sf::FloatRect resetBounds = reset.getLocalBounds();
    sf::Vector2f resetOrigin;
    resetOrigin.x = resetBounds.position.x + resetBounds.size.x / 2.0f;
    resetOrigin.y = resetBounds.position.y + resetBounds.size.y / 2.0f;
    reset.setOrigin(resetOrigin);
    sf::Vector2f resetPos(window.getSize().x / 2.0f + 100.0f, 570.0f);
    reset.setPosition(resetPos);

    // Set up generate button
    sf::FloatRect genTextBounds = generate.getGlobalBounds();
    genButton.setSize(sf::Vector2f(genTextBounds.size.x + padding * 2, genTextBounds.size.y + padding * 2));
    genButton.setOrigin(genButton.getSize() / 2.f);
    genButton.setPosition(generate.getPosition());
    genButton.setFillColor(sf::Color(200, 200, 200, 100));
    genButton.setOutlineColor(sf::Color::Black);
    genButton.setOutlineThickness(2.f);

    // Set up reset button
    sf::FloatRect resetTextBounds = reset.getGlobalBounds();    
    resetButton.setSize(sf::Vector2f(resetTextBounds.size.x + padding * 2, resetTextBounds.size.y + padding * 2));
    resetButton.setOrigin(resetButton.getSize() / 2.f);
    resetButton.setPosition(reset.getPosition());
    resetButton.setFillColor(sf::Color(200, 200, 200, 100));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(2.f);

    window.draw(reset);
    window.draw(generate);
    window.draw(genButton);
    window.draw(resetButton);
}

void SFML::drawHeader(sf::RenderWindow& window, sf::Font& font, sf::Text& header)
{
    // Set up header
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

    window.draw(header);
}

void SFML::highlightCell(sf::RenderWindow& window, int row, int col, const float& gridStartX, const float& gridStartY, const float& cellSize)
{
    sf::RectangleShape highlight(sf::Vector2f(cellSize * 2, cellSize * 2));
    highlight.setPosition(sf::Vector2f(gridStartX + col * cellSize * 2, gridStartY + row * cellSize * 2));
    highlight.setFillColor(sf::Color(0, 255, 0, 100));
    window.draw(highlight);
}

// Helper functions for event loop
sf::RectangleShape SFML::getGenerateButton() const 
{
    return genButton;
}

sf::RectangleShape SFML::getResetButton() const 
{
    return resetButton;
}