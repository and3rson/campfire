#include "Movable.h"
#include "Camera.h"

Movable::Movable(Camera *camera) : WorldObject(camera)
{
    this->font.loadFromFile("./res/fonts/DejaVuSansMono.ttf");
}

//void Movable::moveTo(sf::Vector2f target)
//{
//    this->source = sf::Vector2f(this->getWPosition());
//    this->target = sf::Vector2f(target);
//    sf::Vector2f vector = this->target - this->source;
//
//    // Face the direction of movement
//    this->setWRotation(atan2(vector.y, vector.x) + M_PI / 2);
//
//    this->clock.restart();
//    this->isMoving = true;
//    this->moveStarted();
//}

void Movable::update()
{
//    if (this->isMoving) {
//        if (this->moveVector != NULL) {
//        if (this->momentumVector.x == 0 && this->momentumVector.y == 0) {
//            this->stopMove();
//            return;
//        }

    sf::Vector2f accelerationVectorRotated = WorldObject::rotateVector(this->accelerationVector, this->getWRotation());

    sf::Vector2f directionVector = WorldObject::normalize(accelerationVectorRotated - this->momentumVector);
    float timePassed = ((float) clock.getElapsedTime().asMilliseconds()) / 1000;

    directionVector.x *= timePassed * this->accelerationFactor;
    directionVector.y *= timePassed * this->accelerationFactor;

    this->momentumVector += directionVector;

//    if (WorldObject::getLength(this->momentumVector) > 1) {
//        this->momentumVector = accelerationVectorRotated;
//    }
    if (WorldObject::getLength(accelerationVectorRotated - this->momentumVector) < 0.05) {
        this->momentumVector = accelerationVectorRotated;
    }

    float distanceTraveled = timePassed * moveSpeed;
    sf::Vector2f shift = sf::Vector2f(this->momentumVector.x * distanceTraveled, this->momentumVector.y * distanceTraveled);

    this->setWPosition(this->getWPosition() + shift);

//    if (WorldObject::getLength(this->momentumVector) > WorldObject::getLength(this->accelerationVector)) {
//        this->momentumVector = this->accelerationVector;
//    }

//        float pointsPassed = (float) this->moveSpeed * ((float) clock.getElapsedTime().asMilliseconds() / 1000);
//
//        // TODO: Change "wRotation" here
//
//        sf::Vector2f shift = sf::Vector2f(moveVector->x * pointsPassed, moveVector->y * pointsPassed);
//
//        this->distanceTraveled += pointsPassed;
//
//        if (this->relative) {
//            shift = WorldObject::rotateVector(shift, this->getWRotation());
//        }
//        this->setWPosition(this->getWPosition() + shift);
    this->clock.restart();
//        } else {
//
//            // Update wPosition
//
//            sf::Vector2f vector = this->target - this->source;
//            int length = sqrt(vector.x * vector.x + vector.y * vector.y);
//            int totalTime = (float) length / this->moveSpeed * 1000;
//
//            float k = (float) this->clock.getElapsedTime().asMilliseconds() / totalTime;
//
//            if (k < 1) {
//                vector.x *= k;
//                vector.y *= k;
//
//                this->setWPosition(this->source + vector);
//            } else {
//                this->setWPosition(this->target);
//                this->stopMove();
//            }
//        }
//    }

    WorldObject::update();
}

void Movable::startMove(sf::Vector2f vector, bool relative = false) {
    this->clock.restart();
    this->isMoving = true;
//    this->moveVector = new sf::Vector2f(vector);
    this->relative = relative;
    this->source = this->getWPosition();
    this->moveStarted();
}

void Movable::stopMove() {
    this->isMoving = false;
//    if (this->moveVector) {
//        delete this->moveVector;
//        this->moveVector = 0;
//    } else {
//        std::cerr << "Cannot stopMove() - not moving!" << std::endl;
//    }
    this->distanceTraveled = 0;
    this->moveStopped();
}

Movable::~Movable() {
//    if (this->moveVector) {
//        delete this->moveVector;
//    }
}

sf::Vector2f Movable::getAccelerationVector() {
    return this->accelerationVector;
}

void Movable::setAccelerationVector(sf::Vector2f vector) {
    this->accelerationVector = WorldObject::normalize(vector);
}

void Movable::draw(sf::RenderWindow *window) {
    sf::Vector2f momentumEnd = this->momentumVector;
    momentumEnd.x *= 100;
    momentumEnd.y *= 100;
    sf::Vector2f accelerationEnd = WorldObject::rotateVector(this->accelerationVector, this->getWRotation());
    accelerationEnd.x *= 100;
    accelerationEnd.y *= 100;

    if (!this->parent) {
        sf::Vertex accelerationLine[] = {
            sf::Vertex(WorldObject::applyCameraTransformation(this->getWPosition()), sf::Color::Green),
            sf::Vertex(WorldObject::applyCameraTransformation(this->getWPosition() + accelerationEnd),
                       sf::Color::Green),};
        window->draw(accelerationLine, 2, sf::Lines);

        sf::Text accelerationText("A", this->font, 10);
        accelerationText.setPosition(accelerationLine[1].position + sf::Vector2f(-10, -5));
        accelerationText.setColor(sf::Color::Green);
        window->draw(accelerationText);

        sf::Vertex momentumLine[] = {
            sf::Vertex(WorldObject::applyCameraTransformation(this->getWPosition()), sf::Color::Red),
            sf::Vertex(WorldObject::applyCameraTransformation(this->getWPosition() + momentumEnd), sf::Color::Red),};
        window->draw(momentumLine, 2, sf::Lines);

        sf::Text momentumText("M", this->font, 10);
        momentumText.setPosition(momentumLine[1].position + sf::Vector2f(3, -5));
        momentumText.setColor(sf::Color::Red);
        window->draw(momentumText);
    }
}

void Movable::setMomentumVector(sf::Vector2f vector) {
    this->momentumVector = vector;
}

sf::Vector2f Movable::getMomentumVector() {
    return this->momentumVector;
}
