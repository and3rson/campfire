#include <iostream>
#include <cstdio>

#include "config.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "SteamAdapter.h"
#include "GameEngine.h"
#include "scenes/SplashScene.h"
#include "scenes/MainMenuScene.h"
#include "effects/NoiseEffect.h"

using namespace std;

//#define WINDOW_WIDTH 1200
//#define WINDOW_HEIGHT 800

int main()
{
    SteamAdapter steamAdapter;
    if (!steamAdapter.initialize()) {
        return 1;
    }

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    //    settings.attributeFlags = sf::ContextSettings::Debug;
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    int windowWidth = videoMode.width - 40;
    int windowHeight = videoMode.height - 40;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML App", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setMouseCursorVisible(false);

    window.setPosition(sf::Vector2i((videoMode.width - windowWidth) / 2 + videoMode.width, (videoMode.height - windowHeight) / 2));

    sf::Clock frameClock;
    int frameCount = 0;
    char title[64];

    GameEngine::initialize(&window);
    GameEngine *engine = GameEngine::getInstance();
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

    return 0;
}
