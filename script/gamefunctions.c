/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>*/
/*#include <math.h>
#include <stdio.h>

#include "macros.h"
#include "globais.h"
#include "gamefunctions.h"
*/
#include "globais.h"

/*#define ARQUIVOdeRANKING "././ranking/hiscores.txt"*/

double distance(double x1,double x2, double y1, double y2){
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

bool checkColision(void){
	int i,j;
	for(i = 0;i < LINES;i++){
		for(j = 0;j < COLUMS;j++){
			if(game.Matrix[i][j].isShowing){
				if(distance(game.Matrix[i][j].PosX + IMGWIDTH/2,ActualBall.PosX + IMGWIDTH/2,game.Matrix[i][j].PosY + IMGWIDTH/2,ActualBall.PosY + IMGWIDTH/2) < 2*RADIUS){
					Mix_PlayChannel(-1, sound[1],0);
					return True;
				}
			}
		}
	}
	return False;
}

void generateNewLine(){
	int value;
	int i;
	srand(time(NULL));
	for(i = 0;i < COLUMS;i++){
		value = rand()%5;
		game.Matrix[0][i].image = gJPGSurface[value];
		game.Matrix[0][i].Color = value;
		game.Matrix[0][i].PosX = S_GIWIDTH + i*IMGWIDTH;
		game.Matrix[0][i].PosY = S_GIHEIGHT;
		game.Matrix[0][i].SpeedX = 0;
		game.Matrix[0][i].SpeedY = 0;
		game.Matrix[0][i].isMoving = False;
		game.Matrix[0][i].isShowing = True;
		game.Matrix[0][i].visited = False;
	}

}

int lowerLine(){
	int i,j;
	for(i = LINES - 2; i >= 0;i--){
		for(j = 0;j<COLUMS;j++){
			game.Matrix[i+1][j] = game.Matrix[i][j];
			game.Matrix[i+1][j].PosX = S_GIWIDTH + (j)*IMGWIDTH;
			game.Matrix[i+1][j].PosY = S_GIHEIGHT + (i+1)*IMGHEIGHT;
		}
	}
	game.lowestLine++;
	if(game.lowestLine == LINES){
		return 1;
	}
	generateNewLine();
	return 0;
}

int aproximate(){
	int i,j;
	int quit = 0;
	for(i = 0;i < LINES;i++){
		if(S_GIHEIGHT + i*IMGHEIGHT > ActualBall.PosY){
			break;
		}
		if(i == LINES - 1){
			return 1;
		}
	}
	for(j=0;j<COLUMS;j++){
		if(S_GIWIDTH + j*IMGWIDTH > ActualBall.PosX + IMGWIDTH/2){
			if(!game.Matrix[i][j-1].isShowing){
				break;
			}
			else{
				continue;
			}
		}
	}
	j--;
	if(game.Matrix[i][j].isShowing){
		if(ActualBall.SpeedX < 0){
			j++;
			if(game.Matrix[i][j].isShowing){
				j--;
			}
		}
		if(ActualBall.SpeedX > 0){
			j--;
			if(game.Matrix[i][j].isShowing){
				j++;
			}
		}
	}
		
	if(i > game.lowestLine){
		game.lowestLine = i;
	}
	game.Matrix[i][j].Color = ActualBall.Color;
	game.Matrix[i][j].image = ActualBall.image;
	game.Matrix[i][j].isShowing = True;
	if(countBall(i,j,game.Matrix[i][j].Color,0)){
		undoVisited();
		deleteBubble(i,j,game.Matrix[i][j].Color,0);
		undoVisited();
		deleteIsland();
		Mix_PlayChannel(-1, sound[2],0);
		checkLowest();
	}
	else{
		game.life--;
		if(!game.life){
			if(lowerLine()){
				return 1;
			}
			game.life = 5;
		}
	}
	undoVisited();
	return 0;
}

int countBall(int Pi, int Pj, int c,int secondRound){
	int i,j;
	int sameColorI,sameColorJ;
	int count = 1;
	game.Matrix[Pi][Pj].visited = 1;
	for(i = -1; i < 2;i++){
		for(j = -1;j < 2;j++){
			if(Pi + i < 0){
				continue;
			}
			if(Pi+i >= LINES){
				continue;
			}
			if(Pj+j<0){
				continue;
			}
			if(Pj+j>=COLUMS){
				continue;
			}
			if(game.Matrix[Pi+i][Pj+j].visited){
				continue;
			}
			game.Matrix[Pi+i][Pj+j].visited = 1;
			if(game.Matrix[Pi+i][Pj+j].Color == c && game.Matrix[Pi+i][Pj+j].isShowing){
				count++;
				sameColorI = Pi+i;
				sameColorJ = Pj+j;
			}
		}
	}
	if(!secondRound){
		if(count == 1){
			return 0;
		}
		else if(count > 2){
			return 1;
		}
		else{
			return countBall(sameColorI, sameColorJ, c,1);
		}
	}
	else{
		if(count == 1){
			return 0;
		}
		else{
			return 1;
		}
	}
}

int moveBALL() {
	ActualBall.PosX += ActualBall.SpeedX;
	ActualBall.PosY += ActualBall.SpeedY;
	
	if ( (ActualBall.PosX + IMGWIDTH >= S_GFWIDTH + S_GIWIDTH) || (ActualBall.PosX <= S_GIWIDTH) ) {
		ActualBall.SpeedX = -ActualBall.SpeedX;
		ActualBall.PosX += ActualBall.SpeedX;
		Mix_PlayChannel(-1, sound[1],0);
	}

	if (ActualBall.PosY <= S_GIHEIGHT||checkColision()){
		if(aproximate()){
			return 1;
		}
		ActualBall.SpeedY = 0;
		ActualBall.SpeedX = 0;
		ActualBall = NewBall;
		ActualBall.PosX = 25 + (S_GFWIDTH - IMGWIDTH)/2;
		ActualBall.PosY = (S_GFHEIGHT - IMGHEIGHT);
		NewBall = createBALL(30 + S_GIWIDTH, (S_GFHEIGHT - IMGHEIGHT),0,0,True);
	}
	return 0;
}

/*validação do click: se ele estiver abaixo do jance ele será invalido*/
bool checkValue(int x,int y,double*teta){
	double alfa = (180/pi)*atan2(-y+initY,-x+initX);
	*teta = (atan2(-y+initY,-x+initX));

	if(alfa < 8 || alfa > 172){
		return False;
	}
	return True;
}

/*associa o resuldado para o movimento e a bola que vai se mover*/
bool giveSpeed(double *v, BALL *p){

	if(!(p->isMoving)){
		return False;
	}

	p->SpeedX = (double)v[0]*2;
	p->SpeedY = (double)v[1]*2;
	p->isMoving = False;
	Mix_PlayChannel(-1, sound[0],0);

	return True;
}

double Module(int x,int y){
	return sqrt(x*x + y*y);
}

double *generateSpeed(int x,int y,double teta){
	double *speedReturn;
	speedReturn = (double*)malloc(2*sizeof(double));
	if(!speedReturn){
		return 0;
	}

	
	speedReturn[0] = -2*cos(teta);
	speedReturn[1] = -2*sin(teta);

	return speedReturn;
}

void InitializeMatrix(void){
	
	game.life = 5;
	game.score = 0;
	game.lowestLine = 0;
	
	int i,j;
	int value;
	srand(time(NULL));
	game.Matrix = (BALL**)malloc(LINES*sizeof(BALL*));
	if(!game.Matrix){
		exit(1);
	}
	for(i = 0;i < LINES;i++){
		game.Matrix[i] = (BALL*)malloc(COLUMS*sizeof(BALL));
		if(!game.Matrix[i]){
			exit(1);
		}
		if(!i){
			for(j = 0;j < COLUMS;j++){
				value = rand()%5;
				game.Matrix[i][j].image = gJPGSurface[value];
				game.Matrix[i][j].Color = value;
				game.Matrix[i][j].PosX = S_GIWIDTH + j*IMGWIDTH;
				game.Matrix[i][j].PosY = S_GIHEIGHT + i*IMGHEIGHT;
				game.Matrix[i][j].SpeedX = 0;
				game.Matrix[i][j].SpeedY = 0;
				game.Matrix[i][j].isMoving = False;
				game.Matrix[i][j].isShowing = True;
				game.Matrix[i][j].visited = False;
			}
		}
		else{
			for(j = 0;j < COLUMS;j++){
				game.Matrix[i][j].image = NULL;
				game.Matrix[i][j].PosX = S_GIWIDTH + j*IMGWIDTH;
				game.Matrix[i][j].PosY = S_GIHEIGHT + i*IMGHEIGHT;
				game.Matrix[i][j].SpeedX = 0;
				game.Matrix[i][j].SpeedY = 0;
				game.Matrix[i][j].isMoving = False;
				game.Matrix[i][j].isShowing = False;
				game.Matrix[i][j].visited = False;
			}
		}
	}
}

BALL createBALL( double PosX, double PosY, double SpeedX, double SpeedY, bool isMoving) {
	BALL p;
	int value = rand()%5;

	srand(time(NULL));
	
	
	p.Color = value;
	p.PosX = PosX;
	p.PosY = PosY;
	p.SpeedX = SpeedX;
	p.SpeedY = SpeedY;
	p.image = gJPGSurface[value];
	p.isShowing = 1;
	p.isMoving = isMoving;
	return p;
}

void undoVisited(){
	int i,j;
	for(i=0;i<LINES;i++){
		for(j=0;j<COLUMS;j++){
			game.Matrix[i][j].visited = False;
		}
	}
}

bool deleteBubble(int i,int j,int c,int flag){
	
	game.Matrix[i][j].visited = 1;
	
	if((game.Matrix[i][j].Color != c && !flag) || !game.Matrix[i][j].isShowing){
		return False;
	}
	
	if((game.Matrix[i][j].Color == c || flag) && game.Matrix[i][j].isShowing){
		game.score += 10;
		game.Matrix[i][j].isShowing = False;
	}
	
	if(i < LINES - 1){
		if(!game.Matrix[i+1][j].visited){
			deleteBubble(i+1,j,c,flag);
		}
	}
	
	if(i > 0){
		if(!game.Matrix[i-1][j].visited){
			deleteBubble(i-1,j,c,flag);
		}
	}
	
	if(j < COLUMS - 1){
		if(!game.Matrix[i][j+1].visited){
			deleteBubble(i,j+1,c,flag);
		}
	}
	
	if(j > 0){
		if(!game.Matrix[i][j-1].visited){
			deleteBubble(i,j-1,c,flag);
		}
	}
	if((i < LINES - 1) && (j < COLUMS - 1)){
		if(!game.Matrix[i+1][j+1].visited){
			deleteBubble(i+1,j+1,c,flag);
		}
	}
	
	if((i < LINES - 1) && (j > 0)){
		if(!game.Matrix[i+1][j-1].visited){
			deleteBubble(i+1,j-1,c,flag);
		}
	}
	
	if((i > 0) && (j < COLUMS - 1)){
		if(!game.Matrix[i-1][j+1].visited){
			deleteBubble(i-1,j+1,c,flag);
		}
	}
	
	if((i > 0) && (j > 0)){
		if(!game.Matrix[i-1][j-1].visited){
			deleteBubble(i-1,j-1,c,flag);
		}
	}
}

bool checkBubble(int i,int j){
	
	int teste = 0;
	
	game.Matrix[i][j].visited = 1;
	
	if(!game.Matrix[i][j].isShowing){
		return False;
	}
	
	if(!i && game.Matrix[i][j].isShowing){
		return True;
	}
	
	if(i < LINES - 1){
		if(!game.Matrix[i+1][j].visited){
			teste += checkBubble(i+1,j);
		}
	}
	
	if(i > 0){
		if(!game.Matrix[i-1][j].visited){
			teste += checkBubble(i-1,j);
		}
	}
	
	if(j < COLUMS - 1){
		if(!game.Matrix[i][j+1].visited){
			teste += checkBubble(i,j+1);
		}
	}
	
	if(j > 0){
		if(!game.Matrix[i][j-1].visited){
			teste += checkBubble(i,j-1);
		}
	}
	
	if((i < LINES - 1) && (j < COLUMS - 1)){
		if(!game.Matrix[i+1][j+1].visited){
			teste += checkBubble(i+1,j+1);
		}
	}
	
	if((i < LINES - 1) && (j > 0)){
		if(!game.Matrix[i+1][j-1].visited){
			teste += checkBubble(i+1,j-1);
		}
	}
	
	if((i > 0) && (j < COLUMS - 1)){
		if(!game.Matrix[i-1][j+1].visited){
			teste += checkBubble(i-1,j+1);
		}
	}
	
	if((i > 0) && (j > 0)){
		if(!game.Matrix[i-1][j-1].visited){
			teste += checkBubble(i-1,j-1);
		}
	}
	
	return teste;
	
}

void deleteIsland(){
	int i,j;
	for(i = 1;i < LINES;i++){
		for(j = 0;j<COLUMS;j++){
			if(game.Matrix[i][j].isShowing){
				if(!checkBubble(i,j)){
					undoVisited();
					deleteBubble(i,j,0,1);
					undoVisited();
				}
				undoVisited();
			}
		}
	}
}

void writeName(int key,char*name){
	switch(key){
		case SDLK_a:
			strcat(name,"A");
			break;
		case SDLK_b:
			strcat(name,"B");
			break;
		case SDLK_c:
			strcat(name,"C");
			break;
		case SDLK_d:
			strcat(name,"D");
			break;
		case SDLK_e:
			strcat(name,"E");
			break;
		case SDLK_f:
			strcat(name,"F");
			break;
		case SDLK_g:
			strcat(name,"G");
			break;
		case SDLK_h:
			strcat(name,"H");
			break;
		case SDLK_i:
			strcat(name,"I");
			break;
		case SDLK_j:
			strcat(name,"J");
			break;
		case SDLK_k:
			strcat(name,"K");
			break;
		case SDLK_l:
			strcat(name,"L");
			break;
		case SDLK_m:
			strcat(name,"M");
			break;
		case SDLK_n:
			strcat(name,"N");
			break;
		case SDLK_o:
			strcat(name,"O");
			break;
		case SDLK_p:
			strcat(name,"P");
			break;
		case SDLK_q:
			strcat(name,"Q");
			break;
		case SDLK_r:
			strcat(name,"R");
			break;
		case SDLK_s:
			strcat(name,"S");
			break;
		case SDLK_t:
			strcat(name,"T");
			break;
		case SDLK_u:
			strcat(name,"U");
			break;
		case SDLK_v:
			strcat(name,"V");
			break;
		case SDLK_w:
			strcat(name,"W");
			break;
		case SDLK_x:
			strcat(name,"X");
			break;
		case SDLK_y:
			strcat(name,"Y");
			break;
		case SDLK_z:
			strcat(name,"Z");
			break;
		case SDLK_BACKSPACE:
			name[strlen(name) - 1] = '\0';
			break;
	}
}

int lowScore(){
	FILE*arq;
	if(!arq){return 1;}
	int i;
	char array[30];
	char nameDummy[15];
	int lowest;
	arq = fopen("././ranking/hiscores.txt","r");
	for(i = 0; i < 10;i++){
		fgets(array,30,arq);
	}
	sscanf(array,"%s %d",nameDummy,&lowest);
	fclose(arq);
	return lowest;
}

void registerScore(int score, char*name){
	PLAYER player[11];
	PLAYER temp;
	char line[30];
	int i,j=0;
	FILE *arq;
	arq = fopen("././ranking/hiscores.txt","r");
	if(!arq){exit(1);}

	for(i = 0;i < 11;i++){
		player[i].name = (char*)malloc(16*sizeof(char));
		fgets(line,30,arq);
		sscanf(line,"%s %d",player[i].name, &player[i].score);
		printf("%d\n",player[i].score );
	}
	player[10].name = name;
	player[10].score = score;

	for(i = 0;i < 10;i++){
		printf("%d \t%d \t%d\n",j,i,player[i].score );
		if(player[i+1].score > player[i].score){
			temp = player[i];
			player[i] = player[i+1];
			player[i+1] = temp;
			i =-1;
		}
		j++;
	}
	fclose(arq);
	arq = fopen("././ranking/hiscores.txt","w");
	for(i = 0;i < 10;i++){
		fprintf(arq,"%s  %d\n",player[i].name,player[i].score);
		printf("# %d\n",player[i].score );
	}
	fclose(arq);
}

int checkLowest(){
	int i,j;
	for(i = LINES - 1;i > 0;i--){
		for(j = 0; j < COLUMS;j++){
			if(game.Matrix[i][j].isShowing){
				game.lowestLine = i;
				return 0;
			}
		}
	}
	return 0;
}
				