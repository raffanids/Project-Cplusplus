#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
    // ***** WINDOW Initializaton *****
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game"); //ในที่นี้ลองเป็น 720p ไปก่อนนะ
    //
    



    //      *อาจจะไม่ใช้้*       ***** SHAPE Initialization *****
    /*
    sf::RectangleShape tileShape;
    tileShape.setPosition(1.0 , 1.0);
    tileShape.setSize(sf::Vector2f(200.0, 200.0));
    */
    //                       ^^^^^ SHAPE Initialization ^^^^^




    //                      ***** PICTURE Initialization *****
        // 1) Loading Pictures from file.
        // 2) Setting textures to Sprites.
        // 3) Setting Pictures Properties.

    // *** (1) Loading Pictures from file ***
    // - Resouces Tiles 
    // - 
    
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


    
    // *** (2) Set textures to Sprites ***
    // - Resouces Tiles

    sf::Sprite riceTile;
    riceTile.setTexture(riceTilePNG);
    riceTile.setPosition(100, 100);

    sf::Sprite oreTile;
    oreTile.setTexture(oreTilePNG);
    oreTile.setPosition(200, 200);

    sf::Sprite sheepTile;
    sheepTile.setTexture(sheepTilePNG);
    sheepTile.setPosition(300, 300);

    sf::Sprite woodTile;
    woodTile.setTexture(woodTilePNG);
    woodTile.setPosition(400, 400);

    sf::Sprite brickTile;
    brickTile.setTexture(brickTilePNG);
    brickTile.setPosition(500, 500);



    // *** (3) Setting Pictures Properties ***
    riceTile.setScale(0.25f, 0.25f);
    oreTile.setScale(0.25f, 0.25f);
    sheepTile.setScale(0.25f, 0.25f);
    woodTile.setScale(0.25f, 0.25f);
    brickTile.setScale(0.25f, 0.25f);

    //                      ^^^^^ PICTURE Initialization ^^^^^
   




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
        sf::Event event; //Sensing Realtime Events here
        while (window.pollEvent(event))
        {

            //Close window
            if (event.type == sf::Event::Closed)
                window.close();
            //Close window

   
        }


        
        window.clear();
        
        window.draw(riceTile);
        window.draw(oreTile);
        window.draw(sheepTile);
        window.draw(woodTile);
        window.draw(brickTile);

        

        window.display();
    }

    return 0;
}
