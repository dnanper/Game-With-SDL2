#ifndef ENGINE_H
#define ENGINE_H

#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../inc/SDL_mixer.h"
#include "../map/GameMap.h"
#include "../object/GameObject.h"  
#include "../bullet/Bullet.h"
#include "../shield/Shield.h"
#include "../character/Phanora.h"
#include "../character/Enemy.h"
#include "../text/Text.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
// #include "../state/GameState.h"

#define ENEMY_DELAY 100
#define BOSS_TIME 50
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

class Engine
{
    public:
        static Engine* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();
        // void PopState();
        // void PushState(GameState* current);
        // void ChangeState(GameState* target);

        inline GameMap* GetMap() { return m_LevelMap; }
        inline SDL_Window* GetMainWindow() { return m_Window; }
        inline bool IsRunning()  { return m_IsRunning; }
        inline SDL_Renderer* GetRenderer()  { return m_Renderer; }
        std::vector<std::pair<Bullet*, std::string>> p_bullet_list;
        std::vector<Shield*> p_shield_list;
        // std::vector<GameObject*> m_GameObjects;
        std::vector<std::pair<Enemy*, std::string>> m_enemy_list;
        Phanora* player = nullptr;

        std::map<std::pair<int,int>,bool> type3_pos_list = 
        { {{1000, 1350},0}, {{1160, 1175},0}, {{1350,1100},0}, {{1500,1175},0}, {{1630,1350},0}, {{1500,1525},0}, {{1350,1600},0}, {{1160,1525},0} };
        //bool spawnType3 = false;

        TTF_Font *Font = nullptr;
        TTF_Font *Menu_Font = nullptr;
        TTF_Font *Pause_Font = nullptr;
        Text Mark, numsMark;
        Text Play, Exit, Pause, Restart, Continue, Home;
        Text YouDie;
        SDL_Rect m_Play = {320, 600, 260, 50}, m_Exit = {400, 675, 100, 50}, m_Pause;
        SDL_Rect m_Continue = {370, 365, 160, 35}, m_Restart = { 375, 425, 150, 35}, m_Home = { 400, 480, 100, 35 };
        std::vector< Text*> MenuText;
        std::vector< Text*> PauseText;
        std::vector< Text*> DieText;

        Bullet* Shield = nullptr;

    private:
        Engine(){}
        bool m_IsRunning;
        bool GameOver = 0;
        GameMap* m_LevelMap;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;

        int mark = 0;

        long long time = 0;
        bool boss = 0;
        //std::vector<GameState*> m_States;

        bool m_Starting = 0;
        bool m_Pausing = 0;
        bool m_Ending = 0;
};

#endif  // ENGINE_H