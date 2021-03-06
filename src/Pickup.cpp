#include "../include/Pickup.h"
#include <iostream>
#include <sstream>

Pickup::Pickup(int mW, int mH)
{
    // Initializing vars
    isActive = true;
    maxBounds.x = (mW - 20);
    maxBounds.y = (mH - 20);
}

Pickup::~Pickup()
{

}

// Sets if pickup object is active or not
void Pickup::setActive()
{
    isActive = true;
}

// Getter for isActive
bool Pickup::getActive()
{
    return isActive;
}

// Returns the position of a pickup
sf::Vector2i Pickup::getPos()
{
    return position;
}

// Randomizes pickup position, check against overlapping pickups in Game::update
void Pickup::randPos()
{
    int seedX = rand() % (maxBounds.x / 20 - 1) + 1;
    int seedY = rand() % (maxBounds.y / 20 - 1) + 1;

    position.x = seedX * 20;
    position.y = seedY * 20;


    if(position.x < 20 || position.x > (maxBounds.x - 20) || position.y < 20 || position.y > (maxBounds.y - 20)){
        randPos();
    }
    updatePos();
}

// Debug function, returns a string with the position of the pickup and if it's active or not
std::string Pickup::debug()
{
    std::string s;
    std::ostringstream ss;
    ss.str("");
    ss.clear();

    s += "pX: ";
    ss << position.x;
    s += ss.str();
    ss.str("");
    ss.clear();
    s += "\npY: ";
    ss << position.y;
    s += ss.str();
    ss.str("");
    ss.clear();
    s += "\nActive: ";
    ss << isActive;
    s += ss.str();
    s += "\n";
    return s;
}
