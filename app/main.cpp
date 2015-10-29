#include <iostream>

#include "config.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "SteamAdapter.h"
#include "GameEngine.h"
#include "scenes/MainMenuScene.h"

using namespace std;

//#define WINDOW_WIDTH 1200
//#define WINDOW_HEIGHT 800

int main()
{
    Recycler reg;

    SteamAdapter steamAdapter;
    if (!steamAdapter.initialize()) {
        return 1;
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    //    settings.attributeFlags = sf::ContextSettings::Debug;
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    int windowWidth = videoMode.width / DIV - SUB;
    int windowHeight = videoMode.height / DIV - SUB;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML App", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

    window.setPosition(sf::Vector2i((videoMode.width - windowWidth) / DIV + videoMode.width, (videoMode.height - windowHeight) / DIV));

    sf::Clock frameClock;
    int frameCount = 0;
    char title[64];

    GameEngine::initialize(&window);
    GameEngine *engine = GameEngine::getInstance();
    reg.hold(engine, TRACE);
    engine->start();

    engine->setScene(new MainMenuScene(engine));
//    engine->setScene(new SplashScene(engine));
//    engine->setEffect(new NoiseEffect(engine));

    while (window.isOpen()) {
        engine->tick();

        frameCount++;

        int timeElapsed = frameClock.getElapsedTime().asMilliseconds();

        if (timeElapsed > 100) {
            int fps = 1000 / ((float) timeElapsed / frameCount);
            sprintf(title, "App [FPS: %d]", fps);

            window.setTitle(sf::String(title));
            frameCount = 0;
            frameClock.restart();
        }
    }

    reg.cleanUp();

    std::cerr << "Objects lost: " << Registry::getRefCount() << std::endl;

    std::cerr << "Lost objects:" << std::endl;

    for (Registry *registry : Registry::getAllObjects()) {
        std::cerr << " ! " << ((WorldObject *) registry)->getType() << std::endl;
//        std::cerr << ((Animation *) registry)->getFullName() << std::endl;
    }

    return 0;
}
