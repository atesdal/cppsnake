#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <cmath>

Game::Game(int width, int height, int totPickups)
{
    // Initializing vars and adding walls/pickups to containers
    wColour = sf::Color::Red;
    wallWidth = 10;

    gHeight = height;
    gWidth = width;

    nsSize.x = width;
    nsSize.y = wallWidth;

    ewSize.x = wallWidth;
    ewSize.y = height;

    sf::RectangleShape nWallShape(nsSize);
    sf::RectangleShape sWallShape(nsSize);
    sf::RectangleShape wWallShape(ewSize);
    sf::RectangleShape eWallShape(ewSize);

    nWallShape.setPosition(0, 0);
    sWallShape.setPosition(0, height - nsSize.y);
    wWallShape.setPosition(0, 0);
    eWallShape.setPosition(width - ewSize.x, 0);

    wallArray[0] = nWallShape;
    wallArray[1] = sWallShape;
    wallArray[2] = wWallShape;
    wallArray[3] = eWallShape;

    for(int i = 0; i < 4; i++){
        wallArray[i].setFillColor(wColour);
    }

    for(int i = 0; i < (totPickups - 1); i++){
        Food *f = new Food(width, height);
        pickupVector.push_back(f);
    }
    Glue *g = new Glue(width, height);
    pickupVector.push_back(g);

    if(!font.loadFromFile("Font/arial.ttf"));
    gameTimerText.setFont(font);
    gameTimerText.setPosition((gWidth - 40), 10);
    gameTimerText.setFillColor(sf::Color::White);
    gameOver.setFont(font);
    gameOver.setFillColor(sf::Color::White);
    gameOver.setPosition((gWidth / 2), (gHeight / 2));

    PlayerSnake *a = new PlayerSnake(200, 200);
    AISnake *b = new AISnake(100, 100);
    snakeVector.push_back(a);
    snakeVector.push_back(b);

    int step = 10;
    for(unsigned int i = 0; i <= snakeVector.size(); i++){
        sf::Text newText;
        newText.setFont(font);
        newText.setPosition(10, step);
        step *= 4;
        scoreText.push_back(newText);
    }
}

Game::~Game()
{
    for(auto p :snakeVector){
        p->~Snake();
    }
}

void Game::run()
{
    // Setting default start direction
    Snake::EDirection direction = Snake::EDirection::eNorth;

    sf::RenderWindow window(sf::VideoMode(gWidth, gHeight), "S6277144 SnakeICA");


    // Main game loop
    while(window.isOpen()){

        while(gameState == 0){

            // If statement to check that time has not expired
            if(gameTimer.getElapsedTime().asSeconds() >= 90){
                gameState = 5;
            }

            sf::Event event;
            while(window.pollEvent(event)){

                switch(event.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                    // Keyboard input
                    case sf::Event::KeyPressed:
                        switch(event.key.code){
                            case sf::Keyboard::W:
                                std::cout << "W was pressed" << std::endl;
                                direction = Snake::EDirection::eNorth;
                                break;
                            case sf::Keyboard::A:
                                std::cout << "A was pressed" << std::endl;
                                direction = Snake::EDirection::eWest;
                                break;
                            case sf::Keyboard::S:
                                std::cout << "S was pressed" << std::endl;
                                direction = Snake::EDirection::eSouth;
                                break;
                            case sf::Keyboard::D:
                                std::cout << "D was pressed" << std::endl;
                                direction = Snake::EDirection::eEast;
                                break;
                            case sf::Keyboard::Q:
                                std::cout << "Q was pressed" << std::endl;
                                direction = Snake::EDirection::eHold;
                                break;
                            case sf::Keyboard::Escape:
                                window.close();
                                return;
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            }

            // Drawing objects to the renderwindow
            AISnakeControl();
            window.clear();
            update(direction);
            checkCollisions();
            if(gameState != 0){
                break;
            }
            render(window);
            window.display();

            // Debug messages to console
//            std::cout << snakeVector[0]->debug() << std::endl; //<< snakeVector[1]->debug() << std::endl;
//            std::cout << snakeVector[1]->debug() << std::endl; //<< snakeVector[1]->debug() << std::endl;
//            std::cout << pickupVector[0]->debug() << std::endl;
//            std::cout << pickupVector[1]->debug() << std::endl;
//            std::cout << pickupVector[2]->debug() << std::endl;
//            std::cout << pickupVector[3]->debug() << std::endl;
//            std::cout << pickupVector[4]->debug() << std::endl;

            // Delay
            while(clock.getElapsedTime().asMilliseconds()<500){}
                clock.restart();
        }
        // Game over section
        switch(gameState){
            case 1:
                gameOver.setString("Wall collision!");
                break;
            case 2:
                gameOver.setString("Tail collision!");
                break;
            case 3:
                gameOver.setString("Head on head collision!");
                break;
            case 4:
                gameOver.setString("Head on body collision!");
                break;
            case 5:
                gameOver.setString("Time out!");
                break;
        }
        window.clear();
        window.draw(gameOver);
        window.display();
        while(clock.getElapsedTime().asMilliseconds()<1000){}
                clock.restart();
        window.close();
        return;
    }
}

// Game render function, keeps renders all viable objects to the window
void Game::render(sf::RenderWindow &window)
{
    // Snakes
    for(Snake* p : snakeVector){
        p->render(window);
    }

    // Scores
    for(unsigned int i = 0; i < snakeVector.size(); i++){
        window.draw(scoreText[i]);
    }

    // Game timer
    window.draw(gameTimerText);

    // Walls
    for(sf::RectangleShape p : wallArray){
        window.draw(p);
    }

    // Pickups that are active
    for(auto p : pickupVector){
        if(p->getActive()){
            p->render(window);
        }
    }
}

// Game update function, updates all objects within the game
void Game::update(Snake::EDirection dir)
{
    // Snakes
    for(Snake* p : snakeVector){
        p->update(dir);
    }

    // Score
    for(unsigned int i = 0; i < snakeVector.size(); i++){
        scoreText[i].setString(snakeVector[i]->getScoreString());
    }

    // Game timer
    gameTimerText.setString(timerToString(gameTimer));

    // Pickups
    unsigned int pickUpIndex = 0;
    bool overlap = false;
    for(auto p : pickupVector){
        if(rand()%10 == 0 && !p->getActive()){
            p->setActive();
            p->randPos();
            do{
                overlap = false;
                for(unsigned int i = 0; i < pickupVector.size(); i++){
                    if(i != pickUpIndex){
                        if(p->getPos() == pickupVector[i]->getPos()){
                            p->randPos();
                            overlap = true;
                        }
                    }
                }
            }while(overlap);
        }
        pickUpIndex++;
    }
}

// Collision checker
void Game::checkCollisions()
{
    unsigned int snakeNum = 0;
    for(Snake* p : snakeVector){

        // Snake + Wall
        if(p->getHeadPos().y < 10 || p->getHeadPos().y > (gHeight - 40) || p->getHeadPos().x < 10 || p->getHeadPos().x > (gWidth - 40)){
            gameState = 1;
            return;
        }

        // If statement to ensure no redundant checks if snake is too small to collide with itself
        if(p->getSnakeSize() >= 4){
            // Snake + Own tail
            std::vector<sf::Vector2i> *snakeToCheck = p->getSnakeBody();
            for(int i = 3; i < (p->getSnakeSize()); i++){
                if(p->getHeadPos() == snakeToCheck->at(i)){
                    gameState = 2;
                    delete snakeToCheck;
                    return;
                }
            }
            delete snakeToCheck;
        }

        // Snake + Pickup
        for(int i = 0; i < 5; i++){
            if(p->getHeadPos() == pickupVector[i]->getPos()){
                if(pickupVector[i]->getActive()){
                    if(i == 4){
                        p->giveGlue(pickupVector[i]->consume());
                        p->addScore(20);
                    }
                    else{
                        p->setGrowth(pickupVector[i]->consume());
                        p->addScore((pickupVector[i]->consume() * 10));
                    }
                }
            }
        }

        // Snake + Snake
        // Temporary vector to hold the segment positions of the snake being checked
        std::vector<sf::Vector2i> *nextSnake;
        // For loop to prevent checking if the snake is colliding with itself
        for(unsigned int snakeIndex = 0; snakeIndex < snakeVector.size(); snakeIndex++){

            if(snakeIndex != snakeNum){
                nextSnake = snakeVector[snakeIndex]->getSnakeBody();

                // For loop checking the current snake's head against the body of a different snake
                for(int i = 0; i <= (snakeVector[snakeIndex]->getSnakeSize() - 1); i++){
                    if(p->getHeadPos() == nextSnake->at(i)){
                        if(i == 0){
                            gameState = 3;
                        }
                        else{
                            gameState = 4;
                        }
                        delete nextSnake;
                        return;
                    }
                }
                delete nextSnake;
            }
        }
        snakeNum++;
    }
}

void Game::AISnakeControl()
{
    for(auto p : snakeVector){
        if(p->hasAI()){
            sf::Vector2i currentHead = p->getHeadPos();
            sf::Vector2i currentTarget = sf::Vector2i(-1, -1);
            unsigned int currentOffset = 16000;
            sf::Vector2i offset;
            unsigned int totOffset = 0;
            for(unsigned int i = 0; i < (pickupVector.size()); i++){
                if(pickupVector[i]->getActive()){
                    offset = getOffset(currentHead, pickupVector[i]->getPos());
                    totOffset = offset.x + offset.y;
                    if(totOffset < currentOffset){
                        currentOffset = totOffset;
                        currentTarget = pickupVector[i]->getPos();
                    }
                }
            }
            p->setTarget(currentTarget);
        }
    }
}

sf::Vector2i Game::getOffset(sf::Vector2i src, sf::Vector2i dest)
{
    return sf::Vector2i(abs(src.x - dest.x), abs(src.y - dest.y));
}

// To-string function for the game timer
std::string Game::timerToString(sf::Clock &clock)
{
    std::ostringstream ss;
    std::string s;

    ss << (int)clock.getElapsedTime().asSeconds();
    s += ss.str();

    return s;
}
