#ifndef SHIELD_H
#define SHIELD_H

#include "../animation/Animation.h"
#include "../physics/RigidBody.h"
#include "../physics/Collider.h"
#include "../physics/Vector2D.h"
#include "../character/Character.h"
#include <vector>
#include <string>

#define PI 3.14159265358979323846
#define TI 60

class Shield : public Character
{
    public:
        Shield(Properties* props);
        ~Shield() {}

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
        int getTimeEx() { return timeEx; }
        int getSur() { return Sur; }

    private:
        double x_pos;
        double y_pos;
        bool isDead = 0;
        int timeEx = 0;

        int Sur = 0;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif  // SHIELD_H
