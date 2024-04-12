#ifndef PHANORA_H
#define PHANORA_H

#include "Character.h"
#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"
#include "../sounds/Sound.h"
#include <vector>

#define ATTACK_TIME 10.0f
#define PI 3.14159265358979323846
#define P_SPEED 3
#define HEALTH 30

class Phanora : public Character
{
    public:
        Phanora(Properties* props);

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        RigidBody* GetRigidBody() { return m_RigidBody; }
        Transform* GetTransform() { return m_Transform; }
        Collider* GetCollider() { return m_Collider; }

        void setHealth(int x) { health = health + x; }
        void Refresh();
        int getHealth() { return health; }
        float m_x, m_y;

    private:
        bool m_IsRunning;
        bool m_IsAttacking;
        float m_AttackTime;

        int health = HEALTH;
        int angle;

        unsigned long long CurrentTime;
        unsigned long long LastTime = 0;

        bool canspawnbullet = 0;
        bool shieldup = 0;

        //int i = 0;
        
        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // PHANORA_H