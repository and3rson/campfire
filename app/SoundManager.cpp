//
// Created by anderson on 28.10.15.
//

#include <iostream>
#include "SoundManager.h"
#include "customtypes.h"
#include "GameEngine.h"

SoundManager *SoundManager::instance = 0;

void SoundManager::load(const char *name) {
    if (this->sounds.find(name) == this->sounds.end()) {
        std::cerr << "Loading sound " << name << std::endl;
        Sound *sound = new Sound(name);
        this->hold(sound, TRACE);
        this->sounds[name] = sound;
    } else {
        std::cerr << "Sound " << name << " already loaded" << std::endl;
    }
}

SoundManager::Sound::Sound(const char *name) {
    char path[128];
    sprintf(path, "./res/sounds/%s.ogg", name);
    if (this->soundBuffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound!" << std::endl;
    }
}

SoundManager::Sound::~Sound() {
}

void SoundManager::play(const char *name) {
    this->playing.erase(std::remove_if(this->playing.begin(), this->playing.end(), [] (const sf::Sound *s) {
        if (s->getStatus() == sf::SoundSource::Status::Stopped) {
            delete s;
            return true;
        }
        return false;
    }), this->playing.end());

    sf::Sound *sound = this->sounds[name]->createNew();
    sound->play();
    this->playing.push_back(sound);
}

SoundManager::SoundManager() {

}

SoundManager *SoundManager::getInstance() {
    if (!SoundManager::instance) {
        SoundManager::instance = new SoundManager();
    }
    return SoundManager::instance;
}

std::string SoundManager::Sound::getType() {
    return "SoundManager::Sound";
}

std::string SoundManager::getType() {
    return "SoundManager";
}

sf::Sound *SoundManager::Sound::createNew() {
    return new sf::Sound(this->soundBuffer);
}
