#include "Game.h"

using namespace SampleGame;

int main(int argc, char* argv[])
{
    Game *game = new Game("../resources/config.ini");

    game->initObjects();

    bool running = true;

    //Main loop
    while (running) {
        if (!game->run()) {
            running = false;
        }
    }

    delete game;

    return 0;
}
