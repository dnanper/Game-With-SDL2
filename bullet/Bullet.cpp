#include "Bullet.h"
#include "../collision/CollisionHandler.h"
#include "../graphics/TextureManager.h"
#include "../factory/ObjectFactory.h"
#include "../inputs/Input.h"
#include "../src/Engine.h"
#include <math.h>
#include "../inc/SDL.h"
#include <iostream>
#include "../character/Phanora.h"

static Registrar<Bullet> registrar("BULLET");

Bullet::Bullet(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();

    m_Animation->SerPropsDraw(m_TextureID, 10, 30, p_angle);
}

void Bullet::Draw()
{
    m_Animation->DrawnotFrame(x_pos, y_pos);
}

void Bullet::Update(float dt)
{
    if ( bullet_Type == "e_bullet2")
        m_Animation->SerPropsDraw("e_bullet2", 180, 20, p_angle);
    else if ( bullet_Type == "e_bullet")
    {
        m_Animation->SerPropsDraw("e_bullet", 10, 30, p_angle);
    }
    else if ( bullet_Type == "bullet" )
    {
        m_Animation->SerPropsDraw("bullet", 10, 30, p_angle);
    }
    else if ( bullet_Type == "orb_1" )
    {
        m_Animation->SerPropsDraw("orb_1", 30, 30, 90);
    }
    //m_Animation->SerPropsDraw(m_TextureID, 10, 30, p_angle);
    m_RigidBody->UnSetForce();
    //std::cout << p_angle << std::endl;
    if ( bullet_Type != "e_bullet2" && bullet_Type != "orb_1" )
    {    
        m_RigidBody->ApplyForceX(B_SPEED*cos( (p_angle+270)*PI/180 ));
        m_RigidBody->ApplyForceY(B_SPEED*sin( (p_angle+270)*PI/180 ));
    }
    else if ( bullet_Type == "e_bullet2" )
    {
        m_RigidBody->ApplyForceX(B_SPEED*1.5*cos( (p_angle+270)*PI/180 ));
        m_RigidBody->ApplyForceY(B_SPEED*1.5*sin( (p_angle+270)*PI/180 ));
        //timeEx ++;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition.X = x_pos;
    x_pos += m_RigidBody->Position().X;
    m_Collider->Set(x_pos, y_pos, 10, 30);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        x_pos = m_LastSafePosition.X;
        isDead = 1;
    }

    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = y_pos;
    y_pos += m_RigidBody->Position().Y;
    m_Collider->Set(x_pos, y_pos, 10, 30);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        y_pos = m_LastSafePosition.X;
        isDead = 1;
    }

}

void Bullet::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}

