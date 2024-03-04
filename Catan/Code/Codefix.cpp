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
    
    void addResource(string resource,int amount) {
        transform(resource.begin(), resource.end(), resource.begin(), ::tolower);
        resources[resource] += amount;
    }
    
    bool deductResource(const string& resource, int amount) {
        if (resources[resource] >= amount) {
            resources[resource] -= amount;
            return true;
        }
    return false;
    }
    
    void removeSpecialCard(const string& cardName) {
        specialcard.erase(remove(specialcard.begin(), specialcard.end(), cardName), specialcard.end());
    }
    
    bool tradeWithBank(Bank& bank, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (resources[offerResource] >= offerAmount && bank.resources[requestResource] >= requestAmount) {
            resources[offerResource] -= offerAmount;
            resources[requestResource] += requestAmount;
            bank.resources[requestResource] -= requestAmount;
            bank.resources[offerResource] += offerAmount;
            cout << "Trade successful: " << offerAmount << " " << offerResource << " for " << requestAmount << " " << requestResource << endl;
            return true;
        } else {
            cout << "Trade failed due to insufficient resources." << endl;
            return false;
        }
    }

    bool tradeWithPlayer(Player& player, const string& offerResource, int offerAmount, const string& requestResource, int requestAmount) {
        if (resources[offerResource] >= offerAmount && player.getResources()[requestResource] >= requestAmount) {
            deductResource(offerResource, offerAmount);
            player.addResource(offerResource, offerAmount);
            player.deductResource(requestResource, requestAmount);
            addResource(requestResource, requestAmount);
            cout << "Trade successful between " << name << " and " << player.getName() << endl;
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
                specialcard.push_back("stealcard");
                bank.stealCards--;
                cout << "You drew a special card (steal). Now have " << bank.stealCards << " steal card(s) left in the bank." << endl;
            } else {
                cout << "No steal cards left in the bank." << endl;
            }
                } else if (card == 2) {
                    if (bank.blockCards > 0) {
                    specialcard.push_back("blockcard"); 
                    bank.blockCards--;
                    cout << "You drew a special card (block). Now have " << bank.blockCards << " block card(s) left in the bank." << endl;
                } else {
                    cout << "No block cards left in the bank." << endl;
                }
            }
    }

    void stealResource(Player& targetPlayer, map<string, int>& targetResources, const string& resourceType, int amount = 1) {
        if (targetResources[resourceType] >= amount) {
            targetResources[resourceType] -= amount;
            resources[resourceType] += amount;
        } else {
            cout << "Cannot steal the specified resource from the target. Only stole what was available." << endl;
        }
    }

    void displayStatus() {
        cout << "----------------------------------------------" << endl;
        cout << "Player " << name << " Resources :\n";
        for (const auto& resource : resources) {
            cout << resource.first << ": " << resource.second << "\n";
        }
        cout << "Victory Points: " << calculateVictoryPoints() << "\n";
        cout << "----------------------------------------------\n";
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
        vector<string> resources = {"Sheep", "Wood", "Brick", "Grain", "Ore", "Sheep", "Grain", "Ore", "Brick", "Wood", "Sheep", "Grain", "Wood"};

        vector<int> numbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12 ,5, 6};
        shuffle(numbers.begin(), numbers.end(),default_random_engine(static_cast<unsigned>(std::time(nullptr))));
        numbers.insert(numbers.begin() + 9, 0);

        vector<int> layout = {1, 3, 5, 3, 1};
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
        cout << "----------------------------------------------" << endl;
        cout << "Catan Board Layout:\n\n";
        vector<string> resources;
        vector<int> numbers;
        for (const auto& row : board) {
            for (const auto& tile : row) {
                string resource = get<1>(tile);
                int number = get<2>(tile);
                cout << resource << " (" << number << ") ";
                
            }
            cout << "\n";
        }
        cout << "\n----------------------------------------------";
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
                    int houses = rand()%2+1;
                    string resource = get<1>(tile);
                    a->addResource(resource,houses);
                    cout << houses << " " << resource << "(s) produced for Player " << a->getName() << "\n";
                }
            }
        }
    }

    void nextTurn(Player* a,vector<Player*>& players) {
        cout << "\n----------------------------------------------\n";
        cout << "Player " << a->getName() << "'s turn:\n";
        int roll = rollDice();
        produceResources(players, roll, a);
        cout << "----------------------------------------------\n";
        a->displayStatus();
    }
    
    void incresenextTurn(Player* a,vector<Player*>& players) {
        cout << "\nPlayer " << a->getName() << "'s turn:\n";
        int roll = rollDice();
        produceResources(players, roll, a);
        cout << endl;
    }
};

void playerSteal(vector<Player*>& players, int i) {
    string player1, player2, resource;
    int amount = 1;

    player1 = players[i]->getName();

    cout << "What player you want to steal (p1/p2/p3/p4) : ";
    cin >> player2;

    cout << "Enter the type of resource you want to steal (wood, grain, brick, ore, sheep): ";
    cin >> resource;

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
    players[i]->displayStatus();
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
    int luckdraw = rand()%5+1;
    string ans;
    if(luckdraw == 5){
        cout << "----------------------------------------------\n";
        while(ans != "1"){ 
            cout << a->getName() << " You want to draw SpecialCard? yes(1) or no(2) : ";
            cin >> ans;
            if(ans == "1"){
                a->drawSpecialCard(bank);
                cout << "----------------------------------------------\n";
                break;
            }
        }
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
        cout << a->getName() << " You have a " << card << endl;
        cout << "Do you want to use it? yes(1) or no(2) : ";
        cin >> useCard;
        if (useCard == "1") {
            if (card == "stealcard") {
                playerSteal(players, distance(players.begin(), find(players.begin(), players.end(), a)));
                a->removeSpecialCard(card);
                cout << "You used a special card!" << endl;
            } else if (card == "blockcard") {
                isBlocked(players);
                a->removeSpecialCard(card);
                cout << "You used a special card!" << endl;
            } else {
                cout << "Invalid card type! Returning to main menu." << endl;
            }
        } else if (useCard == "2") {
            break;
        } else {
            cout << "Invalid option! Returning to main menu." << endl;
        }
    cout << "----------------------------------------------\n";
    }
}

void checktradebankresource(Player* a, vector<Player*>& players, Bank& bank){
    string trade1;
    string trade2;
    cout << "What do you want to trade? (wood/grain/brick/ore/sheep) : ";
    cin >> trade2;
    cout << "Trade with? (wood/grain/brick/ore/sheep) : ";
    cin >> trade1;
    a->tradeWithBank(bank,trade1, 4,trade2, 1);
}

bool checktradeplayer(Player* a,Player* p,string trade1,string trade2,int num1,int num2){
    string check;
    cout << "----------------------------------------------\n";
    cout << a->getName() << " want to offer " << trade2 << " with " << trade1 << "  " << num2 << " : " << num1 << endl;
    cout << p->getName() << " want to accept this offer? yes(1) or no(2) : ";
    cin >> check;
    if(check == "1"){
        return true;
    }else{
        return false;
    }
    cout << "----------------------------------------------\n";
}

void checktradeplayerresource(Player* a, vector<Player*>& players, Bank& bank) {
    string playerName, trade1, trade2;
    int num1, num2;

    cout << "Which player do you want to trade with? (p1/p2/p3/p4) : ";
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
    cout << "----------------------------------------------\n";
    cout << a->getName() << " You want to trading with bank(1) or player(2) or Exit(3) : ";
    cin >> trade;
    if(trade == "1"){
        checktradebankresource(a,players,bank);
        a->displayStatus();
    }else if (trade == "2"){
        checktradeplayerresource(a,players,bank);
        a->displayStatus();
    }else {
        cout << "Exiting trading\n";
        cout << "----------------------------------------------\n";
    }
}

void checkbuild(Player* a, vector<Player*>& players){
    string ans;
    cout << "----------------------------------------------\n";
    cout << a->getName() << " You want to build Settlement(1) or City(2) or Exit(3) : ";
    cin >> ans;
    if(ans == "1"){
        a->buildSettlement();
        a->displayStatus();
    }else if (ans == "2"){
        a->buildCity();
        a->displayStatus();
    }else {
        cout << "Exiting buiding\n";
        cout << "----------------------------------------------\n";
    }    
}

void checkwinner(vector<Player*>& players){
    for (auto& player : players) {
        if(player->calculateVictoryPoints() >= 10){
            cout << "Player " << player->getName() << " wins the game!" << endl;
            exit(0);
        }
    }
}

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
}

void initializeGame(vector<Player*>& players) {
    for (auto& player : players) {
        player->initializeResources();
    }
}

void starTurn(vector<Player*>& players){
    cout << "\n----------------------------------------------" << endl;
    for (auto& player : players) {
        player->setBlocked(false);
    }
    shufflePlayers(players);
    printTurnOrder(players);
    cout << "----------------------------------------------" << endl;
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
    catanBoard.displayBoard();
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            catanBoard.incresenextTurn(players[j],players);
        }
    }
    for(int i = 0; i < 99; i++){
        catanBoard.displayBoard();
        starTurn(players);
        for (auto& player : players){
            if(player->isBlocked()) {
                checkBlocked(player,players);
                continue;
            }
            catanBoard.nextTurn(player,players);
            checktrade(player, players, bank);
            checkbuild(player, players);
            drawspcard(player, players, bank);            
            checkSpecialCard(player, players, bank);
            checkwinner(players);
        }
    }
    return 0;
}
