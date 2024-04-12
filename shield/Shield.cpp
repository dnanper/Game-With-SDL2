#include "Shield.h"
#include "../collision/CollisionHandler.h"
#include "../graphics/TextureManager.h"
#include "../factory/ObjectFactory.h"
#include "../inputs/Input.h"
#include "../src/Engine.h"
#include <math.h>
#include "../inc/SDL.h"
#include <iostream>
#include "../character/Phanora.h"

Shield::Shield(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();

    m_Animation->SerPropsDraw(m_TextureID, 120, 40, p_angle);
}

void Shield::Draw()
{
    m_Animation->DrawnotFrame(x_pos, y_pos);
}

void Shield::Update(float dt)
{
    m_Animation->SerPropsDraw(m_TextureID, 120, 40, p_angle);
    m_RigidBody->UnSetForce();
    //std::cout << p_angle << std::endl;
    m_RigidBody->ApplyForceX(5*cos( (p_angle+270)*PI/180 ));
    m_RigidBody->ApplyForceY(5*sin( (p_angle+270)*PI/180 ));

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = x_pos;
    x_pos += m_RigidBody->Position().X;
    m_Collider->Set(x_pos, y_pos, 120, 40);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        x_pos = m_LastSafePosition.X;
        isDead = 1;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = y_pos;
    y_pos += m_RigidBody->Position().Y;
    m_Collider->Set(x_pos, y_pos, 120, 40);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        y_pos = m_LastSafePosition.X;
        isDead = 1;
    }

    Sur += 1;
}

void Shield::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}

