#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

int main() 
{
    const int screenSize = 800;
    sf::RenderWindow window(sf::VideoMode(screenSize, screenSize), "Isometric tiles");
    window.setFramerateLimit(60);
    const int tileSize = 50;
    const float scale = screenSize / 16.0f / tileSize;
    //(5, 0.5), (10, 2), (15, 4.5), (20, 8), 
    std::vector<std::vector<sf::Sprite*>*>* tileBoard = new std::vector<std::vector<sf::Sprite*>*>(tileSize);
    for (int col = 0; col < tileSize; col++) {
        (*tileBoard)[col] = new std::vector<sf::Sprite*>(tileSize); 
    }
    for (int col = 0; col < tileSize; col++) {
        for (int row = 0; row < tileSize; row++) {
            (*(*tileBoard)[col])[row] = new sf::Sprite();
        }
    }
    sf::Sprite tile;

    // Texture for the sprite
    sf::Texture tileTexture;
    tileTexture.loadFromFile("resources/block.png");

    for (int col = 0; col < tileSize; col++) {
        for (int row = 0; row < tileSize; row++) {
            (*(*tileBoard)[col])[row] -> setOrigin(8, 8);
            (*(*tileBoard)[col])[row] -> setTexture(tileTexture);
            (*(*tileBoard)[col])[row] -> scale(scale, scale);
        }
    }

    // Main loop
    int frame = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int col = 0; col < tileSize; col++) {
            int r = 0;
            int g = 0;
            int b = 0;
            for (int row = 0; row < tileSize; row++) {
                float yOffset = -1 * sin(col / 2.0f + frame) * 10 + 10;
                float xOffset = -1 * sin(row / 2.0f + frame) * 10 + 10;
                //make donut wave thing
                float xQuadratic = pow(col - tileSize/2, 2);
                float yQuadratic = pow(row - tileSize/2, 2);
                yOffset = sin(0.2*(sqrt(10 * xQuadratic + 10 * yQuadratic)) - frame / 20.0f) * 30 + 30;
                xOffset = 0;
                float x = screenSize * col / scale;
                float y = screenSize * row / scale;
                float xTile = (x * 0.5f + y * -0.5f) / (pow(tileSize, 2)/50) + 400;
                float yTile = (x * 0.25f + y * 0.25f) / (pow(tileSize, 2)/50) + 200;
                if (r >= 255) {
                    r = 0;
                }
                if (g >= 255) {
                    g = 0;
                }
                if (b >= 255) {
                    b = 0;
                }
                yTile = yTile + yOffset + xOffset;
                g = 4 * yOffset;
                //can loop back from being too big
                //b = xOffset + yOffset * 10;
                r = 255;
                b = 4 * yOffset;
                (*(*tileBoard)[col])[row]-> setPosition(xTile, yTile);
                (*(*tileBoard)[col])[row]-> setColor(sf::Color(r, g, b));

                window.draw(*(*(*tileBoard)[col])[row]);
            }
        }
        window.display();
        frame++;
    }
    delete[] tileBoard;
    return 0;
}