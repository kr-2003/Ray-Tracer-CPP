#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL2/SDL.h>
#include "abImage.hpp"

namespace abRT {
    class Scene {
        public:
            Scene();
            bool Render(abImage &outputImage);

        private:
        
        private:
    };
};

#endif