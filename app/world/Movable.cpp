#include "Movable.h"
#include "Camera.h"

Movable::Movable(Camera *camera) : WorldObject(camera)
{
    this->moveVector = NULL;
}

void Movable::moveTo(sf::Vector2f target)
{
    this->source = sf::Vector2f(this->position);
    this->target = sf::Vector2f(target);
    sf::Vector2f vector = this->target - this->source;

    // Face the direction of movement
    this->rotation = atan2(vector.y, vector.x) + M_PI / 2;

    this->clock.restart();
    this->isMoving = true;
    this->moveStarted();
}

void Movable::update()
{
    if (this->isMoving) {
        if (this->moveVector != NULL) {
            if (this->moveVector->x == 0 && this->moveVector->y == 0) {
                this->stopMove();
                return;
            }

            float cs = cos(camera->rotation + M_PI);
            float sn = sin(camera->rotation + M_PI);

            float x = (float) moveVector->x * cs - (float) moveVector->y * sn;
            float y = (float) moveVector->x * sn + (float) moveVector->y * cs;

//            this->source = this->position;
//            this->target = this->position + sf::Vector2i(x, y);

            float pointsPassed = (float) this->moveSpeed * ((float) clock.getElapsedTime().asMilliseconds() / 1000);

            // TODO: Change "rotation" here

//            std::cerr << "Passed units: " << pointsPassed << " " << x << "/" << y;

            this->position += sf::Vector2f(x * pointsPassed, y * pointsPassed);
            this->clock.restart();
        } else {

            // Update position

            sf::Vector2f vector = this->target - this->source;
            int length = sqrt(vector.x * vector.x + vector.y * vector.y);
            int totalTime = (float) length / this->moveSpeed * 1000;

            float k = (float) this->clock.getElapsedTime().asMilliseconds() / totalTime;

            if (k < 1) {
                vector.x *= k;
                vector.y *= k;

                this->position = this->source + vector;
            } else {
                this->position = this->target;
                this->stopMove();
            }
        }
    }

    WorldObject::update();
}

void Movable::startMove(sf::Vector2f vector) {
    this->clock.restart();
    this->isMoving = true;
    this->moveVector = new sf::Vector2f(vector);
    this->moveStarted();
}

void Movable::stopMove() {
    this->isMoving = false;
    this->moveVector = false;
    this->moveStopped();
}
