/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>*/

/*#include "macros.h"
#include "globais.h"
#include "initfunctions.h"*/
#include "globais.h"

void initButtons(){
	int i;
	for(i = 0;i < 4;i++){
		switch(i){
			case 0:
			case 1:
			case 2:
				Button[i].PosX1 = X1SIZESMALL;
				Button[i].PosX2 = X2SIZESMALL;
				Button[i].PosY1 = Y1SIZESMALL + i*INTERVAL;
				Button[i].PosY2 = Y2SIZESMALL + i*INTERVAL;
				Button[i].onButton = False;
				Button[i].big = False;
				Button[i].imageSMALL = gJPGSurface[2*i];
				Button[i].imageBIG = gJPGSurface[2*i + 1];
				break;
			case 3:
				Button[i].PosX1 = X1AUDIO;
				Button[i].PosX2 = X2AUDIO;
				Button[i].PosY1 = Y1AUDIO;
				Button[i].PosY2 = Y2AUDIO;
				Button[i].onButton = False;
				Button[i].imageSMALL = gJPGSurface[2*i];
				Button[i].imageBIG = gJPGSurface[2*i + 1];
				break;
		}
	}
}

int Initialize() {
	bool success = True;

	srand(time(NULL));

	if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = False;
	}
	else {
		TTF_Init();
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT, 2,4096);
		Mix_AllocateChannels(4);
		VOLUME =  MIX_MAX_VOLUME;
		gWindow = SDL_CreateWindow("Bubble Shooter ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = False;
		}
		else {
			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = False;
			}
			else {
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}



	return success;
}

int loadMedia(int flag) {
	bool success = True;
	int i;
	int n;
	switch(flag){
		case 1:
			n = 10;
			gJPGSurface[0] = loadSurface( "././img/PLAY.png" ,1);
			gJPGSurface[1] = loadSurface( "././img/PLAYBIG.png" ,1);
			gJPGSurface[2] = loadSurface( "././img/HISCORE.png" ,1);
			gJPGSurface[3] = loadSurface( "././img/HISCOREBIG.png" ,1);
			gJPGSurface[4] = loadSurface( "././img/EXIT.png" ,1);
			gJPGSurface[5] = loadSurface( "././img/QUITBIG.png" ,1);
			gJPGSurface[6] = loadSurface( "././img/AUDIO.png" ,1);
			gJPGSurface[7] = loadSurface( "././img/MUTE.png" ,1);
			gJPGSurface[8] = loadSurface( "././img/menuBG.png" ,0);
			gJPGSurface[9] = loadSurface( "././img/bbs.png" ,1);
			break;
		case 2:
			n = 2;
			gJPGSurface[0] = loadSurface( "././img/RETURN.png" ,1);
			gJPGSurface[1] = loadSurface( "././img/hiscoresBG.png" ,0);
			break;
		case 3:
			n = 6;
			gJPGSurface[0] = loadSurface( "././img/bola_vermelha.png" ,1);
			gJPGSurface[1] = loadSurface( "././img/bola_verde.png" ,1);
			gJPGSurface[2] = loadSurface( "././img/bola_amarela.png" ,1);
			gJPGSurface[3] = loadSurface( "././img/bola_azul.png" ,1);
			gJPGSurface[4] = loadSurface( "././img/bola_branca.png" ,1);
			gJPGSurface[5] = loadSurface( "././img/gameBG.png" ,0);
			break;
	}
	for(i = 0;i < n;i++){
		if( gJPGSurface[i] == NULL ) {
			printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
			success = False;
		}
	}		
	return success;
}


void freeSurfaces(int flag){
	int i;
	int n;
	switch(flag){
		case 1:
			n = 10;
			break;
		case 2:
			n = 2;
			break;
		case 3:
			n = 6;
			break;
	}
	for(i = 0;i<n;i++){
		SDL_FreeSurface( gJPGSurface[i] );
		gJPGSurface[i] = NULL;
	}
}

void closing() {
	int i;
	for(i = 0;i<9;i++){
		SDL_FreeSurface( gJPGSurface[i] );
		gJPGSurface[i] = NULL;
	}
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( char *path,int flag ) {
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else {
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}
		else{
			if(flag){
				Uint32 colorkey = SDL_MapRGBA( optimizedSurface->format, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_SetColorKey( optimizedSurface,1, colorkey );
			}
		}
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

void Music(){
	if(VOLUME == 0){
		Mix_ResumeMusic();
		VOLUME = 1;
	}
	else{
		Mix_PauseMusic();
		VOLUME = 0;
	}
}

void loadSound(int flag){
	int i;
	int n;
	switch(flag){
		case 1:
			n = 2;
			sound[0] = Mix_LoadWAV("././sounds/hoverButton.mp3");
			sound[1] = Mix_LoadWAV("././sounds/clickButton.mp3");
			break;
		case 2:
			n = 3;
			sound[0] = Mix_LoadWAV("././sounds/lauchBall.mp3");
			sound[1] = Mix_LoadWAV("././sounds/colideBall.mp3");
			sound[2] = Mix_LoadWAV("././sounds/deleteBall.mp3");
			break;
	}
	for(i = 0;i < n;i++){
		Mix_VolumeChunk(sound[i],MIX_MAX_VOLUME);
	}
}

void loadMusic(int flag){
	int i;
	switch(flag){
		case 1:
			music = Mix_LoadMUS("././sounds/menuMusic.mp3");
			break;
		case 2:
			music = Mix_LoadMUS("././sounds/gameMusic.mp3");
	}
}

void freeSound(int flag){
	int i;
	int n;
	switch(flag){
		case 1:
			n = 2;
			break;
		case 2:
			n = 3;
			break;
	}
	for(i = 0;i < n;i++){
		Mix_FreeChunk(sound[i]);
	}
}