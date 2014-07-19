#include "M7engine.h"

using namespace M7engine;
Engine *engine = Engine::getInstance();
Logger *logger = Logger::getInstance();
InputManager *input = InputManager::getInstance();
ResourceManager *rManager = ResourceManager::getInstance();

class Player : public Entity {
private:
    double speed = 6;
    Font *f;
public:
    Player()
    {
        setImage(rManager->getSprite("cat"));
        f = rManager->getFont("oldpix");
    }

    void update()
    {
        if (input->getKeyHeld(KEY_UP)) {
            setY(getY() - speed);
        }

        if (input->getKeyHeld(KEY_DOWN)) {
            setY(getY() + speed);
        }

        if (input->getKeyHeld(KEY_LEFT)) {
            setX(getX() - speed);
        }

        if (input->getKeyHeld(KEY_RIGHT)) {
            setX(getX() + speed);
        }

        engine->renderText(32, 32, f, "Example Game");
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            setVelocity(getVelocity());
        }
    }
};

class Enemy : public Entity {
private:
public:
    Enemy()
    {
        setImage(rManager->getSprite("wall"));
    }
};

class Wall : public Entity {
private:
public:
    Wall()
    {
        setImage(rManager->getSprite("wall"));
        solid = true;
    }
};

int main(int argc, char **argv) {
    bool running = true;

    //Start log
    logger->setLogFile("m7engine.log");
    logger->logMessage(0, "Engine started");

    //Begin reading config values
    int resX, resY, fs;
    ConfigReader *config = engine->getConfigReader();

    config->loadConfig("../resources/config.ini");

    logger->setLoggingLevel(config->getInt("debug", "log", 0));

    resX = config->getInt("video", "resX", 640);
    resY = config->getInt("video", "resY", 480);
    fs = config->getInt("video", "fs", 0);

    logger->logMessage(0, "Read config values: %i %i %i", resX, resY, fs);

    engine->init(resX, resY, fs);
    engine->setWindowTitle(config->getString("base", "title").c_str());
    engine->setWindowIcon(config->getString("base", "icon").c_str());

    //Load resources
    rManager->loadConfig(config->getString("base", "resconf").c_str());

    input->init();

    //Game objects
    Player *player = new Player;
    Wall *wall1 = new Wall;
    Wall *wall2 = new Wall;

    engine->addEntity(player);
    engine->addEntity(wall1);
    engine->addEntity(wall2);

    player->setPosition(128, 256);
    player->setColor(255, 0, 255);

    wall1->setPosition(64, 64);
    wall2->setPosition(256, 256);

    //Main loop
    while (running) {
        if (!engine->update()) {
            running = false;
        }

        if (input->getKeyReleased(KEY_ESCAPE)) {
            running = false;
        }
    }

    delete engine;

    return 0;
}
