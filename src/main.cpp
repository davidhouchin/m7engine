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
        //Do some startup work
        if (notStarted) {
            startx = getX();
            starty = getY();
            notStarted = false;
        }

        //Key movement code
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

        //Sprite animation
        if ((vSpeed != 0) || (hSpeed != 0)) {
            image->setDelay(10);
        } else {
            image->setDelay(-1);
        }}

        //Move viewport along with character
        engine->setViewport((getX() + getXOffset()) - (engine->getScreenWidth()/2),
                            (getY() + getYOffset()) - (engine->getScreenHeight()/2),
                            engine->getScreenWidth(),
                            engine->getScreenHeight());

        //Stop viewport at edges of screen
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
                engine->playSound(resources->getSound("boom"), 0);
                xOffset = 0;
                yOffset = 0;
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
    Window *win = new Window(275, 200, 240, 155);
    win->setTitle("Calculator");
    win->setSticky(false);
    wm->addWindow(win);

    Label *resultLabel = new Label(win->getX()+2, win->getY()+18, 236, 32);
    resultLabel->setBorder(true);
    resultLabel->setText("0");

    Button *oneBtn = new Button(win->getX()+2, win->getY()+52, 32, 32);
    oneBtn->setText("1");
    oneBtn->setName("one");

    Button *twoBtn = new Button(win->getX()+2, win->getY()+86, 32, 32);
    twoBtn->setText("2");
    twoBtn->setName("two");

    Button *threeBtn = new Button(win->getX()+2, win->getY()+120, 32, 32);
    threeBtn->setText("3");
    threeBtn->setName("three");

    Button *fourBtn = new Button(win->getX()+36, win->getY()+52, 32, 32);
    fourBtn->setText("4");
    fourBtn->setName("four");

    Button *fiveBtn = new Button(win->getX()+36, win->getY()+86, 32, 32);
    fiveBtn->setText("5");
    fiveBtn->setName("five");

    Button *sixBtn = new Button(win->getX()+36, win->getY()+120, 32, 32);
    sixBtn->setText("6");
    sixBtn->setName("six");

    Button *sevenBtn = new Button(win->getX()+70, win->getY()+52, 32, 32);
    sevenBtn->setText("7");
    sevenBtn->setName("seven");

    Button *eightBtn = new Button(win->getX()+70, win->getY()+86, 32, 32);
    eightBtn->setText("8");
    eightBtn->setName("eight");

    Button *nineBtn = new Button(win->getX()+70, win->getY()+120, 32, 32);
    nineBtn->setText("9");
    nineBtn->setName("nine");

    Button *zeroBtn = new Button(win->getX()+104, win->getY()+86, 32, 32);
    zeroBtn->setText("0");
    zeroBtn->setName("zero");

    Button *decimalBtn = new Button(win->getX()+104, win->getY()+120, 32, 32);
    decimalBtn->setText(".");
    decimalBtn->setName("decimal");

    Button *clearBtn = new Button(win->getX()+104, win->getY()+52, 32, 32);
    clearBtn->setText("C");
    clearBtn->setName("clear");

    Button *plusBtn = new Button(win->getX()+172, win->getY()+52, 32, 32);
    plusBtn->setText("+");
    plusBtn->setName("plus");

    Button *minusBtn = new Button(win->getX()+172, win->getY()+86, 32, 32);
    minusBtn->setText("-");
    minusBtn->setName("minus");

    Button *multiplyBtn = new Button(win->getX()+206, win->getY()+52, 32, 32);
    multiplyBtn->setText("X");
    multiplyBtn->setName("multiply");

    Button *divideBtn = new Button(win->getX()+206, win->getY()+86, 32, 32);
    divideBtn->setText("/");
    divideBtn->setName("divide");

    Button *equalsBtn = new Button(win->getX()+172, win->getY()+120, 66, 32);
    equalsBtn->setText("=");
    equalsBtn->setName("equals");

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

    win->setVisible(false);
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
