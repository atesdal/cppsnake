#ifndef AISNAKE_H
#define AISNAKE_H
#include "Snake.h"

// Snake AI class
class AISnake : public Snake
{
    public:
        // Constructor/destructor
        AISnake(int startX, int startY);

        // Inherited functions
        void update(Snake::EDirection dir) override;

        // Public functions
        Snake::EDirection setDirection();
        void setTarget(sf::Vector2i tar) override;

    private:
        // Private vars
        sf::Vector2i target;

};

#endif // AISNAKE_H
