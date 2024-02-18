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
        vector<string> specialcard;
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

void startTurn(player& p1, player& p2, player& p3, player& p4) {
    vector<player*> players = {&p1, &p2, &p3, &p4};
    customShuffle(players);

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
    
    if(card%2 == 0) specialcard.push_back("steal");
    else specialcard.push_back("block");
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
    } else {
        if (resource_type == "wood" && target_resources.wood > 0) {
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
        }
        cout << "Cannot steal the specified resource from the target. Only stole what was available." << endl;
    }
}
void steal(player& thief, player& target, string resource_type, int num) {
    thief.stealresource(target, target.p, resource_type, num);
}

int main(){    
    srand(time(0));
    
    player p1{"p1"};
    player p2{"p2"};
    player p3{"p3"};
    player p4{"p4"};
    
    string player_name1;
    string player_name2;
    string resources;
    int num;
    p1.drawspecialcard();
    for (int i = 0; i < p1.specialcard.size(); i++) {
        cout << p1.specialcard[i] << endl;
    }

    p1.p.wood = 5;
    p1.p.grain = 5;
    p1.p.brickl = 5;
    p1.p.ore = 5;
    p1.p.sheep = 5;

    p2.p.wood = 5;
    p2.p.grain = 5;
    p2.p.brickl = 5;
    p2.p.ore = 5;
    p2.p.sheep = 5;

    p3.p.wood = 5;
    p3.p.grain = 5;
    p3.p.brickl = 5;
    p3.p.ore = 5;
    p3.p.sheep = 5;

    p4.p.wood = 5;
    p4.p.grain = 5;
    p4.p.brickl = 5;
    p4.p.ore = 5;
    p4.p.sheep = 5;
    
    for(int i = 0; i < 4;i++){
    vector<player*> players = {&p1, &p2, &p3, &p4};
    customShuffle(players);
    cout << "Turn order for this round:" << endl;
    for (int i = 0; i < players.size(); ++i){
        cout << i + 1 << ". " << players[i]->name << endl;
    }
    cout << endl;
    for(int i = 0; i < 4;i++){
    cout << "player " << players[i]->name << " " << endl;
    player_name1 = players[i]->name;
    cout << "player steal ? : ";
    cin >> player_name2;
    cout << "Enter the type of resource you want to steal (wood, grain, brick, ore, sheep): ";
    cin >> resources;
    cout << "Enter the number of resources you want to steal: ";
    cin >> num;
    
    if(player_name1 == "p1" && player_name2 == "p2"){
        steal(p1, p2, resources,num);
    }else if(player_name1 == "p1" && player_name2 == "p3"){
        steal(p1, p3, resources, num);
    }else if(player_name1 == "p1" && player_name2 == "p4"){
        steal(p1, p4, resources, num);
    }else if(player_name1 == "p2" && player_name2 == "p1"){
        steal(p2, p1, resources, num);
    }else if(player_name1 == "p2" && player_name2 == "p3"){
        steal(p2, p3, resources, num);
    }else if(player_name1 == "p2" && player_name2 == "p4"){
        steal(p2, p4, resources, num);
    }else if(player_name1 == "p3" && player_name2 == "p1"){
        steal(p3, p1, resources, num);
    }else if(player_name1 == "p3" && player_name2 == "p2"){
        steal(p3, p2, resources, num);
    }else if(player_name1 == "p3" && player_name2 == "p4"){
        steal(p3, p4, resources, num);
    }else if(player_name1 == "p4" && player_name2 == "p1"){
        steal(p4, p1, resources, num);
    }else if(player_name1 == "p4" && player_name2 == "p2"){
        steal(p4, p2, resources, num);
    }else if(player_name1 == "p4" && player_name2 == "p3"){
        steal(p4, p3, resources, num);
    }
    cout << "wood grain brickl ore sheep\n";
    cout << "p1 " << p1.p.wood << " " << p1.p.grain << " " << p1.p.brickl << " " << p1.p.ore << " " << p1.p.sheep << endl;
    cout << "p2 " << p2.p.wood << " " << p2.p.grain << " " << p2.p.brickl << " " << p2.p.ore << " " << p2.p.sheep << endl;
    cout << "p3 " << p3.p.wood << " " << p3.p.grain << " " << p3.p.brickl << " " << p3.p.ore << " " << p3.p.sheep << endl;
    cout << "p4 " << p4.p.wood << " " << p4.p.grain << " " << p4.p.brickl << " " << p4.p.ore << " " << p4.p.sheep << endl;
    }
    }
    return 0;
}
