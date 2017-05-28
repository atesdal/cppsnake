#include "../include/Segment.h"

Segment::Segment(int pX, int pY)
{
    // Initializing vars
    next = nullptr;
    prev = nullptr;
    posX = pX;
    posY = pY;
    segmentShape.setPosition(posX, posY);
    segmentShape.setRadius(10.0f);
    segmentShape.setFillColor(sf::Color::Blue);
}

Segment::~Segment()
{

}

// Setter function for segment position
void Segment::setPosition(int x, int y)
{
    posX = x;
    posY = y;
    segmentShape.setPosition(x, y);
}

// Individual segment render function
void Segment::render(sf::RenderWindow &window)
{
    window.draw(segmentShape);
}

// Getter for segment X position
int Segment::getX() const
{
    return posX;
}

// Getter for segment Y position
int Segment::getY() const
{
    return posY;
}
