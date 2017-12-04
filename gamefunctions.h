#ifndef GAMEFUNC_H
#define GAMEFUNC_H

/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>*/

/*#include "macros.h"*/
#include "globais.h"

void InitializeMatrix(void);
BALL createBALL( double PosX, double PosY, double SpeedX, double SpeedY,bool isMoving);
double distance(double x1,double x2,double y1, double y2);
void generateNewLine(void);
int lowerLine(void);
void undoVisited(void);
int countBall(int Pi, int Pj, int c,int secondRound);
bool deleteBubble(int i,int j,int c,int flag);
bool checkBubble(int i,int j);
void deleteIsland(void);
int checkLowest(void);
int aproximate(void);
bool checkColision(void);
int moveBALL(void);
bool checkValue(int x,int y,double*t);
double Module(int x,int y);
double *generateSpeed(int x, int y,double teta);
bool giveSpeed(double *v, BALL*p);
void writeName(int key,char*name);
int lowScore(void);
void registerScore(int score, char*name);
#endif