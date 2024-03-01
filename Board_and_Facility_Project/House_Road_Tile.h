#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#ifndef HOUSE_ROAD_TILE_HPP
#define HOUSE_ROAD_TILE_HPP


class housePosition
{
public:
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state; // << [if = 0, unowned] [if = 1, house] [if = 2, city]
	int owner; // << example: int state = 2; << this position owned by player 2.
	bool validation;

	void setValidation(bool valid);

};

class verticalRoad
{
public:
	housePosition* topHouse;
	housePosition* bottomHouse;
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state; // << [if = 0, unowned] [if = 1, owned] 
	int owner; // << example: int state = 2; << this vertical road owned by player 2.
	bool validation;

	bool setValidation();
	

	void setHousePosition(housePosition* top, housePosition* bottom);
	
};

class horizontalRoad
{
public:
	housePosition* leftHouse;
	housePosition* rightHouse;
	int xy[2]; // << xy[0] = X, xy[1] = y
	int state; // << [if = 0, unowned] [if = 1, owned] 
	int owner; // << example: int state = 2; << this horizontal road owned by player 2.
	bool validation;

	bool setValidation();

	void setHousePosition(housePosition* left, housePosition* right);
	
};

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
	int state; // << [if = 0, unowned] [if = 1, owned]
	int owner; // << example: int state = 2; << this tile owned by player 2.
	int numberOnTile;
	char resourceType;
	bool validation;

	bool setValidation();
	

	void setRoadPosition(horizontalRoad* top, horizontalRoad* bottom, verticalRoad* left, verticalRoad* right);

	void setHousePosition(housePosition* topleft, housePosition* topright, housePosition* bottomleft, housePosition* bottomright);
	
};

#endif
