#ifndef INPUT_H
#define INPUT_H

#include "../inc/SDL.h"

enum Axis { HORIZONTAL, VERTICAL};

class Input
{
    public:
        static Input* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        int GetMouseX();
        int GetMouseY();
        bool GetMouseCheckLeft();
        bool GetMouseCheckRight();
        int GetAxisKey(Axis axis);
        int x_mouse, y_mouse;
        bool mousecheckright = 0;
        bool mousecheckleft = 0;
        
    private:
        Input();
        void KeyUp();
        void KeyDown();
        void MouseMotion();
        void MouseDownLeft();
        void MouseDownRight();
        void MouseUpLeft();
        void MouseUpRight();
        
        const Uint8* m_KeyStates;
        static Input* s_Instance;
};

#endif  // INPUT_H