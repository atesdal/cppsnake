#include "PlayerSnake.h"

PlayerSnake::PlayerSnake(int startX, int startY) : Snake(startX, startY)
{
    isAI = false;
    snakeColour = sf::Color::Green;
    setColour(snakeColour);
}
