#include <world/Pistol.h>
#include <world/Crate.h>
#include <effects/NoiseEffect.h>
#include <effects/PainEffect.h>
#include <world/Fence.h>
#include <world/GenericEnemy.h>
#include <world/Bob.h>
#include <helpers/VisibilityTracer.h>
#include <helpers/WindingNumber.h>
#include "LevelScene.h"
#include "GameEngine.h"

LevelScene::LevelScene(GameEngine *engine) : AScene(engine)
{
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");

    this->worldClock.restart();
    this->frameClock.restart();

    this->window = this->engine->getWindow();

    sf::Mouse::setPosition(sf::Vector2i(window->getPosition().x + window->getSize().x / 2, window->getPosition().y + window->getSize().y / 2));
}

void LevelScene::tick()
{
    int msPassed = this->frameClock.getElapsedTime().asMilliseconds();
    this->frameClock.restart();

    GEEvent *geEvent;

    while (geEvent = this->engine->getEvent()) {
        this->controlledCreature->setWRotation(this->controlledCreature->getWRotation() + (float) geEvent->dx / 300); // Sensitivity
        delete geEvent;
    }

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        } else if (event.type == sf::Event::KeyPressed) {
            sf::Vector2f accelerationVector = this->controlledCreature->getAccelerationVector();
            switch (event.key.code) {
                case sf::Keyboard::W:
                    accelerationVector.y = -1;
                    break;
                case sf::Keyboard::S:
                    accelerationVector.y = 1;
                    break;
                case sf::Keyboard::A:
                    accelerationVector.x = -1;
                    break;
                case sf::Keyboard::D:
                    accelerationVector.x = 1;
                    break;
                default:
                    break;
            }
            this->controlledCreature->setAccelerationVector(accelerationVector);
        } else if (event.type == sf::Event::KeyReleased) {
            sf::Vector2f accelerationVector = this->controlledCreature->getAccelerationVector();
            switch (event.key.code) {
                case sf::Keyboard::W:
                    if (accelerationVector.y < 0) {
                        accelerationVector.y = 0;
                    }
                case sf::Keyboard::S:
                    if (accelerationVector.y > 0) {
                        accelerationVector.y = 0;
                    }
                    break;
                case sf::Keyboard::A:
                    if (accelerationVector.x < 0) {
                        accelerationVector.x = 0;
                    }
                case sf::Keyboard::D:
                    if (accelerationVector.x > 0) {
                        accelerationVector.x = 0;
                    }
                    break;
                default:
                    break;
            }

            this->controlledCreature->setAccelerationVector(accelerationVector);
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            this->controlledCreature->useArmedItem();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            WorldObject *dropped = this->controlledCreature->dropArmedItem();

            sf::FloatRect wPlayerHitbox = this->controlledCreature->getWHitbox();

            WorldObjectList::iterator it = this->objects.begin();
            for(WorldObject *object = *it; it != this->objects.end(); object = *(++it)) {
                if (object->isPickable()) {
                    std::cerr << " * picking up " << ((Item *) object)->getType() << std::endl;
                    if (wPlayerHitbox.intersects(object->getWHitbox())) {
                        std::cerr << " * picking up " << ((Item *) object)->getType() << std::endl;
                        this->controlledCreature->arm((Item *) object);
                        this->objects.erase(it);
                        break;
                    }
                }
            }

            if (dropped) {
                std::cerr << " * dropped " << dropped->getType() << std::endl;
                this->objects.push_back(dropped);
                sf::Vector2f mV = WorldObject::rotateVector(sf::Vector2f(0, -1), this->controlledCreature->getWRotation());
                mV.x *= 3;
                mV.y *= 3;
                ((Movable *) dropped)->setMomentumVector(mV);
            }
        }
    }

    static sf::Clock testClock;

//    if (testClock.getElapsedTime().asMilliseconds() > 500 && this->enemy->isAlive()) {
//        testClock.restart();
//        this->enemy->setWRotation(this->enemy->getWRotation() + M_PI / 4);
//        this->enemy->startMove(WorldObject::rotateVector(sf::Vector2f(0, -1), this->enemy->getWRotation()), false);
//        this->enemy->useArmedItem();
//    }

    this->activeCamera->update();

    this->controlledCreature->update();

    WorldObjectList collidables;

    int i = 0;

    WorldObjectList all;

    for (WorldObject *top: this->objects) {
        WorldObjectList bunch = this->walk(top);

        for (WorldObject *object: bunch) {
            if (object != this->controlledCreature) {
                // Do not update player again
                object->update();
            }
            all.push_back(object);

            if (object->isCollidable()) {
                sf::FloatRect wHitbox = object->getWHitbox();

                if (! collidables.empty()) {
                    for (WorldObject *other : collidables) {
                        if (object->isCollidable() && other->isCollidable()) {
//                            bool isColliding = object->isColliding(other);
//                            bool intersects = wHitbox.intersects(other->getWHitbox());
//                            if (!isColliding && intersects) {
                            if (wHitbox.intersects(other->getWHitbox())) {
                                object->collisionStarted(other);
                                other->collisionStarted(object);
                            }

//                                object->addCollision(other);
//                                other->addCollision(object);
//                            } else if(isColliding && !intersects) {
//                                object->collisionStopped(other);
//                                other->collisionStopped(object);
//                                object->removeCollision(other);
//                                other->removeCollision(object);
//                            }
                        }
                    }
                }
            }
        }

        collidables.insert(collidables.end(), bunch.begin(), bunch.end());
    }

    VisibilityTracer vt(this->objects);
    VectorList points = vt.calculateVisibility(this->controlledCreature, this->window, M_PI / 2);
//    sf::Font font;
    sf::Vector2f previous;
    int index = 0;

//    points.push_back(points.front());

    for (sf::Vector2f point : points) {
        if (index++) {
            sf::ConvexShape shape;
            shape.setPointCount(3);
            shape.setPoint(0, this->controlledCreature->applyCameraTransformation(this->controlledCreature->getWPosition()));
            shape.setPoint(1, this->controlledCreature->applyCameraTransformation(previous));
            shape.setPoint(2, this->controlledCreature->applyCameraTransformation(point));
            shape.setFillColor(sf::Color(255, 255, 255, 32));
            shape.setOutlineColor(sf::Color(255, 255, 255, 64));
            shape.setOutlineThickness(0);
            window->draw(shape);

            sf::Vertex line[] = {
                sf::Vertex(this->controlledCreature->applyCameraTransformation(previous), sf::Color::White),
                sf::Vertex(this->controlledCreature->applyCameraTransformation(point), sf::Color::White)
            };
            window->draw(line, 2, sf::Lines);

//            char text[32];
//            sprintf(text, "%d", index);
//            sf::Text t(text, this->font, 12);
//            t.setColor(sf::Color::White);
//            t.setPosition(this->controlledCreature->applyCameraTransformation(sf::Vector2f((point.x + previous.x) / 2, (point.y + previous.y) / 2)));
//            window->draw(t);
        }
        previous = point;
    }

//    points.pop_back();

    for (WorldObject *object : all) {
        if (!object->getIsCurrent()) {
//            if (WindingNumber::cn_PnPoly(object->getWPosition(), points)) {
            if (!WindingNumber::insidePolygon(points, object->getWPosition())) {
                if (object->getType() == "creature") {
//                    std::cerr << "Object " << object->getType() << " is visible!" << std::endl;
                    float rotation = object->getWRotation();
                    float final = VisibilityTracer::getAngle(object->getWPosition(), this->controlledCreature->getWPosition()) + M_PI / 2;
                    object->setWRotation(rotation + (final - rotation) / 4);
                    ((Creature *) object)->useArmedItem();
//                    ((Movable *) object)->moveTo(this->controlledCreature->getWPosition());
                }
            }
        }

        object->draw(this->window);
    }

    char str[32];
    sprintf(str, "Vertexes in vision poly: %d", points.size());
    sf::Text t(str, this->font, 14);
    t.setPosition(0, 40);
    window->draw(t);
}

WorldObjectList LevelScene::walk(WorldObject *object) {
    WorldObjectList discovered;

    discovered.push_back(object);

    for (WorldObject *child : object->getChildren()) {
        WorldObjectList children = this->walk(child);
        discovered.insert(discovered.end(), children.begin(), children.end());
    }

    return discovered;
}

void LevelScene::addObject(WorldObject *object) {
    this->objects.push_back(object);
}

//void LevelScene::removeObject(WorldObject *object) {
//
//}
void LevelScene::setControlledCreature(Creature *creature) {
    this->controlledCreature = creature;
}

void LevelScene::setActiveCamera(Camera *camera) {
    this->activeCamera = camera;
}

Creature *LevelScene::getControlledCreature() {
    return this->controlledCreature;
}

Camera *LevelScene::getActiveCamera() {
    return this->activeCamera;
}
