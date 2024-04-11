#ifndef HEALTH_H
#define HEALTH_H

#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../character/Phanora.h"

class Health
{
    public:
        void Update();
        void Render();
        void Clean();
    private:
        int virtualHealth;
        SDL_Rect

};

#endif  // HEALTH_H
