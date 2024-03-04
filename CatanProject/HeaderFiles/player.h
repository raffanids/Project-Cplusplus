#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"
#include "Resource.h"
#include "Facility.h"
#include "Facility_Initialize.h"

#ifndef	PLAYER_HPP
#define	PLAYER_HPP

/*
    How to call initializer:
    Player player[4];


*/
class Player 
{
public:
    std::string name;
    int playerNumber;
    int blockCards;
    int stealCards;
    resource resource;
    Facility facility;
    Facility usableFacility;

    

    // -------------------------------- Initializer ---------------------------------------------------------

    void setPlayerName(std::string inputName);
    void setPlayerNumber(int inputNumber);

    // -------------------------------- Initializer ---------------------------------------------------------



    // ----------------------------- Place Facility ---------------------------------------------------------

    // if invalid return 0, if success return 1, if the position is owned return 2. 
    int placeHousePosition(housePosition realHouse);

    // if invalid return 0, if success return 1, if the position is owned return 2. 
    int placeRoadPosition(verticalRoad realVRoad);

    // if invalid return 0, if success return 1, if the position is owned return 2. 
    int placeRoadPosition(horizontalRoad realHRoad);

    // ----------------------------- Place Facility ---------------------------------------------------------

   

    // -------------------------------- Trade functions ---------------------------------------------------------



    // Don't need to use; called when using playerTradeWithPlayer();
    bool offerTradeWithPlayer(Player player[4], int playerNumber, std::string offeredResource, int amountOfferedResource, std::string requestedResource, int amountRequestedResource);

    void playerTradeWithPlayer(Player player[4], const int playerNumber, std::string offeredResource, int amountOfferedResource, std::string requestedResource, int amountRequestedResource);

    // -------------------------------- Trade functions ---------------------------------------------------------

};




#endif

