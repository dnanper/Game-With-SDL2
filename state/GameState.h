#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../inc/SDL.h"

class GameState
{
    public:
        virtual bool Init() = 0;
        virtual bool Exit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        SDL_Renderer* m_Ctxt;
};

#endif  // GAMESTATE_H
