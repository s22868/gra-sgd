cmake_minimum_required(VERSION 3.24)
project(graSGD)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR D:/LibSDL/VC/SDL2-2.26.3/include)
set(SDL2_LIB_DIR D:/LibSDL/VC/SDL2-2.26.3/lib/x64)

set(SDL2MIXER_INCLUDE_DIR "D:/LibSDL/VC/SDL2_mixer-2.6.3/include")
set(SDL2MIXER_LIB_DIR "D:/LibSDL/VC/SDL2_mixer-2.6.3/lib/x64")

set(SDL2TTF_INCLUDE_DIR "D:/LibSDL/VC/SDL2_ttf-2.20.2/include")
set(SDL2TTF_LIB_DIR "D:/LibSDL/VC/SDL2_ttf-2.20.2/lib/x64")

include_directories(${SDL2_INCLUDE_DIR} ${SDL2MIXER_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp src/Engine/Engine.cpp src/Engine/Engine.h src/Textures/TextureManager.cpp src/Textures/TextureManager.h src/Physics/Vector2D.h src/Physics/Transform.h src/GameObject/GameObject.h src/Hero/Hero.h src/Hero/Player.cpp src/Hero/Player.h src/Animation/Animation.cpp src/Animation/Animation.h src/Physics/RigidBody.h src/InputHandler/InputHandler.cpp src/InputHandler/InputHandler.h src/Time/Time.cpp src/Time/Time.h src/Map/Layer.h src/Map/GameMap.h src/Map/Tile.cpp src/Map/Tile.h src/Map/MapParser.cpp src/Map/MapParser.h src/Vendor/TinyXML/tinystr.h src/Vendor/TinyXML/tinyxml.h src/Vendor/TinyXML/tinystr.cpp src/Vendor/TinyXML/tinyxml.cpp src/Vendor/TinyXML/tinyxmlerror.cpp src/Vendor/TinyXML/tinyxmlparser.cpp src/Hero/Camera.cpp src/Hero/Camera.h src/Physics/Point.h src/Collision/CollisionHandler.cpp src/Collision/CollisionHandler.h src/Collision/Collider.h src/Collecting/Score.cpp src/Collecting/Score.h src/Text/TextManager.cpp src/Text/TextManager.h src/Sound/SoundManager.cpp src/Sound/SoundManager.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib ${SDL2MIXER_LIB_DIR}/SDL2_mixer.lib ${SDL2TTF_LIB_DIR}/SDL2_ttf.dll)