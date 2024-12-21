#ifndef ABIMAGE_H
#define ABIMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class abImage {
    public:
        abImage();
        ~abImage();
        void Initialise(const int xSize, const int ySize, SDL_Renderer *pRenderer);
        void SetPixel(const int x, const int y, const double red, const double green, const double blue);
        void Display();
        int GetXSize();
        int GetYSize();
    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();

    private:
        std::vector<std::vector<double>> m_rChannel;
        std::vector<std::vector<double>> m_gChannel;
        std::vector<std::vector<double>> m_bChannel;

        int m_xSize, m_ySize;

        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;
};

#endif