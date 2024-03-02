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
    map<string, int> resourceCount;
    
    void addResource(const string& resource, int amount) {
        if(resourceCount.find(resource) != resourceCount.end()){
            resourceCount[resource] += amount;
        }
    }

    bool deductResource(const string& resource, int amount) {
        if (resourceCount[resource] >= amount) {
            resourceCount[resource] -= amount;
            return true;
        }
        return false;
    }

    void printResources() const {
        for (const auto& pair : resourceCount) {
            cout << pair.first << ": " << pair.second << "\n";
        }
    }
};

class Bank {
public:
    Resource resources;
    int roads;
    int settlements;
    int cities;
    int blockCards;
    int stealCards;

    Bank() {
        resources.addResource("wood", 19);
        resources.addResource("wool", 19);
        resources.addResource("brick", 19);
        resources.addResource("grain", 19);
        resources.addResource("ore", 19);

        roads = 15;
        settlements = 5;
        cities = 4;

        blockCards = 5;
        stealCards = 5;
    }

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
    
    int getResourceCount(const string& resource) const {
        return resources.resourceCount.at(resource);
    }
};

class Player {
private:
    string name;
    Resource resources;
    vector<unique_ptr<Building>> buildings;
    vector<string> specialCards;
    bool blocked;

public:
    Player(const string& playerName) : name(playerName), resources(), blocked(false) {}

    string getName() const {
        return name;
    }

    Resource& getResources() {
        return resources;
    }

    vector<string> getSpecialCard() const {
        return specialCards;
    }

    bool isBlocked() const {
        return blocked;
    }

    void setBlocked(bool isBlocked) {
        blocked = isBlocked;
    }
    
bool addResource(const string& resource, int amount) {
    if (resources.resourceCount[resource] + amount >= 0) {
        resources.addResource(resource, amount);
        return true;
    }
    return false;
}
    
    void displayResources() const {
        cout << "Player Resources for " << name << ":\n";
        resources.printResources();
    }
    
    void printPlayerResources() const {
    cout << name << "'s resources:" << endl;
    resources.printResources();
    }
    
    void initializeResources() {
        resources.addResource("wood", 0);
        resources.addResource("brick", 0);
        resources.addResource("sheep", 0);
        resources.addResource("grain", 0);
        resources.addResource("ore", 0);
    }

    bool tradeWithBank(Bank& bank, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        return bank.tradeWithPlayer(resources, offerResource, offerAmount, requestResource, requestAmount);
    }
    
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

    void drawSpecialCard(Bank& bank) {
        int card = rand() % 2 + 1;
        if (card == 1) {
            if (bank.stealCards > 0) {
                specialCards.push_back("stealcard");
                bank.stealCards--;
                cout << "You drew a special card (steal). You now have " << bank.stealCards << " steal card(s) left." << endl;
            }
            else {
                cout << "No steal cards left in the bank." << endl;
            }
        }
        else if (card == 2) {
            if (bank.blockCards > 0) {
                specialCards.push_back("blockcard");
                bank.blockCards--;
                cout << "You drew a special card (block). You now have " << bank.blockCards << " block card(s) left." << endl;
            }
            else {
                cout << "No block cards left in the bank." << endl;
            }
        }
    }

    void stealResource(Player& targetPlayer, const string& resourceType, int amount = 1) {
        if (!targetPlayer.isBlocked() && targetPlayer.getResources().resourceCount.count(resourceType) > 0 && targetPlayer.getResources().resourceCount[resourceType] >= amount) {
            targetPlayer.getResources().resourceCount[resourceType] -= amount;
            resources.addResource(resourceType, amount);
        }
        else {
            cout << "Cannot steal the specified resource (" << resourceType << ") from the target." << endl;
        }
    }

    void displayStatus() {
        cout << "Player: " << name << "\nResources:\n";
        resources.printResources();
        cout << "Victory Points: " << calculateVictoryPoints() << "\n\n";
    }

    int calculateVictoryPoints() const {
        int points = 0;
        for (const auto& building : buildings) {
            points += building->getVictoryPoints();
        }
        return points;
    }

    bool buildRoad() {
        if (resources.resourceCount["wood"] >= 1 && resources.resourceCount["brick"] >= 1) {
            buildings.push_back(make_unique<Road>(name));
            resources.deductResource("wood", 1);
            resources.deductResource("brick", 1);
            return true;
        }
        return false;
    }

    bool buildSettlement() {
        if (resources.resourceCount["wood"] >= 1 && resources.resourceCount["brick"] >= 1 &&
            resources.resourceCount["wool"] >= 1 && resources.resourceCount["grain"] >= 1) {
            buildings.push_back(make_unique<Settlement>(name));
            resources.deductResource("wood", 1);
            resources.deductResource("brick", 1);
            resources.deductResource("wool", 1);
            resources.deductResource("grain", 1);
            return true;
        }
        return false;
    }

    bool buildCity() {
        if (resources.resourceCount["grain"] >= 2 && resources.resourceCount["ore"] >= 3) {
            buildings.push_back(make_unique<City>(name));
            resources.deductResource("grain", 2);
            resources.deductResource("ore", 3);
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
        vector<string> resources = {"Wool", "Wood", "Brick", "Grain", "Ore", "Wool", "Grain", "Ore", "Brick", "Wood", "Wool", "Grain", "Ore", "Wood", "Brick", "Grain", "Ore", "Wool"};
        resources.insert(resources.begin() + 9, "Desert");

        vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};
        shuffle(numbers.begin(), numbers.end(), default_random_engine(static_cast<unsigned>(time(nullptr))));
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
        return dis(gen) + dis(gen); // Sum of rolling two dice
    }

void produceResources(int roll) {
    cout << "Dice Roll: " << roll << "\n";
    for (auto& row : board) {
        for (auto& tile : row) {
            if (get<2>(tile) == roll && get<1>(tile) != "Desert") {
                int houses = 1;
                string resource = get<1>(tile);
                if (players[currentPlayerIndex].addResource(resource, houses)) {
                    cout << houses << " " << resource << "(s) produced for Player " << currentPlayerIndex + 1 << "\n";                    
                } else {
                    cout << "Player " << currentPlayerIndex + 1 << " has no space for more " << resource << "(s)\n";
                }
            }
        }
    }
    players[currentPlayerIndex].printPlayerResources();
}

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        cout << "\nPlayer " << currentPlayerIndex + 1 << "'s turn:\n";
        int roll = rollDice();
        produceResources(roll);
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
    string player2, resource;
    int amount = 1;

    cout << "Enter the name of the player to steal from: ";
    cin >> player2;

    cout << "Enter the type of resource you want to steal (wood, grain, brick, ore, wool): ";
    cin >> resource;

    Player* targetPlayer = nullptr;
    for (auto& player : players) {
        if (player->getName() == player2) {
            targetPlayer = player;
            break;
        }
    }

    if (targetPlayer) {
        players[i]->stealResource(*targetPlayer, resource, amount);
    }
    else {
        cout << "Invalid player name. Cannot perform the steal action." << endl;
        return;
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
        if(luckdraw == 9){
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

void checktradebankresource(Player* a, vector<Player*>& players, Bank& bank){
    string trade1;
    string trade2;
    cout << "What do you want to trade? : ";
    cin >> trade2;
    cout << "Trade with? : ";
    cin >> trade1;
    a->tradeWithBank(bank,trade1, 4,trade2, 1);
}

bool checktradeplayer(Player* a,Player* p,string trade1,string trade2,int num1,int num2){
    string check;
    cout << a->getName() << " want to offer " << trade2 << " with " << trade1 << "  " << num2 << " : " << num1 << endl;
    cout << p->getName() << " want to accept this offer? (yes/no) : ";
    cin >> check;
    if(check == "yes"){
        return true;
    }else{
        return false;
    }
}

void checktradeplayerresource(Player* a, vector<Player*>& players, Bank& bank) {
    string playerName, trade1, trade2;
    int num1, num2;

    cout << "Which player do you want to trade with? : ";
    cin >> playerName;

    Player* p = nullptr;
    for (Player* player : players) {
        if (player->getName() == playerName) {
            p = player;
            break;
        }
    }

    if (p == nullptr) {
        cout << "Player not found." << endl;
        return;
    }

    cout << "What do you want to trade away? : ";
    cin >> trade2;

    cout << "How many " << trade2 << " do you want to trade? : ";
    cin >> num2;

    cout << "What do you want in return? : ";
    cin >> trade1;

    cout << "How many " << trade1 << " do you want in return? : ";
    cin >> num1;

    if(checktradeplayer(a, p, trade1, trade2, num1, num2)) {
        a->tradeWithPlayer(*p, trade2, num2, trade1, num1);
    } else {
        cout << "Trade offer declined by " << p << "." << endl;
    }
}

void checktrade(Player* a, vector<Player*>& players, Bank& bank){
    string trade;
    cout << a->getName() << " You want to trading with bank(1) or player(2) : ";
    cin >> trade;
    if(trade == "1"){
        checktradebankresource(a,players,bank);
    }else{
        checktradeplayerresource(a,players,bank);
    }
}

void starTurn(vector<Player*>& players){
    for (auto& player : players) {
        player->setBlocked(false);
    }
    shufflePlayers(players);
    printTurnOrder(players);
}

void initializeGame(vector<Player*>& players) {
    for (auto& player : players) {
        player->initializeResources();
    }
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
        for(int i = 0; i < 4;i++){
            catanBoard.nextTurn();
        }
        starTurn(players);
    for (auto& player : players){
        if(player->isBlocked()) {
            checkBlocked(player,players);
            continue;
        }
        checktrade(player, players, bank);
        drawspcard(player, players, bank);
        checkSpecialCard(player, players, bank);
    }
    }
    return 0;
}
