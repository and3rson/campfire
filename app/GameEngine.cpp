#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow *window) : window(window)
{
}

void GameEngine::start()
{
}

void GameEngine::tick()
{
    this->window->clear();
    this->scene->tick();
    if (this->effect) {
        this->effect->tick();
    }
    this->window->display();
}

void GameEngine::setScene(AScene *scene)
{
    this->scene = scene;
}

void GameEngine::setEffect(AEffect *effect)
{
    this->effect = effect;
}

sf::RenderWindow *GameEngine::getWindow()
{
    return this->window;
}
