#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using namespace std;

void showMap(sf::RenderWindow& window, const sf::Sprite& backgroundmap, vector<sf::Sprite>& tiles, vector<sf::Sprite>& numSprites) {
    window.draw(backgroundmap);

    vector<sf::Vector2f> tilePositions = {
        sf::Vector2f(585, 98),
        sf::Vector2f(477, 202),
        sf::Vector2f(585, 202),
        sf::Vector2f(693, 202),
        sf::Vector2f(369, 306),
        sf::Vector2f(477, 306),
        sf::Vector2f(585, 306),
        sf::Vector2f(693, 306),
        sf::Vector2f(801, 306),
        sf::Vector2f(477, 410),
        sf::Vector2f(585, 410),
        sf::Vector2f(693, 410),
        sf::Vector2f(585, 514)
    };

    vector<sf::Vector2f> numSpritePositions = {
        sf::Vector2f(621, 133),
        sf::Vector2f(513, 237),
        sf::Vector2f(621, 237),
        sf::Vector2f(729, 237),
        sf::Vector2f(405, 341),
        sf::Vector2f(513, 341),
        sf::Vector2f(621, 341),
        sf::Vector2f(729, 341),
        sf::Vector2f(837, 341),
        sf::Vector2f(513, 445),
        sf::Vector2f(621, 445),
        sf::Vector2f(729, 445),
        sf::Vector2f(621, 549)
    };

    for (size_t i = 0; i < tiles.size(); ++i) {
        tiles[i].setPosition(tilePositions[i]);
        tiles[i].setScale(0.15f, 0.15f);
        window.draw(tiles[i]);

        numSprites[i].setPosition(numSpritePositions[i]);
        numSprites[i].setScale(0.20f, 0.20f);
        window.draw(numSprites[i]);
    }
}

void showMain(sf::RenderWindow& window, sf::Sprite& backGroundmain, sf::Sprite& buttonplay, sf::Sprite& buttonhowtoplay, bool& showMainPage) {
    if (showMainPage) {
        backGroundmain.setScale(
            static_cast<float>(window.getSize().x) / backGroundmain.getTexture()->getSize().x,
            static_cast<float>(window.getSize().y) / backGroundmain.getTexture()->getSize().y
        );
        backGroundmain.setOrigin(backGroundmain.getLocalBounds().width / 2, backGroundmain.getLocalBounds().height / 2);
        backGroundmain.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        buttonplay.setScale(0.5f, 0.5f);
        buttonplay.setPosition(75, 400);

        buttonhowtoplay.setScale(0.5f, 0.5f);
        buttonhowtoplay.setPosition(85, 450);

        window.draw(backGroundmain);
        window.draw(buttonplay);
        window.draw(buttonhowtoplay);
    }
}

void showHowtoplay(sf::RenderWindow& window, sf::Sprite& backGroundhtp, sf::Sprite& buttonplay, bool& showHowtoplayPage) {
    backGroundhtp.setScale(
        static_cast<float>(window.getSize().x) / backGroundhtp.getTexture()->getSize().x,
        static_cast<float>(window.getSize().y) / backGroundhtp.getTexture()->getSize().y
    );

    backGroundhtp.setOrigin(backGroundhtp.getLocalBounds().width / 2, backGroundhtp.getLocalBounds().height / 2);
    backGroundhtp.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.draw(backGroundhtp);
    window.draw(buttonplay);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Catan Game");

    sf::Texture grain, ore, sheep, wood, brick, two, three, four, five, six, eight, nine, ten, eleven, twelve;
    grain.loadFromFile("riceTilePNG.png");
    ore.loadFromFile("oreTilePNG.png");
    sheep.loadFromFile("sheepTilePNG.png");
    wood.loadFromFile("woodTilePNG.png");
    brick.loadFromFile("brickTilePNG.png");
    two.loadFromFile("two.png");
    three.loadFromFile("three.png");
    four.loadFromFile("four.png");
    five.loadFromFile("five.png");
    six.loadFromFile("six.png");
    eight.loadFromFile("eight.png");
    nine.loadFromFile("nine.png");
    ten.loadFromFile("ten.png");
    eleven.loadFromFile("eleven.png");
    twelve.loadFromFile("twelve.png");

    sf::Texture backGroundMap;
    backGroundMap.loadFromFile("backGroundJPG.jpg");

    sf::Texture backGroundMain;
    backGroundMain.loadFromFile("startBackGround.png");

    sf::Texture backGroundHTP;
    backGroundHTP.loadFromFile("winterbackground.png");

    sf::Sprite backGroundmap, backGroundmain, backGroundhtp;
    backGroundmap.setTexture(backGroundMap);
    backGroundmain.setTexture(backGroundMain);
    backGroundhtp.setTexture(backGroundHTP);

    vector<sf::Texture> textures = { sheep, wood, brick, grain, ore, sheep, grain, ore, brick, wood, sheep, grain, wood };
    vector<sf::Texture> num = { two, three, four, five, six, eight, nine, ten, eleven, twelve , five, six, eight };

    random_device rd;
    mt19937 g(rd());
    shuffle(textures.begin(), textures.end(), g);
    shuffle(num.begin(), num.end(), g);

    vector<sf::Sprite> tiles;
    vector<sf::Sprite> numSprites;

    for (int i = 0; i < 13; ++i) {
        sf::Sprite tile;
        tile.setTexture(textures[i]);
        tiles.push_back(tile);

        sf::Sprite numSprite;
        numSprite.setTexture(num[i]);
        numSprites.push_back(numSprite);
    }

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("playBotton.png");

    sf::Sprite buttonplay;
    buttonplay.setTexture(buttonTexture);

    sf::Texture button2Texture;
    button2Texture.loadFromFile("HowToPlayBotton.png");

    sf::Sprite buttonhowtoplay;
    buttonhowtoplay.setTexture(button2Texture);

    bool showMainPage = true;
    bool showHowtoplayPage = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::FloatRect buttonBounds = buttonplay.getGlobalBounds();
                    sf::FloatRect button2Bounds = buttonhowtoplay.getGlobalBounds();
                    if (buttonBounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                        showMainPage = false;
                        showHowtoplayPage = false;
                    }
                    else if (button2Bounds.contains(static_cast<sf::Vector2f>(mousePos))) {
                        showMainPage = false;
                        showHowtoplayPage = true;
                    }
                }
            }
        }

        window.clear();

        if (showMainPage) {
            showMain(window, backGroundmain, buttonplay, buttonhowtoplay, showMainPage);
        }
        else if (showHowtoplayPage) {
            showHowtoplay(window, backGroundhtp, buttonplay, showHowtoplayPage);
        }
        else {
            showMap(window, backGroundmap, tiles, numSprites);
        }

        window.display();
    }

    return 0;
}
