#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow *window) : window(window)
{
}

void GameEngine::start()
{
    sf::Texture texture;
//    if (texture.loadFromFile("./res/textures/ground.jpg")) {
//        cerr << "Failed to load sprite!";
//    }

    this->worldClock.restart();
    this->frameClock.restart();

//    groundSprite.setTexture(*texture);
//    groundSprite.setOrigin(texture->getSize().x, texture->getSize().y);
//    groundSprite.setPosition(sf::Vector2f(0, 0));
//    groundSprite.setColor(sf::Color(0, 128, 255));

    int width = window->getSize().x;
    int height = window->getSize().y;

    this->lastMousePos = NULL;

    this->camera = new Camera();

    this->player = new Creature(this->camera);
    this->player->setPosition(sf::Vector2f(400, 300));

    this->enemy = new Creature(this->camera);
    this->enemy->setPosition(sf::Vector2f(200, 200));
    this->enemy->moveTo(sf::Vector2f(random() % 100 + 100, random() % 100 + 100));

    this->camera->attachTo(this->player);

    this->moveVector = sf::Vector2f(0, 0);

    sf::Mouse::setPosition(sf::Vector2i(window->getPosition().x + window->getSize().x / 2, window->getPosition().y + window->getSize().y / 2));
}

void GameEngine::tick()
{
    int msPassed = this->frameClock.getElapsedTime().asMilliseconds();
    this->frameClock.restart();

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        } else if (event.type == sf::Event::MouseMoved) {
            if (this->lastMousePos != NULL) {
                int dx = event.mouseMove.x - this->lastMousePos->x;
                int dy = event.mouseMove.y - this->lastMousePos->y;

                this->player->rotation += (float) dx / 300; // Sensitivity
            } else {
                this->lastMousePos = new sf::Vector2i();
            }
            this->lastMousePos->x = event.mouseMove.x;
            this->lastMousePos->y = event.mouseMove.y;
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    this->moveVector.y = 1;
                    break;
                case sf::Keyboard::S:
                    this->moveVector.y = -1;
                    break;
                case sf::Keyboard::A:
                    this->moveVector.x = 1;
                    break;
                case sf::Keyboard::D:
                    this->moveVector.x = -1;
                    break;
                default:
                    break;
            }
            this->player->startMove(this->moveVector);
        } else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                case sf::Keyboard::S:
                    this->moveVector.y = 0;
                    break;
                case sf::Keyboard::A:
                case sf::Keyboard::D:
                    this->moveVector.x = 0;
                    break;
                default:
                    break;
            }

            this->player->startMove(this->moveVector);
        }
    }

    static sf::Clock testClock;

    if (testClock.getElapsedTime().asMilliseconds() > 1000) {
        testClock.restart();
        sf::Vector2f target = sf::Vector2f(random() % 100 + 100, random() % 100 + 100);
//        srand(testClock.getElapsedTime().asMicroseconds());
//        std::cerr << this->enemy->position.x << "//" << target.x << "/" << target.y;
        this->enemy->moveTo(target);
    }

    window->clear();

    this->player->update();
    this->camera->update();
    this->enemy->update();

    window->draw(this->player->getDrawable());
    window->draw(this->enemy->getDrawable());

    window->display();
}
