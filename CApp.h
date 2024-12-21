#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "./RayTrace/abImage.hpp"
#include "./RayTrace/scene.hpp"
#include "./RayTrace/camera.hpp"

class CApp 
{
    public:
        CApp();

        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event *event);
        void OnLoop();
        void OnRender();
        void OnExit();

    private:
        abImage m_image;
        abRT::Scene m_scene;
        bool isRunning;
        SDL_Window *pWindow;
        SDL_Renderer * pRenderer;
};

#endif