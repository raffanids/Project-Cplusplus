#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

int main()
{
    // ***** WINDOW Initializaton *****
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game"); //ã¹·Õè¹ÕéÅÍ§à»ç¹ 720p ä»¡èÍ¹¹Ð
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

    sf::Texture RockPNG;
    RockPNG.loadFromFile("RockPNG.png");

    sf::Texture RockPNG1;
    RockPNG1.loadFromFile("RockPNG1.png");
    
    sf::Texture card;
    card.loadFromFile("card.jpg");

    sf::Texture housecard;
    housecard.loadFromFile("housecard.png");

    sf::Texture Buildingcard;
    Buildingcard.loadFromFile("Buildingcard.png");

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

    sf::Sprite Tile14;
    Tile14.setTexture(RockPNG);
    Tile14.setScale(0.52f, 0.31f);
    Tile14.setPosition(58, 540);

    sf::Sprite Tile15;
    Tile15.setTexture(RockPNG1);
    Tile15.setScale(0.48f, 0.30f);
    Tile15.setPosition(880, -20);

    sf::Sprite Tile16;
    Tile16.setTexture(card);
    Tile16.setScale(0.60f, 0.40f);
    Tile16.setPosition(900, 120);

    sf::Sprite Tile17;
    Tile17.setTexture(card);
    Tile17.setScale(0.60f, 0.40f);
    Tile17.setPosition(950, 120);

    sf::Sprite Tile18;
    Tile18.setTexture(card);
    Tile18.setScale(0.60f, 0.40f);
    Tile18.setPosition(1000, 120);

    sf::Sprite Tile19;
    Tile19.setTexture(card);
    Tile19.setScale(0.60f, 0.40f);
    Tile19.setPosition(1070, 120);

    sf::Sprite Tile20;
    Tile20.setTexture(housecard);
    Tile20.setScale(0.15f, 0.14f);
    Tile20.setPosition(40, 500);

    sf::Sprite Tile21;
    Tile21.setTexture(Buildingcard);
    Tile21.setScale(0.15f, 0.14f);
    Tile21.setPosition(150, 500);

 
    
    /* Finished
    //                    ***** MUSIC Initialization & Play *****
    sf::Music music;
    if (!music.openFromFile("CatanMusic.mp3"))
        return EXIT_FAILURE;

    music.play();
    //                    ^^^^^ MUSIC Initialization & Play ^^^^^
    */



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
                printf("%d,%d", (int)mouseX, (int)mouseY);
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
        window.draw(Tile14);
        window.draw(Tile15);
        window.draw(Tile16);
        window.draw(Tile17);
        window.draw(Tile18);
        window.draw(Tile19);
        window.draw(Tile20);
        window.draw(Tile21);

        window.display();
    }

    return 0;
}