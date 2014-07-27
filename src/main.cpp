#include "M7engine.h"

using namespace M7engine;
Engine *engine = Engine::getInstance();
Logger *logger = Logger::getInstance();
InputManager *input = InputManager::getInstance();
ResourceManager *rManager = ResourceManager::getInstance();
CollisionManager *cManager = engine->getCollisionManager();
ConfigReader *oConfig = new ConfigReader;

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
            drawFilledRectangle(engine->getViewportX(), engine->getViewportY(), engine->getViewportW(), 32, 200, 200, 200, 95);
            engine->renderTextF(engine->getViewportX() + 20, engine->getViewportY() + 10, f, "FPS: %i", engine->getFPS());
            engine->renderTextF(engine->getViewportX() + 96, engine->getViewportY() + 10, f, "MOUSE XY: %i %i", input->getMouseX(), input->getMouseY());
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
    int speed;
    bool dead, notStarted;
    int startx, starty;
public:
    Player()
    {
        setName("player");
        setProperties(oConfig, getName());

        speed = 5;
        dead = false;
        notStarted = true;
    }

    void update()
    {
        if (notStarted) {
            startx = getX();
            starty = getY();
            notStarted = false;
        }

        if (!dead) {
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
        }}

        engine->setViewport((getX()+getXOffset()) - (engine->getScreenWidth()/2),
                            (getY()+getYOffset()) - (engine->getScreenHeight()/2),
                            engine->getScreenWidth(),
                            engine->getScreenHeight());

        if (engine->getViewportX() < 0) {
            engine->setViewport(0, engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportY() < 0) {
            engine->setViewport(engine->getViewportX(), 0, engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportX() > 640 - engine->getViewportW()) {
            engine->setViewport(640 - engine->getViewportW(), engine->getViewportY(), engine->getViewportW(), engine->getViewportH());
        }
        if (engine->getViewportY() > 480 - engine->getViewportH()) {
            engine->setViewport(engine->getViewportX(), 480 - engine->getViewportH(), engine->getViewportW(), engine->getViewportH());
        }

        //std::cout << engine->getViewportX() << " " << engine->getViewportY() << " " << engine->getViewportW() << " " << engine->getViewportH() << std::endl;

        //drawRectangle(getX(), getY(), getWidth(), getHeight(), 255, 0, 0, 150);
    }

    void collision(Entity *other)
    {
        if (other->getFamily() == "enemy") {
            if (!dead) {
                dead = true;
                setImage(rManager->getSprite("explosion"));
                engine->playSound(rManager->getSound("boom"), 0);
                hSpeed = 0;
                vSpeed = 0;
                timer[0] = 60;
            }
        }
    }

    void alarm(int timerNum)
    {
        if (timerNum == 0) {
            setImage(rManager->getSprite("cat"));
            setX(startx);
            setY(starty);
            dead = false;
        }
    }
};

class EnemyH : public Entity {
private:
public:
    EnemyH()
    {
        setName("enemyh");
        setProperties(oConfig, getName());
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
        setName("enemyv");
        setProperties(oConfig, getName());
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
        setProperties(oConfig, getName());
    }
};

class Level {
private:
    std::string filename;
    int interval;
    int width;
    int height;
public:
    Level()
    {
        interval = 0;
        width = 0;
        height = 0;
    }

    bool load(std::string filename)
    {
        std::ifstream file(filename.c_str());
        if (!file.is_open()) {
            logger->logError(0, "Failed to load level '%s'", filename.c_str());
            return false;
        }

        int xx, yy;
        xx = 0;
        yy = 0;

        Entity *entity;

        while (!file.eof()) {
            std::string line;
            std::getline(file, line, '\n');

            if (line[0] == '#') {
                continue;
            }

            if (line[0] == 's') {
                interval = stringToInt(split(line, ':').back());
                yy = interval;
                continue;
            }

            if (line[0] == 'w') {
                width = stringToInt(split(line, ':').back());
                continue;
            }

            if (line[0] == 'h') {
                height = stringToInt(split(line, ':').back());
                continue;
            }

            switch (stringToInt(line)) {
            case 1: entity = new Player; entity->setPosition(xx, yy); break;
            case 2: entity = new Wall; entity->setPosition(xx, yy); break;
            case 3: entity = new EnemyH; entity->setPosition(xx, yy); break;
            case 4: entity = new EnemyV; entity->setPosition(xx, yy); break;
            default: break;
            }

            xx += interval;
            if (xx >= width) {
                xx = 0; yy += interval;
            }

            continue;
        }

        return true;
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
    oConfig->loadConfig("../resources/objects.ini");

    //Game objects
    Controller *controller = new Controller;

    Level *level = new Level;
    level->load("../resources/test.map");

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
            switch (engine->getWindowMode()) {
            case 0: engine->setWindowMode(1); break;
            case 1: engine->setWindowMode(2); break;
            case 2: engine->setWindowMode(0); break;
            }
        }
    }

    delete engine;

    return 0;
}
