#ifndef PICKUP_H
#define PICKUP_H
#include <SFML/Graphics.hpp>
#include <string>

// Pickup parent class
class Pickup
{
    public:
        // Constructor/destructor
        Pickup(int mW, int mH);
        virtual ~Pickup();

        // Public functions
        void setActive();
        bool getActive();
        sf::Vector2i getPos();
        void randPos();
        std::string debug();

        // Pure virtual functions
        virtual void updatePos() = 0;
        virtual int consume() = 0;
        virtual void render(sf::RenderWindow &window) = 0;

    protected:
        // Protected vars, accessible by Food and Glue
        sf::Vector2i position;
        sf::Vector2i maxBounds;
        bool isActive;
};

#endif // PICKUP_H
