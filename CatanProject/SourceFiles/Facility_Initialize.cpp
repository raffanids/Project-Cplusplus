#include "Facility_Initialize.h"

#include<iostream>
#include<vector>
#include<string>
#include<cmath>

#include "House_Road_Tile.h"

/*
	HOW TO CALL INITIALIZERS:

	housePosition House[6][6];
	housePosition realHouse[24];

	verticalRoad vRoad[5][6];
	verticalRoad realVRoad[18];

	horizontalRoad hRoad[6][5];
	horizontalRoad realHRoad[18];

	tile Tile[5][5];
	tile realTile[13];

	HOUSE_INITIALIZING(House, realHouse);
	VERTICAL_ROAD_INITIALIZING(vRoad, House, realVRoad);
	HORIZONTAL_ROAD_INITIALIZING(hRoad, House, realHRoad);
	TILE_INTIALIZING(Tile, vRoad, hRoad, House, realTile);
*/




//------------------------------------------------------------------------------------------- HOUSE ---------------------------------------------------------------------------------------

// (1)
void HOUSE_INITIALIZING(housePosition H[6][6],housePosition validH[24])
{
	// housePosition H[6][6];


	// set xy of house positions for checking
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			H[i][j].xy[0] = i;
			H[i][j].xy[1] = j;
		}
	
	// Set Validation to all houses
	int k = 0;
	for (int i = 0; i < 6; i++)
	{
		if ((2 == i) || (i == 3))
			for (int j = 0; j < 6; j++)
			{
				H[i][j].setValidation(true);
				validH[k] = H[i][j];
				k++;
			}

		else if ((1 == i) || (i == 4))
			for (int j = 0; j < 6; j++)
				if ((j < 1) || (j > 4))
					H[i][j].setValidation(false);
				else
				{
					H[i][j].setValidation(true);
					validH[k] = H[i][j];
					k++;
				}
		else if ((0 == i) || (i == 5))
			for (int j = 0; j < 6; j++)
				if ((j < 2) || (j > 3))
					H[i][j].setValidation(false);
				else
				{
					H[i][j].setValidation(true);
					validH[k] = H[i][j];
					k++;
				}
	}
}


// (2)
void CHECKING_HOUSE_POSITIONS(housePosition H[6][6]) 
{
	// cout xy of house positions for checking
	std::cout << "HousePosition (X,Y)\n";
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << "(" << H[i][j].xy[0] << "," << H[i][j].xy[1] << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
// overload for validHouse
void CHECKING_HOUSE_POSITIONS(housePosition validH[24])
{
	// cout xy of house positions for checking
	std::cout << "ValidHousePosition (X,Y)\n";
	for (int i = 0; i < 24; i++)
	{
			std::cout << "(" << validH[i].xy[0] << "," << validH[i].xy[1] << ") ";
	
	}
	std::cout << std::endl;

}



// (3)
void CHECK_HOUSE_VALIDATION(housePosition H[6][6])
{
	// cout to check validation of all houses
	std::cout << "House validation: \n";
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (H[i][j].validation == true)
				std::cout << 1;
			else if (H[i][j].validation == false)
				std::cout << 0;
			std::cout << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}


//------------------------------------------------------------------------------------------- VERTICAL_ROAD ---------------------------------------------------------------------------------------


// (1)
void VERTICAL_ROAD_INITIALIZING(verticalRoad vRoad[5][6] , housePosition H[6][6], verticalRoad valid_V_Road[18])
{
	// verticalRoad vRoad[5][6];

	// Setting house positions.

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			vRoad[i][j].setHousePosition(&H[i][j], &H[i + 1][j]);
		}
	}		

	// set xy of road positions for checking
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++)
		{
			vRoad[i][j].xy[0] = i;
			vRoad[i][j].xy[1] = j;
		}

	// Setting Vertical Roads Validations.
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (vRoad[i][j].setValidation())
			{
				valid_V_Road[k] = vRoad[i][j];
				k++;
			}

		}
	}
}

// (2)
void CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(verticalRoad vRoad[5][6])
{
	// cout house positions to check.
	std::cout << "VerticalRoad->housePosition [top(X,Y),bottom(X,Y)]\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << "[(" << vRoad[i][j].topHouse->xy[0] << "," << vRoad[i][j].topHouse->xy[1] << "),(" << vRoad[i][j].bottomHouse->xy[0] << "," << vRoad[i][j].bottomHouse->xy[1] << ")] ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
// overload
void CHECKING_HOUSE_POSITIONS_IN_VERTICAL_ROAD(verticalRoad vRoad[18])
{
	// cout house positions to check.
	std::cout << "ValidVerticalRoad->housePosition [top(X,Y),bottom(X,Y)]\n";
	for (int i = 0; i < 18; i++)
	{
		
			std::cout << "[(" << vRoad[i].topHouse->xy[0] << "," << vRoad[i].topHouse->xy[1] << "),(" << vRoad[i].bottomHouse->xy[0] << "," << vRoad[i].bottomHouse->xy[1] << ")] ";
		
	}
	std::cout << std::endl;
}

// (3)
void CHECKING_VERTICAL_ROAD_VALIDATION(verticalRoad vRoad[5][6]) 
{
	// cout Validations to check.
	std::cout << "VerticalRoad.validation Check :\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (vRoad[i][j].validation == true)
				std::cout << 1;
			else if (vRoad[i][j].validation == false)
				std::cout << 0;
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// (4)
void CHECKING_VERTICAL_ROAD_POSITION(verticalRoad vRoad[5][6])
{
	// cout xy of road positions for checking
	std::cout << "VerticalRoadPosition (X,Y) : \n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << "(" << vRoad[i][j].xy[0] << "," << vRoad[i][j].xy[1] << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
// overload for valid vertical road
void CHECKING_VERTICAL_ROAD_POSITION(verticalRoad vRoad[18])
{
	// cout xy of road positions for checking
	std::cout << "ValidVerticalRoadPosition (X,Y) : \n";
	for (int i = 0; i < 18; i++)
	{
		
		std::cout << "(" << vRoad[i].xy[0] << "," << vRoad[i].xy[1] << ") ";
		
	}
	std::cout << std::endl;

}


//-------------------------------------------------------------------  HORIZONTAL ROAD INITIALIZING ------------------------------------------------------------------------------------------------


// (1)
void HORIZONTAL_ROAD_INITIALIZING(horizontalRoad hRoad[6][5], housePosition H[6][6], horizontalRoad valid_H_Road[18])
{
	// Setting house positions.
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			hRoad[i][j].setHousePosition(&H[i][j], &H[i][j + 1]);
		}
	}



	// set xy of road positions for checking
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 5; j++)
		{
			hRoad[i][j].xy[0] = i;
			hRoad[i][j].xy[1] = j;
		}
	
	// Setting Horizontal Roads Validations.
	int k = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if(hRoad[i][j].setValidation())
			{
				valid_H_Road[k] = hRoad[i][j];
				k++;
			}
		}
	}
}

// (2)
void CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(horizontalRoad hRoad[6][5])
{
	// cout house positions to check.
		std::cout << "HorizontalRoad->housePosition [Left(X,Y),Right(X,Y)]\n";
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				std::cout << "[(" << hRoad[i][j].leftHouse->xy[0] << "," << hRoad[i][j].leftHouse->xy[1] << "),(" << hRoad[i][j].rightHouse->xy[0] << "," << hRoad[i][j].rightHouse->xy[1] << ")] ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
}
// overload
void CHECKING_HOUSE_POSITIONS_IN_HORIZONTAL_ROAD(horizontalRoad hRoad[18])
{
	// cout house positions to check.
	std::cout << "ValidHorizontalRoad->housePosition [Left(X,Y),Right(X,Y)]\n";
	for (int i = 0; i < 18; i++)
	{
			std::cout << "[(" << hRoad[i].leftHouse->xy[0] << "," << hRoad[i].leftHouse->xy[1] << "),(" << hRoad[i].rightHouse->xy[0] << "," << hRoad[i].rightHouse->xy[1] << ")] ";

	}
	std::cout << std::endl;
}


// (3)
void CHECKING_HORIZONTAL_ROAD_VALIDATION(horizontalRoad hRoad[6][5])
{

	// cout Validations to check.
	std::cout << "HorizontalRoad.validation Check :\n";
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (hRoad[i][j].validation == true)
				std::cout << "-";
			else if (hRoad[i][j].validation == false)
				std::cout << ".";
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

// (4)
void CHECKING_HORIZONTAL_ROAD_POSITION(horizontalRoad hRoad[6][5])
{
	// cout xy of road positions for checking
	std::cout << "HorizontalRoadPosition (X,Y) : \n";
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << "(" << hRoad[i][j].xy[0] << "," << hRoad[i][j].xy[1] << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
// overload for valid horizontal road
void CHECKING_HORIZONTAL_ROAD_POSITION(horizontalRoad hRoad[18])
{
	// cout xy of road positions for checking
	std::cout << "ValidHorizontalRoadPosition (X,Y) : \n";
	for (int i = 0; i < 18; i++)
	{
			std::cout << "(" << hRoad[i].xy[0] << "," << hRoad[i].xy[1] << ") ";
	}
	std::cout << std::endl;
}


//-------------------------------------------------------------------  TILE INITIALIZING ------------------------------------------------------------------------------------------------

// (1)
void TILE_INTIALIZING(tile T[5][5], verticalRoad vRoad[5][6], horizontalRoad hRoad[6][5], housePosition H[6][6], tile validT[13])
{
	// Setting Roads positions.

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			T[i][j].setRoadPosition(&hRoad[i][j], &hRoad[i + 1][j], &vRoad[i][j], &vRoad[i][j + 1]);
		}
	}

	// Settiing houses to tiles.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			T[i][j].setHousePosition(T[i][j].topHorizontalRoad->leftHouse, T[i][j].topHorizontalRoad->rightHouse, T[i][j].bottomHorizontalRoad->leftHouse, T[i][j].bottomHorizontalRoad->rightHouse);
		}
	}

	// set xy of tiles positions for checking
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			T[i][j].xy[0] = i;
			T[i][j].xy[1] = j;
		}


	//	Setting Tile Validations.
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (T[i][j].setValidation())
			{
				validT[k] = T[i][j];
				k++;
			}
		}
	}

}

// (2)
void CHECKING_ROAD_POSITIONS_IN_TILE(tile T[5][5])
{
	// Cout roads positions for checking.

		std::cout << "Tile->Road {hRoad [top(x,y),bottom(x,y)],vRoad [left(x,y),right(x,y)]} :\n";
		for (int i = 0; i < 5; i++)
		{
			std::cout << "Tile row" << i + 1 << ":" << std::endl;
			for (int j = 0; j < 5; j++)
			{
				std::cout << "{hRoad [top(" << T[i][j].topHorizontalRoad->xy[0] << "," << T[i][j].topHorizontalRoad->xy[1] << "),bottom("
					<< T[i][j].bottomHorizontalRoad->xy[0] << "," << T[i][j].bottomHorizontalRoad->xy[1]
					<< ")],vRoad [left(" << T[i][j].leftVerticalRoad->xy[0] << "," << T[i][j].leftVerticalRoad->xy[1] << "),right(" << T[i][j].rightVerticalRoad->xy[0] << ","
					<< T[i][j].rightVerticalRoad->xy[1] << ")]} ";
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
}
// overload
void CHECKING_ROAD_POSITIONS_IN_TILE(tile T[13])
{
	// Cout roads positions for checking.

	std::cout << "ValidTile->Road {hRoad [top(x,y),bottom(x,y)],vRoad [left(x,y),right(x,y)]} :\n";
	for (int i = 0; i < 13; i++)
	{
			std::cout << "{hRoad [top(" << T[i].topHorizontalRoad->xy[0] << "," << T[i].topHorizontalRoad->xy[1] << "),bottom("
				<< T[i].bottomHorizontalRoad->xy[0] << "," << T[i].bottomHorizontalRoad->xy[1]
				<< ")],vRoad [left(" << T[i].leftVerticalRoad->xy[0] << "," << T[i].leftVerticalRoad->xy[1] << "),right(" << T[i].rightVerticalRoad->xy[0] << ","
				<< T[i].rightVerticalRoad->xy[1] << ")]} ";
			std::cout << std::endl;
		
	}
	std::cout << std::endl;
}

// (3)
void CHECKING_TILE_VALIDATION(tile T[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (T[i][j].validation == true)
				std::cout << "[]";
			else if (T[i][j].validation == false)
				std::cout << " .";
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

// (4)
void CHECKING_HOUSE_POSITIONS_IN_TILE(tile T[5][5])
{
	// cout house position in tile for checking.
	std::cout << "Tile->House {topHouse [left(x,y),right(x,y)],bottomHouse [left(x,y),right(x,y)]} :\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << "{topHouse [left(" << T[i][j].topLeftHouse->xy[0] << "," << T[i][j].topLeftHouse->xy[1] << "),right("
				<< T[i][j].topRightHouse->xy[0] << "," << T[i][j].topRightHouse->xy[1]
				<< ")],bottomHouse [left(" << T[i][j].bottomLeftHouse->xy[0] << "," << T[i][j].bottomLeftHouse->xy[1] << "),right(" << T[i][j].bottomRightHouse->xy[0] << ","
				<< T[i][j].bottomRightHouse->xy[1] << ")]} ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
// overload
void CHECKING_HOUSE_POSITIONS_IN_TILE(tile T[13])
{
	// cout house position in tile for checking.
	std::cout << "ValidTile->House {topHouse [left(x,y),right(x,y)],bottomHouse [left(x,y),right(x,y)]} :\n";
	for (int i = 0; i < 13; i++)
	{
			std::cout << "{topHouse [left(" << T[i].topLeftHouse->xy[0] << "," << T[i].topLeftHouse->xy[1] << "),right("
				<< T[i].topRightHouse->xy[0] << "," << T[i].topRightHouse->xy[1]
				<< ")],bottomHouse [left(" << T[i].bottomLeftHouse->xy[0] << "," << T[i].bottomLeftHouse->xy[1] << "),right(" << T[i].bottomRightHouse->xy[0] << ","
				<< T[i].bottomRightHouse->xy[1] << ")]} ";
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

// (5)
void CHECKING_TILE_POSITIONS(tile T[5][5])
{
	// cout xy of tile positions for checking
	std::cout << "TilePosition (X,Y) : \n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << "(" << T[i][j].xy[0] << "," << T[i][j].xy[1] << ") ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}
// overload for validTile
void CHECKING_TILE_POSITIONS(tile validT[13])
{
	// cout xy of tile positions for checking
	std::cout << "ValidTilePosition (X,Y) : \n";
	for (int i = 0; i < 13; i++)
	{
		std::cout << "(" << validT[i].xy[0] << "," << validT[i].xy[1] << ") ";
	}
	std::cout << std::endl;
}

// (6)
void SETTING_NUMBER_ON_TILE(tile realTile[13], int inputNumber[13])
{
	for (int i = 0; i < 13; i++)
	{
		realTile[i].setNumberOnTile(inputNumber[i]);
	}

}

// (7)
void SETTING_RESOURCE_TYPE_ON_TILE(tile realTile[13], std::string inputResourceType[13])
{
	for (int i = 0; i < 13; i++)
	{
		realTile[i].setResourceTypeOnTile(inputResourceType[i]);
	}

}

