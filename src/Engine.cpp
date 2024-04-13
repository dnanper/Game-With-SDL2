#include "Engine.h"
#include "../graphics/TextureManager.h"
#include "../sounds/Sound.h"
#include "../text/Text.h"
#include <iostream>
#include "../physics/Transform.h"
#include "../Character/Phanora.h"
#include "../inputs/Input.h"
#include "../timer/Timer.h"
#include "../camera/Camera.h"
#include "../map/MapParser.h"
#include "../character/Enemy.h"
//#include "../factory/ObjectFactory.h"
#include "../bullet/Bullet.h"
#include "../collision/CollisionHandler.h"
#include "../physics/Vector2D.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("MAIN GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if ( m_Window == nullptr )
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( m_Renderer == nullptr )
    {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;        
    }

    if (!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to Load map" << std::endl;
    }

    if (TTF_Init() == -1 )
    {
        std::cout << "Could not initailize SDL2 tff: " << TTF_GetError() << "\n"; 
    }
    Font = TTF_OpenFont("fonts/VTKSDURA3d.ttf", 25);
    Menu_Font = TTF_OpenFont("fonts/VTKSDURA3d.ttf", 50);
    Pause_Font = TTF_OpenFont("fonts/VTKSDURA3d.ttf", 35);

    if ( Font == nullptr ) std::cout << "Failed to Load Font\n";

    m_LevelMap = MapParser::GetInstance()->GetMap("BossRoom");


// Load texture
    TextureManager::GetInstance()->Load("player_idle", "image/finaltest.png");
    TextureManager::GetInstance()->Load("player_move", "image/move.png");

    TextureManager::GetInstance()->Load("bullet", "image/bullet.png");
    TextureManager::GetInstance()->Load("e_bullet", "image/e_bullet.png");
    TextureManager::GetInstance()->Load("e_bullet2", "image/laze.png");

    TextureManager::GetInstance()->Load("enemy_idle", "image/enemy.png");
    TextureManager::GetInstance()->Load("enemy_idle2", "image/enemy_2.png");
    TextureManager::GetInstance()->Load("enemy_idle3", "image/enemy_3.png");
    TextureManager::GetInstance()->Load("enemy_die", "image/explorsion.png");

    TextureManager::GetInstance()->Load("sheild", "image/shield.png");

    TextureManager::GetInstance()->Load("bg", "image/bg.png");
    TextureManager::GetInstance()->Load("portal", "image/portal.png");

    TextureManager::GetInstance()->Load("menu_bg", "image/menu_bg.png");
    TextureManager::GetInstance()->Load("pause_bg", "image/pause.png");
//

// Load sounds
    Sound::GetInstance()->LoadEffect("shoot", "audio/gun.mp3");
    Sound::GetInstance()->LoadEffect("e_dead", "audio/enemy_dead2.wav");
    Sound::GetInstance()->LoadMusic("bg", "audio/Menu.wav");
    Sound::GetInstance()->PlayMusic("bg");
// Load Text
    MenuText.push_back(&Play);
    MenuText.push_back(&Pause);
    MenuText.push_back(&Exit);

    PauseText.push_back(&Continue);
    PauseText.push_back(&Home);
    PauseText.push_back(&Restart);

    DieText.push_back(&Home);
    DieText.push_back(&Restart);

    Play.Set_Text("Start Game");
    Play.Set_Rect(m_Play);
    Exit.Set_Text("Exit");
    Exit.Set_Rect(m_Exit);
    Pause.Set_Text("Pause Game");

    Continue.Set_Text("Continue");
    Continue.Set_Rect(m_Continue);
    Home.Set_Text("Home");
    Home.Set_Rect(m_Home);
    Restart.Set_Text("Restart");
    Restart.Set_Rect(m_Restart);

    YouDie.Set_Text("YOU DIE!!!");
    YouDie.SetColor(Text::WHITECOLOR);
    YouDie.LoadFromRenderText(Menu_Font, m_Renderer);

    for (auto x : PauseText)
    {
        (*x).SetColor(Text::WHITECOLOR);
        (*x).LoadFromRenderText(Pause_Font, m_Renderer);
    }   

    for (auto x : MenuText)
    {
        (*x).SetColor(Text::BLACKCOLOR);
        (*x).LoadFromRenderText(Menu_Font, m_Renderer);
    }   

    HighScore.SetColor(Text::REDCOLOR);
    HighScore.Set_Text("High Score: ");
    HighScore.LoadFromRenderText(Font, m_Renderer);

    Mark.SetColor(Text::REDCOLOR);
    string str_Mark = "SCORE: ";
    Mark.Set_Text(str_Mark);
    Mark.LoadFromRenderText(Font, m_Renderer);

    numsMark.SetColor(Text::WHITECOLOR);
    numsHighScore.SetColor(Text::WHITECOLOR);
//
    std::fstream HighScoreFile;
	HighScoreFile.open("src/Save.txt");
    if ( !HighScoreFile.is_open() )
        std::cout << "chua mo\n";
    else std::cout << "da mo\n";
	HighScoreFile >> highscore;
//
    player = new Phanora(new Properties("player", 450, 450, 60, 60));

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning = true;
}

void Engine::Update()
{
    // Pause
    //Mix_Volume(-1, 16);
    if ( m_Pausing )
    {
        int mouse_X = Input::GetInstance()->GetMouseX();
        int mouse_Y = Input::GetInstance()->GetMouseY();
        for ( auto x : PauseText )
        {
            if ( mouse_X >= (*x).m_Rect.x && mouse_X <= (*x).m_Rect.x + (*x).m_Rect.w &&
                 mouse_Y >= (*x).m_Rect.y && mouse_Y <= (*x).m_Rect.y + (*x).m_Rect.h )
            {
                (*x).SetColor(Text::REDCOLOR);
                (*x).LoadFromRenderText(Pause_Font, m_Renderer);
                if ( ((*x).GetText() == "Continue") && Input::GetInstance()->GetMouseCheckLeft() )
                    m_Pausing = 0;
                if ( ((*x).GetText() == "Home") && Input::GetInstance()->GetMouseCheckLeft() )
                {    
                    m_Starting = 0;
                    m_Pausing = 0;
                    player->Refresh();
                    p_bullet_list.clear();
                    m_enemy_list.clear();
                    mark = 0;
                    for (auto &type : type3_pos_list)
                    {
                        type.second = 0;
                    }
                }
                if ( ((*x).GetText() == "Restart") && Input::GetInstance()->GetMouseCheckLeft() )
                {
                    m_Pausing = 0;
                    player->Refresh();
                    p_bullet_list.clear();
                    m_enemy_list.clear();
                    mark = 0;
                    for (auto &type : type3_pos_list)
                    {
                        type.second = 0;
                    }
                }
            }
            else
            {
                (*x).SetColor(Text::WHITECOLOR);
                (*x).LoadFromRenderText(Pause_Font, m_Renderer);
            }
        }
    }
    if ( m_Ending )
    {
        int mouse_X = Input::GetInstance()->GetMouseX();
        int mouse_Y = Input::GetInstance()->GetMouseY();
        for ( auto x : DieText )
        {
            if ( mouse_X >= (*x).m_Rect.x && mouse_X <= (*x).m_Rect.x + (*x).m_Rect.w &&
                 mouse_Y >= (*x).m_Rect.y && mouse_Y <= (*x).m_Rect.y + (*x).m_Rect.h )
            {
                (*x).SetColor(Text::REDCOLOR);
                (*x).LoadFromRenderText(Pause_Font, m_Renderer);
                if ( ((*x).GetText() == "Home") && Input::GetInstance()->GetMouseCheckLeft() )
                {    
                    m_Starting = 0;
                    m_Pausing = 0;
                    m_Ending = 0;
                    player->Refresh();
                    p_bullet_list.clear();
                    m_enemy_list.clear();
                    mark = 0;
                    for (auto &type : type3_pos_list)
                    {
                        type.second = 0;
                    }
                }
                if ( ((*x).GetText() == "Restart") && Input::GetInstance()->GetMouseCheckLeft() )
                {
                    m_Pausing = 0;
                    m_Ending = 0;
                    player->Refresh();
                    p_bullet_list.clear();
                    m_enemy_list.clear();
                    mark = 0;
                    for (auto &type : type3_pos_list)
                    {
                        type.second = 0;
                    }
                }
            }
            else
            {
                (*x).SetColor(Text::WHITECOLOR);
                (*x).LoadFromRenderText(Pause_Font, m_Renderer);
            }
        }
    }

    // Menu
    if ( !m_Starting && !m_Ending )
    {
        int mouse_X = Input::GetInstance()->GetMouseX();
        int mouse_Y = Input::GetInstance()->GetMouseY();
        for ( auto x : MenuText )
        {
            if ( mouse_X >= (*x).m_Rect.x && mouse_X <= (*x).m_Rect.x + (*x).m_Rect.w &&
                 mouse_Y >= (*x).m_Rect.y && mouse_Y <= (*x).m_Rect.y + (*x).m_Rect.h )
            {
                (*x).SetColor(Text::REDCOLOR);
                (*x).LoadFromRenderText(Menu_Font, m_Renderer);
                if ( ((*x).GetText() == "Start Game") && Input::GetInstance()->GetMouseCheckLeft() )
                    m_Starting = 1;
                if ( ((*x).GetText() == "Exit") && Input::GetInstance()->GetMouseCheckLeft() )
                    m_IsRunning = 0;
            }
            else
            {
                (*x).SetColor(Text::BLACKCOLOR);
                (*x).LoadFromRenderText(Menu_Font, m_Renderer);
            }
        }
    }   

    if ( m_Starting && !m_Pausing && !m_Ending )
    {    
        // read highscore from txt
        //std::cout << highscore << endl;
        //
        if ( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE) )
        {
            m_Pausing = 1;
        }
        float dt = Timer::GetInstance()->GetDeltaTime();
        //std::cout << time << std::endl;
        //std::cout << "health: " << player->getHealth() << std::endl;
        if ( !boss ) time++;
        // spawn enemy
        if ( time == ENEMY_DELAY )
        {
        //    std::cout << " Create new enemy\n";
        //type 1
            int i = 0;
            for ( auto e = m_enemy_list.begin(); e != m_enemy_list.end(); e++)
            {
                if ( (*e).second == "enemy_idle" )
                {
                    i++;
                }
            }
            if ( i < 5 )
            {
            Enemy* enemy = new Enemy(new Properties("enemy", 1350, 1350, 60 ,60));
            enemy->setType("enemy_idle");
            m_enemy_list.push_back({enemy, "enemy_idle"});
            }
        //type 2
            Enemy* enemy2 = new Enemy(new Properties("enemy", 1300, 1300, 60 ,60));
            enemy2->setType("enemy_idle2");
            m_enemy_list.push_back({enemy2, "enemy_idle2"});
        //type 3
            int cnt = 0;
            for ( auto &x : type3_pos_list )
            {
                if ( x.second == 0 )
                {
                    Enemy* enemy3 = new Enemy(new Properties("enemy", 1350, 1350, 60, 60));
                    enemy3->setType("enemy_idle3");
                    m_enemy_list.push_back({enemy3, "enemy_idle3"});
                    x.second = 1;
                    enemy3->type3_pos = cnt;
                    //std::cout << "cnt: " << cnt << "-----------------------------"<< std::endl;
                    break;
                }
                cnt++;
            }
            cnt = 0;
        
            time = 0;
        }

        if ( m_enemy_list.size() == BOSS_TIME*2 )
            boss = 1;

        if (boss)
        {
            //std::cout << "boss appear!!!" << std::endl;
        }
        
        player->Update(dt);
        for (unsigned int i = 0; i != m_enemy_list.size(); i++)
        {
            m_enemy_list[i].first->Update(dt);
            //std::cout << m_enemy_list[i].second << std::endl;
        }
        for (auto x : p_shield_list)
            x->Update(dt);
        for (auto x : p_bullet_list)
            x.first->Update(dt);

        // check bullet-enemy collision
        for ( auto e = m_enemy_list.begin(); e != m_enemy_list.end(); e++)
        {
            for ( auto b = p_bullet_list.begin(); b != p_bullet_list.end(); b++)
            {
                if ( (*b).second == "bullet" )
                {
                    if (CollisionHandler::GetInstance()->CheckCollision( (*e).first->getCollider()->Get(), (*b).first->getCollider()->Get() ))
                    {
                        (*e).first->e_health -= B_DAME;
                        if ( (*e).first->e_health == 0)
                        {
                            (*e).first->setIsBlown();
                        }
                        (*b).first->setIsDead();
                    }
                }
                // else if ( (*b).second == "e_bullet2" && (*b).first->getTimeEx() == 50 )
                // {
                //     (*b).first->setIsDead();
                // }
            }
        }
        // check shiled broke
        for ( auto s = p_shield_list.begin(); s != p_shield_list.end(); s++)
        {
            if ( (*s)->getSur() == TI )
            {
                (*s)->setIsDead();
            }
        }
        // check shield-bullet collision
        for (auto b = p_bullet_list.begin(); b != p_bullet_list.end(); b++ )
        {
            for (auto s = p_shield_list.begin(); s != p_shield_list.end(); s++)
            {
                if (CollisionHandler::GetInstance()->CheckCollision( (*s)->getCollider()->Get(), (*b).first->getCollider()->Get() ))
                {
                    (*b).first->setIsDead();
                }
            }
        }
        // check e_bullet-player collision
        for ( auto b = p_bullet_list.begin(); b != p_bullet_list.end(); b++)
        {
            if ( (*b).second == "e_bullet" )
            {
                if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*b).first->getCollider()->Get() ))
                {
                    player->setHealth(-B_DAME_1);
                    (*b).first->setIsDead();
                }
            }
            else if ( (*b).second == "e_bullet2" )
            {
                if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*b).first->getCollider()->Get() ))
                {
                    player->setHealth(-B_DAME_2);
                    (*b).first->setIsDead();
                }
            }
        }
        // check m_Ending
        if ( player->getHealth() <= 0 )
        {
            m_Ending = 1;
            //m_Starting = 0;
        }

        // check enemy1-player collision
        for ( auto e = m_enemy_list.begin(); e != m_enemy_list.end(); e++)
        {
            if ( (*e).second == "enemy_idle")
            {
                if (CollisionHandler::GetInstance()->CheckCollision( player->GetCollider()->Get(), (*e).first->getCollider()->Get() ))
                {
                    player->setHealth(-B_DAME_2);
                }
            }
        }
        // check enemy_dead
        for (auto x = m_enemy_list.begin(); x != m_enemy_list.end(); )
        {
            if ( (*x).first->getIsDead() )
            {
                if ( (*x).second == "enemy_idle3" )
                {
                    int k = (*x).first->type3_pos;
                    int i = 0;
                    for (auto &type : type3_pos_list)
                    {
                        if ( i == k )
                        {
                            //std::cout <<
                            type.second = 0;
                            break;
                        }
                        i++;
                    }                
                }
                mark += 1;
                m_enemy_list.erase(x);
                //Sound::GetInstance()->PlayEffect("e_dead");
            }
            else
                x++;
        }
        // high score
            std::fstream HighScoreFile;
            HighScoreFile.open("src/Save.txt");
            if ( mark > stoi(highscore) )
            {
                highscore = to_string(mark);
            }
            HighScoreFile << highscore;
        //
        // check bullet_dead
        for (auto x = p_bullet_list.begin(); x != p_bullet_list.end(); )
        {
            if ( (*x).first->getIsDead() )
                p_bullet_list.erase(x);
            else
                x++;
        }
        // check sheid dead
        for (auto x = p_shield_list.begin(); x != p_shield_list.end();)
        {
            if ( (*x)->getIsDead() )
                p_shield_list.erase(x);
            else
                x++;
        }
        // check player dead
        if ( player->getHealth() < 0 )
        {
            GameOver = true;
        }
        Camera::GetInstance()->Update(dt);  
        m_LevelMap->Update();
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    if ( !m_Starting && !m_Pausing && !m_Ending )
    {
        TextureManager::GetInstance()->DrawBG("menu_bg", 0, 0, 900, 900, 1, 0);
        Play.RenderText(m_Renderer, 320, 600 );
        Exit.RenderText(m_Renderer, 400, 675 );
    }

    if ( m_Starting )
    {
        TextureManager::GetInstance()->Draw("bg", 0, 0, 2700, 2700, 1, 0);
        TextureManager::GetInstance()->Draw("portal",1068, 1138, 564, 423, 1, 0);
        m_LevelMap->Render();

        player->Draw();
        for (unsigned int i = 0; i != m_enemy_list.size(); i++)
            m_enemy_list[i].first->Draw();
        for (auto x : p_shield_list)
            x->Draw();
        for (auto x : p_bullet_list)
            x.first->Draw();
        
        HighScore.RenderText(m_Renderer,10, 50 );
        numsHighScore.Set_Text(highscore);
        numsHighScore.LoadFromRenderText(Font, m_Renderer);
        numsHighScore.RenderText(m_Renderer, 170, 50);

        Mark.RenderText(m_Renderer, 10, 10);
        numsMark.Set_Text(to_string(mark));
        numsMark.LoadFromRenderText(Font, m_Renderer);
        numsMark.RenderText(m_Renderer, 100, 10);
    }

    if ( m_Pausing )
    {
        TextureManager::GetInstance()->DrawBG("pause_bg", 200 , 200, 500, 500, 1, 0);
        Continue.RenderText(m_Renderer, 370, 365 );
        Restart.RenderText(m_Renderer, 375, 425 );
        Home.RenderText(m_Renderer, 400, 485 );
    }

    if ( m_Ending )
    {
        TextureManager::GetInstance()->DrawBG("pause_bg", 200 , 200, 500, 500, 1, 0);
        Restart.RenderText(m_Renderer, 375, 425 );
        Home.RenderText(m_Renderer, 400, 485 );
        YouDie.RenderText(m_Renderer, 350, 300);
    }

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}

bool Engine::Clean()
{   
    player->Clean();
    for (unsigned int i = 0; i != m_enemy_list.size(); i++)
        m_enemy_list[i].first->Clean();

    for (auto x : p_bullet_list)
        x.first->Clean();

    for (auto x : p_shield_list)
        x->Clean();

    for (auto x : MenuText )
        (*x).Free();
    for (auto x : PauseText )
        (*x).Free();
    Mark.Free();
    numsMark.Free();

    TextureManager::GetInstance()->Clean();
    Sound::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}