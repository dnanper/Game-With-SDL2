#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"
#include "../sounds/Sound.h"
#include "../star/garlic.h"
#include <string>
#include <vector>
#include <iostream>
#include "Phanora.h"

#define E_SPEED_TYPE_1 3
#define E_HEALTH_TYPE 15
#define E_SPEED_TYPE_2 4

using namespace std;

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;

class Enemy: public Character
{
    public:
        Enemy(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

        float target_X_type1;
        float target_Y_type1;
        float target_X;
        float target_Y;
        float target_type3_X;
        float target_type3_Y;
        double a_angle;
        double e_angle;
        int type3_pos;
        int e_health = E_HEALTH_TYPE;


        
        Collider* getCollider() { return m_Collider; }
        bool getIsBlown() { return blown; }
        void setIsBlown() { blown = 1; }
        bool getIsDead() { return dead; }
        void setType(std::string type) { enemy_Type = type; }
        int blowTime = 0;
        std::vector<std::pair<int,int>> m_type3_pos_list = 
        { {1000, 1350}, {1160, 1175}, {1350,1100}, {1500,1175}, {1630,1350}, {1500,1525}, {1350,1600}, {1160,1525} };

        TileMap grid = CollisionHandler::GetInstance()->GetTileMap();
    
    private:
        bool blown = 0;
        bool dead = 0;
        
        std::string enemy_Type;

        int EshotTime_type2 = 0;
        bool type3Alr = 0;

        float distance = 450;
        unsigned long long CurrentTime;
        unsigned long long LastTime = 0;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // ENEMY_H