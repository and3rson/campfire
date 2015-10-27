#include <world/Pistol.h>
#include <world/Crate.h>
#include <effects/NoiseEffect.h>
#include <effects/PainEffect.h>
#include <world/Fence.h>
#include <world/GenericEnemy.h>
#include <world/Bob.h>
#include <helpers/VisibilityTracer.h>
#include "MainMenuScene.h"
#include "GameEngine.h"

MainMenuScene::MainMenuScene(GameEngine *engine) : AScene(engine)
{
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");

    this->worldClock.restart();
    this->frameClock.restart();

    this->window = this->engine->getWindow();

    this->hold(this->camera = new Camera(), TRACE);

    this->hold(this->grid = new Grid(this->camera), TRACE);

    this->hold(this->player = new Bob(this->camera), TRACE);
    this->player->setWPosition(sf::Vector2f(400, 300));
    this->player->arm(new Pistol(this->camera));
    this->player->setAsCurrent();
    this->objects.push_back(this->player);

    Fence *fence = new Fence(this->camera);
    this->hold(fence, TRACE);
    this->objects.push_back(fence);

    Fence *fence2 = new Fence(this->camera);
    this->hold(fence2, TRACE);
    fence2->setWPosition(sf::Vector2f(128, 0));
    this->objects.push_back(fence2);

    this->hold(this->enemy = new GenericEnemy(this->camera), TRACE);
    this->enemy->setWPosition(sf::Vector2f(200, 200));
    this->enemy->startMove(sf::Vector2f(0, -1), false);
    Pistol *pistol = new Pistol(this->camera);
    this->hold(pistol, TRACE);
    this->enemy->arm(pistol);
    this->objects.push_back(this->enemy);

    Crate *c1 = new Crate(this->camera);
    c1->setWPosition(sf::Vector2f(300, 400));
    this->hold(c1, TRACE);
    this->objects.push_back(c1);
    Crate *c2 = new Crate(this->camera);
    c2->setWPosition(sf::Vector2f(200, 300));
    this->hold(c2, TRACE);
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
        this->player->setWRotation(this->player->getWRotation() + (float) geEvent->dx / 300); // Sensitivity
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
                if (object->isPickable()) {
                    std::cerr << " * picking up " << ((Item *) object)->getType() << std::endl;
                    if (wPlayerHitbox.intersects(object->getWHitbox())) {
                        std::cerr << " * picking up " << ((Item *) object)->getType() << std::endl;
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

    if (testClock.getElapsedTime().asMilliseconds() > 500 && this->enemy->isAlive()) {
        testClock.restart();
        this->enemy->setWRotation(this->enemy->getWRotation() + M_PI / 4);
        this->enemy->startMove(WorldObject::rotateVector(sf::Vector2f(0, -1), this->enemy->getWRotation()), false);
        this->enemy->useArmedItem();
    }

    this->camera->update();

    this->player->update();

    this->grid->update();
    this->grid->draw(window);

    WorldObjectList collidables;

    int i = 0;

    for (WorldObject *top: this->objects) {
        WorldObjectList bunch = this->walk(top);

        for (WorldObject *object: bunch) {
            if (object != this->player) {
                // Do not update player again
                object->update();
            }
            object->draw(this->window);

            if (object->isCollidable()) {
                sf::FloatRect wHitbox = object->getWHitbox();

                if (! collidables.empty()) {
                    for (WorldObject *other : collidables) {
                        if (object->isCollidable() && other->isCollidable()) {
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

    VisibilityTracer vt(this->objects);
    VectorList points = vt.calculateVisibility(this->player, this->window);
    sf::Font font;
    sf::Vector2f previous;
    int index = 0;

    points.push_back(points.front());

    for (sf::Vector2f point : points) {
        if (index++) {
            sf::ConvexShape shape;
            shape.setPointCount(3);
            shape.setPoint(0, this->player->applyCameraTransformation(this->player->getWPosition()));
            shape.setPoint(1, this->player->applyCameraTransformation(previous));
            shape.setPoint(2, this->player->applyCameraTransformation(point));
            shape.setFillColor(sf::Color(255, 255, 255, 32));
            shape.setOutlineColor(sf::Color(255, 255, 255, 64));
            shape.setOutlineThickness(0);
            window->draw(shape);

            window->draw(shape);
        }
        previous = point;
    }

    char str[32];
    sprintf(str, "Vertexes in vision poly: %d", points.size());
    sf::Text t(str, this->font, 14);
    t.setPosition(0, 40);
    window->draw(t);
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
