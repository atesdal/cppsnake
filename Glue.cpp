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

// Randomizes position of the glue pickup
void Glue::randPos()
{
    position.x = ((rand()%(maxBounds.x / 20) * 20) - 20);
    position.y = ((rand()%(maxBounds.y / 20) * 20) - 20);

    if(position.x < 20 || position.x > (maxBounds.x - 20) || position.y < 20 || position.y > (maxBounds.y - 20)){
        randPos();
    }
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
