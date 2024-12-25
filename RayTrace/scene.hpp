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
#include "cylinder.hpp"

namespace abRT {
    class Scene {
        public:
            Scene();
            bool Render(abImage &outputImage);
            bool CastRay(abRT::Ray &castRay, std::shared_ptr<abRT::ObjectBase> &closestObject, abVector<double> &closestIntPoint, abVector<double> &closestLocalNormal, abVector<double> &closestLocalColor);

        private:
        
        private:
            abRT::Camera m_camera;
            std::vector<std::shared_ptr<abRT::ObjectBase>> m_objectList;
            std::vector<std::shared_ptr<abRT::LightBase>> m_lightList;
    };
};

#endif