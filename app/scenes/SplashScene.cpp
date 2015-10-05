#include "SplashScene.h"

SplashScene::SplashScene(GameEngine *engine) : AScene(engine)
{
    this->window = this->engine->getWindow();
}

void SplashScene::tick()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
    }

//    this->window->clear();

//    this->window->display();
}
