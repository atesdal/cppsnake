#ifndef GAME_H
#define GAME_H
#include "Snake.h"
#include "AISnake.h"
#include "Pickup.h"
#include "Food.h"
#include "Glue.h"
#include <vector>
#include <SFML/Graphics.hpp>

// Main game class, holds all game objects
class Game
{
    public:
        // Constructor/destructor
        Game(int width, int height, int totPickups = 5);
        ~Game();

        // Public functions
        void run();

    private:
        // Private functions
        void render(sf::RenderWindow &window);
        void update(Snake::EDirection dir);
        void checkCollisions();
        std::string timerToString(sf::Clock &clock);

        // Private vars
        int gameState = 0;
        sf::Vector2f nsSize, ewSize;
        sf::Color wColour;
        int gHeight, gWidth, wallWidth;
        int stepAmount = 10;
        int shiftAmount = 1;
        sf::Clock clock, gameTimer;
        sf::Text gameOver, gameTimerText;
        sf::Font font;

        // Containers for game objects
        std::vector<Pickup*> pickupVector;
        std::vector<Snake*> snakeVector;
        sf::RectangleShape wallArray[4];
        std::vector<sf::Text> scoreText;

};

#endif // GAME_H
