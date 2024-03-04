#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Resource {
public:
    map<string, int> resourceCount;

    Resource() {
        resourceCount["wood"] = 0;
        resourceCount["wool"] = 0;
        resourceCount["brick"] = 0;
        resourceCount["grain"] = 0;
        resourceCount["ore"] = 0;
    }

    void addResource(const string& resource, int amount) {
        resourceCount[resource] += amount;
    }

    bool deductResource(const string& resource, int amount) {
        if (resourceCount[resource] >= amount) {
            resourceCount[resource] -= amount;
            return true;
        }
        return false;
    }

    void printResources() const {
        for (const auto& res : resourceCount) {
            cout << res.first << ": " << res.second << endl;
        }
    }
};

class Bank {
public:
    Resource resources;

    Bank() {
        resources.addResource("wood", 19);
        resources.addResource("wool", 19);
        resources.addResource("brick", 19);
        resources.addResource("grain", 19);
        resources.addResource("ore", 19);
    }

    // Updated to handle variable trade ratios and amounts
    bool tradeWithPlayer(Resource& playerResources, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (playerResources.resourceCount[offerResource] >= offerAmount && resources.resourceCount[requestResource] >= requestAmount) {
            playerResources.deductResource(offerResource, offerAmount);
            playerResources.addResource(requestResource, requestAmount);
            resources.addResource(offerResource, offerAmount);
            resources.deductResource(requestResource, requestAmount);
            cout << "Trade successful: " << offerAmount << " " << offerResource << " for " << requestAmount << " " << requestResource << endl;
            return true;
        } else {
            cout << "Trade failed due to insufficient resources." << endl;
            return false;
        }
    }
};

class Player {
public:
    string name;
    Resource resources;

    Player(string name) : name(name) {}

    // Directly handles trading with the bank with variable trade ratios and amounts
    bool tradeWithBank(Bank& bank, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        return bank.tradeWithPlayer(resources, offerResource, offerAmount, requestResource, requestAmount);
    }

    // Enables direct resource trading between players
    bool tradeWithPlayer(Player& otherPlayer, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (resources.resourceCount[offerResource] >= offerAmount && otherPlayer.resources.resourceCount[requestResource] >= requestAmount) {
            resources.deductResource(offerResource, offerAmount);
            otherPlayer.resources.addResource(offerResource, offerAmount);
            otherPlayer.resources.deductResource(requestResource, requestAmount);
            resources.addResource(requestResource, requestAmount);
            cout << "Trade successful between " << name << " and " << otherPlayer.name << endl;
            return true;
        } else {
            cout << "Trade failed due to insufficient resources." << endl;
            return false;
        }
    }

    void printPlayerResources() const {
        cout << name << "'s resources:" << endl;
        resources.printResources();
    }
};

int main() {
    Bank bank;
    Player player1("Player 1");
    Player player2("Player 2"); // Added for demonstration of player-to-player trading

    // Example of player trading with the bank
    player1.resources.addResource("wood", 5); // Player has 5 wood initially
    cout << "Before trading with the bank:" << endl;
    player1.printPlayerResources();

    player1.tradeWithBank(bank, "wood", 4, "brick", 1); // Adjusted to use the updated tradeWithBank method

    cout << "After trading with the bank:" << endl;
    player1.printPlayerResources();

    // Example of player-to-player trading
    player2.resources.addResource("grain", 3); // Player 2 has 3 grain initially
    cout << "\nBefore player-to-player trading:" << endl;
    player1.printPlayerResources();
    player2.printPlayerResources();

    player1.tradeWithPlayer(player2, "wood", 2, "grain", 2); // Player 1 trades 2 wood for 2 grain with Player 2

    cout << "\nAfter player-to-player trading:" << endl;
    player1.printPlayerResources();
    player2.printPlayerResources();

    return 0;
}
