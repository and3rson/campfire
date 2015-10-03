#include "Sprited.h"

Sprited::Sprited(const char *spriteName, Camera *camera = 0) : Movable(camera)
{
    std::string path = "./res/sprites/";
    path += spriteName;
    path +=+ ".json";
    std::ifstream file(path.c_str());

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(file, root)) {
        std::cerr << "JSON parsing error: " << reader.getFormattedErrorMessages() << std::endl;
    }

    this->width = root["width"].asInt();
    this->height = root["height"].asInt();

    Json::Value jAnimations = root["animations"];

    for (Json::ValueIterator animationsIterator = jAnimations.begin(); animationsIterator != jAnimations.end(); animationsIterator++) {
        Json::Value jAnimation = *animationsIterator;

        Animation *animation = new Animation(jAnimation["fps"].asInt());

        Json::Value jFrames = jAnimation["frames"];

        for (Json::ValueIterator framesIterator = jFrames.begin(); framesIterator != jFrames.end(); framesIterator++) {
            Json::Value jFrame = *framesIterator;
            sf::Vector2i frame;
            frame.x = jFrame[0].asInt();
            frame.y = jFrame[1].asInt();
            animation->frames.push_back(frame);
        }

        animations[animationsIterator.key().asString()] = animation;
        this->currentAnimation = animation;
    }

    std::string texturePath = "./res/textures/";
    texturePath += root["texture"].asString();

    this->texture.loadFromFile(texturePath.c_str());
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
    this->sprite.setOrigin(root["origin"]["x"].asInt(), root["origin"]["y"].asInt());
}

void Sprited::setAnimation(const char *name) {
    this->currentAnimation = this->animations[name];
    this->clock.restart();
    this->currentFrame = 0;
}

void Sprited::update()
{
    Movable::update();

    if (this->clock.getElapsedTime().asMilliseconds() > 1000 / this->currentAnimation->fps) {
        // Update animation

        this->clock.restart();
        this->currentFrame = (this->currentFrame + 1) % this->currentAnimation->frames.size();
        sf::Vector2i shift = this->currentAnimation->frames[this->currentFrame];
        this->sprite.setTextureRect(sf::IntRect(shift.x, shift.y, this->width, this->height));
    }

    this->sprite.setRotation((this->rotation - this->camera->rotation) / (2 * M_PI) * 360); // + this->rotation / (2 * M_PI) * 360);

    if (this->camera) {
        sf::Vector2f pos = this->applyCameraTransformation(this->position);
        this->sprite.setPosition(400 + pos.x, 320 + pos.y);
        //        std::cerr << angle << std::endl;
    } else {
        this->sprite.setPosition(this->position.x, this->position.y);
    }
}