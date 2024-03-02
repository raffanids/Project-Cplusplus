#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"
#include "Facility_Initialize.h"

/*
	to check for dubug :
		
		CHECKING_HOUSE_POSITIONS(H);
		CHECK_HOUSE_VALIDATION(H);

		CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(vRoad, H);
		CHECKING_VERTICAL_ROAD_VALIDATION(vRoad, H);
		CHECKING_VERTICAL_ROAD_POSITION(vRoad, H);

		CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(hRoad, H);
		CHECKING_HORIZONTAL_ROAD_VALIDATION(hRoad, H);
		CHECKING_HORIZONTAL_ROAD_POSITION(hRoad, H);

		CHECKING_ROAD_POSITIONS_IN_TILE(T, vRoad, hRoad, H);
		CHECKING_TILE_VALIDATION(T, vRoad, hRoad, H);
		CHECKING_HOUSE_POSITIONS_IN_TILE(T, vRoad, hRoad, H);
*/
int main()
{
	housePosition H[6][6];
	housePosition realH[24];

	verticalRoad vRoad[5][6];
	verticalRoad realVRoad[18];
	
	horizontalRoad hRoad[6][5];
	horizontalRoad realHRoad[18];
	
	tile T[5][5];
	tile realT[13];

	// Initialize
	HOUSE_INITIALIZING(H, realH);
	VERTICAL_ROAD_INITIALIZING(vRoad, H, realVRoad);
	HORIZONTAL_ROAD_INITIALIZING(hRoad, H, realHRoad);
	TILE_INTIALIZING(T, vRoad, hRoad, H, realT);

	//Checking
	//House
	CHECKING_HOUSE_POSITIONS(H);
	CHECKING_HOUSE_POSITIONS(realH);
	CHECK_HOUSE_VALIDATION(H);
	//Vertical road
	CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(vRoad);
	CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(realVRoad);
	CHECKING_VERTICAL_ROAD_VALIDATION(vRoad);
	CHECKING_VERTICAL_ROAD_POSITION(vRoad);
	CHECKING_VERTICAL_ROAD_POSITION(realVRoad);
	//Horizontal road
	CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(hRoad);
	CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(realHRoad);
	CHECKING_HORIZONTAL_ROAD_VALIDATION(hRoad);
	CHECKING_HORIZONTAL_ROAD_POSITION(hRoad);
	CHECKING_HORIZONTAL_ROAD_POSITION(realHRoad);
	//Tile
	CHECKING_ROAD_POSITIONS_IN_TILE(T);
	CHECKING_ROAD_POSITIONS_IN_TILE(realT);
	CHECKING_TILE_VALIDATION(T);
	CHECKING_HOUSE_POSITIONS_IN_TILE(T);
	CHECKING_HOUSE_POSITIONS_IN_TILE(realT);
	CHECKING_TILE_POSITIONS(T);
	CHECKING_TILE_POSITIONS(realT);
	


	
}