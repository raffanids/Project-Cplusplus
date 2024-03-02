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

    bool tradeWithPlayer(Resource& playerResources, const string& offerResource, int offerAmount, const string& requestResource) {
        if (offerAmount != 4 || playerResources.resourceCount[offerResource] < offerAmount || resources.resourceCount[requestResource] < 1) {
            cout << "Trade failed." << endl;
            return false;
        }
        playerResources.deductResource(offerResource, offerAmount);
        playerResources.addResource(requestResource, 1);
        resources.addResource(offerResource, offerAmount);
        resources.deductResource(requestResource, 1);
        cout << "Trade successful: 4 " << offerResource << " for 1 " << requestResource << endl;
        return true;
    }
};

class Player {
public:
    string name;
    Resource resources;

    Player(string name) : name(name) {}

    void tradeWithBank(Bank& bank, const string& offerResource, const string& requestResource) {
        bank.tradeWithPlayer(resources, offerResource, 4, requestResource);
    }

    void printPlayerResources() const {
        cout << name << "'s resources:" << endl;
        resources.printResources();
    }
};

int main() {
    Bank bank;
    Player player1("Player 1");

    // Example of player trading with the bank
    player1.resources.addResource("wood", 5); // Player has 5 wood initially
    cout << "Before trading with the bank:" << endl;
    player1.printPlayerResources();

    player1.tradeWithBank(bank, "wood", "brick"); // Player trades 4 wood for 1 brick

    cout << "After trading with the bank:" << endl;
    player1.printPlayerResources();

    return 0;
}
