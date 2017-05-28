#include "AISnake.h"

AISnake::AISnake(int startX, int startY) : Snake(startX, startY)
{

}

AISnake::~AISnake()
{

}
void AISnake::swapSegments(Snake::EDirection dir)
{
    // AI snake uses random movement
    switch((rand()%3)){
        case 0:
            dir = Snake::EDirection::eNorth;
            break;
        case 1:
            dir = Snake::EDirection::eEast;
            break;
        case 2:
            dir = Snake::EDirection::eSouth;
            break;
        case 3:
            dir = Snake::EDirection::eWest;
            break;
    }

    // Check to see if snake is trying to move backwards into itself
    if(dirCheck(dir)){
        swapSegments(lastMove);
    }
    else{
        // If there is only one segment in the snake
        if(head->next != nullptr){
            tail->next = head;
            head->prev = tail;
            tail = tail->prev;
            tail->next = nullptr;
            head = head->prev;
            head->prev = nullptr;

            switch(dir){
                case EDirection::eNorth:
                    head->setPosition(head->next->getX(), head->next->getY() - stepAmount);
                    break;
                case EDirection::eEast:
                    head->setPosition(head->next->getX() + stepAmount, head->next->getY());
                    break;
                case EDirection::eSouth:
                    head->setPosition(head->next->getX(), head->next->getY() + stepAmount);
                    break;
                case EDirection::eWest:
                    head->setPosition(head->next->getX() - stepAmount, head->next->getY());
                default:
                    break;
            }
        }
        else{
            switch(dir){
                case EDirection::eNorth:
                    head->setPosition(head->getX(), head->getY() - stepAmount);
                    break;
                case EDirection::eEast:
                    head->setPosition(head->getX() + stepAmount, head->getY());
                    break;
                case EDirection::eSouth:
                    head->setPosition(head->getX(), head->getY() + stepAmount);
                    break;
                case EDirection::eWest:
                    head->setPosition(head->getX() - stepAmount, head->getY());
                default:
                    break;
            }
        }
        // Update lastMove var to enforce legal movement
        lastMove = dir;
    }
}

void AISnake::grow(Snake::EDirection dir)
{
    // AI snake uses random movement
    switch((rand()%3)){
        case 0:
            dir = Snake::EDirection::eNorth;
            break;
        case 1:
            dir = Snake::EDirection::eEast;
            break;
        case 2:
            dir = Snake::EDirection::eSouth;
            break;
        case 3:
            dir = Snake::EDirection::eWest;
            break;
    }

    // Check to see if snake is trying to move backwards into itself
    if(dirCheck(dir)){
        swapSegments(lastMove);
    }
    else{
        Segment *newSegment = new Segment();
            switch(dir){
                case EDirection::eNorth:
                    newSegment->setPosition(head->getX(), head->getY() - stepAmount);
                    break;
                case EDirection::eEast:
                    newSegment->setPosition(head->getX() + stepAmount, head->getY());
                    break;
                case EDirection::eSouth:
                    newSegment->setPosition(head->getX(), head->getY() + stepAmount);
                    break;
                case EDirection::eWest:
                    newSegment->setPosition(head->getX() - stepAmount, head->getY());
                    break;
                case EDirection::eHold:
                    newSegment->prev = tail;
                    tail->next = newSegment;
                    tail = newSegment;
                    return;
            }
            newSegment->next = head;
            head->prev = newSegment;
            head = newSegment;
            // Update lastMove var to enforce legal movement
            lastMove = dir;
            snakeSize++;
    }
    // Increment snakeSize for later use

}
