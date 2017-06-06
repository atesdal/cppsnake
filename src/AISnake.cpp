#include "AISnake.h"

AISnake::AISnake(int startX, int startY) : Snake(startX, startY)
{
    isAI = true;
    snakeColour = sf::Color::Blue;
    setColour(snakeColour);
}

void AISnake::update(Snake::EDirection dir)
{
    dir = setDirection();

    // If snake is growing
    if(growthAmount != 0){
        grow(dir);
        growthAmount--;
    }

    // If "break" key was pressed
//    else if(dir == EDirection::eHold){
//        if(hasGlue){
//            hasGlue = false;
//            if(growthAmount != 0){
//                grow(dir);
//            }
//        }
//        else{
//            update(lastMove);
//        }
//    }

    // For normal movement
    else{
        swapSegments(dir);
    }
}

Snake::EDirection AISnake::setDirection()
{
    Snake::EDirection dir;
    if(head->getX() < target.x){
        dir = Snake::EDirection::eEast;
    }
    else if(head->getX() > target.x){
        dir = Snake::EDirection::eWest;
    }
    else if(head->getY() < target.y){
        dir = Snake::EDirection::eSouth;
    }
    else{
        dir = Snake::EDirection::eNorth;
    }

    return dir;
}

void AISnake::setTarget(sf::Vector2i tar)
{
    target = tar;
}
