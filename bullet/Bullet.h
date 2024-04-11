#ifndef BULLET_H
#define BULLET_H

#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"
#include "../character/Character.h"
#include <vector>
#include <string>

#define PI 3.14159265358979323846
#define B_SPEED 8
#define B_DAME 5
#define B_DAME_2 1

class Bullet : public Character
{
    public:
        Bullet(Properties* props);
        ~Bullet() {}

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        double p_angle;

        RigidBody* p_RigidBody;

        Collider* getCollider() { return m_Collider; }
        void Set_xpos(int x) { x_pos = x; }
        void Set_ypos(int y) { y_pos = y; }
        bool getIsDead() { return isDead; }
        void setIsDead() { isDead = 1; }
        void setType(std::string type) { bullet_Type = type; }
        void setBeamSize(int x) { beamSize = x; }
        int getTimeEx() { return timeEx; }

    private:
        double x_pos;
        double y_pos;
        bool isDead = 0;
        int beamSize;
        int timeEx = 0;
        std::string bullet_Type;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // BULLET_H
