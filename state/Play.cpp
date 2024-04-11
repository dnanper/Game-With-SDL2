#include "Play.h"
// #include "../gui/GUI.h"

Play::PLay() {}

bool Play::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->Load("player_idle", "image/finaltest.png");
    TextureManager::GetInstance()->Load("player_move", "image/move.png");
    TextureManager::GetInstance()->Load("enemy_idle", "image/enemy.png");
    TextureManager::GetInstance()->Load("bg", "image/bg.png");

    Camera::GetInstance()->Set
}