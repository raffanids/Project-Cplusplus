#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <ctime>
#include <tuple>
#include <iomanip>

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

class Bank {
    public:
        map<string, int> resources;
        int roads;
        int settlements;
        int cities;
        int blockCards;
        int stealCards;

    Bank() {
        resources["wood"] = 19;
        resources["brick"] = 19;
        resources["sheep"] = 19;
        resources["grain"] = 19;
        resources["ore"] = 19;

        roads = 15;
        settlements = 5;
        cities = 4;

        blockCards = 5;
        stealCards = 5;
    }
};

class Player {
private:
    string name;
    map<string, int> resources;
    vector<unique_ptr<Building>> buildings;
    vector<string> specialcard;
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

    vector<string> getSpecialCard() const {
        return specialcard;
    }

    bool isBlocked() const {
        return blocked;
    }

    void setBlocked(bool isBlocked) {
        blocked = isBlocked;
    }
    
    void addResource(string resource) {
        if (resource == "Wood") {
            resources["wood"] += 1;
        } else if (resource == "Grain") {
            resources["grain"] += 1;
        } else if (resource == "Brick") {
            resources["brick"] += 1;
        } else if (resource == "Ore") {
            resources["ore"] += 1;
        } else if (resource == "Sheep") {
            resources["sheep"] += 1;
        } else {
            cout << "?" << endl;
        }
    }
    
    void drawSpecialCard(Bank& bank) {
        int card = rand() % 2 + 1;
        if (card == 1) {
            if (bank.stealCards > 0) {
                specialcard.push_back("stealcard");
                bank.stealCards--;
                cout << "You drew a special card (steal). You now have " << bank.stealCards << " steal card(s) left." << endl;
            } else {
                cout << "No steal cards left in the bank." << endl;
            }
                } else if (card == 2) {
                    if (bank.blockCards > 0) {
                    specialcard.push_back("blockcard"); 
                    bank.blockCards--;
                    cout << "You drew a special card (block). You now have " << bank.blockCards << " block card(s) left." << endl;
                } else {
                    cout << "No block cards left in the bank." << endl;
                }
            }
    }

    void stealResource(Player& targetPlayer, map<string, int>& targetResources, const string& resourceType, int amount = 1) {
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
        cout << "Player " << name << " Resources :\n";
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

class SquareCatanBoard {
    vector<vector<tuple<bool, string, int, int, int>>> board;
    vector<Player> players;
    int currentPlayerIndex;

    public:
    SquareCatanBoard(int numPlayers) : currentPlayerIndex(0) {
        initializeBoard();
        players.reserve(numPlayers);
        for (int i = 0; i < numPlayers; ++i) {
            players.emplace_back("Player " + to_string(i + 1));
        }
    }
    
    void initializeBoard() {
        vector<string> resources = {"Sheep", "Wood", "Brick", "Grain", "Ore", "Sheep", "Grain", "Ore", "Brick", "Wood", "Sheep", "Grain", "Ore", "Wood", "Brick", "Grain", "Ore", "Sheep"};
        resources.insert(resources.begin() + 9, "Desert");

        vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};
        shuffle(numbers.begin(), numbers.end(),default_random_engine(static_cast<unsigned>(std::time(nullptr))));
        numbers.insert(numbers.begin() + 9, 0);

        vector<int> layout = {3, 4, 5, 4, 3};
        int resourceIndex = 0, numberIndex = 0;
        for (int rowSize : layout) {
            vector<tuple<bool, string, int, int, int>> row;
            for (int j = 0; j < rowSize; ++j) {
                row.emplace_back(true, resources[resourceIndex++], numbers[numberIndex++], 0, 0);
            }
            board.push_back(row);
        }
    }

    void displayBoard() const {
        cout << "Catan Board Layout:\n\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                string resource = get<1>(tile);
                int number = get<2>(tile);
                cout << setw(8) << resource
                          << " (" << number << ") "
                          << " Houses: " << get<3>(tile)
                          << " Roads: " << get<4>(tile) << "  ";
            }
            cout << "\n\n";
        }
    }

    int rollDice() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 6);
        return dis(gen) + dis(gen);
    }

    void produceResources(vector<Player*>& players, int roll, Player* a) {
        cout << "Dice Roll: " << roll << "\n";
        for (const auto& row : board) {
            for (const auto& tile : row) {
                if (get<2>(tile) == roll && get<1>(tile) != "Desert") {
                    int houses = 1;
                    string resource = get<1>(tile);
                    a->addResource(resource);
                    cout << a->getName() << " ";
                    cout << houses << " " << resource << "(s) produced for Player " << a->getName() << "\n";
                }
            }
        }
        a->displayStatus();
    }


    void nextTurn(Player* a,vector<Player*>& players) {
        cout << "\nPlayer " << a->getName() << "'s turn:\n";
        int roll = rollDice();
        produceResources(players, roll, a);
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

void drawspcard(Player* a,vector<Player*>& players,Bank& bank){
    int luckdraw = rand()%10+1;
    string ans;
    cout << a->getName() << " Want to draw SpecialCard?(yes/no) : ";
    cin >> ans;
    if(ans == "yes"){
        if(true){
        a->drawSpecialCard(bank);
        }else return; 
    if(ans == "no") return;
    }
}

void checkBlocked(Player* a, vector<Player*>& players){
    if (a->isBlocked()) {
        cout << a->getName() << " is blocked and cannot play this turn." << endl;
    }
}

void checkSpecialCard(Player* a, vector<Player*>& players, Bank& bank) { 
    vector<string> specialcards = a->getSpecialCard();
    string useCard;
    string nameCard;
    for (const string& card : specialcards) {
        if (card == "stealcard" && card == "blockcard") {
            cout << a->getName() << " You have a special card." << endl;
            cout << "Do you want to use it? (yes/no): ";
            cin >> useCard;
            if (useCard == "yes") {
                cout << "Use Steal (1) or block (2) : ";
                cin >> nameCard;
                if (card == "stealcard") {
                    playerSteal(players, distance(players.begin(), find(players.begin(), players.end(), a)));
                } else if (card == "blockcard") {
                    isBlocked(players);
                    cout << "You used a special card! You can take another turn." << endl;
                }
            else{ break; }
            }
        }
        if (card == "stealcard" || card == "blockcard") {
            cout << a->getName() << " You have a special card." << endl;
            cout << "Do you want to use it? (yes/no): ";
            cin >> useCard;

            if (useCard == "yes") {
                if (card == "stealcard") {
                    playerSteal(players, distance(players.begin(), find(players.begin(), players.end(), a)));
                } else if (card == "blockcard") {
                    isBlocked(players);
                    cout << "You used a special card! You can take another turn." << endl;
                }
            else{ break; }
            }
        }
    }
}

void initializeGame(vector<Player*>& players) {
    for (auto& player : players) {
        player->initializeResources();
    }
}

void starTurn(vector<Player*>& players){
    for (auto& player : players) {
        player->setBlocked(false);
    }
    shufflePlayers(players);
    printTurnOrder(players);
}

int main() {
    srand(time(0));
    Bank bank;
    vector<Player*> players;
    
    Player p1("p1");
    Player p2("p2");
    Player p3("p3");
    Player p4("p4");

    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);
    players.push_back(&p4);

    SquareCatanBoard catanBoard(4);
    initializeGame(players);
    
    for(int i = 0; i < 10;i++){
        catanBoard.displayBoard();
        starTurn(players);
    for (auto& player : players){
        if(player->isBlocked()) {
            checkBlocked(player,players);
            continue;
        }
        catanBoard.nextTurn(player,players);
        drawspcard(player, players, bank);
        checkSpecialCard(player, players, bank);
    }
    }
    return 0;
}
