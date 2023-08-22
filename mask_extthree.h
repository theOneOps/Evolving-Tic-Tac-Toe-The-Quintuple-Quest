#ifndef MASK_EXTTHREE_H
#define MASK_EXTTHREE_H

#include "pile.h"
#include "display.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "core.h"
#include "SDL.h"

//masquage des données pour les fonctions de SDL

SDL_PixelFormat* getWindPixelSurface(SDL_Surface * pWinSurf);

SDL_Surface* getSurfaceFromSdlComponent(sdlComponent** component);

SDL_Window* getWindowFromSdlComponent(sdlComponent** component);

void setInitWindowToSdlComponentWind(sdlComponent** component);

SDL_Renderer* getRendererFromComponent(sdlComponent** component);

void setComponentRenderer(sdlComponent** component);

void setComponentPWinSurf(sdlComponent** component);


// pour les fonctions addTokenFunction, comeBackFunction et deleteTokenFunction...


// A rajouter dans le .h...

void setInitRenderer(SDL_Renderer **renderer,SDL_Window** windows);

void setImgSurf(SDL_Surface** surf,const char* f);

void setInitTexture(SDL_Texture** t ,SDL_Renderer** r,SDL_Surface** img);


//extension 6... Window to show event rules

void createWindowExtensionSix(const char* f,SDL_Window **windows);

#endif
