#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include "../map/GameMap.h"
#include "../object/GameObject.h"
#include "GameState.h"
#include "../character/Enemy.h"
#include "../character/Phanora.h"
#include "../timer/Timer.h"
#include "Menu.h"
#include "../inputs/Input.h"
#include "../camera/Camera.h"
#include "../map/MapParser.h"
#include "../map/TileLayer.h"
#include "../factory/ObjectFactory.h"
#include "../graphics/TextureManager.h"
#include "../collision/CollisionHandler.h"

class Play : public GameState
{
    public:
        PLay();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();
        //inline GameMap* GetMap() { return m_LevelMap; }
    
    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        GameMap* m_LevelMap;
        std::vector<GameObject*> m_GameObjects;
};

#endif  // PLAY_H
