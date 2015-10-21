#include <world/Pistol.h>
#include <world/Crate.h>
#include <effects/NoiseEffect.h>
#include "MainMenuScene.h"
#include "GameEngine.h"

MainMenuScene::MainMenuScene(GameEngine *engine) : AScene(engine)
{
    this->worldClock.restart();
    this->frameClock.restart();

    this->window = this->engine->getWindow();

    this->lastMousePos = NULL;

    this->camera = new Camera();

    this->grid = new Grid(this->camera);

    this->player = new Creature("bob", this->camera);
    this->player->setPosition(sf::Vector2f(400, 300));
    this->player->arm(new Pistol(this->camera));
    this->player->setAsCurrent();
    this->objects.push_back(this->player);

    this->enemy = new Creature("bob", this->camera);
    this->enemy->setPosition(sf::Vector2f(200, 200));
    this->enemy->startMove(sf::Vector2f(0, -1), false);
    this->enemy->arm(new Pistol(this->camera));
    this->objects.push_back(this->enemy);

    Crate *c1 = new Crate(this->camera);
    c1->setPosition(sf::Vector2f(300, 400));
    this->objects.push_back(c1);
    Crate *c2 = new Crate(this->camera);
    c2->setPosition(sf::Vector2f(200, 300));
    this->objects.push_back(c2);

    this->camera->attachTo(this->player);

    this->moveVector = sf::Vector2f(0, 0);

    sf::Mouse::setPosition(sf::Vector2i(window->getPosition().x + window->getSize().x / 2, window->getPosition().y + window->getSize().y / 2));
}

void MainMenuScene::tick()
{
    int msPassed = this->frameClock.getElapsedTime().asMilliseconds();
    this->frameClock.restart();

    GEEvent *geEvent;

    while (geEvent = this->engine->getEvent()) {
        this->player->wRotation += (float) geEvent->dx / 300; // Sensitivity
        delete geEvent;
    }

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    this->moveVector.y = -1;
                    break;
                case sf::Keyboard::S:
                    this->moveVector.y = 1;
                    break;
                case sf::Keyboard::A:
                    this->moveVector.x = -1;
                    break;
                case sf::Keyboard::D:
                    this->moveVector.x = 1;
                    break;
                default:
                    break;
            }
            this->player->startMove(this->moveVector, true);
        } else if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    if (this->moveVector.y == -1) {
                        this->moveVector.y = 0;
                    }
                case sf::Keyboard::S:
                    if (this->moveVector.y == 1) {
                        this->moveVector.y = 0;
                    }
                    break;
                case sf::Keyboard::A:
                    if (this->moveVector.x == -1) {
                        this->moveVector.x = 0;
                    }
                case sf::Keyboard::D:
                    if (this->moveVector.x == 1) {
                        this->moveVector.x = 0;
                    }
                    break;
                default:
                    break;
            }

            this->player->startMove(this->moveVector, true);
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            this->player->useArmedItem();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            WorldObject *dropped = this->player->dropArmedItem();

            sf::FloatRect wPlayerHitbox = this->player->getWHitbox();

            WorldObjectList::iterator it = this->objects.begin();
            for(WorldObject *object = *it; it != this->objects.end(); object = *(++it)) {
                if (object->getType() == "item") {
                    std::cerr << " * picking up " << ((Item *) object)->getType() << std::endl;
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

    if (testClock.getElapsedTime().asMilliseconds() > 500) {
        testClock.restart();
        this->enemy->wRotation += M_PI / 4;
        this->enemy->startMove(WorldObject::rotateVector(sf::Vector2f(0, -1), this->enemy->wRotation), false);
        this->enemy->useArmedItem();
    }

    this->camera->update();

    this->grid->update();
    this->grid->draw(window);

    WorldObjectList collidables;

    int i = 0;

    for (WorldObject *top: this->objects) {
        WorldObjectList bunch = this->walk(top);

        for (WorldObject *object: bunch) {
            object->update();
            object->draw(this->window);

            if (object->isCollidable()) {
                sf::FloatRect wHitbox = object->getWHitbox();

                if (! collidables.empty()) {
                    for (WorldObject *other : collidables) {
                        if (other->isCollidable() && other->isCollidable()) {
                            bool isColliding = object->isColliding(other);
                            bool intersects = wHitbox.intersects(other->getWHitbox());
                            if (!isColliding && intersects) {
                                object->collisionStarted(other);
                                other->collisionStarted(object);
                                object->addCollision(other);
                                other->addCollision(object);
                            } else if(isColliding && !intersects) {
                                object->collisionStopped(other);
                                other->collisionStopped(object);
                                object->removeCollision(other);
                                other->removeCollision(object);
                            }
                        }
                    }
                }
            }
        }

        collidables.insert(collidables.end(), bunch.begin(), bunch.end());
    }
}

WorldObjectList MainMenuScene::walk(WorldObject *object) {
    WorldObjectList discovered;

    discovered.push_back(object);

    for (WorldObject *child : object->getChildren()) {
        WorldObjectList children = this->walk(child);
        discovered.insert(discovered.end(), children.begin(), children.end());
    }

    return discovered;
}
