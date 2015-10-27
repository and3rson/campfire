//
// Created by anderson on 09.10.15.
//

#ifndef APP_PISTOL_H
#define APP_PISTOL_H

#include "Item.h"
#include "Projectile.h"

#include <SFML/Audio.hpp>

class Pistol : public Item {

public:
    Pistol(Camera *camera);
    virtual void use();

    virtual void update();
    virtual void draw(sf::RenderWindow *window);

    virtual std::string getType();
    virtual bool isCollidable();

    int ammo = 12;

    sf::Font font;
    int maxAmmo = 12;

    sf::Text ammoText;

    void updateAmmoGUI();

private:
    sf::SoundBuffer useSoundBuffer;
    sf::Sound useSound;
};


#endif //APP_PISTOL_H
