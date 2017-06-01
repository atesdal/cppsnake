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
        virtual ~Snake() = 0;

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
        void update(EDirection dir);
        void render(sf::RenderWindow &window);
        void setGrowth(int amount);
        void giveGlue(bool glue);
        int getSnakeSize() const;
        sf::Vector2i getHeadPos() const;
        std::string getScoreString();
        void addScore(int amount);
        std::vector<sf::Vector2i>* getSnakeBody() const;
        std::string debug();

        // Virtual functions
        virtual void swapSegments(EDirection dir) = 0;
        virtual void grow(EDirection dir) = 0;

    protected:
        // Protected functions
        bool dirCheck(EDirection dir);

        // Protected vars
        int score = 0;
        int snakeSize = 1;
        int growthAmount = 0;
        int stepAmount = 20;
        bool hasGlue = false;
        sf::CircleShape snakeHead;
        Segment *head, *tail;
        EDirection lastMove;
};

#endif // SNAKE_H
