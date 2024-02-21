#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ctime>

using namespace std;

class Building {
protected:
    int victoryPoints;
    string owner;

public:
    Building(const string& owner) : owner(owner) {}
    virtual ~Building() {}

    virtual int getVictoryPoints() const = 0;
    const string& getOwner() const { return owner; }
};

class Road : public Building {
public:
    Road(const string& owner) : Building(owner) {
        victoryPoints = 0;
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class Settlement : public Building {
public:
    Settlement(const string& owner) : Building(owner) {
        victoryPoints = 1;
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class City : public Building {
public:
    City(const string& owner) : Building(owner) {
        victoryPoints = 2;
    }

    int getVictoryPoints() const override {
        return victoryPoints;
    }
};

class Resource {
public:
    int wood;
    int grain;
    int brick;
    int ore;
    int sheep;
};

class Player {
private:
    string name;
    map<string, int> resources;
    vector<unique_ptr<Building>> buildings;
    vector<int> specialcard;
    bool blocked;

public:
    Player(const string& playerName) : name(playerName), blocked(false) {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["sheep"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    string getName() const {
        return name;
    }
    
     map<string, int>& getResources() {
        return resources;
    }

    void initializeResources() {
        resources["wood"] = 0;
        resources["brick"] = 0;
        resources["sheep"] = 0;
        resources["grain"] = 0;
        resources["ore"] = 0;
    }

    vector<int> getSpecialCard() const {
        return specialcard;
    }

    bool isBlocked() const {
        return blocked;
    }

    void setBlocked(bool isBlocked) { // เพิ่มฟังก์ชัน setBlocked เพื่อกำหนดค่าตัวแปร blocked
        blocked = isBlocked;
    }

    void drawSpecialCard() {
        vector<int> cards;
        for (int i = 1; i <= 20; ++i) {
            cards.push_back(i);
        }
        int index = rand() % cards.size();
        int card = cards[index];
        cards.erase(cards.begin() + index);

        if (card % 2 == 0) specialcard.push_back(1); //steal
        else specialcard.push_back(2); //block
    }

    void stealResource(Player& targetPlayer, map<string, int>& targetResources, const string& resourceType, int amount) {
        if (targetResources["wood"] >= amount && resourceType == "wood") {
            targetResources["wood"] -= amount;
            resources["wood"] += amount;
        } else if (targetResources["grain"] >= amount && resourceType == "grain") {
            targetResources["grain"] -= amount;
            resources["grain"] += amount;
        } else if (targetResources["brick"] >= amount && resourceType == "brick") {
            targetResources["brick"] -= amount;
            resources["brick"] += amount;
        } else if (targetResources["ore"] >= amount && resourceType == "ore") {
            targetResources["ore"] -= amount;
            resources["ore"] += amount;
        } else if (targetResources["sheep"] >= amount && resourceType == "sheep") {
            targetResources["sheep"] -= amount;
            resources["sheep"] += amount;
        } else {
            cout << "Cannot steal the specified resource from the target. Only stole what was available." << endl;
        }
    }


    void displayStatus() {
        cout << "Player: " << name << "\nResources:\n";
        for (const auto& resource : resources) {
            cout << resource.first << ": " << resource.second << "\n";
        }
        cout << "Victory Points: " << calculateVictoryPoints() << "\n\n";
    }

    int calculateVictoryPoints() {
        int points = 0;
        for (const auto& building : buildings) {
            points += building->getVictoryPoints();
        }
        return points;
    }

    bool buildRoad() {
        if (resources["wood"] >= 1 && resources["brick"] >= 1) {
            buildings.push_back(make_unique<Road>(name));
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            return true;
        }
        return false;
    }

    bool buildSettlement() {
        if (resources["wood"] >= 1 && resources["brick"] >= 1 && resources["sheep"] >= 1 && resources["grain"] >= 1) {
            buildings.push_back(make_unique<Settlement>(name));
            resources["wood"] -= 1;
            resources["brick"] -= 1;
            resources["sheep"] -= 1;
            resources["grain"] -= 1;
            return true;
        }
        return false;
    }

    bool buildCity() {
        if (resources["grain"] >= 2 && resources["ore"] >= 3) {
            buildings.push_back(make_unique<City>(name));
            resources["grain"] -= 2;
            resources["ore"] -= 3;
            return true;
        }
        return false;
    }
};

void shufflePlayers(vector<Player*>& players) {
    random_device rd;
    mt19937 g(rd());
    shuffle(players.begin(), players.end(), g);
}

void printTurnOrder(const vector<Player*>& players) {
    cout << "Turn order for this round:" << endl;
    for (size_t i = 0; i < players.size(); ++i) {
        cout << i + 1 << ". " << players[i]->getName() << endl;
    }
    cout << endl;
}

void playerSteal(vector<Player*>& players, int i) {
    string player1, player2, resource;
    int amount;

    player1 = players[i]->getName();

    cout << "Player to steal from: ";
    cin >> player2;

    cout << "Enter the type of resource you want to steal (wood, grain, brick, ore, sheep): ";
    cin >> resource;

    cout << "Enter the number of resources you want to steal: ";
    cin >> amount;

    Player* targetPlayer = nullptr;
    for (auto& player : players) {
        if (player->getName() == player2) {
            targetPlayer = player;
            break;
        }
    }

    if (targetPlayer) {
        players[i]->stealResource(*targetPlayer, targetPlayer->getResources(), resource, amount);
    } else {
        cout << "Invalid player name. Cannot perform the steal action." << endl;
    }

    for (const auto& player : players) {
        player->displayStatus();
    }
}

bool isBlocked(vector<Player*>& players) {
    string name;
    cout << "Player to block: ";
    cin >> name;
    for (auto& player : players) {
        if (player->getName() == name) {
            player->setBlocked(true);
            return true;
        }
    }
    return false;
}

void checkSpecialCard(vector<Player*>& players) {
    for (auto& player : players) {
        if (player->isBlocked()) {
            cout << player->getName() << " is blocked and cannot play this turn." << endl;
            continue;
        }
        for (int card : player->getSpecialCard()) {
            if (card == 1) {
                cout << player->getName() << " You have a special card." << endl;
                cout << "Do you want to use it? (yes/no): ";
                string useCard;
                cin >> useCard;
                if (useCard == "yes") {
                    playerSteal(players, distance(players.begin(), find(players.begin(), players.end(), player)));
                    cout << "You used a special card! You can take another turn." << endl;
                }
            }
            if (card == 2) {
                cout << player->getName() << " You have a special card." << endl;
                cout << "Do you want to use it? (yes/no): ";
                string useCard;
                cin >> useCard;
                if (useCard == "yes") {
                    isBlocked(players);
                    cout << "You used a special card! You can take another turn." << endl;
                }
            }
        }
    }
}

int main() {
    srand(time(0));
    vector<Player*> players;
    Player p1("p1");
    Player p2("p2");
    Player p3("p3");
    Player p4("p4");

    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);
    players.push_back(&p4);

    for (auto& player : players) {
        player->drawSpecialCard();
    }

    for (const auto& player : players) {
        cout << player->getName() << " special cards: ";
        for (int card : player->getSpecialCard()) {
            cout << card << " ";
        }
        cout << endl;
    }

    for (auto& player : players) {
        player->initializeResources();
    }

    for (int i = 0; i < 4; i++) {
        for (auto& player : players) {
            player->setBlocked(false);
        }
        shufflePlayers(players);
        printTurnOrder(players);
        checkSpecialCard(players);
    }

    return 0;
}
