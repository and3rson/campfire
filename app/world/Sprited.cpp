#include "Sprited.h"

Sprited::Sprited(const char *spriteName, Camera *camera = 0) : AMovable(camera)
{
    std::string path = "./res/sprites/";
    path += spriteName;
    path += ".json";
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
        if (!this->currentAnimation) {
            this->currentAnimation = animation;
        }
    }

    std::string texturePath = "./res/textures/";
    texturePath += root["texture"].asString();

    this->texture.loadFromFile(texturePath.c_str());
    this->texture.setSmooth(true);
    this->sprite = sf::Sprite(this->texture);
    this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));

    this->rOrigin = sf::Vector2f(root["origin"]["x"].asInt(), root["origin"]["y"].asInt());

    this->sprite.setOrigin(this->rOrigin);

    this->oHitbox.left = this->rOrigin.x + root["hitbox"][0].asFloat();
    this->oHitbox.top = this->rOrigin.y + root["hitbox"][1].asFloat();
    this->oHitbox.width = this->rOrigin.x + root["hitbox"][2].asFloat() - this->oHitbox.left;
    this->oHitbox.height = this->rOrigin.y + root["hitbox"][3].asFloat() - this->oHitbox.top;
}

void Sprited::setAnimation(const char *name, bool reset) {
    if (this->currentAnimation != this->animations[name] || reset) {
        if (this->animations.count(name) != 1) {
            std::cerr << "Error: animation '" << name << "' not found!" << std::endl;
            return;
        }
//        std::cerr << "Animation set to " << name << std::endl;
        // Set new animation
        this->currentAnimation = this->animations[name];
        this->clock.restart();
        this->currentFrame = 0;

        // Force redraw sprite
        sf::Vector2i shift = this->currentAnimation->frames[this->currentFrame];
        this->sprite.setTextureRect(sf::IntRect(shift.x, shift.y, this->width, this->height));
    }
}

void Sprited::update()
{
    AMovable::update();

    if (this->clock.getElapsedTime().asMilliseconds() > 1000 / this->currentAnimation->fps) {
        // Update animation
        this->clock.restart();
        this->currentFrame = (this->currentFrame + 1) % this->currentAnimation->frames.size();

        // Scroll sprite
        sf::Vector2i shift = this->currentAnimation->frames[this->currentFrame];
        this->sprite.setTextureRect(sf::IntRect(shift.x, shift.y, this->width, this->height));
    }

    this->sprite.setRotation((this->wRotation - this->camera->wRotation) / (2 * M_PI) * 360); // + this->wRotation / (2 * M_PI) * 360);

    if (this->camera) {
        // Transform sprite wPosition based on camera wPosition & wRotation
        this->sprite.setPosition(this->applyCameraTransformation(this->wPosition));
    } else {
        // No camera set, meaning this object's wPosition is not affected by camera.
        this->sprite.setPosition(this->wPosition.x, this->wPosition.y);
    }
}

void Sprited::draw(sf::RenderWindow *window)
{
    window->draw(this->sprite);

    static sf::RectangleShape origin;
    origin.setOrigin(2, 2);
    origin.setSize(sf::Vector2f(5, 5));
    origin.setPosition(this->sprite.getPosition());
    origin.setFillColor(sf::Color(255, 0, 0, 128));
    window->draw(origin);

    static sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setOrigin(this->sprite.getOrigin());
    rect.setPosition(this->sprite.getPosition());
    rect.setRotation(this->sprite.getRotation());
    rect.setSize(sf::Vector2f(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height));
    window->draw(rect);

//    sf::Vector2f hitboxOrigin = sf::Vector2f(
//
//    );
//    sf::Vector2f hitboxPosition = sf::Vector2f(
//            this->wPosition.x + this->oHitbox.left,
//            this->wPosition.y + this->oHitbox.top
//    );

    static sf::RectangleShape hitboxRect;
    hitboxRect.setFillColor(sf::Color::Transparent);
    hitboxRect.setOutlineThickness(1);
    hitboxRect.setOutlineColor(sf::Color::Red);
    hitboxRect.setOrigin(this->sprite.getOrigin() - sf::Vector2f(this->oHitbox.left, this->oHitbox.top));
    hitboxRect.setSize(sf::Vector2f(this->oHitbox.width, this->oHitbox.height));
    hitboxRect.setPosition(this->applyCameraTransformation(this->wPosition));
    hitboxRect.setRotation(-this->camera->wRotation / M_PI * 180);
    window->draw(hitboxRect);
}
