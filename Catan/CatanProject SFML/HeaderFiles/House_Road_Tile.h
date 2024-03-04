#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "randomNumber.h"


#ifndef HOUSE_ROAD_TILE_HPP
#define HOUSE_ROAD_TILE_HPP

//--------------------------------------------------------------------------------------------- House ---------------------------------------------------------------------------------------------


class housePosition
{
public:
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state = 0; // << [if = 0, unowned] [if = 1, house] [if = 2, city]
	int owner = 0; // << example: int owner = 2; << this position owned by player 2.
	bool validation;

	// initializer
	void setValidation(bool valid);

	// in game functions

	// if invalid return 0, if success return 1, if the position is owned return 2. 
	int setOwner(int playerNumber);
	int upgradeHouseToCity(int playerNumber);
};


//--------------------------------------------------------------------------------------------- Vertical road ---------------------------------------------------------------------------------------------


class verticalRoad
{
public:
	housePosition* topHouse;
	housePosition* bottomHouse;
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state = 0; // << [if = 0, unowned] [if = 1, owned] 
	int owner = 0; // << example: int owner = 2; << this vertical road owned by player 2.
	bool validation;

	// initializer
	bool setValidation();
	void setHousePosition(housePosition* top, housePosition* bottom);

	// in game functions

	// if invalid return 0, if success return 1, if the position is owned return 2. 
	int setOwner(int playerNumber);
};


//--------------------------------------------------------------------------------------------- Horizontal road ---------------------------------------------------------------------------------------------


class horizontalRoad
{
public:
	housePosition* leftHouse;
	housePosition* rightHouse;
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state = 0; // << [if = 0, unowned] [if = 1, owned] 
	int owner = 0; // << example: int owner = 2; << this horizontal road owned by player 2.
	bool validation;

	// initializer
	bool setValidation();
	void setHousePosition(housePosition* left, housePosition* right);

	// in game functions

	// if invalid return 0, if success return 1, if the position is owned return 2. 
	int setOwner(int playerNumber);
};


//--------------------------------------------------------------------------------------------- Tile ---------------------------------------------------------------------------------------------


class tile
{
public:
	housePosition* topLeftHouse;
	housePosition* topRightHouse;
	housePosition* bottomLeftHouse;
	housePosition* bottomRightHouse;

	verticalRoad* leftVerticalRoad;
	verticalRoad* rightVerticalRoad;
	horizontalRoad* topHorizontalRoad;
	horizontalRoad* bottomHorizontalRoad;

	int xy[2]; // << xy[0] = X, xy[1] = y
	int state = 0; // << [if = 0, unowned] [if = 1, owned]
	int owner[4] = { 0, 0, 0, 0}; // << example: int owner = 2; << this tile owned by player 2.
	int numberOnTile;
	std::string resourceType;
	bool validation;

	// initializer
	bool setValidation();
	void setRoadPosition(horizontalRoad* top, horizontalRoad* bottom, verticalRoad* left, verticalRoad* right);
	void setHousePosition(housePosition* topleft, housePosition* topright, housePosition* bottomleft, housePosition* bottomright);
	void setNumberOnTile(int Number);
	void setResourceTypeOnTile(std::string inputResource);

	// in game functions

	void setOwner(); // set together with house.setOwner.
	
	
};

#endif
