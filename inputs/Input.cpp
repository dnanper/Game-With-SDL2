#include "Input.h"
#include "../src/Engine.h"
#include <iostream>

Input* Input::s_Instance = nullptr;

Input::Input()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
            case SDL_MOUSEMOTION:
                MouseMotion();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ( event.button.button == SDL_BUTTON_LEFT )
                    MouseDownLeft();
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    MouseDownRight();
                break;
            case SDL_MOUSEBUTTONUP:
                if ( event.button.button == SDL_BUTTON_LEFT )
                    MouseUpLeft();
                else if ( event.button.button == SDL_BUTTON_RIGHT )
                    MouseUpRight();
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return (m_KeyStates[key] == 1);
}

int Input::GetMouseX()
{
    return x_mouse;
}

int Input::GetMouseY()
{
    return y_mouse;
}

bool Input::GetMouseCheckLeft()
{
    return mousecheckleft;
}

bool Input::GetMouseCheckRight()
{
    return mousecheckright;
}

void Input::MouseDownLeft()
{
    mousecheckleft = 1;
}

void Input::MouseDownRight()
{
    mousecheckright = 1;
}

void Input::MouseUpLeft()
{
    mousecheckleft = 0;
}

void Input::MouseUpRight()
{
    mousecheckright = 0;
}

void Input::MouseMotion()
{
    SDL_GetMouseState( &x_mouse, &y_mouse);
    //std::cout << x_mouse << " " << y_mouse << std::endl;
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

int Input::GetAxisKey(Axis axis)
{
    switch(axis)
    {
        case HORIZONTAL:
            if (GetKeyDown(SDL_SCANCODE_D))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_A))
                return -1;
            break;

        case VERTICAL:
            if (GetKeyDown(SDL_SCANCODE_W))
                return 1;
            if (GetKeyDown(SDL_SCANCODE_S))
                return -1;
            break;
        
        default:
            return 0;
    }
}