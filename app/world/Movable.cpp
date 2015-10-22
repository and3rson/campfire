#include "Movable.h"
#include "Camera.h"

AMovable::AMovable(Camera *camera) : WorldObject(camera)
{
    this->moveVector = NULL;
}

void AMovable::moveTo(sf::Vector2f target)
{
    this->source = sf::Vector2f(this->wPosition);
    this->target = sf::Vector2f(target);
    sf::Vector2f vector = this->target - this->source;

    // Face the direction of movement
    this->wRotation = atan2(vector.y, vector.x) + M_PI / 2;

    this->clock.restart();
    this->isMoving = true;
    this->moveStarted();
}

void AMovable::update()
{
    if (this->isMoving) {
        if (this->moveVector != NULL) {
            if (this->moveVector->x == 0 && this->moveVector->y == 0) {
                this->stopMove();
                return;
            }

//            float cs = cos(camera->wRotation + M_PI);
//            float sn = sin(camera->wRotation + M_PI);
//
//            float x = (float) moveVector->x * cs - (float) moveVector->y * sn;
//            float y = (float) moveVector->x * sn + (float) moveVector->y * cs;

//            this->source = this->wPosition;
//            this->target = this->wPosition + sf::Vector2i(x, y);

            float pointsPassed = (float) this->moveSpeed * ((float) clock.getElapsedTime().asMilliseconds() / 1000);

            // TODO: Change "wRotation" here

//            std::cerr << "Passed units: " << pointsPassed << " " << x << "/" << y;

            sf::Vector2f shift = sf::Vector2f(moveVector->x * pointsPassed, moveVector->y * pointsPassed);

            this->distanceTraveled += pointsPassed;

            if (this->relative) {
                shift = WorldObject::rotateVector(shift, this->wRotation);
            }
            this->wPosition += shift;
//            this->wPosition += sf::Vector2f(moveVector->x * pointsPassed, moveVector->y * pointsPassed);
            this->clock.restart();
        } else {

            // Update wPosition

            sf::Vector2f vector = this->target - this->source;
            int length = sqrt(vector.x * vector.x + vector.y * vector.y);
            int totalTime = (float) length / this->moveSpeed * 1000;

            float k = (float) this->clock.getElapsedTime().asMilliseconds() / totalTime;

            if (k < 1) {
                vector.x *= k;
                vector.y *= k;

                this->wPosition = this->source + vector;
            } else {
                this->wPosition = this->target;
                this->stopMove();
            }
        }
    }

    WorldObject::update();
}

void AMovable::startMove(sf::Vector2f vector, bool relative = false) {
    this->clock.restart();
    this->isMoving = true;
    this->moveVector = new sf::Vector2f(vector);
    this->relative = relative;
    this->source = this->wPosition;
    this->moveStarted();
}

void AMovable::stopMove() {
    this->isMoving = false;
    this->moveVector = 0;
    this->distanceTraveled = 0;
    this->moveStopped();
}
