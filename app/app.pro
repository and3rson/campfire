TEMPLATE = app

CONFIG =

SOURCES += main.cpp \
    SteamAdapter.cpp \
    GameEngine.cpp \
    world/WorldObject.cpp \
    world/Sprited.cpp \
    world/Creature.cpp \
    world/Movable.cpp \
    types/Animation.cpp \
    world/Camera.cpp \
    jsoncpp/jsoncpp.cpp \
    world/Grid.cpp \
    scenes/MainMenuScene.cpp \
    scenes/AScene.cpp \
    scenes/SplashScene.cpp \
    effects/AEffect.cpp \
    effects/NoiseEffect.cpp \
    world/Projectile.cpp

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += ../sdk/public/steam/

QMAKE_CXXFLAGS += -std=c++11

if (mingw): INCLUDEPATH += ../include/
if (mingw): QMAKE_CXXFLAGS += -DSFML_SYSTEM_EXPORTS -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions --param=ssp-buffer-size=4 -O3 -DNDEBUG

if (linux-g++): QMAKE_LFLAGS += -Xlinker ../sdk/redistributable_bin/linux64/libsteam_api.so -lsfml-graphics -lsfml-system -lsfml-window -lX11

if (mingw): QMAKE_LIBS += -L ../sdk/redistributable_bin/ -lsteam_api -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -lglew32 -lopengl32 -lwinmm -ljpeg -lfreetype -lgdi32

HEADERS += \
    SteamAdapter.h \
    GameEngine.h \
    world/WorldObject.h \
    world/Sprited.h \
    world/Creature.h \
    world/Movable.h \
    types/Animation.h \
    world/Camera.h \
    world/Grid.h \
    scenes/MainMenuScene.h \
    scenes/AScene.h \
    scenes/SplashScene.h \
    effects/AEffect.h \
    effects/NoiseEffect.h \
    world/Projectile.h
