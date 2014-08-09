#include "M7engine.h"

using namespace M7engine;
Engine *engine = Engine::getInstance();
Logger *logger = Logger::getInstance();
InputManager *input = InputManager::getInstance();
ResourceManager *resources = ResourceManager::getInstance();
CollisionManager *cManager = engine->getCollisionManager();
WindowManager *wm = WindowManager::getInstance();
ConfigReader *oConfig = new ConfigReader;

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

        speed = 3;
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
            if (!cManager->getPlaceMeetingSolid(getXBBox(), getYBBox() - speed, this->id)) {
                vSpeed = speed * -1;
                if (this->getSprite()->getName() != "playerup") {setImage(resources->getSprite("playerup")); }
            } else {
                vSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_DOWN)) {
            if (!cManager->getPlaceMeetingSolid(getXBBox(), getYBBox() + speed, this->id)) {
                vSpeed = speed;
                if (this->getSprite()->getName() != "playerdown") {setImage(resources->getSprite("playerdown")); }
            } else {
                vSpeed = 0;
            }
        } else {
            vSpeed = 0;
        }

        if (input->getKeyHeld(KEY_LEFT)) {
            if (!cManager->getPlaceMeetingSolid(getXBBox() - speed, getYBBox(), this->id)) {
                hSpeed = speed * -1;
                if (this->getSprite()->getName() != "playerleft") {setImage(resources->getSprite("playerleft")); }
            } else {
                hSpeed = 0;
            }
        } else if (input->getKeyHeld(KEY_RIGHT)) {
            if (!cManager->getPlaceMeetingSolid(getXBBox() + speed, getYBBox(), this->id)) {
                hSpeed = speed;
                if (this->getSprite()->getName() != "playerright") {setImage(resources->getSprite("playerright")); }
            } else {
                hSpeed = 0;
            }
        } else {
            hSpeed = 0;
        }

        if ((vSpeed != 0) || (hSpeed != 0)) {
            image->setDelay(10);
        } else {
            image->setDelay(-1);
        }}

        engine->setViewport((getX() + getXOffset()) - (engine->getScreenWidth()/2),
                            (getY() + getYOffset()) - (engine->getScreenHeight()/2),
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
        if (engine->getViewportY() > 1920 - engine->getViewportH()) {
            engine->setViewport(engine->getViewportX(), 1920 - engine->getViewportH(), engine->getViewportW(), engine->getViewportH());
        }
    }

    void collision(Entity *other)
    {
        if ((other->getFamily() == "enemy") && (!notStarted)) {
            if (!dead) {
                dead = true;
                setImage(resources->getSprite("explosion"));
                xOffset = 0;
                yOffset = 0;
                engine->playSound(resources->getSound("boom"), 0);
                hSpeed = 0;
                vSpeed = 0;
                timer[0] = (image->getMaxFrames()-1) * image->getDelay();
                setAlpha(200);
            }
        }
    }

    void alarm(int timerNum)
    {
        if (timerNum == 0) {
            setImage(resources->getSprite("playerdown"));
            setOriginToImageCenter();
            setX(startx);
            setY(starty);
            dead = false;
            setAlpha(255);
        }
    }
};

class EnemyH : public Entity {
private:
public:
    EnemyH()
    {
        setName("zombie");
        setProperties(oConfig, getName());
        setImage(resources->getSprite("zombieright"));
        hSpeed = 4;
    }

    void update()
    {
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            hSpeed = (hSpeed * -1);
            if (this->getSprite()->getName() != "zombieleft") {
                setImage(resources->getSprite("zombieleft"));
            } else {
                setImage(resources->getSprite("zombieright"));
            }
        }
    }
};

class EnemyV : public Entity {
private:
public:
    EnemyV()
    {
        setName("zombie");
        setProperties(oConfig, getName());
        vSpeed = 4;
    }

    void update()
    {
    }

    void collision(Entity *other)
    {
        if (other->getSolid()) {
            vSpeed = (vSpeed * -1);
            if (this->getSprite()->getName() != "zombieup") {
                setImage(resources->getSprite("zombieup"));
            } else {
                setImage(resources->getSprite("zombiedown"));
            }
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

class Tree : public Entity {
private:
public:
    Tree()
    {
        setName("tree");
        setProperties(oConfig, getName());
    }
};

class Dirt : public Tile {
private:
public:
    Dirt()
    {
        setName("dirt");
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
        Tile *tile;

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
            case 5: tile = new Dirt; tile->setPosition(xx, yy); break;
            case 6: entity = new Tree; entity->setPosition(xx, yy); break;
            default: break;
            }

            xx += interval;
            if (xx >= width) {
                xx = 0; yy += interval;
            }

            continue;
        }

        engine->sortEntitiesByDepth();
        engine->sortTilesByDepth();

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

    if (config->getBool("debug", "drawbboxes", false) == true) {
        engine->toggleDrawBoundingBoxes();
    }

    //Load resources
    resources->setPath(config->getString("base", "respath"));
    resources->loadConfig(config->getString("base", "resconf"));

    //Start monitoring input
    input->init();

    //Load widget config
    wm->loadConfig("../resources/widget.ini");

    //Give the console it's font
    engine->getConsole()->setFont(resources->getFont("veramono"));

    return true;
}

bool initObjects()
{
    oConfig->loadConfig("../resources/objects.ini");

    //Game objects
    Level *level = new Level;
    level->load("../resources/maps/test.map");

    //Test Window/Widgets
    {
    Window *win = new Window;
    win->setX(100);
    win->setY(100);
    win->setWidth(240);
    win->setHeight(155);
    win->setTitle("Calculator");
    wm->addWindow(win);

    Label *resultLabel = new Label;
    resultLabel->setX(win->getX()+2);
    resultLabel->setY(win->getY()+18);
    resultLabel->setWidth(236);
    resultLabel->setHeight(32);
    resultLabel->setBorder(true);
    resultLabel->setText("0");

    Button *oneBtn = new Button;
    oneBtn->setX(win->getX()+2);
    oneBtn->setY(win->getY()+52);
    oneBtn->setWidth(32);
    oneBtn->setHeight(32);
    oneBtn->setText("1");

    Button *twoBtn = new Button;
    twoBtn->setX(win->getX()+2);
    twoBtn->setY(win->getY()+86);
    twoBtn->setWidth(32);
    twoBtn->setHeight(32);
    twoBtn->setText("2");

    Button *threeBtn = new Button;
    threeBtn->setX(win->getX()+2);
    threeBtn->setY(win->getY()+120);
    threeBtn->setWidth(32);
    threeBtn->setHeight(32);
    threeBtn->setText("3");

    Button *fourBtn = new Button;
    fourBtn->setX(win->getX()+36);
    fourBtn->setY(win->getY()+52);
    fourBtn->setWidth(32);
    fourBtn->setHeight(32);
    fourBtn->setText("4");

    Button *fiveBtn = new Button;
    fiveBtn->setX(win->getX()+36);
    fiveBtn->setY(win->getY()+86);
    fiveBtn->setWidth(32);
    fiveBtn->setHeight(32);
    fiveBtn->setText("5");

    Button *sixBtn = new Button;
    sixBtn->setX(win->getX()+36);
    sixBtn->setY(win->getY()+120);
    sixBtn->setWidth(32);
    sixBtn->setHeight(32);
    sixBtn->setText("6");

    Button *sevenBtn = new Button;
    sevenBtn->setX(win->getX()+70);
    sevenBtn->setY(win->getY()+52);
    sevenBtn->setWidth(32);
    sevenBtn->setHeight(32);
    sevenBtn->setText("7");

    Button *eightBtn = new Button;
    eightBtn->setX(win->getX()+70);
    eightBtn->setY(win->getY()+86);
    eightBtn->setWidth(32);
    eightBtn->setHeight(32);
    eightBtn->setText("8");

    Button *nineBtn = new Button;
    nineBtn->setX(win->getX()+70);
    nineBtn->setY(win->getY()+120);
    nineBtn->setWidth(32);
    nineBtn->setHeight(32);
    nineBtn->setText("9");

    Button *zeroBtn = new Button;
    zeroBtn->setX(win->getX()+104);
    zeroBtn->setY(win->getY()+86);
    zeroBtn->setWidth(32);
    zeroBtn->setHeight(32);
    zeroBtn->setText("0");

    Button *decimalBtn = new Button;
    decimalBtn->setX(win->getX()+104);
    decimalBtn->setY(win->getY()+120);
    decimalBtn->setWidth(32);
    decimalBtn->setHeight(32);
    decimalBtn->setText(".");

    Button *clearBtn = new Button;
    clearBtn->setX(win->getX()+104);
    clearBtn->setY(win->getY()+52);
    clearBtn->setWidth(32);
    clearBtn->setHeight(32);
    clearBtn->setText("C");

    Button *plusBtn = new Button;
    plusBtn->setX(win->getX()+172);
    plusBtn->setY(win->getY()+52);
    plusBtn->setWidth(32);
    plusBtn->setHeight(32);
    plusBtn->setText("+");

    Button *minusBtn = new Button;
    minusBtn->setX(win->getX()+172);
    minusBtn->setY(win->getY()+86);
    minusBtn->setWidth(32);
    minusBtn->setHeight(32);
    minusBtn->setText("-");

    Button *multiplyBtn = new Button;
    multiplyBtn->setX(win->getX()+206);
    multiplyBtn->setY(win->getY()+52);
    multiplyBtn->setWidth(32);
    multiplyBtn->setHeight(32);
    multiplyBtn->setText("*");

    Button *divideBtn = new Button;
    divideBtn->setX(win->getX()+206);
    divideBtn->setY(win->getY()+86);
    divideBtn->setWidth(32);
    divideBtn->setHeight(32);
    divideBtn->setText("/");

    Button *equalsBtn = new Button;
    equalsBtn->setX(win->getX()+172);
    equalsBtn->setY(win->getY()+120);
    equalsBtn->setWidth(66);
    equalsBtn->setHeight(32);
    equalsBtn->setText("=");

    win->addWidget(resultLabel);
    win->addWidget(oneBtn);
    win->addWidget(twoBtn);
    win->addWidget(threeBtn);
    win->addWidget(fourBtn);
    win->addWidget(fiveBtn);
    win->addWidget(sixBtn);
    win->addWidget(sevenBtn);
    win->addWidget(eightBtn);
    win->addWidget(nineBtn);
    win->addWidget(zeroBtn);
    win->addWidget(decimalBtn);
    win->addWidget(clearBtn);
    win->addWidget(plusBtn);
    win->addWidget(minusBtn);
    win->addWidget(multiplyBtn);
    win->addWidget(divideBtn);
    win->addWidget(equalsBtn);
    }

    return true;
}

int main()
{
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

        if (input->getKeyReleased(KEY_F4)) {
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
