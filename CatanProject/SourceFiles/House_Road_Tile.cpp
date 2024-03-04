#include "House_Road_Tile.h"

#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "randomNumber.h"

//---------------------------------------------------------------------------------------- HOUSE ------------------------------------------------------------------------------------------------------

void housePosition::setValidation(bool valid)
	{
		if (valid == false)
			validation = false;
		else validation = true;
	}

// if invalid return 0, if success return 1, if the position is owned return 2. 
int housePosition::setOwner(int playerNumber)
{
	if (validation == false) // this house position is invalid
		return 0;
	else if (state == 0) // this house position is unowned > can own
	{
		owner = playerNumber;
		state = 1;
		return 1;

	}
	else if (state == 1 || state == 2) // this house position is owned
	{
		return 2;
	}
}

int housePosition::upgradeHouseToCity(int playerNumber)
{
	if (owner == playerNumber)
	{
		if (state == 2) // already upgraded
			return 3; 
		else // Work!!!
		{
			state = 2; 
			return 1; 
		}
	}
	else if (owner != playerNumber)
	{
		return 2; // unowned by the player
	}
}






//housePosition();
	/*~housePosition()// destructor
	{
		std::cout << "House position , state , owner is deleted";
	}*/
	


//---------------------------------------------------------------------------------------- VERTICAL ROAD ------------------------------------------------------------------------------------------------------


	bool verticalRoad::setValidation()
	{
		if ((topHouse->validation == false)||(bottomHouse->validation == false))
			validation = false;
		else validation = true;

		return validation;
	}

	void verticalRoad::setHousePosition(housePosition* top , housePosition* bottom)
	{
		topHouse = top;
		bottomHouse = bottom;
	}

	// if invalid return 0, if success return 1, if the position is owned return 2. 
	int verticalRoad::setOwner(int playerNumber)
	{
		if (validation == false) // this road position is not valid
			return 0;
		else if (state == 0) // this road is unowned > can own
		{
			owner = playerNumber;
			state = 1;
			return 1;

		}
		else if (state == 1) // this road is owned
		{
			return 2;
		}
	}


//---------------------------------------------------------------------------------------- HORIZONTAL ROAD ------------------------------------------------------------------------------------------------------


	bool horizontalRoad::setValidation()
	{
		if ((leftHouse->validation == false)||(rightHouse->validation == false))
			validation = false;
		else validation = true;
		return validation;
	}

	void horizontalRoad::setHousePosition(housePosition* left, housePosition* right)
	{
		leftHouse = left;
		rightHouse = right;
	}
	
	// if invalid return 0, if success return 1, if the position is owned return 2. 
	int horizontalRoad::setOwner(int playerNumber)
	{
		if (validation == false) // this road position is not valid
			return 0;
		else if (state == 0) // this road is unowned > can own
		{
			owner = playerNumber;
			state = 1; 
			return 1;

		}
		else if (state == 1) // this road is owned
		{
			return 2;
		}
	}


//---------------------------------------------------------------------------------------- TILE ------------------------------------------------------------------------------------------------------



	bool tile::setValidation()
	{
		if ((leftVerticalRoad->validation == false) || (rightVerticalRoad->validation == false) || (topHorizontalRoad->validation == false) || (bottomHorizontalRoad->validation == false))
			validation = false;
		else validation = true;

		return validation;
	}

	void tile::setRoadPosition(horizontalRoad* top, horizontalRoad* bottom, verticalRoad* left, verticalRoad* right)
	{
		topHorizontalRoad = top;
		bottomHorizontalRoad = bottom;
		leftVerticalRoad = left;
		rightVerticalRoad = right;
	}
	
	void tile::setHousePosition(housePosition* topleft, housePosition* topright, housePosition* bottomleft, housePosition* bottomright)
	{
		topLeftHouse = topleft;
		topRightHouse = topright;
		bottomLeftHouse = bottomleft;
		bottomRightHouse = bottomright;
	}
	
	void tile::setNumberOnTile(int Number)
	{
		numberOnTile = Number;
	}
	
	void tile::setResourceTypeOnTile(std::string inputResource)
	{
		resourceType = inputResource;
	}

	// set together with house.setOwner.
	void tile::setOwner()
	{
		owner[0] = topLeftHouse->owner;
		owner[1] = topRightHouse->owner;
		owner[2] = bottomLeftHouse->owner;
		owner[3] = bottomRightHouse->owner;

		if (owner[0] == 1 || owner[1] == 1 || owner[2] == 1 || owner[3] == 1)
			state = 1;
	}



