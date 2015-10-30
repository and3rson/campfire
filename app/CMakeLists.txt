cmake_minimum_required(VERSION 3.3)
project(app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../sdk/public/steam/)

link_libraries(steam_api sfml-graphics sfml-window sfml-system sfml-audio X11 stdc++)
link_directories(${CMAKE_SOURCE_DIR}/../sdk/redistributable_bin/linux64)

set(
        SOURCE_FILES
        effects/AEffect.cpp
        effects/AEffect.h
        effects/NoiseEffect.cpp
        effects/NoiseEffect.h
        jsoncpp/json/json-forwards.h
        jsoncpp/json/json.h
        jsoncpp/jsoncpp.cpp
        scenes/AScene.cpp
        scenes/AScene.h
    scenes/LevelScene.cpp
    scenes/LevelScene.h
        scenes/SplashScene.cpp
        scenes/SplashScene.h
        types/Animation.cpp
        types/Animation.h
        world/Camera.cpp
        world/Camera.h
        world/Creature.cpp
        world/Creature.h
        world/Grid.cpp
        world/Grid.h
        world/Movable.cpp
        world/Movable.h
        world/Projectile.cpp
        world/Projectile.h
        world/Sprited.cpp
        world/Sprited.h
        world/WorldObject.cpp
        world/WorldObject.h
        GameEngine.cpp
        GameEngine.h
        main.cpp
        SteamAdapter.cpp
        SteamAdapter.h
        world/Item.cpp
        world/Item.h
        world/Pistol.cpp
        world/Pistol.h
        world/Crate.cpp
        world/Crate.h
        duktape/duktape.cpp
        duktape/duktape.h
        Director.cpp
        Director.h
        GEEvent.cpp
        GEEvent.h
        customtypes.h
        config.h effects/PainEffect.cpp effects/PainEffect.h world/Fence.cpp world/Fence.h world/GenericEnemy.cpp world/GenericEnemy.h world/Bob.cpp world/Bob.h helpers/VisibilityTracer.cpp helpers/VisibilityTracer.h Registry.cpp Registry.h SoundManager.cpp SoundManager.h Recycler.cpp Recycler.h helpers/WindingNumber.cpp helpers/WindingNumber.h scenes/TestLevelScene.cpp scenes/TestLevelScene.h)

add_executable(app ${SOURCE_FILES})
