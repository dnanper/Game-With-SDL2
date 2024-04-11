#ifndef ANIMATION_H
#define ANIMATION_H

#include "../inc/SDL.h"
#include <string>

class Animation
{
    public:
        Animation() {}

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight, float angle);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void SerPropsDraw(std::string textureID, int width, int height, float angle);
        void DrawnotFrame(int x, int y);

    private:
        int m_SpriteRow;
        int m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;

        int m_Width;
        int m_Height;
        float m_Angle;

        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif  // ANIMATION_H