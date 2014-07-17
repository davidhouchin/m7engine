#include "M7engine.h"

using namespace M7engine;
Engine *engine = Engine::getInstance();
Logger *logger = Logger::getInstance();
InputManager *inputManager = InputManager::getInstance();
ResourceManager *rManager = ResourceManager::getInstance();

class TestE : public M7engine::Entity {
private:
    bool isMoving;
    int xOffset, yOffset;
    M7engine::Font *f;

public:
    TestE() {
        isMoving = false;
        xOffset = 0;
        yOffset = 0;
        timer[0] = 120;
        f = rManager->getFont("elgethy");
    }

    void update() {
        if (inputManager->getMouseX() < getX() + getWidth() && inputManager->getMouseX() > getX()) {
            if (inputManager->getMouseY() < getY() + getHeight() && inputManager->getMouseY() > getY()) {
                if (inputManager->getMousePressed(1)) {
                    isMoving = true;
                    xOffset = inputManager->getMouseX() - getX();
                    yOffset = inputManager->getMouseY() - getY();
                }
            }
        }

        if (inputManager->getMouseReleased(1)) {
            isMoving = false;
        }

        if (isMoving) {
            setX(inputManager->getMouseX() - xOffset);
            setY(inputManager->getMouseY() - yOffset);
        }

        if (this->id == 0){engine->renderTextF(128, 64, f, "This text is owned by entity %i", this->id);}
        else if (this->id == 1){engine->renderTextF(128, 128, f, "This text is owned by entity %i", this->id);}
    }

    void alarm(int timerNum) {
        if (timerNum == 0) {
            Logger::getInstance()->logMessage(0, "Alarm 0 from entity %i!", this->id);
        }
    }
};

int main(int argc, char **argv) {
    using namespace M7engine;
    bool running = true;

    logger->setLogFile("m7engine.log");
    logger->setLoggingLevel(1);
    logger->logMessage(0, "Engine started");

    int resX, resY, fs;
    ConfigReader *config = engine->getConfigReader();

    config->loadConfig("../resources/config.ini");
    resX = config->getInt("video", "resX", 640);
    resY = config->getInt("video", "resY", 480);
    fs = config->getInt("video", "fs", 0);
    logger->logMessage(0, "Read config values: %i %i %i", resX, resY, fs);

    engine->init(resX, resY, fs);
    engine->setWindowTitle("Window Title!");
    engine->setWindowIcon("../resources/m7.png");

    rManager->loadConfig("../resources/resources.ini");

    inputManager->init();

    TestE *test = new TestE;
    TestE *test2 = new TestE;
    TestE *test3 = new TestE;
    Sound *tsound = new Sound;

    engine->addEntity(test);
    engine->addEntity(test2);
    engine->addEntity(test3);

    test->setImage(rManager->getSprite("monster"));
    test->setPosition(128, 128);
    test->setColor(255, 0, 255);
    test->setAlpha(255);
    test->getSprite()->setSize(64, 64);
    test->setSize(64, 64);

    test2->setImage(rManager->getSprite("cat"));
    test2->setPosition(256, 128);
    test2->setColor(0, 255, 0);
    test2->setAlpha(125);

    test3->setImage(rManager->getSprite("explosion"));
    test3->setPosition(256, 256);

    tsound = rManager->getSound("boom");

    Timer timer;
    timer.start();

    while (running) {
        if (!engine->update()) {
            running = false;
        }

        if (inputManager->getKeyReleased(KEY_ESCAPE)) {
            running = false;
        }

        if (inputManager->getKeyReleased(KEY_SPACE)) {
            engine->playSound(tsound, 0);
        }

        if (inputManager->getKeyReleased(KEY_C)) {
            std::cout << engine->getConfigReader()->getFirstSection() << std::endl;
            std::cout << engine->getConfigReader()->getNextSection(engine->getConfigReader()->getFirstSection()) << std::endl;
        }
    }

    delete engine;

    return 0;
}
