#include <world/Pistol.h>
#include "MainMenuScene.h"
#include "GameEngine.h"

MainMenuScene::MainMenuScene(GameEngine *engine) : AScene(engine)
{
    this->worldClock.restart();
    this->frameClock.restart();

    this->window = this->engine->getWindow();

    int width = this->window->getSize().x;
    int height = this->window->getSize().y;

    this->lastMousePos = NULL;

    this->camera = new Camera();

    this->grid = new Grid(this->camera);

    this->player = new Creature("bob", this->camera);
    this->player->setPosition(sf::Vector2f(400, 300));
    this->player->arm(new Pistol(this->camera));
    this->objects.push_back(this->player);

//    this->enemy = new Creature("girl", this->camera);
    this->enemy = new Creature("bob", this->camera);
    this->enemy->setPosition(sf::Vector2f(200, 200));
    this->enemy->moveTo(sf::Vector2f(_dbgRandom(), _dbgRandom()));
    this->objects.push_back(this->enemy);

    this->camera->attachTo(this->player);
    //    this->camera->update();
    std::cerr << "POS:" << this->camera->wPosition.x << std::endl;

    this->moveVector = sf::Vector2f(0, 0);

    sf::Mouse::setPosition(sf::Vector2i(window->getPosition().x + window->getSize().x / 2, window->getPosition().y + window->getSize().y / 2));
}

void MainMenuScene::tick()
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

                this->player->wRotation += (float) dx / 300; // Sensitivity
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
                    if (this->moveVector.y == 1) {
                        this->moveVector.y = 0;
                    }
                case sf::Keyboard::S:
                    if (this->moveVector.y == -1) {
                        this->moveVector.y = 0;
                    }
                    break;
                case sf::Keyboard::A:
                    if (this->moveVector.x == 1) {
                        this->moveVector.x = 0;
                    }
                case sf::Keyboard::D:
                    if (this->moveVector.x == -1) {
                        this->moveVector.x = 0;
                    }
                    break;
                default:
                    break;
            }

            this->player->startMove(this->moveVector);
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//            Projectile *projectile = new Projectile(this->camera);
//            projectile->setPosition(sf::Vector2f(this->player->wPosition));
//            projectile->wRotation = this->player->wRotation;
//            projectile->startMove(sf::Vector2f(0, 1));
//            std::cerr << "SHOOT" << std::endl;
//            this->objects.push_back(projectile);
            this->player->useArmedItem();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            WorldObject *dropped = this->player->dropArmedItem();

            sf::FloatRect wPlayerHitbox = this->player->getWHitbox();

            std::cerr << "object count: " << this->objects.size() << std::endl;
            std::vector<WorldObject *>::iterator it = this->objects.begin();
            for(WorldObject *object = *it; it != this->objects.end(); object = *(++it)) {
                std::cerr << " - " << ((Item *) object)->getType() << std::endl;
                std::cerr << " - " << ((Item *) object)->getType() << std::endl;
                if (object->getType() == "item") {
                    std::cerr << "picking up " << ((Item *) object)->getType() << std::endl;
                    if (wPlayerHitbox.intersects(object->getWHitbox())) {
                        this->player->arm((Item *) object);
                        this->objects.erase(it);
                        break;
                    }
                }
            }

            if (dropped) {
                std::cerr << " * dropped " << dropped->getType() << std::endl;
                this->objects.push_back(dropped);
            }
        }
    }

    static sf::Clock testClock;

    if (testClock.getElapsedTime().asMilliseconds() > 1000) {
        testClock.restart();
        sf::Vector2f target = sf::Vector2f(_dbgRandom(), _dbgRandom());
        //        srand(testClock.getElapsedTime().asMicroseconds());
        //        std::cerr << this->enemy->wPosition.x << "//" << target.x << "/" << target.y;
        this->enemy->moveTo(target);
    }

//    window->clear();

    this->camera->update();
//    this->player->update();
//    this->enemy->update();

    this->grid->update();
    this->grid->draw(window);

    for (WorldObject *object: this->objects) {
        object->update();
        object->draw(window);
    }

//    player->draw(window);
//    enemy->draw(window);

//    window->display();
}
