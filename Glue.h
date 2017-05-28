#ifndef GLUE_H
#define GLUE_H
#include "Pickup.h"

// Child class of pickup
class Glue : public Pickup
{
    public:
        // Constructor/destructor
        Glue(int mW, int mH);
        ~Glue();

        // Inherited functions
        void randPos();
        int consume();
        void render(sf::RenderWindow &window);

    private:
        // Private vars
        sf::RectangleShape glueShape;
        int glueValue = 1;
};

#endif // GLUE_H
