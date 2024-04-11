#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "../physics/Transform.h"
#include "../inc/SDL.h"
#include "../inc/SDL_image.h"
#include "../physics/Point.h"
#include <string>

struct Properties
{
    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE)
        {
            X=x;
            Y=y;
            Flip=flip;
            Width=width;
            Height=height;
            TextureID=textureID;
        }
    
    public:
        std::string TextureID;
        int Width, Height;
        float X, Y;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props) : m_TextureID(props->TextureID),
        m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip)
        {
            m_Transform = new Transform(props->X, props->Y);

            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_Origin= new Point(px, py);
        }

        inline Point* GetOrigin() { return m_Origin; }

        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;

        Transform* m_Transform;

    protected:
        Point* m_Origin;
        
        int m_Width, m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif  // GAMEOBJECT_H