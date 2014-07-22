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
    bool showInfo, aDir;
    int a;
public:
    Controller()
    {
        f = rManager->getFont("elgethy");
        f->setColor(60, 185, 85);
        f2 = rManager->getFont("oldpix");
        showInfo = true;
        a = 0;
        aDir = true;
    }

    void update()
    {
        if (input->getKeyReleased(KEY_TAB)) {
            showInfo = !showInfo;
        }

        //Performance Text
        if (showInfo) {
            drawFilledRectangle(0, 0, engine->getScreenWidth(), 32, 200, 200, 200, 200);
            engine->renderTextF(20, 10, f, "FPS: %i", engine->getFPS());
            engine->renderTextF(96, 10, f, "MOUSE XY: %i %i", input->getMouseX(), input->getMouseY());
        }

        if (aDir) {
            a++;
        } else {
            a--;
        }

        if (a >= 255) {
            aDir = false;
        } else if (a <= 0) {
            aDir = true;
        }

        f2->setAlpha(a);
        engine->renderText(engine->getScreenWidth()/2, engine->getScreenHeight()/2, f2, "Example");
    }

};

class Player : public Entity {
private:
    int speed = 5;
public:
    Player()
    {
        setName("player");
    }

    void update()
    {
        if (input->getKeyHeld(KEY_UP)) {
            if (!cManager->getPlaceMeetingSolid(getX(), getY() - speed, this->id)) {
                vSpeed = speed * -1;
            } else {
                vSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            if (!cManager->getPlaceMeetingSolid(getX(), getY() + speed, this->id)) {
                vSpeed = speed;
            } else {
                vSpeed = 0;
            }
        } else {
            vSpeed = 0;
        }

        if (input->getKeyHeld(KEY_LEFT)) {
            if (!cManager->getPlaceMeetingSolid(getX() - speed, getY(), this->id)) {
                hSpeed = speed * -1;
            } else {
                hSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            if (!cManager->getPlaceMeetingSolid(getX() + speed, getY(), this->id)) {
                hSpeed = speed;
            } else {
                hSpeed = 0;
            }
        } else {
            hSpeed = 0;
        }

        drawRectangle(getX(), getY(), getWidth(), getHeight(), 255, 0, 0, 150);
    }

    void collision(Entity *other)
    {
        if (other->getName() == "enemy") {
            std::cout << "You died!" << std::endl;
        }
    }
};

class EnemyH : public Entity {
private:
public:
    EnemyH()
    {
        setName("enemy");
        setImage(rManager->getSprite("badguy"));
        hSpeed = 6;
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            hSpeed = (hSpeed * -1);
        }
    }
};

class EnemyV : public Entity {
private:
public:
    EnemyV()
    {
        setName("enemy");
        setImage(rManager->getSprite("badguy"));
        vSpeed = 6;
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            vSpeed = (vSpeed * -1);
        }
    }
};

class Wall : public Entity {
private:
public:
    Wall()
    {
        setName("wall");
        setImage(rManager->getSprite("wall"));
        solid = true;
        setOriginToCenter();
        timer[0] = 90;
    }

    void alarm(int timerNum) {
        if (timerNum == 0) {
            if (getColor().r == 255) {
                setColor(0, 0, 255);
            } else {
                setColor(255, 0, 0);
            }
            timer[0] = 90;
        }
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
    engine->setWindowTitle(config->getString("base", "title", "").c_str());
    engine->setWindowIcon(config->getString("base", "icon", "").c_str());

    //Load resources
    rManager->setPath(config->getString("base", "respath"));
    rManager->loadConfig(config->getString("base", "resconf"));

    //Start monitoring input
    input->init();

    return true;
}

bool initObjects()
{
    ConfigReader *oConfig = new ConfigReader;
    oConfig->loadConfig("../resources/objects.ini");

    //Game objects
    Controller *controller = new Controller;
    Player *player = new Player;
    Wall *wall1 = new Wall;
    Wall *wall2 = new Wall;
    Wall *wall3 = new Wall;
    EnemyH *enemy1 = new EnemyH;
    EnemyV *enemy2 = new EnemyV;

    player->setPosition(128, 256);
    player->setProperties(oConfig, player->getName());

    wall1->setPosition(64, 64);
    wall2->setPosition(256, 64);
    wall3->setPosition(256, 256);

    enemy1->setPosition(128, 64);
    enemy1->setColor(255, 0, 0);

    enemy2->setPosition(256, 96);
    enemy2->setColor(0, 255, 0);

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
