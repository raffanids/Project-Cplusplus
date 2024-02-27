#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Resource class remains unchanged
class Bank {
public:
    map<string, int> resources;

    Bank() {
        resources["wood"] = 19;
        resources["wool"] = 19;
        resources["brick"] = 19;
        resources["grain"] = 19;
        resources["ore"] = 19;
    }

    bool tradeWithPlayer(string offerResource, int offerAmount, string requestResource) {
        // Check if the bank has enough of the requested resource
        if (resources[requestResource] < 1) {
            cout << "Bank does not have enough " << requestResource << "." << endl;
            return false;
        }
        // Check if the offer amount is correct
        if (offerAmount != 4) {
            cout << "Trade failed. You need to offer 4 resources of the same type." << endl;
            return false;
        }

        // Perform the trade
        resources[offerResource] += offerAmount;
        resources[requestResource] -= 1;
        cout << "Trade successful. Traded 4 " << offerResource << " for 1 " << requestResource << "." << endl;
        return true;
    }
};

class Player {
public:
    string name;
    Resource resources;

    Player(string name) : name(name) {
        resources["wood"] = 0;
        resources["wool"] = 0;
        resources["brick"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

     void tradeWithBank(Bank& bank, string offerResource, string requestResource) {
        if (resources[offerResource] < 4) {
            cout << name << " does not have enough " << offerResource << " to trade with the bank." << endl;
            return;
        }

        if (bank.tradeWithPlayer(offerResource, 4, requestResource)) {
            resources[offerResource] -= 4;
            resources[requestResource] += 1;
        }
    }

    void printPlayerResources() const {
        cout << name << "'s Resources:" << endl;
        for (const auto& resource : resources) {
            cout << resource.first << ": " << resource.second << endl;
        }
    }
};

    void tradeWith(Player& otherPlayer, const string& giveResource, int giveAmount, const string& getResource, int getAmount) {
        // Check if the current player has enough resources to give
        if (!hasEnoughResources(giveResource, giveAmount)) {
            cout << name << " does not have enough " << giveResource << " to trade." << endl;
            return;
        }

        // Check if the other player has enough resources to give
        if (!otherPlayer.hasEnoughResources(getResource, getAmount)) {
            cout << otherPlayer.name << " does not have enough " << getResource << " to trade." << endl;
            return;
        }

        // Perform the trade
        deductResource(giveResource, giveAmount);
        addResource(getResource, getAmount);
        otherPlayer.deductResource(getResource, getAmount);
        otherPlayer.addResource(giveResource, giveAmount);

        cout << name << " traded " << giveAmount << " " << giveResource << " with "
             << otherPlayer.name << " for " << getAmount << " " << getResource << "." << endl;
    }

    bool hasEnoughResources(const string& resource, int amount) {
        if (resource == "wood") return resources.wood >= amount;
        if (resource == "wool") return resources.wool >= amount;
        if (resource == "brick") return resources.brick >= amount;
        if (resource == "grain") return resources.grain >= amount;
        if (resource == "ore") return resources.ore >= amount;
        return false;
    }

    void deductResource(const string& resource, int amount) {
        if (resource == "wood") resources.wood -= amount;
        if (resource == "wool") resources.wool -= amount;
        if (resource == "brick") resources.brick -= amount;
        if (resource == "grain") resources.grain -= amount;
        if (resource == "ore") resources.ore -= amount;
    }

    void addResource(const string& resource, int amount) {
        if (resource == "wood") resources.wood += amount;
        if (resource == "wool") resources.wool += amount;
        if (resource == "brick") resources.brick += amount;
        if (resource == "grain") resources.grain += amount;
        if (resource == "ore") resources.ore += amount;
    }

    void printPlayerResources() const {
        // The same print function
    }
};

int main() {
     Bank bank;
    Player player1("Player 1");

    // Player gets some resources for demonstration purposes
    player1.resources["wood"] = 5; // Assume player has 5 wood

    // Player tries to trade with the bank
    player1.tradeWithBank(bank, "wood", "brick");

    player1.printPlayerResources();
    // Main function setup, demonstration of trade
    Player player1("Player 1");
    Player player2("Player 2");

    // Assuming both players initially have some resources for the sake of demonstration
    player1.resources.wood = 5;
    player2.resources.brick = 5;

    player1.tradeWith(player2, "wood", 2, "brick", 1);

    player1.printPlayerResources();
    player2.printPlayerResources();

    return 0;
}
