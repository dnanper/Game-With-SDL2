#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include <map>

class TextureManager
{
    public:
        static TextureManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();
        }

        bool Load(std::string id, std::string filename);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawObject(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE, float angle = 0);
        void DrawBG(std::string id, int x, int y, int width, int height, float scrollRatio, float angle, SDL_RendererFlip flip=SDL_FLIP_NONE);

    private:
        TextureManager(){};
        std::map<std::string, SDL_Texture*> m_TextureMap;
        static TextureManager* s_Instance;
};

#endif  // TEXTUREMANAGER_H