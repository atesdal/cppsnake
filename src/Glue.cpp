#include "../include/Glue.h"

Glue::Glue(int mW, int mH) : Pickup(mW, mH)
{
    // Initializes vars and gives a random position
    glueShape.setFillColor(sf::Color::Yellow);
    glueShape.setSize(sf::Vector2f(20.0f, 20.0f));
    randPos();
}

Glue::~Glue()
{

}

void Glue::updatePos()
{
    glueShape.setPosition(position.x, position.y);
}

// Function that gets called when a snake head collides with the pickup
int Glue::consume()
{
    isActive = false;
    return glueValue;
}

// Pickup render function
void Glue::render(sf::RenderWindow &window)
{
    window.draw(glueShape);
}
