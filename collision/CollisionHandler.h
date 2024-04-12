#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../inc/SDL.h"
#include <vector>
#include "../map/TileLayer.h"
#include "../map/GameMap.h"

class CollisionHandler
{
    public:
        // va cham voi map
        bool MapCollision(SDL_Rect a);
        // va cham voi enemy
        bool CheckCollision(SDL_Rect a, SDL_Rect b);

        inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler(); }

        TileMap GetTileMap() { return m_CollisionTilemap; }

    private:
        CollisionHandler();
        TileMap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
        static CollisionHandler* s_Instance;

};

#endif  // COLLISIONHANDLER_H