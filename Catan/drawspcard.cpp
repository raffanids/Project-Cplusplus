#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime> 

using namespace std;

class resource{
    public:
        int wood;
        int grain;
        int brickl;
        int ore;
        int sheep;
};
class player{
    public:
        string name; 
        int cards;
        vector<int> specialcard;
        bool blocked;
        resource p;
        void drawspecialcard();
        void stealresource(player& target_player, resource& target_resources,string resource_type,int n);
};

void customShuffle(vector<player*>& players) {
    int n = players.size();
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(players[i], players[j]);
    }
}

void shufflePlayers(vector<player*>& players) {
    customShuffle(players);
}

void printTurnOrder(const vector<player*>& players) {
    cout << "Turn order for this round:" << endl;
    for (int i = 0; i < players.size(); ++i) {
        cout << i + 1 << ". " << players[i]->name << endl;
    }
    cout << endl;
}

void player::drawspecialcard(){
    vector<int> cards;
    for (int i = 1; i <= 20; ++i) {
        cards.push_back(i);
    }
    int index = rand() % cards.size();
    int card = cards[index];
    
    cards.erase(cards.begin() + index);
    
    if(card%2 == 0) specialcard.push_back(1); //steal
    else specialcard.push_back(2); //block
}

void steal(player& thief, player& target, string resource_type, int num) {
    thief.stealresource(target, target.p, resource_type, num);
}

void checksteal(vector<player*>& players,string name1,string name2,string resources,int num){
    string a[4] = {"p1", "p2", "p3", "p4"};
    
    vector<player*> sortplayers;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(players[j]->name == a[i]){
                sortplayers.push_back(players[j]);
                break;
            }
        }
    }
    
    if(name1 == "p1" && name2 == "p2"){
        steal(*sortplayers[0], *sortplayers[1], resources, num);
    } else if(name1 == "p1" && name2 == "p3"){
        steal(*sortplayers[0], *sortplayers[2], resources, num);
    } else if(name1 == "p1" && name2 == "p4"){
        steal(*sortplayers[0], *sortplayers[3], resources, num);
    } else if(name1 == "p2" && name2 == "p1"){
        steal(*sortplayers[1], *sortplayers[0], resources, num);
    } else if(name1 == "p2" && name2 == "p3"){
        steal(*sortplayers[1], *sortplayers[2], resources, num);
    } else if(name1 == "p2" && name2 == "p4"){
        steal(*sortplayers[1], *sortplayers[3], resources, num);
    } else if(name1 == "p3" && name2 == "p1"){
        steal(*sortplayers[2], *sortplayers[0], resources, num);
    } else if(name1 == "p3" && name2 == "p2"){
        steal(*sortplayers[2], *sortplayers[1], resources, num);
    } else if(name1 == "p3" && name2 == "p4"){
        steal(*sortplayers[2], *sortplayers[3], resources, num);
    } else if(name1 == "p4" && name2 == "p1"){
        steal(*sortplayers[3], *sortplayers[0], resources, num);
    } else if(name1 == "p4" && name2 == "p2"){
        steal(*sortplayers[3], *sortplayers[1], resources, num);
    } else if(name1 == "p4" && name2 == "p3"){
        steal(*sortplayers[3], *sortplayers[2], resources, num);
    }
}

void player::stealresource(player& target_player, resource& target_resources, string resource_type, int n) {
    if (resource_type == "wood" && target_resources.wood >= n) {
        target_resources.wood -= n;
        p.wood += n;
    } else if (resource_type == "grain" && target_resources.grain >= n) {
        target_resources.grain -= n;
        p.grain += n;
    } else if (resource_type == "brick" && target_resources.brickl >= n) {
        target_resources.brickl -= n;
        p.brickl += n;
    } else if (resource_type == "ore" && target_resources.ore >= n) {
        target_resources.ore -= n;
        p.ore += n;
    } else if (resource_type == "sheep" && target_resources.sheep >= n) {
        target_resources.sheep -= n;
        p.sheep += n;
    } else if (resource_type == "wood" && target_resources.wood > 0) {
            p.wood += target_resources.wood;
            target_resources.wood = 0;
        } else if (resource_type == "grain" && target_resources.grain > 0) {
            p.grain += target_resources.grain;
            target_resources.grain = 0;
        } else if (resource_type == "brick" && target_resources.brickl > 0) {
            p.brickl += target_resources.brickl;
            target_resources.brickl = 0;
        } else if (resource_type == "ore" && target_resources.ore > 0) {
            p.ore += target_resources.ore;
            target_resources.ore = 0;
        } else if (resource_type == "sheep" && target_resources.sheep > 0) {
            p.sheep += target_resources.sheep;
            target_resources.sheep = 0;
        } else cout << "Cannot steal the specified resource from the target. Only stole what was available." << endl;
    }

void playersteal(vector<player*>& players,int i){
    string player_name1, player_name2, resources;
    int num;
    
    player_name1 = players[i]->name;

    cout << "player steal ? : ";
    cin >> player_name2;

    cout << "Enter the type of resource you want to steal (wood, grain, brick, ore, sheep): ";
    cin >> resources;

    cout << "Enter the number of resources you want to steal: ";
    cin >> num;

    checksteal(players, player_name1, player_name2, resources, num);
        
    string a[4] = {"p1", "p2", "p3", "p4"};
    vector<player*> sortplayers;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(players[j]->name == a[i]){
                sortplayers.push_back(players[j]);
                break;
            }
        }
    }
        
    cout << "wood grain brickl ore sheep\n";
    for (int i = 0; i < players.size(); ++i){
        player* currentPlayer = sortplayers[i];
        cout << currentPlayer->name << " " << currentPlayer->p.wood << " " << currentPlayer->p.grain << " " << currentPlayer->p.brickl << " " << currentPlayer->p.ore << " " << currentPlayer->p.sheep << endl;
    }
}

bool isBlocked(vector<player*>& players){
    string name;
    cout << "player block ? : ";
    cin >> name;
    for (int i = 0; i < players.size(); i++){
        if (players[i]->name == name) {
            players[i]->blocked = true;
            return true;
        }
    }
    return false;
}

void checkspecialcard(vector<player*>& players){
    for (int i = 0; i < players.size(); ++i){
        if(players[i]->blocked == true){
            cout << players[i]->name << " is blocked and cannot play this turn." << endl;
            continue;
        }
        for (int j = 0; j < players[i]->specialcard.size(); ++j){
            if(players[i]->specialcard[j] == 1){
                cout << players[i]->name << " You have a special card." << endl;
                cout << "Do you want to use it? (yes/no): ";
                string useCard;
                cin >> useCard;
                if (useCard == "yes"){
                    playersteal(players,i);       
                    cout << "You used a special card! You can take another turn." << endl;
                }
            }
            if(players[i]->specialcard[j] == 2){
                cout << players[i]->name << " You have a special card." << endl;
                cout << "Do you want to use it? (yes/no): ";
                string useCard;
                cin >> useCard;
                if (useCard == "yes"){
                    isBlocked(players);       
                    cout << "You used a special card! You can take another turn." << endl;
                }
            }
        }
    }
}

int main(){    
    srand(time(0));
    vector<player*> players;    
    player p1{"p1"};
    player p2{"p2"};
    player p3{"p3"};
    player p4{"p4"};
    
    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);
    players.push_back(&p4);

    for (int i = 0; i < players.size(); ++i) {
        players[i]->drawspecialcard();
    }
    
    for (int i = 0; i < players.size(); ++i) {
        cout << players[i]->name << " special cards: " ;
        for (int j = 0; j < players[i]->specialcard.size(); ++j) {
            cout << players[i]->specialcard[j] << endl;
        }
    }
    
    for(int i = 0; i < players.size(); i++){
        players[i]->p.wood = 5;
        players[i]->p.grain = 5;
        players[i]->p.brickl = 5;
        players[i]->p.ore = 5;
        players[i]->p.sheep = 5;
    }

    for(int i = 0; i < 4;i++){
        for(int j = 0; j < players.size();j++){
            players[j]->blocked = false;
        }
    shufflePlayers(players);  
    printTurnOrder(players);
    checkspecialcard(players);
    }
    return 0;
}
