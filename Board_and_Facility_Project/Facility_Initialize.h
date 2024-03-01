#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"

#ifndef FACILITY_INITIALIZE_HPP
#define FACILITY_INITIALIZE_HPP

// (1)
void HOUSE_INITIALIZING(housePosition [6][6], housePosition validH[24]);

// (2)
void CHECKING_HOUSE_POSITIONS(housePosition [6][6]);
// overload for valid house
void CHECKING_HOUSE_POSITIONS(housePosition[24]);

// (3)
void CHECK_HOUSE_VALIDATION(housePosition [6][6]);

//------------------------------------------------------------------------------------------- VERTICAL_ROAD ---------------------------------------------------------------------------------------

// (1)
void VERTICAL_ROAD_INITIALIZING(verticalRoad [5][6], housePosition [6][6], verticalRoad valid_V_Road[18]);

// (2)
void CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(verticalRoad [5][6]);
// overload
void CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(verticalRoad[18]);

// (3)
void CHECKING_VERTICAL_ROAD_VALIDATION(verticalRoad [5][6]);

// (4)
void CHECKING_VERTICAL_ROAD_POSITION(verticalRoad [5][6]);
// overload for validVerticalRoad
void CHECKING_VERTICAL_ROAD_POSITION(verticalRoad vRoad[18]);


//------------------------------------------------------------------------------------------- HORIZONTAL_ROAD ---------------------------------------------------------------------------------------

// (1)
void HORIZONTAL_ROAD_INITIALIZING(horizontalRoad [6][5], housePosition [6][6], horizontalRoad valid_H_Road[18]);

// (2)
void CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(horizontalRoad [6][5]);
// overload
void CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(horizontalRoad[18]);


// (3)
void CHECKING_HORIZONTAL_ROAD_VALIDATION(horizontalRoad [6][5]);

// (4)
void CHECKING_HORIZONTAL_ROAD_POSITION(horizontalRoad [6][5]);
// overload for validHorizontalRoad
void CHECKING_HORIZONTAL_ROAD_POSITION(horizontalRoad hRoad[18]);

//------------------------------------------------------------------------------------------ TILE INITIALIZING ------------------------------------------------------------------------------------------------

// (1)
void TILE_INTIALIZING(tile [5][5], verticalRoad [5][6], horizontalRoad [6][5], housePosition [6][6], tile validT[13]);

// (2)
void CHECKING_ROAD_POSITIONS_IN_TILE(tile [5][5]);
// overload
void CHECKING_ROAD_POSITIONS_IN_TILE(tile[13]);

// (3)
void CHECKING_TILE_VALIDATION(tile [5][5]);

// (4)
void CHECKING_HOUSE_POSITIONS_IN_TILE(tile [5][5]);
// overload
void CHECKING_HOUSE_POSITIONS_IN_TILE(tile[13]);

// (5)
void CHECKING_TILE_POSITIONS(tile T[5][5]);
// overload for validTile
void CHECKING_TILE_POSITIONS(tile T[13]);





#endif


