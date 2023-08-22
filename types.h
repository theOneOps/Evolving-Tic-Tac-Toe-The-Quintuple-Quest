#ifndef MORPION36_TYPES_H
#define MORPION36_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL.h"

#define X 20//8
#define Y 20//8
#define NB_IMAGES 3
#define tailleImg 30//40

//tailleImg -> est la taille en pixels de mes cercles/croix du rendu...


typedef struct player
{
    char team;// le signe du player (X ou O)
    bool robot;//boolean pour savoir si c'est un bot ou non
    int countNbQuintuplet;//le nombre de quintuplet formé pat le joueur
    int countQuintupletPossible;//le nombre de quintuplet encore possible de former
}player;

//masquage de player*

typedef player* typePlayer;

typedef struct pos{
    int posX;
    int posY;
}pos;

//La structure du token

typedef struct token
{
    char sign; // 'X' ou 'O' , '_' si vide
    int value_r;
    int value_c;
    pos position;//position de la case
    bool filled;//booolean pour savoir si la case est vide ou non
    bool countOne;//boolean pour savoir si cette case est déjà compter pour un premier quintuplet
    bool countTwo;//.... pour un second quintuplet
    bool threeCaseValid;//boolean pour faire passer le bg de la case en gris s'il compte pour un quintuplet
}token;

//masquage de token*
typedef token* caseType;

//masquage de token**
typedef token** caseTypeAdr;

//structure de grille dont les cases sont de type de token*

typedef token*** game_tab;


//structure du composant de la SDL

typedef struct sdlComponent
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface * pWinSurf;
}sdlComponent;

typedef sdlComponent** compSdl;

#endif //MORPION36_TYPES_H
