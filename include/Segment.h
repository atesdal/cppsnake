#ifndef SEGMENT_H
#define SEGMENT_H
#include <SFML/Graphics.hpp>

// Snake segment class
class Segment
{
    public:
        //Constructor/destructor
        Segment(sf::Color col, int pX = 0, int pY = 0);
        ~Segment();

        // Public functions
        void setPosition(int x, int y);
        void render(sf::RenderWindow &window);
        void setColour(sf::Color col);
        int getX() const;
        int getY() const;

        // Public variables
        Segment *next, *prev;

    private:
        // Private vars
        int posX, posY;
        sf::CircleShape segmentShape;
};

#endif // SEGMENT_H
