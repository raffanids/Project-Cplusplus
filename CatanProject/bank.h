#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "randomNumber.h"
#include "House_Road_Tile.h"
#include "Resource.h"
#include "player.h"
#include "Facility.h"

#ifndef	BANK_HPP
#define	BANK_HPP

class Bank
{
public:
    resource resources;
    Facility facilities;
    int blockCards;
    int stealCards;

    Bank(); // constructor

    // call every turn
    void produceResourceToPlayer(Player player[4], tile trueTile[13], int rolledNumber);
        



    // -------------------------------- Trade functions ---------------------------------------------------------

    //Don't need to use; called when tradeWithPlayer
    // if player has enough resources return true, if not return false
    bool checkPlayerResourceBeforeTrade(Player player[4], int playerNumber, const std::string offeredResource);

    // if the bank has enough resources return true, if not return false
    bool checkBankResourceBeforeTrade(const std::string requestedResource);

    // success return true, if not return false
    bool tradeWithPlayer(Player player[4], int playerNumber, const std::string offeredResource, const std::string requestedResource); // not complete, need to display

    bool tradeFacilityWithPlayer(); // not complete
    // -------------------------------- Trade functions ---------------------------------------------------------


    // -------------------------------- Special Card ---------------------------------------------------------

    void giveFacility(Player player[4], int playerNumber, std::string requestedFacility);

    void giveSpecialCard(Player player[4], int playerNumber, std::string inputSpecialCard);

    void removeSpecialCard(Player player[4], int playerNumber, std::string inputSpecialCard);

    // if draw success return true, bank insufficient cards return false
    bool drawSpecialCard(Player player[4], int playerNumber);


    // -------------------------------- Special Card ---------------------------------------------------------

};

#endif
