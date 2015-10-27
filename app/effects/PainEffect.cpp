//
// Created by anderson on 22.10.15.
//

#include <world/Camera.h>
#include "PainEffect.h"

PainEffect::PainEffect(GameEngine *engine, Camera *camera, int power, int duration) : AEffect(engine), camera(camera), power(power), duration(duration) {
    this->window = this->engine->getWindow();
    this->clock.restart();
    this->camera->rShift = sf::Vector2f(0, 0);
}

bool PainEffect::tick() {
//    sf::Image capture = this->window->capture();
    this->camera->setWPosition(this->camera->getWPosition() - this->camera->rShift);
    float normal = ((float) this->clock.getElapsedTime().asMilliseconds()) / this->duration;
    float result = pow((normal - 1) , 4);
    int ampFull = ((float) this->power) * result;
    int ampHalf = ampFull / 2;
    if (ampHalf > 0) {
        this->camera->rShift += sf::Vector2f(
                this->random(ampFull) - ampHalf,
                this->random(ampFull) - ampHalf
        );
        std::cout << result * 64 << std::endl;
        sf::Color blood(128, 0, 0, result * 72);
        sf::RectangleShape filter(sf::Vector2f(this->engine->getWindow()->getSize()));
        filter.setFillColor(blood);
        this->window->draw(filter);
        return true;
    } else {
        this->camera->rShift = sf::Vector2f(0, 0);
        return false;
    }
}
