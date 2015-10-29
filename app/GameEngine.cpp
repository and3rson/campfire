#include "GameEngine.h"
#include "customtypes.h"
#include "SoundManager.h"

GameEngine* GameEngine::instance = 0;
Recycler GameEngine::recycler;

GameEngine::GameEngine(sf::RenderWindow *window) : window(window)
{
    Director::getInstance();
    this->hold(SoundManager::getInstance(), TRACE);

#ifdef __linux__
    this->dpy = XOpenDisplay(NULL);
//    this->grab = XGrabPointer(
//            this->dpy,
//            DefaultRootWindow(this->dpy),
//            true,
//            ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | EnterWindowMask | LeaveWindowMask,
//            GrabModeAsync,
//            GrabModeAsync,
//            DefaultRootWindow(this->dpy),
//            None,
//            CurrentTime
//    );
#endif
}

void GameEngine::start()
{
}

void GameEngine::tick()
{
    this->window->clear();
//    sf::Image img = this->window->capture();
//    sf::Texture texture;
//    texture.loadFromImage(img);
//    sf::Sprite blur(texture);
//    this->window->draw(blur);

    sf::Vector2i windowOrigin = this->window->getPosition();
    sf::Vector2u windowSize = this->window->getSize();
    int centerX, centerY;
    centerX = windowOrigin.x + windowSize.x / 2;
    centerY = windowOrigin.y + windowSize.y / 2;

    Window returned;
    int root_x, root_y, win_x, win_y;
    unsigned int mask_return;
    XQueryPointer(this->dpy, DefaultRootWindow(this->dpy), &returned, &returned, &root_x, &root_y, &win_x, &win_y, &mask_return);
    XWarpPointer(this->dpy, 0, DefaultRootWindow(this->dpy), 0, 0, 0, 0, centerX, centerY);
    XFlush(this->dpy);
//    XEvent event;
//    while (XPending(this->dpy)) {
//        XNextEvent(this->dpy, &event);
//        std::cout << "XEvent: " << (&event) << std::endl;
//    }

    if (this->lastX != -1 && this->lastY !=-1 && (this->lastX != win_x || this->lastY != win_y)) {
//        std::cout << win_x - this->lastX << " / " << win_y - this->lastY << std::endl;
        this->events.push_back(new GEEvent(win_x - this->lastX, win_y = this->lastY));
    }

//    if (this->lastX != -1 && this->lastY !=-1 && (this->lastX != win_x || this->lastY != win_y)) {
//        this->events.push_back(new GEEvent(win_x, win_y));
//    }

    lastX = centerX;
    lastY = centerY;

    this->scene->tick();
    if (this->effect) {
        if (!this->effect->tick()) {
            this->setEffect(NULL);
            delete this->effect;
        }
    }
    this->window->display();

    this->recycler.cleanUp();

//    std::cout << win_x << "/" << win_y << std::endl;
}

void GameEngine::setScene(AScene *scene)
{
    this->scene = scene;
    this->hold(scene, TRACE);
}

void GameEngine::setEffect(AEffect *effect)
{
    this->effect = effect;
}

sf::RenderWindow *GameEngine::getWindow()
{
    return this->window;
}

GEEvent* GameEngine::getEvent() {
    if (this->events.size()) {
        GEEvent *event = this->events.front();
        this->events.erase(this->events.begin());
        return event;
    }

    return NULL;
}

//GameEngine::Event::Event(int x, int y) {
//    this.x = x;
//    this.y = y;
//}
GameEngine *GameEngine::getInstance() {
    if (!GameEngine::instance) {
        std::cerr << "GameEngine needs to be initialized first!";
    }
    return GameEngine::instance;
}

void GameEngine::initialize(sf::RenderWindow *window) {
    GameEngine::instance = new GameEngine(window);
}

void GameEngine::recycle(Registry *object, const char *a, int b, const char *c) {
    GameEngine::recycler.hold(object, a, b, c);
}

GameEngine::~GameEngine() {
    delete this->dpy;
    std::cerr << "Destroying GameEngine" << std::endl;
}

std::string GameEngine::getType() {
    return "GameEngine";
}

AScene *GameEngine::getScene() {
    return this->scene;
}
