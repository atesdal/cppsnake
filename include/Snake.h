#ifndef SNAKE_H
#define SNAKE_H
#include <SFML/Graphics.hpp>
#include "Segment.h"
#include <vector>

// Snake class, holds information about the snake and functions as a linked list for segments
class Snake
{
    public:
        // Constructor/destructor
        Snake(int startX, int startY);
        virtual ~Snake();

        // Enum for directions, eNorth = up
        //                      eEast = right
        //                      eSouth = down
        //                      eWest = left
        //                      eHold = break
        enum class EDirection
        {
            eNorth,
            eEast,
            eSouth,
            eWest,
            eHold
        };

        // Public functions
        void render(sf::RenderWindow &window);
        void setGrowth(int amount);
        void giveGlue(bool glue);
        int getSnakeSize() const;
        sf::Vector2i getHeadPos() const;
        std::string getScoreString();
        void addScore(int amount);
        std::vector<sf::Vector2i>* getSnakeBody() const;
        bool hasAI() const;
        std::string debug();

        // Virtual functions
        virtual void update(EDirection dir);
        virtual void swapSegments(EDirection dir);
        virtual void grow(EDirection dir);
        virtual void setTarget(sf::Vector2i tar);

    protected:
        // Protected functions
        bool dirCheck(EDirection dir);
        void setColour(sf::Color col);

        // Protected vars
        int score = 0;
        int snakeSize = 1;
        int growthAmount = 0;
        int stepAmount = 20;
        bool hasGlue = false;
        sf::Color snakeColour;
        Segment *head, *tail;
        EDirection lastMove;
        bool isAI;
};

#endif // SNAKE_H
