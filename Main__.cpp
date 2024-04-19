/*
g++ -Llib -o Space_bang Main__.cpp src/Engine.cpp graphics/TextureManager.cpp factory/ObjectFactory.cpp physics/Vector2D.h physics/Transform.h physics/Collider.h object/IObject.h  object/GameObject.h character/Character.h character/Phanora.cpp animation/Animation.cpp inputs/Input.cpp physics/RigidBody.h timer/Timer.cpp camera/Camera.cpp physics/Point.h map/GameMap.h map/Layer.h map/MapParser.cpp map/TileLayer.cpp vendor/tinyxml/tinystr.cpp vendor/tinyxml/tinyxml.cpp vendor/tinyxml/tinyxmlerror.cpp vendor/tinyxml/tinyxmlparser.cpp collision/CollisionHandler.cpp character/Enemy.cpp bullet/Bullet.cpp bullet/Bullet.h sounds/Sound.cpp text/Text.cpp star/garlic.cpp shield/Shield.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
*/
#include "src/Engine.h"
#include "timer/Timer.h"

#undef main

int main(int agrc, char** argv)
{
    Engine::GetInstance()->Init();

    while (Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick(); 
    }

    Engine::GetInstance()->Clean();

    return 0;
}

