#include "Menu.h"
#include "PLay.h"
#include "../src/Engine.h"
#include "inputs/Input.h"

Menu::Menu() {}

bool Menu::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    std::cout << "Menu Initializes!" << std::endl;
    return true;
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);
    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update()
{

}

bool Menu::Exit()
{
    std::cout << "exit menu!\n";
    return true;
}

void Menu::StartGame()
{
    std::cout << "Game start!\n";
}

void Menu::Editor()
{
    std::cout << "editor mode!\n";
}

void Menu::Settings()
{
    std::cout << "setting mode!\n";
}

void Menu::Quit()
{
    std::cout << "quit game!\n";
}