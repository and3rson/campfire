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
//    sf::Image img = this->window->capture();
//    sf::Texture texture;
//    texture.loadFromImage(img);
//    sf::Sprite blur(texture);
    this->window->clear();
//    this->window->draw(blur);
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
