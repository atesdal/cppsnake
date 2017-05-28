/*
  Snake ICA start project using SFML
    SFML documentation: http://www.sfml-dev.org/documentation/2.4.2/classes.php
  Windows build
    To build on Windows you need to have the correct version of CodeBlocks
      Download from here: http://www.codeblocks.org/downloads/26
      Must be the download titled "codeblocks-16.01mingw-setup.exe"
*/

#include <iostream>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Game.h"


int main()
{
    // Seeding rand function
    srand(time(NULL));

    // Creating a game with a 800x600 window
    Game g(800, 600);

    // Starting the game
    g.run();

    return 0;
}
