#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "abImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"
#include "objplane.hpp"
#include "pointlight.hpp"

namespace abRT {
    class Scene {
        public:
            Scene();
            bool Render(abImage &outputImage);

        private:
        
        private:
            abRT::Camera m_camera;
            std::vector<std::shared_ptr<abRT::ObjectBase>> m_objectList;
            std::vector<std::shared_ptr<abRT::LightBase>> m_lightList;
    };
};

#endif