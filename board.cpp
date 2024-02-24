#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <tuple>
#include <iomanip> // For std::setw
#include <string>

class SquareCatanBoard {
public:
    SquareCatanBoard() {
        std::vector<std::string> resources = {"Wool", "Wood", "Brick", "Grain", "Ore", "Wool", "Grain", "Ore", "Brick", "Wood", "Wool", "Grain", "Ore", "Wood", "Brick", "Grain", "Ore", "Wool"};
        resources.insert(resources.begin() + 9, "Desert"); // Insert "Desert" in the center

        std::vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};
        std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(std::random_device{}()));
        numbers.insert(numbers.begin() + 9, 0); // Insert 0 for the desert

        std::vector<int> layout = {3, 4, 5, 4, 3};
        initializeBoard(layout, resources, numbers);
    }

    void addHouse(int row, int col) {
        if (isValidPosition(row, col)) {
            std::get<3>(board[row][col]) += 1; // Increment house count
        }
    }

    void addRoad(int row, int col) {
        if (isValidPosition(row, col)) {
            std::get<4>(board[row][col]) += 1; // Increment road count
        }
    }

    void displayBoard() const {
        std::cout << "Catan Board Layout with Houses and Roads:\n\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                std::string resource = std::get<1>(tile);
                int number = std::get<2>(tile);
                int houses = std::get<3>(tile);
                int roads = std::get<4>(tile);
                std::cout << std::setw(8) << resource 
                          << " (" << number << ") "
                          << " H:" << houses << " R:" << roads << "  ";
            }
            std::cout << "\n\n";
        }
    }

private:
    // Board structure adjusted to store counts of houses and roads instead of vectors
    std::vector<std::vector<std::tuple<bool, std::string, int, int, int>>> board;

    void initializeBoard(const std::vector<int>& layout, const std::vector<std::string>& resources, const std::vector<int>& numbers) {
        int resourceIndex = 0, numberIndex = 0;
        for (int i = 0; i < layout.size(); ++i) {
            std::vector<std::tuple<bool, std::string, int, int, int>> row;
            for (int j = 0; j < layout[i]; ++j) {
                std::string resource = resources[resourceIndex++];
                int number = numbers[numberIndex++];
                row.push_back({true, resource, number, 0, 0}); // Initialize houses and roads as 0
            }
            board.push_back(row);
        }
    }

    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < board.size() && col >= 0 && col < board[row].size() && std::get<0>(board[row][col]);
    }
};

int main() {
    SquareCatanBoard catanBoard;
    // Example of adding houses and roads
    catanBoard.addHouse(2, 2); // Add a house to the center tile (Desert)
    catanBoard.addRoad(1, 1); // Add a road to a nearby tile

    catanBoard.displayBoard();
    return 0;
}
