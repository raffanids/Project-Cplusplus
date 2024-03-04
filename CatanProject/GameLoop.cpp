#include "GameLoop.h"

#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"
#include "Facility_Initialize.h"
#include "Resource.h"
#include "Facility.h"
#include "player.h"
#include "bank.h"



void GameLoop::calculateVictoryPoints(Player player[4])
{
    for (int i = 0; i < 4; i++)
        points[i] = (player[i].facility.settlement) + (player[i].facility.city * 2);
   
    for (int i = 0; i < 4; i++)
    {
        if (points[i] >= 10) // << someone got 10 points -> game ended
        {
            endGame = true;
            
        }
        else
        {
            endGame = false; // << loop
            
        }
    }
    
}





void GameLoop::setBlock(int playerNumber, bool block)
{
    if (block == true)
        blockStatus[playerNumber - 1] = true; // set blocked
    if (block == false)
        blockStatus[playerNumber - 1] = false; // set unblocked
}

// if player don't have block card return false, block success return true
bool GameLoop::useBlockCard(Player player[4], int userNumber, int targetNumber)
{
    if (player[userNumber - 1].blockCards > 0) // player has blockCard
    {
        setBlock(targetNumber, true);
        player[userNumber - 1].blockCards--;
        return true;
    }
    else // player does NOT has blockCard
    {
        return false;
    }
}


// if player don't have steal card return false, steal success return true
bool GameLoop::useStealCard(Player player[4], int userNumber, int targetNumber, const std::string targetResource)
{
    if (player[userNumber - 1].stealCards < 1) // check if user has the card
    {
        return false;
    }
    else
    {
        player[userNumber - 1].stealCards --;

        if (targetResource == "wood")
        {
            player[userNumber - 1].resource.wood = player[targetNumber - 1].resource.wood;
            player[targetNumber - 1].resource.wood = 0;
            return true;
        }

        if (targetResource == "brick")
        {
            player[userNumber - 1].resource.brick = player[targetNumber - 1].resource.brick;
            player[targetNumber - 1].resource.brick = 0;
            return true;
        }

        if (targetResource == "wool")
        {
            player[userNumber - 1].resource.wool = player[targetNumber - 1].resource.wool;
            player[targetNumber - 1].resource.wool = 0;
            return true;
        }

        if (targetResource == "ore")
        {
            player[userNumber - 1].resource.ore = player[targetNumber - 1].resource.ore;
            player[targetNumber - 1].resource.ore = 0;
            return true;
        }

        if (targetResource == "grain")
        {
            player[userNumber - 1].resource.grain = player[targetNumber - 1].resource.grain;
            player[targetNumber - 1].resource.grain = 0;
            return true;
        }
    }

}

// if the game is ended return 0, game still loop return 1
bool GameLoop::nextturn(Player player[4], Bank bank, tile trueTile[13])
{
    calculateVictoryPoints(player);

    if(endGame == true)
    {
        return 0;
    }
    else
    {
        // increase turn
        if (playerTurn == 4)
            playerTurn = 1;
        else
        {
            playerTurn++;
        }

        if (blockStatus[playerTurn - 1] == false) // if the player is Not blocked
        {
            int rollNumber = rollDice(); // call rollDice 
            //display dice
            bank.produceResourceToPlayer(player, trueTile, rollNumber);

            return 1;
        }
        else // if the player is blocked
        {
            setBlock(playerTurn, false);
            nextturn(player, bank, trueTile);
            
            return 1;
        }
    }
}