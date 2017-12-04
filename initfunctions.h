#ifndef INIT_H
#define INIT_H

/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>*/
/*
#include "macros.h"*/
#include "globais.h"

bool Initialize(void);
SDL_Surface* loadSurface( char *path,int flag );
int loadMedia(int flag);
void freeSurfaces(int flag);
void closing(void);
void initButtons(void);
void Music(void);
void loadSound(int flag);
void loadMusic(int flag);
void freeSound(int flag);

#endif