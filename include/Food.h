#ifndef FOOD_H
#define FOOD_H
#include "Pickup.h"

// Child class of pickup
class Food : public Pickup
{
    public:
        // Constructor/destructor
        Food(int mW, int mH);
        ~Food();

        // Inherited functions
        void randPos();
        int consume();
        void render(sf::RenderWindow &window);

    private:
        // Private vars
        sf::RectangleShape foodShape;
        int growValue;
};

#endif // FOOD_H
