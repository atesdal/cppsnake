#include "../include/Food.h"
#include <iostream>

Food::Food(int mW, int mH) : Pickup(mW, mH)
{
    // Initializes vars and gives a random position
    foodShape.setFillColor(sf::Color::Red);
    foodShape.setSize(sf::Vector2f(20.0f, 20.0f));
    randPos();
    growValue = (rand()%2 + 1);
}

Food::~Food()
{

}

void Food::updatePos()
{
    foodShape.setPosition(position.x, position.y);
}

// Function that gets called when a snake head collides with the pickup
int Food::consume()
{
    isActive = false;
    return growValue;
}

// Pickup render function
void Food::render(sf::RenderWindow &window)
{
    window.draw(foodShape);
}
