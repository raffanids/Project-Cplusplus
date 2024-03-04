#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game");

    sf::Texture grain;
    grain.loadFromFile("riceTilePNG.png");

    sf::Texture ore;
    ore.loadFromFile("oreTilePNG.png");

    sf::Texture sheep;
    sheep.loadFromFile("sheepTilePNG.png");

    sf::Texture wood;
    wood.loadFromFile("woodTilePNG.png");

    sf::Texture brick;
    brick.loadFromFile("brickTilePNG.png");

    sf::Texture two;
    two.loadFromFile("two.png");

    sf::Texture three;
    three.loadFromFile("three.png");

    sf::Texture four;
    four.loadFromFile("four.png");

    sf::Texture five;
    five.loadFromFile("five.png");

    sf::Texture six;
    six.loadFromFile("six.png");

    sf::Texture eight;
    eight.loadFromFile("eight.png");

    sf::Texture nine;
    nine.loadFromFile("nine.png");

    sf::Texture ten;
    ten.loadFromFile("ten.png");

    sf::Texture eleven;
    eleven.loadFromFile("eleven.png");

    sf::Texture twelve;
    twelve.loadFromFile("twelve.png");

    sf::Texture backGroundTexture;
    backGroundTexture.loadFromFile("backGroundJPG.jpg");

    sf::Sprite backGround;
    backGround.setTexture(backGroundTexture);

    vector<sf::Texture> textures = { sheep, wood, brick, grain, ore, sheep, grain, ore, brick, wood, sheep, grain, wood };
    vector<sf::Texture> num = { two, three, four, five, six, eight, nine, ten, eleven, twelve , five, six, eight };
    
    random_device rd;
    mt19937 g(rd());

    shuffle(textures.begin(), textures.end(), g);
    shuffle(num.begin(), num.end(), g);

    vector<sf::Sprite> tiles;
    vector<sf::Sprite> numSprites;

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
        tiles.push_back(tile);
    }

    for (int i = 0; i < num.size(); ++i) {
        sf::Sprite numSprite;
        numSprite.setTexture(num[i]);
        numSprite.setScale(0.20f, 0.20f);
        switch (i) {
        case 0:
            numSprite.setPosition(621, 133);
            break;
        case 1:
            numSprite.setPosition(513, 237);
            break;
        case 2:
            numSprite.setPosition(621, 237);
            break;
        case 3:
            numSprite.setPosition(729, 237);
            break;
        case 4:
            numSprite.setPosition(405, 341);
            break;
        case 5:
            numSprite.setPosition(513, 341);
            break;
        case 6:
            numSprite.setPosition(621, 341);
            break;
        case 7:
            numSprite.setPosition(729, 341);
            break;
        case 8:
            numSprite.setPosition(837, 341);
            break;
        case 9:
            numSprite.setPosition(513, 445);
            break;
        case 10:
            numSprite.setPosition(621, 445);
            break;
        case 11:
            numSprite.setPosition(729, 445);
            break;
        case 12:
            numSprite.setPosition(621, 549);
            break;
        default:
            break;
        }
        numSprites.push_back(numSprite);
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

        for (auto& numSprite : numSprites) {
            window.draw(numSprite);
        }

        window.display();
    }

    return 0;
}
