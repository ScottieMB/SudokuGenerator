# 🧠 **Sudoku Visualizer**
A dynamic C++ Sudoku board generator and visualizer using SFML, showcasing real-time backtracking to construct a valid 9×9 Sudoku puzzle.

## 🛠️ Tech Stack
Language: C++
Graphics: SFML (Simple and Fast Multimedia Library)
Algorithm: Backtracking + Fisher-Yates Shuffle

## 📦 Build & Run
### Prerequisites
SFML 3.0+ installed on your system
C++17 or later compatible compiler (e.g. g++ or clang++)

### Build Instructions
```
g++ -std=c++17 -o sudoku Board.cpp sfml.cpp main.cpp -lsfml-graphics -lsfml-window -lsfml-system
./sudoku
```

## 💡 Algorithm Overview
The board is filled in row-major order. For each cell:
- Shuffle a list of numbers [1-9] using the Fisher-Yates algorithm.
- Try inserting each number into the cell.
- If valid according to Sudoku rules:
- Insert it and recurse to the next cell.
- Visually update the grid with a brief delay.
- If no valid number fits, backtrack by resetting the cell to 0.

## 🚀 Future Improvements
- Add puzzle-solving mode
- Let users input their own boards
- Add difficulty levels for puzzle generation
- Animate invalid moves in a solver mode
