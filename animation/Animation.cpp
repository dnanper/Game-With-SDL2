#include "Animation.h"
#include "../graphics/TextureManager.h"
#include <iostream>

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, float angle)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip, angle);
}

void Animation::DrawnotFrame(int x, int y)
{
    TextureManager::GetInstance()->DrawObject(m_TextureID, x, y, m_Width, m_Height, 1, m_Angle, SDL_FLIP_NONE);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}

void Animation::SerPropsDraw(std::string textureID, int width, int height, float angle)
{
    m_TextureID = textureID;
    m_Width = width;
    m_Height = height;
    m_Angle = angle;
}