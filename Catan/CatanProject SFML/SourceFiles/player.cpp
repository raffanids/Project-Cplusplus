#include "player.h"


#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"
#include "Resource.h"
#include "Facility.h"
#include "Facility_Initialize.h"


/*
    How to call initializer:
    Player player[4];


*/


// -------------------------------- Initializer ---------------------------------------------------------

void Player::setPlayerName(std::string inputName)
{
    name = inputName;
}

void Player::setPlayerNumber(int inputNumber)
{
    playerNumber = inputNumber;
}

// -------------------------------- Initializer ---------------------------------------------------------





// ----------------------------- Place Facility ---------------------------------------------------------

// if invalid return 0, if success return 1, if the position is owned return 2. 
int Player::placeHousePosition(housePosition realHouse)
{
    int check = realHouse.setOwner(playerNumber);
    if (check == 1)
    {
        usableFacility.settlement--;
        return 1;
    }
    else if (check == 2)
        return 2;

    else if (check == 0)
        return 0;
    
}

// if invalid return 0, if success return 1, if the position is owned return 2. 
int Player::placeRoadPosition(verticalRoad realVRoad)
{
    int check = realVRoad.setOwner(playerNumber);
    if (check == 1)
    {
        usableFacility.road--;
        return 1;
    }
    else if (check == 2)
        return 2;

    else if (check == 0)
        return 0;
}

// overload

// if invalid return 0, if success return 1, if the position is owned return 2. 
int Player::placeRoadPosition(horizontalRoad realHRoad)
{
    int check = realHRoad.setOwner(playerNumber);
    if (check == 1)
    {
        usableFacility.road--;
        return 1;
    }
    else if (check == 2)
        return 2;

    else if (check == 0)
        return 0;
}

// ---------------------------- Place Facility ---------------------------------------------------------





// -------------------------------- Trade functions ---------------------------------------------------------



// Don't need to use; called when using playerTradeWithPlayer();
bool Player::offerTradeWithPlayer(Player player[4], int playerNumber, std::string offeredResource, int amountOfferedResource, std::string requestedResource, int amountRequestedResource)
{
    bool deal;
    // switch to targeted player turn to offer
    //display yes and no button
    //get input
    
    if (deal == true)
        return true;
    else if (deal == false)
        return false;
}

void Player::playerTradeWithPlayer(Player player[4], const int playerNumber, std::string offeredResource, int amountOfferedResource, std::string requestedResource, int amountRequestedResource)
{
    if (offerTradeWithPlayer(player, playerNumber, offeredResource, amountOfferedResource, requestedResource, amountRequestedResource))
    {
        resource.deductResource(offeredResource, amountOfferedResource);
        player[playerNumber - 1].resource.addResource(offeredResource, amountOfferedResource);
        player[playerNumber - 1].resource.deductResource(requestedResource, amountRequestedResource);
        resource.addResource(requestedResource, amountRequestedResource);
    }
    else std::cout << "Trade Failed.\n"; // << display
}




// -------------------------------- Trade functions ---------------------------------------------------------


