#define SDL_MAIN_HANDLED
#include "globais.h"

/*#include <SDL2/SDL.h>
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
#include "gamefunctions.h"*/

void gameplay(){
	double *SpeedVector;
	int ArrowX, ArrowY;
	SDL_Rect srcRect, dstRect;
	SDL_Event Event;
	bool quit = False, kill = False;
	bool action;
	double teta;
	char*name = (char*)calloc(15,sizeof(char));
	int count = 0;
	char str[10];
	int i,j;
	
	ActualBall = createBALL(IMGWIDTH/2 + (S_GFWIDTH - IMGWIDTH)/2 , (S_GFHEIGHT - IMGHEIGHT),0,0,True);
	NewBall = createBALL(30 + S_GIWIDTH, (S_GFHEIGHT - IMGHEIGHT),0,0,True);
	InitializeMatrix();
	loadMusic(2);
	Mix_PlayMusic(music,-1);
	font = TTF_OpenFont("././fonts/vinivicious.ttf",24);
	if (!font) {
		printf("Nao consegui carregar fonte. %s\n", TTF_GetError());
		exit(1);
	}
	Message_rect.x = 250; Message_rect.y = 50;
	ttfColor.r = 0; ttfColor.g = 0; ttfColor.b = 0;
	while( !quit && !kill ){		
		while( SDL_PollEvent( &Event ) != 0 ) {
			switch (Event.type) {
				case SDL_QUIT:
					closing();
					exit(1);
				break;
				case SDL_KEYDOWN:
					if (Event.key.keysym.sym == SDLK_ESCAPE) {
						kill = True;
					}
					if (Event.key.keysym.sym == SDLK_m) {
						Button[3].big = !Button[3].big;
						Music();
					}
				break;

				case SDL_MOUSEBUTTONDOWN:
					if(Event.button.button == SDL_BUTTON_LEFT){
						SDL_GetMouseState(&ArrowX,&ArrowY);
						action = checkValue(ArrowX,ArrowY,&teta);
						if(action){

							SpeedVector = generateSpeed(ArrowX,ArrowY,teta);

							if(!SpeedVector){
								exit(1);
							}
							giveSpeed(SpeedVector,&ActualBall);
						}
					}
				break;
			}
		}
		count = (SDL_GetTicks() / 150) % 4;
		srcRect.x = 800*(count%4); srcRect.y = 0;
		srcRect.w = 800;
		srcRect.h = 630;
		dstRect.x = 0;
		dstRect.y = 0;
		SDL_BlitSurface( gJPGSurface[5], &srcRect,gScreenSurface, &dstRect );
		quit = moveBALL();
		srcRect.x = IMGWIDTH*(count%4); srcRect.y = 0;
		srcRect.w = IMGWIDTH;
		srcRect.h = IMGHEIGHT;
		
		for(i=0;i<LINES;i++){
			for(j=0;j<COLUMS;j++){
				dstRect.x = game.Matrix[i][j].PosX;
				dstRect.y = game.Matrix[i][j].PosY;
				if(game.Matrix[i][j].isShowing){
					if( SDL_BlitSurface( game.Matrix[i][j].image, &srcRect,gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
						quit = True;
					}
				}
			}
		}
		dstRect.x = ActualBall.PosX;
		dstRect.y = ActualBall.PosY;
		if( SDL_BlitSurface( ActualBall.image, &srcRect,gScreenSurface, &dstRect ) < 0 ) {
			printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
			quit = True;
		}
		
		dstRect.x = NewBall.PosX;
		dstRect.y = NewBall.PosY;
		if( SDL_BlitSurface( NewBall.image, &srcRect,gScreenSurface, &dstRect ) < 0 ) {
			printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
			quit = True;
		}
		Message_rect.x = 640; Message_rect.y = 120;
		Message_rect.w = 200; Message_rect.h = 100;
		snprintf(str,sizeof(str),"%d",game.score);
		surfaceMessage = TTF_RenderText_Solid( font , str , ttfColor );
		SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
		SDL_FreeSurface(surfaceMessage);

		Message_rect.x = 650; Message_rect.y = 200;
		Message_rect.w = 200; Message_rect.h = 100;
		snprintf(str,sizeof(str),"%d",game.life);
		surfaceMessage = TTF_RenderText_Solid( font , str , ttfColor );
		SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
		SDL_FreeSurface(surfaceMessage);

		Message_rect.x = 618; Message_rect.y = 200;
		Message_rect.w = 50; Message_rect.h = 50;
		surfaceMessage = TTF_RenderText_Solid( font , "L" , ttfColor );
		SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
		SDL_FreeSurface(surfaceMessage);
  		/*atualiza a imagem que será exibida na tela*/
		SDL_UpdateWindowSurface( gWindow );


		
		SDL_Delay(0);
	}
	TTF_CloseFont(font);
	/*Tela de Nomeacao do jogador*/
	if(lowScore() < game.score){
		quit = 0;
		ttfColor.r = 245; ttfColor.g = 245; ttfColor.b = 245;
		font = TTF_OpenFont("././fonts/pixelmix.ttf",18);
		while(!quit){
			while( SDL_PollEvent( &Event ) != 0 ) {
				switch (Event.type) {
					case SDL_QUIT:
						closing();
						exit(1);
					break;
					case SDL_KEYDOWN:
						writeName(Event.key.keysym.sym,name);
						if (Event.key.keysym.sym == SDLK_ESCAPE) {
							quit = 1;
						}
						if(Event.key.keysym.sym == SDLK_RETURN){
							quit = 1;
						}
					break;
				}
			}

			SDL_FillRect( gScreenSurface, NULL, SDL_MapRGB( gScreenSurface->format, 0, 0, 0));
			SDL_BlitSurface( NULL, NULL,gScreenSurface, NULL );

			/*texto grande*/
			font = TTF_OpenFont("././fonts/vinivicious.ttf",30);
			Message_rect.x = (S_WIDTH/2)-100; Message_rect.y = 50;
			surfaceMessage = TTF_RenderText_Solid( font , "Game Over" , ttfColor );
			SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
			TTF_CloseFont(font);
			SDL_FreeSurface(surfaceMessage);
			font = TTF_OpenFont("././fonts/vinivicious.ttf",20);
			Message_rect.x = (S_WIDTH/2)-130; Message_rect.y = 80;
			surfaceMessage = TTF_RenderText_Solid( font , "Escreva o seu Nome:" , ttfColor );
			SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
			TTF_CloseFont(font);
			SDL_FreeSurface(surfaceMessage);
			
			
			/*Nome do jogador*/
			font = TTF_OpenFont("././fonts/vinivicious.ttf",22);
			surfaceMessage = TTF_RenderText_Solid( font ,name, ttfColor );
			Message_rect.x = (S_WIDTH/2)-(8*strlen(name)); 
			Message_rect.y = 300;
			Message_rect.w = 50 /*+ 18*strlen(name)*/; 
			Message_rect.h = 50;
			SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
			TTF_CloseFont(font);
			SDL_FreeSurface(surfaceMessage);
			SDL_UpdateWindowSurface( gWindow );
		}
		registerScore(game.score,name);
	}
}	

void records(){
	SDL_Rect srcRect, dstRect;
	SDL_Event Event;
	int ArrowX, ArrowY;
	int count;
	int quit = 0;
	int i;
	char*array = (char*)malloc(29*sizeof(char));
	int score;
	char str[15];
	FILE*arq;
	arq = fopen("././ranking/hiscores.txt","r");
	if(!arq){exit(1);}
	
	font = TTF_OpenFont("././fonts/vinivicious.ttf",48);
	if (!font) {
		printf("Nao consegui carregar fonte. %s\n", TTF_GetError());
		exit(1);
	}
	while(!quit){
		SDL_GetMouseState(&ArrowX,&ArrowY);
		while( SDL_PollEvent( &Event ) != 0 ) {
			switch (Event.type) {
				case SDL_QUIT:
					closing();
					exit(1);
				break;
				case SDL_KEYDOWN:
					if (Event.key.keysym.sym == SDLK_ESCAPE) {
						quit = True;
					}
				break;

				case SDL_MOUSEBUTTONDOWN:
					if(Event.button.button == SDL_BUTTON_LEFT){
						if( 50<= ArrowX && ArrowX <= 259 && 500 <= ArrowY && ArrowY <= 600){
							Mix_PlayChannel(-1, sound[1],0);
							quit = 1;
						}
					}
					break;
			}
		}
		count = (SDL_GetTicks() / 150) % 18;
		srcRect.x = count*800; srcRect.y = 0;
		srcRect.w = S_WIDTH;
		srcRect.h = S_HEIGHT;
		dstRect.x = 0;
		dstRect.y = 0;
		SDL_BlitSurface( gJPGSurface[1], &srcRect,gScreenSurface, &dstRect );
		Message_rect.x = 250; Message_rect.y = 50;
		Message_rect.w = 400; Message_rect.h = 150;
		ttfColor.r = 245; ttfColor.g = 245; ttfColor.b = 245;
		surfaceMessage = TTF_RenderText_Solid( font , "HI-SCORES" , ttfColor );
		SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
		TTF_CloseFont(font);
		SDL_FreeSurface(surfaceMessage);
		font = TTF_OpenFont("././fonts/vinivicious.ttf",18);
		for(i = 0; i < 10;i++){
			fscanf(arq,"%s %d",array,&score);
			snprintf(str,sizeof(str),"%d",score);
			strcat(array,"  "); strcat(array,str);
			surfaceMessage = TTF_RenderText_Solid( font ,array, ttfColor );
			Message_rect.x = 350; Message_rect.y = 120 + 30*i;
			Message_rect.w = 200; Message_rect.h = 50;
			SDL_BlitSurface( surfaceMessage , NULL , gScreenSurface , &Message_rect );
			SDL_FreeSurface(surfaceMessage);
		}
		rewind(arq);
		srcRect.x = 0; srcRect.y = 0;
		srcRect.w = 209;srcRect.h = 100;
		dstRect.x = 50;
		dstRect.y = 500;
		SDL_BlitSurface( gJPGSurface[0], &srcRect,gScreenSurface, &dstRect );
		SDL_UpdateWindowSurface( gWindow );
		TTF_CloseFont(font);
		font = TTF_OpenFont("././fonts/vinivicious.ttf",48);
	}
	free(font);
	fclose(arq);
}

	
int main(int argc, char** argv){
	SDL_Rect srcRect, dstRect;
	SDL_Event Event;
	int ArrowX, ArrowY;
	int quit = 0;
	int count;
	int i;
	int played[3];
	for (i = 0; i < 3; i++){
		played[i] = 0;
	}
	if( !Initialize() ) {
		printf( "Failed to initialize!\n" );
		return 1;
	}
	loadMedia(1);
	initButtons();
	loadSound(1);
	loadMusic(1);
	Mix_PlayMusic(music,-1);
	while(!quit){
		SDL_GetMouseState(&ArrowX,&ArrowY);
		for(i = 0;i < 4;i++){
			switch(i){
				case 0:
				case 1:
				case 2:
					if(ArrowX >= Button[i].PosX1 && ArrowX <= Button[i].PosX2 && ArrowY >= Button[i].PosY1 && ArrowY <= Button[i].PosY2){
						Button[i].PosX1 = X1SIZEBIG;
						Button[i].PosX2 = X2SIZEBIG;
						Button[i].PosY1 = Y1SIZEBIG + i*INTERVAL;
						Button[i].PosY2 = Y2SIZEBIG + i*INTERVAL;
						Button[i].onButton = True;
						Button[i].big = True;
						if(played[i] == 0){
							Mix_PlayChannel(-1, sound[0],0);
							played[i] = 1;
						}
					}
					else{
						Button[i].PosX1 = X1SIZESMALL;
						Button[i].PosX2 = X2SIZESMALL;
						Button[i].PosY1 = Y1SIZESMALL + i*INTERVAL;
						Button[i].PosY2 = Y2SIZESMALL + i*INTERVAL;
						Button[i].onButton = False;
						Button[i].big = False;
						played[i] = 0;
					}
					break;
				case 3:
					if(ArrowX >= Button[i].PosX1 && ArrowX <= Button[i].PosX2 && ArrowY >= Button[i].PosY1 && ArrowY <= Button[i].PosY2){
						Button[i].onButton = True;
					}
					else{
						Button[i].onButton = False;
					}
					break;
			}
		}
		while( SDL_PollEvent( &Event ) != 0 ) {
			switch (Event.type) {
				case SDL_QUIT:
					quit = True;
				break;
				case SDL_KEYDOWN:
					if (Event.key.keysym.sym == SDLK_ESCAPE) {
						quit = True;
					}
				break;

				case SDL_MOUSEBUTTONDOWN:
					if(Event.button.button == SDL_BUTTON_LEFT){
						for(i = 0;i < 4;i++){
							if(Button[i].onButton){
								Mix_PlayChannel(-1, sound[1],0);
								switch(i){
									case 0:
										SDL_Delay(1000);
										freeSurfaces(1);
										loadMedia(3);
										Mix_FreeMusic(music);
										loadMusic(2);
										freeSound(1);
										loadSound(2);
										gameplay();
										freeSurfaces(3);
										loadMedia(1);
										freeSound(2);
										loadSound(1);
										Mix_FreeMusic(music);
										loadMusic(1);
										initButtons();
										Mix_PlayMusic(music,-1);
										break;
									case 1:
										freeSurfaces(1);
										loadMedia(2);
										records();
										freeSurfaces(2);
										loadMedia(1);
										initButtons();
										break;
									case 2:
										quit = True;
										break;
									case 3:
										Button[i].big = !Button[i].big;
										Music();
										break;
								}
							}
						}
					}
				break;
			}
		}
		/*SDL_BlitSurface( gJPGSurface[9], NULL, gScreenSurface, NULL );*/
		count = (SDL_GetTicks() / 150) % 12;
		srcRect.x = S_WIDTH*count; srcRect.y = 0;
		srcRect.w = S_WIDTH;
		srcRect.h = S_HEIGHT;
		dstRect.x = 0;
		dstRect.y = 0;
		SDL_BlitSurface( gJPGSurface[8], &srcRect,gScreenSurface, &dstRect );
		srcRect.x = 0; srcRect.y = 0;
		dstRect.x = 144; dstRect.y = 0;
		SDL_BlitSurface( gJPGSurface[9], &srcRect,gScreenSurface, &dstRect );
		srcRect.x = 0; srcRect.y = 0;
		for(i = 0;i < 4;i++){
			dstRect.x = Button[i].PosX1;
			dstRect.y = Button[i].PosY1;
			if(Button[i].big){
				if( SDL_BlitSurface( Button[i].imageBIG, &srcRect,gScreenSurface, &dstRect ) < 0 ) {
					printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					quit = True;
				}
			}
			else{
				if( SDL_BlitSurface( Button[i].imageSMALL, &srcRect,gScreenSurface, &dstRect ) < 0 ) {
					printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					quit = True;
				}
			}
		}
		SDL_UpdateWindowSurface( gWindow );
	}
	closing();
	return 0;
}
