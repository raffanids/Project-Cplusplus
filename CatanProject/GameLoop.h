#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "House_Road_Tile.h"
#include "Facility_Initialize.h"
#include "Resource.h"
#include "Facility.h"
#include "player.h"
#include "bank.h"

#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

/*
    How to call initializer:
    GameLoop system;




*/



class GameLoop
{
public:
    int points[4] = { 0, 0, 0, 0 }; // points[0] = player1 , points[1] = player2 , ...
    bool blockStatus[4] = { false, false, false, false }; // blockStatus[0] = 0; -> player1 is NOT blocked, blockStatus[1] = 1; -> player2 IS BLOCKED
    int playerTurn = 1;
    int startingTurn = 1;
    bool endTurn = false;
    bool endGame = false;

    
    void calculateVictoryPoints(Player player[4]); // calculate every turn


    void setBlock(int playerNumber, bool block);

    // if player don't have block card return false, block success return true
    bool useBlockCard(Player player[4], int userNumber, int targetNumber);

    // if player don't have steal card return false, steal success return true
    bool useStealCard(Player player[4], int userNumber, int targetNumber, const std::string targetResource);

    // if the game is ended return 0, game still loop return 1
    bool nextturn(Player player[4], Bank bank, tile trueTile[13]);

    void startPhase(Player player[4], Bank bank, tile trueTile[13])
    {
        bank.giveFacility(player, playerTurn, "settlement");
        bank.giveFacility(player, playerTurn, "road");
        
        if(startingTurn == 1)
        {
            if(playerTurn < 4)
                playerTurn++;
            else
            {
                startingTurn = 2;
            }
        }else if(startingTurn == 2)
        {
            playerTurn--;
        }
    }


};





#endif