#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <map>
#include <string>

struct Player {
    std::string name;
    int position; 
    std::map<int, std::string> resources;
};


int rollDice() {
    return (rand() % 6 + 1) + (rand() % 6 + 1); 
}

int main() {
    srand(static_cast<unsigned int>(time(0))); 
    Player player = {"Player1", 0, {{4, "Food"}, {6, "Wood"}, {8, "Ore"}}};
    int diceRoll = rollDice();
    std::cout << "Dice rolled: " << diceRoll << std::endl;
    if (player.resources.find(diceRoll) != player.resources.end()) {
        std::string resource = player.resources[diceRoll];
        std::cout << player.name << " rolled a " << diceRoll << "! You receive " << resource << "." << std::endl;
    } else {
        std::cout << "No matching resources for this position." << std::endl;
    }

    return 0;
}
