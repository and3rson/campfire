#include "Grid.h"

Grid::Grid(Camera *camera) : WorldObject(camera)
{
//    this->font.loadFromFile("./res/fonts/Roboto-Regular.ttf");
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");
}

void Grid::draw(sf::RenderWindow *window)
{
    sf::Vector2f cameraPos = this->camera->position;
    sf::Vector2u windowSize = window->getSize();

//    std::cerr << cameraPos.x << "/" << cameraPos.y << "..." << windowSize.y;

    sf::Vector2f screenCenter = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);

    sf::CircleShape cs(10);
    cs.setFillColor(sf::Color(0, 128, 255));

    sf::Vector2f pos(camera->position);

    pos.x = ((int) pos.x / DENSITY) * DENSITY;
    pos.y = ((int) pos.y / DENSITY) * DENSITY;

//    cs.setPosition(this->applyCameraTransformation(pos));
//    std::cerr << cs.getPosition().x;

//    window->draw(cs);

    sf::Color gridColor(255, 255, 255, 32);
    sf::Color textColor(128, 192, 255, 196);

    for (int x = pos.x - DENSITY * 20; x < pos.x + DENSITY * 20; x += DENSITY) {
        sf::Vertex line[] = {
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(x, pos.y - windowSize.y)), gridColor),
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(x, pos.y + windowSize.y)), gridColor),
        };
        window->draw(line, 2, sf::Lines);
        for (int y = pos.y - DENSITY * 10; y < pos.y + DENSITY * 10; y += DENSITY) {
            char textChar[32];
            sprintf(textChar, "%d:%d", x, y);
            sf::Text text(sf::String(textChar), this->font, 10);
            text.setColor(textColor);
            text.setPosition(this->applyCameraTransformation(sf::Vector2f(x + 5, y + 5)));
            text.setRotation(- this->camera->rotation / M_PI * 180);
            window->draw(text);
        }
    }
    for (int y = pos.y - DENSITY * 10; y < pos.y + DENSITY * 10; y += DENSITY) {
        sf::Vertex line[] = {
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(pos.x - windowSize.x, y)), gridColor),
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(pos.x + windowSize.x, y)), gridColor),
        };
        window->draw(line, 2, sf::Lines);
    }
}
