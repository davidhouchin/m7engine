#include "M7engine.h"

using namespace M7engine;
Engine *engine = Engine::getInstance();
Logger *logger = Logger::getInstance();
InputManager *input = InputManager::getInstance();
ResourceManager *rManager = ResourceManager::getInstance();
CollisionManager *cManager = engine->getCollisionManager();

class Controller : public Entity {
private:
    Font *f, *f2;
public:
    Controller()
    {
        f = rManager->getFont("elgethy");
        f2 = rManager->getFont("oldpix");
    }

    void update()
    {
        engine->renderText(engine->getScreenWidth()/2, engine->getScreenHeight()/2, f2, "Example");
        engine->renderTextF(20, 20, f, "FPS: %i", engine->getFPS());
    }

};

class Player : public Entity {
private:
    int speed = 5;
public:
    Player()
    {
        setImage(rManager->getSprite("cat"));
        setOriginToCenter();
    }

    void update()
    {
        if (input->getKeyHeld(KEY_UP)) {
            if (!cManager->getPlaceMeetingInstance(getX(), getY() - speed, this->id, 2)) {
                vSpeed = speed * -1;
            } else {
                vSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            if (!cManager->getPlaceMeetingInstance(getX(), getY() + speed, this->id, 2)) {
                vSpeed = speed;
            } else {
                vSpeed = 0;
            }
        } else {
            vSpeed = 0;
        }

        if (input->getKeyHeld(KEY_LEFT)) {
            if (!cManager->getPlaceMeetingInstance(getX() - speed, getY(), this->id, 2)) {
                hSpeed = speed * -1;
            } else {
                hSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            if (!cManager->getPlaceMeetingInstance(getX() + speed, getY(), this->id, 2)) {
                hSpeed = speed;
            } else {
                hSpeed = 0;
            }
        } else {
            hSpeed = 0;
        }
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            //speed = 0;
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
        solid = false;
        setOriginToCenter();
    }
};

bool initEngine()
{
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

    //Start engine
    engine->init(resX, resY, fs);
    engine->setWindowTitle(config->getString("base", "title").c_str());
    engine->setWindowIcon(config->getString("base", "icon").c_str());

    //Load resources
    rManager->setPath(config->getString("base", "respath"));
    rManager->loadConfig(config->getString("base", "resconf"));

    //Start monitoring input
    input->init();

    return true;
}

bool initObjects()
{
    //Game objects
    Controller *controller = new Controller;
    Player *player = new Player;
    Wall *wall1 = new Wall;
    Wall *wall2 = new Wall;

    engine->addEntity(controller);
    engine->addEntity(player);
    engine->addEntity(wall1);
    engine->addEntity(wall2);

    player->setPosition(128, 256);
    player->setColor(255, 0, 255);

    wall1->setPosition(64, 64);
    wall2->setPosition(256, 256);

    return true;
}

int main(int argc, char **argv) {
    initEngine();
    initObjects();

    bool running = true;

    //Main loop
    while (running) {
        if (!engine->update()) {
            running = false;
        }

        if (input->getKeyReleased(KEY_ESCAPE)) {
            running = false;
        }

        if (input->getKeyReleased(KEY_SPACE)) {
        }
    }

    delete engine;

    return 0;
}
