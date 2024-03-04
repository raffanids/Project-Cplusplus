#include "bank.h"

#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"
#include "Resource.h"
#include "player.h"

Bank::Bank() 
{
    resources.addResource("wood", 19);
    resources.addResource("wool", 19);
    resources.addResource("brick", 19);
    resources.addResource("grain", 19);
    resources.addResource("ore", 19);

    facilities.addFacility("road", 15);
    facilities.addFacility("settlement", 5);
    facilities.addFacility("city", 4);

    blockCards = 5;
    stealCards = 5;
}

// call every turn
void Bank::produceResourceToPlayer(Player player[4], tile trueTile[13], int rolledNumber)
{
    for (int i = 0; i < 13; i++) // check all 13 trueTile(s)
    {
        if (trueTile[i].numberOnTile == rolledNumber) // check if number On the trueTile has the same number as rolledNumber
        {
            for (int j = 0; j < 4; j++) // paying all the owners on that tile
            {

                if (trueTile[i].owner[j] != 0) // check if on that position has been owned
                {
                    player[trueTile[i].owner[j]].resource.addResource(trueTile[i].resourceType, 1); // paying the same resource as the resourceType on tile 
                }
            }
        }
    }
}




// -------------------------------- Trade functions ---------------------------------------------------------

//Don't need to use; called when tradeWithPlayer
// if player has enough resources return true, if not return false
bool Bank::checkPlayerResourceBeforeTrade(Player player[4], int playerNumber, const std::string offeredResource)
{
    if (offeredResource == "wood")
        if (player[playerNumber - 1].resource.wood >= 4)
            return true;
        else return false;

    if (offeredResource == "brick")
        if (player[playerNumber - 1].resource.brick >= 4)
            return true;
        else return false;

    if (offeredResource == "grain")
        if (player[playerNumber - 1].resource.grain >= 4)
            return true;
        else return false;

    if (offeredResource == "ore")
        if (player[playerNumber - 1].resource.ore >= 4)
            return true;
        else return false;

    if (offeredResource == "wool")
        if (player[playerNumber - 1].resource.wool >= 4)
            return true;
        else return false;

}

// if the bank has enough resources return true, if not return false
bool Bank::checkBankResourceBeforeTrade(const std::string requestedResource)
{
    if (requestedResource == "wood")
    {
        if (resources.wood > 0)
            return true;
        else return false;
    }

    if (requestedResource == "brick")
    {
        if (resources.brick > 0)
            return true;
        else return false;
    }

    if (requestedResource == "grain")
    {
        if (resources.grain > 0)
            return true;
        else return false;
    }

    if (requestedResource == "ore")
    {
        if (resources.ore > 0)
            return true;
        else return false;
    }

    if (requestedResource == "wool")
    {
        if (resources.wool > 0)
            return true;
        else return false;
    }
}

// success return true, if not return false
bool Bank::tradeWithPlayer(Player player[4], int playerNumber, const std::string offeredResource, const std::string requestedResource)
{
    if(checkBankResourceBeforeTrade(requestedResource) == false)
    {
        std::cout << "Trade failed due to insufficient resources of the bank." << std::endl; // ****  need to code the displaying on window
        return false;
    }
    else if (checkPlayerResourceBeforeTrade(player, playerNumber, offeredResource))
    {
        player[playerNumber - 1].resource.deductResource(requestedResource, 4); //player give 4 resources to bank

        resources.addResource(offeredResource, 4); //bank receive 4 resources

        resources.deductResource(requestedResource, 1); //bank give 1 resource to player

        player[playerNumber - 1].resource.addResource(requestedResource, 1); //player receive 1 resource

        return true;
    }
    
    else
    {
        std::cout << "Trade failed due to insufficient resources." << std::endl; // ****  need to code the displaying on window
        return false;
    }
}

// -------------------------------- Trade functions ---------------------------------------------------------




// -------------------------------- Special Card ---------------------------------------------------------------

void Bank::giveFacility(Player player[4], int playerNumber, std::string requestedFacility)
{
    player[playerNumber - 1].facility.addFacility(requestedFacility, 1);
}

void Bank::giveSpecialCard(Player player[4], int playerNumber, std::string inputSpecialCard)
{
    if (inputSpecialCard == "blockCard")
    {
        blockCards--;
        player[playerNumber - 1].blockCards++;
    }


    if (inputSpecialCard == "stealCard")
    {
        stealCards--;
        player[playerNumber - 1].stealCards++;
    }

}

void Bank::removeSpecialCard(Player player[4], int playerNumber, std::string inputSpecialCard)
{
    if (inputSpecialCard == "blockCard")
    {
        player[playerNumber - 1].blockCards--;
    }


    if (inputSpecialCard == "stealCard")
    {
        player[playerNumber - 1].stealCards--;
    }
}

// if draw success return true, bank insufficient cards return false
bool Bank::drawSpecialCard(Player player[4], int playerNumber)
{
    if (stealCards >= 0 && blockCards >= 0)
    {
        int card = randomNumber(2);
        if (card == 1)
        {
            giveSpecialCard(player, playerNumber, "stealCard");
            return true;
        }
        if (card == 2)
        {
            giveSpecialCard(player, playerNumber, "blockCard");
            return true;
        }
    }
    else if (stealCards >= 0)
    {
        giveSpecialCard(player, playerNumber, "stealCard");
        return true;
    }
    else if (blockCards >= 0)
    {
        giveSpecialCard(player, playerNumber, "blockCard");
        return true;
    }
    else
    {
        return false;
    }
}



// -------------------------------- Special Card ---------------------------------------------------------------
