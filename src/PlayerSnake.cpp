#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(int startX, int startY) : Snake(startX, startY, sf::Color::Green)
{
    isAI = false;
    snakeColour = sf::Color::Green;
}
