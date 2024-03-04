/*#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "House_Road_Tile.h"
#include "Facility_Initialize.h"
#include "Resource.h"
#include "Facility.h"
#include "player.h"
#include "bank.h"
#include "GameLoop.h"
#include "randomNumber.h"


int main()
{
    srand(time(0));
    // ***** WINDOW Initializaton *****
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game"); //ในที่นี้ลองเป็น 720p ไปก่อนนะ
    //


    

    //                      ***** PICTURE Initialization *****
        // 1) Loading Pictures from file.
        // 2) Setting textures to Sprites.
        // 3) Setting Pictures Properties.

    // *** (1) Loading Pictures from file ***
    // - Resouces Tiles 
    // - Background
    
    // ** Resouces Tiles ** 
    
    sf::Texture riceTilePNG;
    riceTilePNG.loadFromFile("riceTilePNG.png");

    sf::Texture oreTilePNG;
    oreTilePNG.loadFromFile("oreTilePNG.png");

    sf::Texture sheepTilePNG;
    sheepTilePNG.loadFromFile("sheepTilePNG.png");

    sf::Texture woodTilePNG;
    woodTilePNG.loadFromFile("woodTilePNG.png");

    sf::Texture brickTilePNG;
    brickTilePNG.loadFromFile("brickTilePNG.png");
    
    // Background
    sf::Texture backGroundJPG;
    backGroundJPG.loadFromFile("backGroundJPG.jpg");
    
    // *** (2) Set textures to Sprites ***
    // - Resouces Tiles
    
    
    ////////////////////////////////////////////////std::vector<Tile> Tiles[13];
    // background
    sf::Sprite backGround;
    backGround.setTexture(backGroundJPG);
    
    // 1 Tile = 108 X 108 pixels
    // Row1
    sf::Sprite Tile1;
    Tile1.setTexture(riceTilePNG);
    Tile1.setScale(0.15f, 0.15f);
    Tile1.setPosition(585, 98);

    // Row2
    sf::Sprite Tile2;
    Tile2.setTexture(oreTilePNG);
    Tile2.setScale(0.15f, 0.15f);
    Tile2.setPosition(477, 202);

    sf::Sprite Tile3;
    Tile3.setTexture(oreTilePNG);
    Tile3.setScale(0.15f, 0.15f);
    Tile3.setPosition(585, 202);

    sf::Sprite Tile4;
    Tile4.setTexture(oreTilePNG);
    Tile4.setScale(0.15f, 0.15f);
    Tile4.setPosition(693, 202);

    // Row3
    sf::Sprite Tile5;
    Tile5.setTexture(sheepTilePNG);
    Tile5.setScale(0.15f, 0.15f);
    Tile5.setPosition(369, 306);

    sf::Sprite Tile6;
    Tile6.setTexture(sheepTilePNG);
    Tile6.setScale(0.15f, 0.15f);
    Tile6.setPosition(477, 306);

    sf::Sprite Tile7;
    Tile7.setTexture(sheepTilePNG);
    Tile7.setScale(0.15f, 0.15f);
    Tile7.setPosition(585, 306);

    sf::Sprite Tile8;
    Tile8.setTexture(sheepTilePNG);
    Tile8.setScale(0.15f, 0.15f);
    Tile8.setPosition(693, 306);

    sf::Sprite Tile9;
    Tile9.setTexture(sheepTilePNG);
    Tile9.setScale(0.15f, 0.15f);
    Tile9.setPosition(801, 306);

    // Row4
    sf::Sprite Tile10;
    Tile10.setTexture(woodTilePNG);
    Tile10.setScale(0.15f, 0.15f);
    Tile10.setPosition(477, 410);

    sf::Sprite Tile11;
    Tile11.setTexture(woodTilePNG);
    Tile11.setScale(0.15f, 0.15f);
    Tile11.setPosition(585, 410);

    sf::Sprite Tile12;
    Tile12.setTexture(woodTilePNG);
    Tile12.setScale(0.15f, 0.15f);
    Tile12.setPosition(693, 410);

    //Row5
    sf::Sprite Tile13;
    Tile13.setTexture(brickTilePNG);
    Tile13.setScale(0.15f, 0.15f);
    Tile13.setPosition(585, 514);


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




    /* Finished
    //                    ***** MUSIC Initialization & Play *****
    sf::Music music;
    if (!music.openFromFile("CatanMusic.mp3"))
        return EXIT_FAILURE;
     
    music.play();
    //                    ^^^^^ MUSIC Initialization & Play ^^^^^
    */

   
/*
    while (window.isOpen())
    { 

        sf::Event event; 
        while (window.pollEvent(event))
        {   //Sensing Realtime Events in here

            //Close window
            if (event.type == sf::Event::Closed)
                window.close();
            //Close window

            float mouseX = event.mouseMove.x;
            float mouseY = event.mouseMove.y;

            if (event.type == sf::Event::MouseMoved)
                printf("%d,%d", (int)mouseX , (int)mouseY );
                std::cout << " ";
        }

       

        
        window.clear();
        
        window.draw(backGround);
        window.draw(Tile1);
        window.draw(Tile2);
        window.draw(Tile3);
        window.draw(Tile4);
        window.draw(Tile5);
        window.draw(Tile6);
        window.draw(Tile7);
        window.draw(Tile8);
        window.draw(Tile9);
        window.draw(Tile10);
        window.draw(Tile11);
        window.draw(Tile12);
        window.draw(Tile13);
        
        

        window.display();
    }

    return 0;
}
*/