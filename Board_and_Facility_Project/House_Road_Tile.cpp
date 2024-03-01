#include "House_Road_Tile.h"

#include<iostream>
#include<vector>
#include<string>
#include<cmath>





void housePosition::setValidation(bool valid)
	{
		if (valid == false)
			validation = false;
		else validation = true;
	}

	//housePosition();
	/*~housePosition()// destructor
	{
		std::cout << "House position , state , owner is deleted";
	}*/
	



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
	//verticalRoad();
	/*~verticalRoad()
	{
		std::cout << "Vertical Road position , state , owner is deleted";
	}*/



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
	//horizontalRoad();
	/*~horizontalRoad()
	{
		std::cout << "Horizontal Road position , state , owner is deleted";
	}*/





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
	//tile();
	/*~tile()
	{
		std::cout << "The " << numberOnTile << " " << resourceType << " tile is deleted";
	}*/





