//
// Created by anderson on 28.10.15.
//

#ifndef APP_SOUNDMANAGER_H
#define APP_SOUNDMANAGER_H


#include <SFML/Audio.hpp>
#include "Registry.h"
#include <map>

class SoundManager : public Registry {
public:
    static SoundManager *getInstance();

    void load(const char *name);
    void play(const char *name);

    virtual std::string getType();

    class Sound : public Registry {
    public:
        Sound(const char *name);
        ~Sound();
        sf::Sound *createNew();

        virtual std::string getType();

    private:
        sf::SoundBuffer soundBuffer;
    };

private:
    static SoundManager *instance;
    SoundManager();
    std::map<const char *, Sound *> sounds;
    std::vector<sf::Sound *> playing;
};


#endif //APP_SOUNDMANAGER_H
