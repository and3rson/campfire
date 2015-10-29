#include "Grid.h"

Grid::Grid(Camera *camera) : WorldObject(camera)
{
//    this->font.loadFromFile("./res/fonts/Roboto-Regular.ttf");
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");
}

void Grid::draw(sf::RenderWindow *window)
{
    sf::Vector2f cameraPos = this->camera->getWPosition();
    sf::Vector2u windowSize = window->getSize();

//    std::cerr << cameraPos.x << "/" << cameraPos.y << "..." << windowSize.y;

    sf::Vector2f screenCenter = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);

    sf::CircleShape cs(10);
    cs.setFillColor(sf::Color(0, 128, 255));

    sf::Vector2f pos(camera->getWPosition());

    pos.x = ((int) pos.x / DENSITY) * DENSITY;
    pos.y = ((int) pos.y / DENSITY) * DENSITY;

//    cs.setWPosition(this->applyCameraTransformation(pos));
//    std::cerr << cs.getWPosition().x;

//    window->draw(cs);

    sf::Color gridColor(255, 255, 255, 32);
    sf::Color textColor(128, 192, 255, 196);

    sf::Vertex xLine[] = {
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(0, 0)), sf::Color::Red),
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(0, DENSITY)), sf::Color::Red),
    };
    window->draw(xLine, 2, sf::Lines);
    sf::Vertex yLine[] = {
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(0, 0)), sf::Color::Green),
            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(DENSITY, 0)), sf::Color::Green),
    };
    window->draw(yLine, 2, sf::Lines);

    sf::Vector2f tr = this->applyCameraTransformation(sf::Vector2f(-1000, -1000));
//    std::cout << tr.x << " / " << tr.y << std::endl;

    bool odd = false;
    sf::Color color1(255, 255, 255, 16);
    sf::Color color2(255, 255, 255, 32);

    for (int x = pos.x - DENSITY * 20; x < pos.x + DENSITY * 20; x += DENSITY) {
//        sf::Vertex line[] = {
//            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(x, pos.y - windowSize.y)), gridColor),
//            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(x, pos.y + windowSize.y)), gridColor),
//        };
//
//        window->draw(line, 2, sf::Lines);

        for (int y = pos.y - DENSITY * 20; y < pos.y + DENSITY * 20; y += DENSITY) {
            char textChar[32];
            sprintf(textChar, "%d:%d", x, y);
            sf::Text text(sf::String(textChar), this->font, 10);
            text.setColor(textColor);
            text.setPosition(this->applyCameraTransformation(sf::Vector2f(x + 5, y + 5)));
            text.setRotation(- this->camera->getWRotation() / M_PI * 180);
            window->draw(text);

//            sf::RectangleShape rect(sf::Vector2f(DENSITY, DENSITY));
//            rect.setFillColor((x + y) % (DENSITY * 2) == 0 ? color1 : color2);
////            rect.setOrigin(DENSITY / 2, DENSITY / 2);
//            rect.setOrigin(0, 0);
//            rect.setWRotation(- this->camera->wRotation / M_PI * 180);
//            rect.setWPosition(this->applyCameraTransformation(sf::Vector2f(x, y)));
//            window->draw(rect);
        }
    }
    for (int y = pos.y - DENSITY * 10; y < pos.y + DENSITY * 10; y += DENSITY) {
//        sf::Vertex line[] = {
//            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(pos.x - windowSize.x, y)), gridColor),
//            sf::Vertex(this->applyCameraTransformation(sf::Vector2f(pos.x + windowSize.x, y)), gridColor),
//        };
//        window->draw(line, 2, sf::Lines);
    }
}

std::string Grid::getType() {
    return "grid";
}
