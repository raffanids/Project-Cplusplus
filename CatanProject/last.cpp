#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game");

    sf::Texture grainTexture;
    grainTexture.loadFromFile("riceTilePNG.png");

    sf::Texture oreTexture;
    oreTexture.loadFromFile("oreTilePNG.png");

    sf::Texture sheepTexture;
    sheepTexture.loadFromFile("sheepTilePNG.png");

    sf::Texture woodTexture;
    woodTexture.loadFromFile("woodTilePNG.png");

    sf::Texture brickTexture;
    brickTexture.loadFromFile("brickTilePNG.png");

    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile("backGroundJPG.jpg");

    sf::Sprite backGround;
    backGround.setTexture(backGroundTexture);

    vector<sf::Texture> textures = { sheepTexture, woodTexture, brickTexture, grainTexture, oreTexture, sheepTexture, grainTexture, oreTexture, brickTexture, woodTexture, sheepTexture, grainTexture, woodTexture };
    vector<int> numbers = { 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 5, 6 };

    random_device rd;
    mt19937 g(rd());

    shuffle(textures.begin(), textures.end(), g);
    shuffle(numbers.begin(), numbers.end(), g);

    vector<sf::Sprite> tiles;
    vector<sf::Text> textNumbers;

    for (int i = 0; i < textures.size(); ++i) {
        sf::Sprite tile;
        tile.setTexture(textures[i]);
        tile.setScale(0.15f, 0.15f);
        switch (i) {
        case 0:
            tile.setPosition(585, 98);
            break;
        case 1:
            tile.setPosition(477, 202);
            break;
        case 2:
            tile.setPosition(585, 202);
            break;
        case 3:
            tile.setPosition(693, 202);
            break;
        case 4:
            tile.setPosition(369, 306);
            break;
        case 5:
            tile.setPosition(477, 306);
            break;
        case 6:
            tile.setPosition(585, 306);
            break;
        case 7:
            tile.setPosition(693, 306);
            break;
        case 8:
            tile.setPosition(801, 306);
            break;
        case 9:
            tile.setPosition(477, 410);
            break;
        case 10:
            tile.setPosition(585, 410);
            break;
        case 11:
            tile.setPosition(693, 410);
            break;
        case 12:
            tile.setPosition(585, 514);
            break;
        default:
            break;
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseMoved) {
                    float mouseX = event.mouseMove.x;
                    float mouseY = event.mouseMove.y;
                    cout << "Mouse Position: " << mouseX << ", " << mouseY << endl;
                }
            }

            window.clear();

            window.draw(backGround);
            for (auto& tile : tiles) {
                window.draw(tile);
            }

            for (auto& number : textNumbers) {
                window.draw(number);
            }

            window.display();
        }

        
    }

    return 0;
}
