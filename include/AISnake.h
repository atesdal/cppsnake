#ifndef AISNAKE_H
#define AISNAKE_H
#include "Snake.h"

// Snake AI class
class AISnake : public Snake
{
    public:
        // Constructor/destructor
        AISnake(int startX, int startY);
        ~AISnake();

        // Public functions
        void swapSegments(Snake::EDirection dir);
        void grow(Snake::EDirection dir);
        bool avoidCollision(Snake::EDirection dir);

};

#endif // AISNAKE_H
