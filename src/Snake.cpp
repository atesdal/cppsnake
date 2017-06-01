#include "../include/Snake.h"
#include <iostream>
#include <sstream>
#include <string>

Snake::Snake(int startX, int startY)
{
    // Creating starting segment and initializing vars
    head = new Segment(startX, startY);
    tail = head;
    snakeHead.setPosition(head->getX(), head->getY());
    snakeHead.setRadius(10.0f);
    snakeHead.setFillColor(sf::Color::Green);
}

Snake::~Snake()
{

}

// Internal snake update function, determines legal movement, growth and breaks
void Snake::update(EDirection dir)
{
    // If snake is growing
    if(growthAmount != 0){
        grow(dir);
        growthAmount--;
    }

    // If "break" key was pressed
    else if(dir == EDirection::eHold){
        if(hasGlue){
            hasGlue = false;
            if(growthAmount != 0){
                grow(dir);
            }
        }
        else{
            update(lastMove);
        }
    }

    // For normal movement
    else{
        swapSegments(dir);
    }
}

// Internal snake render function, loops through list calling all the segment renders
void Snake::render(sf::RenderWindow &window)
{
    Segment *a = head;
    while(a != nullptr){
        a->render(window);
        a = a->next;
    }
}

// Snake movement function, moves last list element(tail) to the front and sets new position based on old the old heads position
//void Snake::swapSegments(EDirection dir)
//{
//    // Check to see if snake is trying to move backwards into itself
//    if(dirCheck(dir)){
//        swapSegments(lastMove);
//    }
//    else{
//        // If there is only one segment in the snake
//        if(head->next != nullptr){
//            tail->next = head;
//            head->prev = tail;
//            tail = tail->prev;
//            tail->next = nullptr;
//            head = head->prev;
//            head->prev = nullptr;
//
//            switch(dir){
//                case EDirection::eNorth:
//                    head->setPosition(head->next->getX(), head->next->getY() - stepAmount);
//                    break;
//                case EDirection::eEast:
//                    head->setPosition(head->next->getX() + stepAmount, head->next->getY());
//                    break;
//                case EDirection::eSouth:
//                    head->setPosition(head->next->getX(), head->next->getY() + stepAmount);
//                    break;
//                case EDirection::eWest:
//                    head->setPosition(head->next->getX() - stepAmount, head->next->getY());
//                default:
//                    break;
//            }
//        }
//        else{
//            switch(dir){
//                case EDirection::eNorth:
//                    head->setPosition(head->getX(), head->getY() - stepAmount);
//                    break;
//                case EDirection::eEast:
//                    head->setPosition(head->getX() + stepAmount, head->getY());
//                    break;
//                case EDirection::eSouth:
//                    head->setPosition(head->getX(), head->getY() + stepAmount);
//                    break;
//                case EDirection::eWest:
//                    head->setPosition(head->getX() - stepAmount, head->getY());
//                default:
//                    break;
//            }
//        }
//        // Update lastMove var to enforce legal movement
//        lastMove = dir;
//    }
//}

// Snake grow function, creates new segment and adds it to the front in the direction the player inputs
//void Snake::grow(EDirection dir)
//{
//    // Check to see if snake is trying to move backwards into itself
//    if(dirCheck(dir)){
//        grow(lastMove);
//    }
//    else{
//        Segment *newSegment = new Segment();
//        switch(dir){
//            case EDirection::eNorth:
//                newSegment->setPosition(head->getX(), head->getY() - stepAmount);
//                break;
//            case EDirection::eEast:
//                newSegment->setPosition(head->getX() + stepAmount, head->getY());
//                break;
//            case EDirection::eSouth:
//                newSegment->setPosition(head->getX(), head->getY() + stepAmount);
//                break;
//            case EDirection::eWest:
//                newSegment->setPosition(head->getX() - stepAmount, head->getY());
//                break;
//            case EDirection::eHold:
//                newSegment->prev = tail;
//                tail->next = newSegment;
//                tail = newSegment;
//                return;
//        }
//        newSegment->next = head;
//        head->prev = newSegment;
//        head = newSegment;
//        // Update lastMove var to enforce legal movement
//        lastMove = dir;
//        snakeSize++;
//    }
//    // Increment snakeSize for later use
//
//}

// Internal function to enforce legal movement, returns true if directions are opposite
bool Snake::dirCheck(EDirection dir)
{
    switch(dir){
        case Snake::EDirection::eNorth:
            if(lastMove == Snake::EDirection::eSouth){
                return true;
            }
            break;

        case Snake::EDirection::eEast:
            if(lastMove == Snake::EDirection::eWest){
                return true;
            }
            break;

        case Snake::EDirection::eSouth:
            if(lastMove == Snake::EDirection::eNorth){
                return true;
            }
            break;

        case Snake::EDirection::eWest:
            if(lastMove == Snake::EDirection::eEast){
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    return false;
}

// Setter function for snake growth
void Snake::setGrowth(int amount)
{
    growthAmount = amount;
}

// Setter function for glue
void Snake::giveGlue(bool glue)
{
    hasGlue = true;
}

// Getter for the size of the snake
int Snake::getSnakeSize() const
{
    return snakeSize;
}

// Getter for the heads position
sf::Vector2i Snake::getHeadPos() const
{
    return sf::Vector2i(head->getX(), head->getY());
}

// Returns the score as string for text output in the game class
std::string Snake::getScoreString()
{
    std::string s;
    std::ostringstream ss;

    ss << score;
    s += ss.str();
    return s;
}

// Adds score
void Snake::addScore(int amount)
{
    score += amount;
}

// Returns a vector containing the position of all segments in a snake, used for collision tests
std::vector<sf::Vector2i>* Snake::getSnakeBody() const
{
    Segment *travNode = head;
    std::vector<sf::Vector2i> *posVector = new std::vector<sf::Vector2i>;
    while(travNode != nullptr){
        posVector->push_back(sf::Vector2i(travNode->getX(), travNode->getY()));
        travNode = travNode->next;
    }
    return posVector;
}

// Debug function, returns a string with pointers to the segments and their global position
std::string Snake::debug()
{
    std::string s;

    std::ostringstream ss;
    Segment *travNode = head;
    ss.str("");
    ss.clear();

    s += "The elements in the snake are ";
    do{
        s += "\n";
        ss << travNode;
        s += ss.str();
        ss.str("");
        ss.clear();
        s += " :";
        ss << travNode->getX();
        s += ss.str();
        ss.str("");
        ss.clear();
        s += ", ";
        ss << travNode->getY();
        s += ss.str();
        ss.str("");
        ss.clear();
        if(travNode == head){
            s += " HEAD";
        }
        travNode = travNode->next;
    }while(travNode != nullptr);
    s += "\n";
    return s;
}
