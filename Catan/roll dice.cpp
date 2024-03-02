#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <tuple>
#include <iomanip>
#include <string>
#include <ctime>
#include <map>

class Player {
    std::map<std::string, int> resources;
    int victoryPoints;

public:
    Player() : victoryPoints(0) {
        resources = {{"Wool", 0}, {"Wood", 0}, {"Brick", 0}, {"Grain", 0}, {"Ore", 0}};
    }

    void addResource(std::string resource, int amount) {
        resources[resource] += amount;
    }

    void displayResources() const {
        std::cout << "Player Resources:\n";
        for (const auto& pair : resources) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
    }
};

class SquareCatanBoard {
    std::vector<std::vector<std::tuple<bool, std::string, int, int, int>>> board;
    std::vector<Player> players;
    int currentPlayerIndex;

public:
    SquareCatanBoard(int numPlayers) : currentPlayerIndex(0) {
        players = std::vector<Player>(numPlayers, Player());
        initializeBoard();
    }

    void initializeBoard() {
        std::vector<std::string> resources = {"Wool", "Wood", "Brick", "Grain", "Ore", "Wool", "Grain", "Ore", "Brick", "Wood", "Wool", "Grain", "Ore", "Wood", "Brick", "Grain", "Ore", "Wool"};
        resources.insert(resources.begin() + 9, "Desert"); // Insert "Desert" in the center

        std::vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};
        std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));
        numbers.insert(numbers.begin() + 9, 0); // Insert 0 for the desert

        std::vector<int> layout = {3, 4, 5, 4, 3};
        int resourceIndex = 0, numberIndex = 0;
        for (int rowSize : layout) {
            std::vector<std::tuple<bool, std::string, int, int, int>> row;
            for (int j = 0; j < rowSize; ++j) {
                row.emplace_back(true, resources[resourceIndex++], numbers[numberIndex++], 0, 0);
            }
            board.push_back(row);
        }
    }

    void displayBoard() const {
        std::cout << "Catan Board Layout:\n\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                std::string resource = std::get<1>(tile);
                int number = std::get<2>(tile);
                std::cout << std::setw(8) << resource 
                          << " (" << number << ") "
                          << " Houses: " << std::get<3>(tile) 
                          << " Roads: " << std::get<4>(tile) << "  ";
            }
            std::cout << "\n\n";
        }
    }

    int rollDice() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 6);
        return dis(gen) + dis(gen); // Sum of rolling two dice
    }

    void produceResources(int roll) {
        std::cout << "Dice Roll: " << roll << "\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                if (std::get<2>(tile) == roll && std::get<1>(tile) != "Desert") {
                    int houses = std::get<3>(tile);
                    std::string resource = std::get<1>(tile);
                    players[currentPlayerIndex].addResource(resource, houses);
                    std::cout << houses << " " << resource << "(s) produced for Player " << currentPlayerIndex + 1 << "\n";
                }
            }
        }
        players[currentPlayerIndex].displayResources();
    }

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        std::cout << "\nPlayer " << currentPlayerIndex + 1 << "'s turn:\n";
        int roll = rollDice();
        produceResources(roll);
    }
};

int main() {
    SquareCatanBoard catanBoard(2); // Simulate a game with 2 players
    catanBoard.displayBoard();

    // Simulate a few rounds of the game
    for (int i = 0; i < 10; ++i) {
        catanBoard.nextTurn();
    }

    return 0;
}
