#include "Board.h"
#include "SFML.h"

// populate board with 0s
Board::Board() : board(9, std::vector<int>(9, 0))
{

}

// construct valid sudoku board
bool Board::constructBoard(int index, sf::RenderWindow& window, sf::Font& font, sf::Text& header, const float& gridStartX, const float& gridStartY, const float& cellSize, const float& gridSize, const float& cellCenter)
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

            window.clear(sf::Color(240, 240, 240));
            drawHeader(window, font, header);
            drawButtons(window, font);
            drawGrid(window, gridStartX, gridStartY, gridSize, cellSize, cellCenter);
            drawCell(window, font, gridStartX, gridStartY, cellSize);
            window.display();
            sf::sleep(sf::milliseconds(50)); 

            if (constructBoard(index + 1, window, font, header, gridStartX, gridStartY, cellSize, gridSize, cellCenter))
            {
                return true;
            }
            // backtrack
            board[row][col] = 0;

            window.clear(sf::Color(240, 240, 240));
            drawHeader(window, font, header);
            drawButtons(window, font);
            drawGrid(window, gridStartX, gridStartY, gridSize, cellSize, cellCenter);
            drawCell(window, font, gridStartX, gridStartY, cellSize);
            window.display();       
            sf::sleep(sf::milliseconds(50));
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

//TODO : MODULARIZE

void Board::drawCell(sf::RenderWindow& window, sf::Font& font, const float& gridStartX, const float& gridStartY, const float& cellSize)
{
    for (int row = 0; row < 9; ++row) 
    {
        for (int col = 0; col < 9; ++col) 
        {
            int value = board[row][col];
            if (value == 0) continue;

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

void Board::drawGrid(sf::RenderWindow& window, const float& gridStartX, const float& gridStartY, const float& gridSize, const float& cellSize, const float& cellCenter)
{   
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

    window.draw(rows);
    window.draw(cols);
}

void Board::drawButtons(sf::RenderWindow& window, sf::Font& font)
{
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

    window.draw(reset);
    window.draw(generate);
    window.draw(genButton);
    window.draw(resetButton);
}

void Board::drawHeader(sf::RenderWindow& window, sf::Font& font, sf::Text& header)
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