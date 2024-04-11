#include "TextureManager.h"
#include "../src/Engine.h"
#include "../camera/Camera.h"
#include <iostream>

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Failed to create texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    std::cout << "filename: " << filename << std::endl;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio;
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angle, nullptr, flip /*lat*/);
}

void TextureManager::DrawBG(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angle, nullptr, flip /*lat*/);
}

void TextureManager::DrawObject(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio;
    // std::cout << "root: " << x << " " << y << std::endl;
    // std::cout << width << " " << height << std::endl;
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angle, nullptr, flip /*lat*/);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip, float angle)
{
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x - (int)cam.X, y - (int)cam.Y, width, height};
    // debug
    /*
    std::cout << "id: " << id << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "srcRect.x: " << srcRect.x << std::endl;
    std::cout << "srcRect.y: " << srcRect.y << std::endl;
    std::cout << "row: " << row << std::endl;
    std::cout << "frame: " << frame << std::endl;
    std::cout << "m_TextureMap[id]: " << m_TextureMap[id] << std::endl;
    */
    //std::cout << "player: " << x << " " << y << std::endl;
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, angle, nullptr, flip /*lat*/);
}

// Use for Map
void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize* frame, tileSize*(row), tileSize, tileSize};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x-(int)cam.X, y-(int)cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();

    SDL_Log("Texture Map Cleaned!");
}