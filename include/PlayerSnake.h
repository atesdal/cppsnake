#ifndef PLAYERSNAKE_H
#define PLAYERSNAKE_H
#include "Snake.h"

class PlayerSnake : public Snake
{
    public:
        PlayerSnake(int startX, int startY);
        ~PlayerSnake();
        void swapSegments(Snake::EDirection dir);
        void grow(Snake::EDirection dir);

    protected:

    private:
};

#endif // PLAYERSNAKE_H
