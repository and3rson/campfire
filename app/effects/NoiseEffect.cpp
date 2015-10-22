#include "NoiseEffect.h"

NoiseEffect::NoiseEffect(GameEngine *engine) : AEffect(engine)
{
    this->window = this->engine->getWindow();
}

bool NoiseEffect::tick()
{
    int maxW = this->window->getSize().x;
    int maxH = this->window->getSize().x;

    for (int i = 0; i < 20; i++) {
        int shade = this->random(256);
        sf::Vector2f pos = sf::Vector2f(this->random(maxW), this->random(maxH));
        sf::Color color = sf::Color(shade, shade, shade, 256 - shade);
        sf::Vertex line[] = {
            sf::Vertex(pos, color),
            sf::Vertex(pos + sf::Vector2f(this->random(10) - 5, this->random(10) - 5), color)
        };
        this->window->draw(line, 2, sf::Lines);
    }

    int color = this->random(256);
    int opacity = this->random(24);

    sf::RectangleShape shade;
    shade.setFillColor(sf::Color(color, color, color, opacity));
    shade.setPosition(0, 0);
    shade.setSize(sf::Vector2f(maxW, maxH));
    this->window->draw(shade);
}
