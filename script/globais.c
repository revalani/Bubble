/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>*/
/*
#include "macros.h"*/
#include "globais.h"

BALL NewBall;
BALL ActualBall;
GAME game;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gJPGSurface[10];

BUTTON Button[4];

Mix_Music* music;
Mix_Chunk* sound[3]; 
int VOLUME = 0;

TTF_Font*font;
SDL_Color ttfColor;
SDL_Surface* surfaceMessage;
SDL_Texture* Message;
SDL_Rect Message_rect;