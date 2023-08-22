#include "mask_extthree.h"
#include "SDL.h"

//============================== Getters et Setters ========================================


SDL_PixelFormat* getWindPixelSurface(SDL_Surface * pWinSurf)
{
   return pWinSurf->format;
}

SDL_Surface* getSurfaceFromSdlComponent(sdlComponent** component)
{
    return (*component)->pWinSurf;
}

SDL_Window* getWindowFromSdlComponent(sdlComponent** component)
{
    return (*component)->window;
}

void setInitWindowToSdlComponentWind(sdlComponent** component)
{
    (*component)->window = SDL_CreateWindow(
        "-Morpion game in SDL-",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        X*tailleImg,
        Y*tailleImg,
        SDL_WINDOW_SHOWN
    );
}

SDL_Renderer* getRendererFromComponent(sdlComponent** component)
{
    return (*component)->renderer;
}

void setComponentRenderer(sdlComponent** component)
{
    (*component)->renderer = SDL_CreateRenderer((*component)->window, -1, 0);
}

void setComponentPWinSurf(sdlComponent** component)
{
    (*component)->pWinSurf = SDL_GetWindowSurface((*component)->window);
}

//rajouter...

void setInitRenderer(SDL_Renderer** renderer,SDL_Window** windows)
{
    *renderer = (SDL_CreateRenderer(*windows, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
}

void setImgSurf(SDL_Surface** surf, const char* f)
{
    *surf = IMG_Load(f);
}

void setInitTexture(SDL_Texture** t ,SDL_Renderer** r,SDL_Surface** img)
{
    *t =  SDL_CreateTextureFromSurface(*r, *img);
}

//extension 6...

void createWindowExtensionSix(const char* f,SDL_Window **windows)
{
    *windows = SDL_CreateWindow(f, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, 0);
}
