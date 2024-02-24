#include <iostream>
#include <vector>

class SquareCatanBoard {
public:
    SquareCatanBoard() {
        // Initialize the board with the specified row sizes
        board = {
            {true},
            {true, true, true},
            {true, true, true, true, true},
            {true, true, true},
            {true}
        };
    }

    void displayBoard() const {
        std::cout << "Custom Square Catan Board Layout:\n";
        // Calculate the maximum width for proper alignment
        int maxWidth = board[2].size(); // The widest row
        for (const auto& row : board) {
            int spaces = (maxWidth - row.size()) / 2; // Calculate leading spaces for alignment
            std::cout << std::string(spaces * 6, ' '); // 6 spaces per tile for alignment
            for (const auto& hasTile : row) {
                std::cout << (hasTile ? "[Tile] " : "       "); // Display [Tile] or space
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<bool>> board;
};

int main() {
    SquareCatanBoard catanBoard;
    catanBoard.displayBoard();
    return 0;
}
