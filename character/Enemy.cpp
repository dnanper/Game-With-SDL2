#include "Enemy.h"
#include "../graphics/TextureManager.h"
#include "../inc/SDL.h"
#include "../src/Engine.h"
#include "../collision/CollisionHandler.h"
#include "../camera/Camera.h"
#include <iostream>
#include "../factory/ObjectFactory.h"
#include <math.h>

static Registrar<Enemy> registrar("ENEMY");

Enemy::Enemy(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 80);
}

void Enemy::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, e_angle);
    // SDL_Rect box = m_Collider->Get();
    // SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Enemy::Update(float dt)
{
    m_Animation->SetProps("enemy_idle", 1, 6, 80);
    m_RigidBody->UnSetForce();
    //movement
    target_X = Engine::GetInstance()->player->m_Transform->X;
    target_Y = Engine::GetInstance()->player->m_Transform->Y;

    e_angle = -90 +  atan2( target_Y - m_Transform->Y, target_X - m_Transform->X ) * ( 180/PI);
    if ( e_angle < 0 ) e_angle = 360 + e_angle;
    e_angle += 180;
// type 1
    if ( enemy_Type == "enemy_idle")
    {
        m_Animation->SetProps("enemy_idle", 1, 6, 80);
        if ( !blown) m_RigidBody->ApplyForceX(E_SPEED_TYPE_1*cos( (e_angle+270)*PI/180 ));
        if ( !blown) m_RigidBody->ApplyForceY(E_SPEED_TYPE_1*sin( (e_angle+270)*PI/180 ));
    }
// type 2
    else if (enemy_Type == "enemy_idle2" )
    {
        distance = sqrt( (target_X-m_Transform->X)*(target_X-m_Transform->X) + (target_Y-m_Transform->Y)*(target_Y-m_Transform->Y) );
        CurrentTime = SDL_GetTicks();
        m_Animation->SetProps("enemy_idle2", 1, 6, 80);
    // movement
        if (!blown)
        {
            if ( distance > 300 && EshotTime_type2 == 0 )
            {
                m_RigidBody->ApplyForceX(E_SPEED_TYPE_2*cos( (e_angle+270)*PI/180 ));
                m_RigidBody->ApplyForceY(E_SPEED_TYPE_2*sin( (e_angle+270)*PI/180 ));
            }
            else
            {
        // bullet
                if ( CurrentTime > LastTime+100 )
                {
                    EshotTime_type2 ++;
                    Bullet* p_bullet=new Bullet(new Properties("bullet", 450, 450, 10 ,30));
                    p_bullet->setType("e_bullet");
                    p_bullet->Set_xpos(m_Transform->X + m_Width/2);
                    p_bullet->Set_ypos(m_Transform->Y + m_Height/2);
                    p_bullet->p_angle = e_angle;
                    Engine::GetInstance()->p_bullet_list.push_back({p_bullet, "e_bullet"});
                    LastTime = CurrentTime;
                }
                if ( EshotTime_type2 == 6 )
                {
                    EshotTime_type2 = 0;
                }
            }
        }
    }
// type 3
    else if (enemy_Type == "enemy_idle3")
    {
        m_Animation->SetProps("enemy_idle3", 1, 6, 80);
    //movement
        if ( type3Alr == 0 )
        {
            //std::cout << "not ready!\n"; 
            target_type3_X = m_type3_pos_list[type3_pos].first;
            target_type3_Y = m_type3_pos_list[type3_pos].second;
            //std::cout << "target: " << target_type3_X << " " << target_type3_Y << std::endl;
        }
        //std::cout << "(" << target_type3_X << " " <<  target_type3_Y << ")" << "(" << m_Transform->X << " " <<  m_Transform->Y << ")\n";
        if ( ( (target_type3_X-10<m_Transform->X) && (target_type3_X+10>m_Transform->X) ) && ( (target_type3_Y-10<m_Transform->Y) && (target_type3_Y+10>m_Transform->Y) ) )
        {
            m_RigidBody->UnSetForce();
            type3Alr = 1;
            // bullet
            CurrentTime = SDL_GetTicks();
            // distance + angle
            if (type3_pos == 0)
            {
                distance = (int)sqrt( (target_X-10-m_Transform->X)*(target_X-10-m_Transform->X) + (target_Y-m_Transform->Y)*(target_Y-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y - m_Transform->Y, target_X- 60 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            else if (type3_pos == 1)
            {
                distance = (int)sqrt( (target_X-5-m_Transform->X)*(target_X-5-m_Transform->X) + (target_Y-5-m_Transform->Y)*(target_Y-5-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y-30 - m_Transform->Y, target_X-30 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;            
            }
            else if ( type3_pos == 2 )
            {
                distance = (int)sqrt( (target_X-m_Transform->X)*(target_X-m_Transform->X) + (target_Y-10-m_Transform->Y)*(target_Y-10-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y-60 - m_Transform->Y, target_X - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;            
            }
            else if ( type3_pos == 3 )
            {
                distance = (int)sqrt( (target_X+5-m_Transform->X)*(target_X+5-m_Transform->X) + (target_Y-5-m_Transform->Y)*(target_Y-5-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y+30 - m_Transform->Y, target_X+30 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            else if ( type3_pos == 4 )
            {
                distance = (int)sqrt( (target_X+10-m_Transform->X)*(target_X+10-m_Transform->X) + (target_Y-m_Transform->Y)*(target_Y-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y - m_Transform->Y, target_X+60 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            else if ( type3_pos == 5 )
            {
                distance = (int)sqrt( (target_X+5-m_Transform->X)*(target_X+5-m_Transform->X) + (target_Y+5-m_Transform->Y)*(target_Y+5-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y+30 - m_Transform->Y, target_X+30 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            else if ( type3_pos == 6 )
            {
                distance = (int)sqrt( (target_X-m_Transform->X)*(target_X-m_Transform->X) + (target_Y+10-m_Transform->Y)*(target_Y+10-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y+60 - m_Transform->Y, target_X - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            else if ( type3_pos == 7 )
            {
                distance = (int)sqrt( (target_X-5-m_Transform->X)*(target_X-5-m_Transform->X) + (target_Y+5-m_Transform->Y)*(target_Y+5-m_Transform->Y) );
                e_angle = -90 +  atan2( target_Y+30 - m_Transform->Y, target_X-30 - m_Transform->X ) * ( 180/PI);
                if ( e_angle < 0 ) e_angle = 360 + e_angle;
                e_angle += 180;
            }
            //
            if ( CurrentTime > LastTime+1500 && distance <= 900 )
            {
                Bullet* p_bullet=new Bullet(new Properties("bullet", 450, 450, 180 ,20));
                p_bullet->setType("e_bullet2");
                //std::cout << m_Transform->X << " " << m_Transform->Y << std::endl;
                p_bullet->Set_xpos(m_Transform->X + m_Width/2);
                p_bullet->Set_ypos(m_Transform->Y + m_Height/2);
                p_bullet->p_angle = e_angle;
                Engine::GetInstance()->p_bullet_list.push_back({p_bullet, "e_bullet2"});
                LastTime = CurrentTime;
            }
        }
        else
        {
            e_angle = -90 +  atan2( target_type3_Y - 1350, target_type3_X - 1350 ) * ( 180/PI);
            if ( e_angle < 0 ) e_angle = 360 + e_angle;
            e_angle += 180;
            m_RigidBody->ApplyForceX(E_SPEED_TYPE_2*cos( (e_angle+270)*PI/180 ));
            m_RigidBody->ApplyForceY(E_SPEED_TYPE_2*sin( (e_angle+270)*PI/180 ));
        }
    }

// collsion with map
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 45, 45);
    
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }
    // Y
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 45, 45);
    
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->Y = m_LastSafePosition.Y;
    }
    // death
    if ( blown ) 
    {
        std::cout << "now blow!\n";
        m_RigidBody->UnSetForce();
        m_Animation->SetProps("enemy_die", 1, 6, 80);
        blowTime++;
        if ( blowTime == 7 )
        {
            dead = 1;
            blowTime = 0;
        }
        Sound::GetInstance()->PlayEffect("e_dead");
    }
    m_Animation->Update();
}

void Enemy::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}