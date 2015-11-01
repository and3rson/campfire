#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <SFML/Graphics.hpp>
#include <customtypes.h>
#include "config.h"
#include "Registry.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Camera;


class WorldObject : public Registry
{
public:
    WorldObject(Camera *camera = 0);

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

    void setWPosition(sf::Vector2f);
    sf::Vector2f getWPosition();

    void setWRotation(float rotation);
    float getWRotation();

    sf::Vector2f applyCameraTransformation(sf::Vector2f pos);

    static sf::Vector2f rotateVector(sf::Vector2f vector, float angle);
    static float getDistance(sf::Vector2f a, sf::Vector2f b);
    static float getLength(sf::Vector2f a);
    static sf::Vector2f normalize(sf::Vector2f a);

    virtual bool collisionStarted(WorldObject *other);
    virtual bool collisionStopped(WorldObject *other);
    virtual bool isCollidable();

    enum Material {
        NONE,
        METAL,
        WOOD,
        GLASS,
        FLESH,
        CONCRETE
    };

    virtual Material getMaterial();

    sf::FloatRect getWHitbox();
    VectorList getWLightbox();

    WorldObjectList getChildren();

    void addChild(WorldObject *other);
    void removeChild(WorldObject *other);

//    void addCollision(WorldObject *other);
//    void removeCollision(WorldObject *other);
//    bool isColliding(WorldObject *other);

    virtual bool isPickable();

    bool current = false;

    void setAsCurrent();
    bool getIsCurrent();

protected:
    Camera *camera = 0;

    WorldObject *parent = 0;
    WorldObjectList children;
//    WorldObjectList collisions;

    sf::FloatRect oHitbox;
    sf::FloatRect oLightbox;
    sf::Vector2f rOrigin;

private:
    float wRotation = 0;
    sf::Vector2f wPosition;
};

#endif // WORLDOBJECT_H
