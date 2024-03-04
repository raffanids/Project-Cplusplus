
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