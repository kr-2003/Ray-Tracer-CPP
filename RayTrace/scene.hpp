#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "abImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"

namespace abRT {
    class Scene {
        public:
            Scene();
            bool Render(abImage &outputImage);

        private:
        
        private:
            abRT::Camera m_camera;
            abRT::ObjSphere m_testSphere;
    };
};

#endif