#include "ClassBd_Rs.h"
#include "Player.h"
#include "ClassSCB.h"
#include "Function.h"

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