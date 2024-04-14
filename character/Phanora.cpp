#include "Phanora.h"
#include "../graphics/TextureManager.h"
#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../inputs/Input.h"
#include "../src/Engine.h"
#include "../camera/Camera.h"
#include "../collision/CollisionHandler.h"
#include "../factory/ObjectFactory.h"
#include "../bullet/Bullet.h"
#include "../shield/Shield.h"
#include <math.h>

static Registrar<Phanora> registrar("PLAYER");

Phanora::Phanora(Properties* props): Character(props)
{
    m_Collider = new Collider();
    m_Collider->SetBuffer(0,0,0,0);

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 120);
}

void Phanora::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, angle);
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect hBar = { (int)m_Transform->X - (int)cam.X, (int)m_Transform->Y - (int)cam.Y - 10, 60- (30-health)*2, 10 };
    SDL_Rect vBar = { (int)m_Transform->X - (int)cam.X, (int)m_Transform->Y - (int)cam.Y - 10, 60, 10 };
    SDL_Rect outline = { (int)m_Transform->X - (int)cam.X, (int)m_Transform->Y - (int)cam.Y - 10, 60, 10 };
    // phong nen
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &vBar);
    // mau
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &hBar);
    // vien
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &outline);
    // debugger
    /*
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    */
}

void Phanora::Refresh()
{
    health = HEALTH;
    m_Transform->X = 450;
    m_Transform->Y = 450;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 45, 45);
    m_Animation->Update();
}

void Phanora::Update(float dt)
{
    m_Animation->SetProps("player_idle", 1, 6, 120);
    m_RigidBody->UnSetForce();

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) )
    {
        m_RigidBody->ApplyForceX(P_SPEED*BACKWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) )
    {
        m_RigidBody->ApplyForceX(P_SPEED*FORWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_NONE);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) )
    {
        m_RigidBody->ApplyForceY(P_SPEED*UPWARD);
        m_Animation->SetProps("player_move", 1, 6, 120);
    }

    if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) )
    {
        m_RigidBody->ApplyForceY(P_SPEED*DOWNWARD);
        m_Animation->SetProps("player_move", 1, 6, 120, SDL_FLIP_NONE);
    }

    // SDL_Log("%f", dt);
    // X
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
    // m_Transform->TranslateX(m_RigidBody->Position().X);
    // m_Transform->TranslateY(m_RigidBody->Position().Y);
    // camera
    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    //mouse motion
    m_x = 450;
    m_y = 450;
    if ( m_Origin->X <= 450 ) m_x = m_Origin->X;
    if ( m_Origin->X >= 2250 ) m_x = m_Origin->X - 2250 + 450;
    if ( m_Origin->Y <= 450 ) m_y = m_Origin->Y;
    if ( m_Origin->Y >= 2250 ) m_y = m_Origin->Y - 2250 + 450;
    // debug: std::cout << ": " << m_x << " " << m_y << std::endl;
    angle = -90 + atan2( m_y/*450*/ - Input::GetInstance()->GetMouseY(), m_x/*450*/ - Input::GetInstance()->GetMouseX()) * ( 180/PI);
    if ( angle < 0 ) angle = 360 + angle;

    // bullet
    if ( Input::GetInstance()->GetMouseCheckLeft() )
    {
        canspawnbullet = 1;
    }

    if ( !Input::GetInstance()->GetMouseCheckLeft() )
    {
        canspawnbullet = 0;
    }

    if ( Input::GetInstance()->GetMouseCheckRight() )
    {
        shieldup = 1;
    }

    if ( !Input::GetInstance()->GetMouseCheckRight() )
    {
        shieldup = 0;
    }

    CurrentTime=SDL_GetTicks();
    if ( canspawnbullet && ( CurrentTime>LastTime+100) && !shieldup )
    {
        //std::cout << "create new bullet\n";
        //i++;
        Bullet* p_bullet=new Bullet(new Properties("bullet", 450, 450, 10 ,30));
        p_bullet->p_angle = angle;
        p_bullet->Set_xpos(m_Transform->X + m_Width/2);
        p_bullet->Set_ypos(m_Transform->Y + m_Height/2);
        p_bullet->setType("bullet");
        Engine::GetInstance()->p_bullet_list.push_back({p_bullet, "bullet"});
        LastTime = CurrentTime;

        Sound::GetInstance()->PlayEffect("shoot");
        // for (auto x:  Engine::GetInstance()->p_bullet_list)
        // {
        //     std::cout << i << std::endl;
        // }
    }

    if ( shieldup && !canspawnbullet  && (CurrentTime>LastTime+1000) )
    {
        std::cout << "shield up\n";
        Shield* p_shield = new Shield(new Properties("sheild", 450, 450, 120, 40));
        p_shield->p_angle = angle;
        p_shield->Set_xpos(m_Transform->X+m_Width/2-60);
        p_shield->Set_ypos(m_Transform->Y + m_Height/2);
        Engine::GetInstance()->p_shield_list.push_back(p_shield);
        LastTime = CurrentTime;
    }

    m_Animation->Update();
}

void Phanora::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
