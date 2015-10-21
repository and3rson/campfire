#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SFML/Graphics.hpp>
#include <customtypes.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Camera;


class WorldObject
{
public:
    WorldObject(Camera *camera = 0);

    virtual void update();
    void setPosition(sf::Vector2f);
    sf::Vector2f applyCameraTransformation(sf::Vector2f pos);
    static sf::Vector2f rotateVector(sf::Vector2f vector, float angle);
    virtual void draw(sf::RenderWindow *window) = 0;
    virtual std::string getType();

    virtual bool collisionStarted(WorldObject *other);
    virtual bool collisionStopped(WorldObject *other);
    virtual bool isCollidable();

    sf::FloatRect getWHitbox();

    WorldObjectList getChildren();

    sf::FloatRect oHitbox;
    sf::Vector2f wPosition;
    sf::Vector2f rOrigin;
    float wRotation = 0;
    Camera *camera = 0;

    void addChild(WorldObject *other);
    void removeChild(WorldObject *other);

    void addCollision(WorldObject *other);
    void removeCollision(WorldObject *other);
    bool isColliding(WorldObject *other);

    bool current = false;

    void setAsCurrent();
    bool getIsCurrent();

protected:
    WorldObject *parent = 0;
    WorldObjectList children;
    WorldObjectList collisions;
};

#endif // WORLDOBJECT_H
