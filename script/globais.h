
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "macros.h"
#include "initfunctions.h"
#include "gamefunctions.h"
#include "macros.h"

#ifndef GLOBAIS_H
#define GLOBAIS_H



typedef struct _BUTTON{
	int PosX1,PosX2,PosY1,PosY2;
	bool onButton;
	bool big;
	SDL_Surface* imageSMALL;
	SDL_Surface* imageBIG;
} BUTTON;

typedef struct _BALL{
	int Color;
	double PosX, PosY;
	double SpeedX, SpeedY;
	bool isMoving;
	bool isShowing;
	SDL_Surface* image;
	bool visited;
} BALL;

typedef struct _GAME{
	BALL**Matrix;
	int life;
	int score;
	int lowestLine;
} GAME;

typedef struct _PLAYER{
	char*name;
	int score;
} PLAYER;

extern int alternate;

extern BALL NewBall;
extern BALL ActualBall;
extern GAME game;

extern BUTTON Button[];

extern SDL_Window* gWindow;
extern SDL_Surface* gScreenSurface;
extern SDL_Surface* gJPGSurface[];

extern Mix_Music* music;
extern Mix_Chunk* sound[]; 
extern int VOLUME;

extern TTF_Font*font;
extern SDL_Color ttfColor;
extern SDL_Surface* surfaceMessage;
extern SDL_Rect Message_rect;

#endif