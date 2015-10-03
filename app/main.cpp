#include <iostream>
#include <cstdio>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// #include "SteamAdapter.h"
#include "GameEngine.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

int main()
{
//    SteamAdapter steamAdapter;
//    if (!steamAdapter.initialize()) {
//        return 1;
//    }

    cout << "Hello World!" << endl;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML App", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    window.setPosition(sf::Vector2i((videoMode.width - WINDOW_WIDTH) / 2, (videoMode.height - WINDOW_HEIGHT) / 2));

    sf::Clock frameClock;
    int frameCount = 0;
    char title[64];

    GameEngine *engine = new GameEngine(&window);
    engine->start();

    while (window.isOpen()) {
        engine->tick();

        frameCount++;

        int timeElapsed = frameClock.getElapsedTime().asMilliseconds();

        if (timeElapsed > 100) {
            int fps = 1000 / ((float) timeElapsed / frameCount);
            sprintf(title, "SFML App [FPS: %d]", fps);

            window.setTitle(sf::String(title));
            frameCount = 0;
            frameClock.restart();
        }
    }

    return 0;
}
