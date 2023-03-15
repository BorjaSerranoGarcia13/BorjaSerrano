#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/time.h>
#include <esat/sprite.h>

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "base_datos.cc"
#include "lista_disparos.cc"

unsigned char fps=25;
double current_time,last_time;
const int WindowX=800, WindowY=600;

struct TShoot{
	TCoord position;
	int count_alive;
};

struct TExplosion{
	TCoord position;
	int count_explosion;
	bool alive;
	esat::Vec2 direction;
};

struct TPlayer{
	TCoord position, last_position, initial_position;
	TShoot shoot;
	TExplosion *explosion=NULL;
	float gravity, speed, acceleration,
		rotation, scale;
	int lifes, score, fuel, bonus, total_shots, last_screen, count_speed, n_explosion,destroyed_turrets, exploding_count, next_ship;
	bool turbo, exploding, alive, shield, complete_map, reactor, record_score;
	//esat::Vec2 direction;	
};

struct TStars{
	TCoord position;
	int aparition, rgb[3];
	bool alive;
};

struct TPlanet{
	TCoord position;
};

struct TEnemy{
	TCoord position, last_position;
	TShoot shoot;
	float speed;
	bool alive, shooting;	
	esat::Vec2 shoot_direction;
};

struct TScore{
	int number;
	int position;
	char user[60];
};

TScore *score=NULL;

TPlayer player;
TNodo *shot=NULL;
TStars *stars=NULL;
TPlanet *planet=NULL;
TEnemy *enemy=NULL;

int *planet_alive=NULL, *planet_bonus=NULL, count_bonus=0;
float *count_figure=NULL;
float scale_map=0, planet_speed=0.02;
bool zoomin=false, zoomout=false, zoomleft=false,zoomright=false;
float counttt=0;
float ppp=0, pppp=0;
bool start=false, change_ss=false, new_ss=false;
//TAREAS
/*
PARA JUEVES
torretas disparan donde sea
arreglar zoom y asi torretas disparan

PLAYER
- Fuel-- falta recoger fuel
- Score

ENEMIGOS
- Disparo
- Muerte
- Movimiento

MAPA
- Zoom

2player
vari en el +0 poner jj o lo que sea y manejar de ahi que jj cambie cuando quiera el 2 player y cambiar color a nave, asi manejp
puntuacion vidas etc etc

*/

// ALL INIS
void IniBonus(){
	planet_bonus=(int*)calloc(8,sizeof(int));
	if(screen==4){
		*(planet_bonus+0)=8000;
		*(planet_bonus+1)=2000;
		*(planet_bonus+2)=9000;
		*(planet_bonus+3)=6000;
		*(planet_bonus+4)=4000;
	}else if(screen==12){
		*(planet_bonus+0)=9000;
		*(planet_bonus+1)=9000;
		*(planet_bonus+2)=9000;
		*(planet_bonus+3)=9000;
		*(planet_bonus+4)=9000;
		
	}else if(screen==13){
		*(planet_bonus+0)=9000;
		*(planet_bonus+1)=9000;
		*(planet_bonus+2)=9000;
		*(planet_bonus+3)=9000;
		
	}
}

void IniPlayer(){
	player.record_score=false;
	player.reactor=false;
	player.next_ship=10000;
	player.complete_map=false;
	player.destroyed_turrets=0;
	player.position.x=400;
	player.position.y=300;
	if(start==false){
		player.last_screen=4;
		player.last_position.x=400;
		player.last_position.y=398;
		player.score=0;
		player.fuel=10000;
		player.lifes=5;
		player.bonus=0;
	}
	player.rotation=0;
	player.scale=5;
	player.speed=0;
	player.acceleration=0;
	
	player.turbo=false;
	player.gravity=0;
	player.total_shots=0;
	player.count_speed=0;
	player.exploding=false;
	player.alive=true;
	player.exploding_count=0;
	d={0,-1};
	change_direction=d;
	player.shield=false;
	player.explosion=(TExplosion*)malloc(12*sizeof(TExplosion));
	for(int i=0;i<12;i++){
		(player.explosion+i)->alive=false;
		(player.explosion+i)->count_explosion=0;
	}
	if(primero!=NULL){
		shot=primero;
		while(shot!=NULL){
			VaciarLista(shot);
			shot=shot->prox;
		}
		player.total_shots=0;
	}
	start=true;
}

void IniFigures(){
	count_figure=(float*)calloc(20,sizeof(float));
	/*
	count+0 colores octagono inicio nave
	count+1 star o lineU	
	count+2 semiarrow grande y pequeño
	count+3 line size
	count+4 line large
	count+5 ring
	count+6 star
	count+7 maze
	count+8 octagon green
	count+9 eye animation
	count+10 star blue 5 points
	counbt+11 green octagon semicirle
	count+12 3 cirlces
	*/
}

void IniStars(){
	stars=(TStars*)malloc(400*sizeof(TStars));
	for(int i=0;i<1000;i++){
		stars->alive=false;
	}
}

void IniPlanet(){
	planet=(TPlanet*)malloc(15*sizeof(TPlanet));
	for(int i=0;i<15;i++){
		(planet+i)->position.x=400;
		(planet+i)->position.y=300;
	}
	scale_map=0;
	planet_speed=0.02;
	zoomin=false;
	zoomout=false;
	zoomleft=false;
	zoomright=false;
	counttt=0;
	ppp=0;pppp=0;
}

void IniEnemy(){
	enemy=(TEnemy*)malloc(16*sizeof(TEnemy));
	switch(screen){
		case 4: (enemy+0)->last_position.x=115;
				(enemy+0)->last_position.y=288;
				(enemy+1)->last_position.x=100-10;
				(enemy+1)->last_position.y=288;
				break;
		case 12: (enemy+0)->last_position.x=660;
				(enemy+0)->last_position.y=127;
				(enemy+1)->last_position.x=675-10;
				(enemy+1)->last_position.y=127;
				break;
		case 13: (enemy+0)->last_position.x=130;
				(enemy+0)->last_position.y=296;
				(enemy+1)->last_position.x=145-10;
				(enemy+1)->last_position.y=296;
				break;
	}
	(enemy+0)->position.x=400;
	(enemy+0)->position.y=300;
	(enemy+1)->position.x=400;
	(enemy+1)->position.y=300;
	(enemy+0)->alive=true;
	(enemy+0)->shooting=false;
	(enemy+0)->speed=2.5f;
	(enemy+0)->shoot.count_alive=0;
	(enemy+0)->shoot_direction={0,0};
	
	(enemy+1)->alive=true;
	(enemy+1)->shooting=false;
	(enemy+1)->speed=2.5f;
	(enemy+1)->shoot.count_alive=0;
	
	(enemy+2)->position.x=-60;
	(enemy+2)->position.y=100;
	(enemy+2)->alive=true;
	(enemy+2)->speed=2.5f;
	(enemy+3)->position.x=900;
	(enemy+3)->position.y=150;
	(enemy+3)->alive=true;
	(enemy+3)->speed=2.5f;
	
	for(int i=4;i<16;i++){
		(enemy+i)->alive=true;
		(enemy+i)->shooting=false;
		(enemy+i)->speed=2.5f;
		(enemy+i)->shoot.count_alive=0;
	}
}

void IniExplosion(){
	
}

void PlanetAlive(){
	planet_alive=(int*)calloc(8,sizeof(int));
}

void AllIni(){
	IniPlayer();
	IniFigures();
	IniStars();
	IniPlanet();
	IniEnemy();
	if(change_ss==false)PlanetAlive();
	change_ss=true;
	if(new_ss==false)IniBonus();
}


// COMMON FUNCTIONS
void NormalizeVector(float &i, float &j) {
	// para vector unitario
	float Modulo = sqrt((i*i) + (j*j));
	i = i / Modulo;
	j = j / Modulo;
}

// SCORE SCREEN
int count_score=0;
void ScreenR5(){
	esat::DrawSetTextFont("./Recursos/Fonts/Font2.ttf");
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	esat::DrawSetTextSize(50);
	esat::DrawText(250,80,"HIGH SCORE");
	esat::DrawSetTextSize(20);
	
	FILE *pf=fopen("score.txt","rb");
	if(pf!=NULL){
		char us[60];
		int max=0, yy=0;
		while(!feof(pf)){
			fgets(us,60,pf);
			max++;
		}max--;
		score=(TScore*)calloc(max,sizeof(TScore));
		
		rewind(pf);
		int i=0, max_score=0;
		// GUARDO TODAS LAS SCORE Y SU POSICION
		while(!feof(pf)){
			fgets(us,60,pf);
			if(i%2==0){
				(score+max_score)->number=atoi(us);
				max_score++;
			}else{
				for(int r=0;r<40;r++){
					(score+max_score-1)->user[r]=us[r];
				}	
			}
			i++;
		}
		// ORDENO TODAS LAS SCORE					
		int w=0;
		while(w!=(max_score-1)){
			w=0;
			for (int k=0;k<(max_score-1);k++){
				if((score+k)->number>=(score+k+1)->number){
					w=w+1;
				}else{
					int tem=(score+k)->number;
					(score+k)->number=(score+k+1)->number;
					(score+k+1)->number=tem;
					
					char te[40];
					for(int r=0;r<40;r++){
						te[r]=(score+k)->user[r];
						
					}
					for(int r=0;r<40;r++){
						(score+k)->user[r]=(score+k+1)->user[r];
					}
					for(int r=0;r<40;r++){
						(score+k+1)->user[r]=te[r];
					}
				}
			}
		}
		for(int ff=0;ff<10;ff++){
			esat::DrawSetFillColor(255,0,0);
			(score+ff)->user[39]='\0';
			esat::DrawText(300+80,200+yy,(score+ff)->user);
			char rr[40];
			itoa((score+ff)->number,rr,10);
			esat::DrawSetFillColor(255,255,0);
			esat::DrawText(150+80,200+yy,rr);				
			yy+=35;
			if(player.score==(score+ff)->number)player.record_score=true;
		}
	}
	if(player.record_score==true){
		esat::DrawSetTextSize(30);
		esat::DrawSetFillColor(255,0,255);esat::DrawText(30+80,150,"- CONGRATS FOR NEW HIGH SCORE -");
	}
	fclose(pf);
	count_score++;
	if(count_score>40){
		screen=4;count_score=0;
	}
}

void SaveScore(){
	time_t tiempo, otro;
	tm tiempo1,tiempo2;
	time(&tiempo);
	_localtime64_s(&tiempo1, &tiempo);
	char w[20];
	itoa(player.score,w,10);
	char d[10],dd[10],ddd[10];
	itoa(tiempo1.tm_mday,d,10);
	itoa(tiempo1.tm_mon,dd,10);
	tiempo1.tm_year+=1900;
	itoa(tiempo1.tm_year,ddd,10);
	
	
	FILE *pf;
	pf=fopen("score.txt","ab");	
	fputs(w,pf);fputs("\n",pf);
	fputs(user->username,pf);fputs("      ",pf);
	fputs(d,pf);fputs("/",pf);
	fputs(dd,pf);fputs("/",pf);
	fputs(ddd,pf);fputs("\n",pf);
	
	fclose(pf);	
}

// QUAD COLLISION
bool CheckRectangleColision(short x, short y, short width, short height, short x2, short y2, short width2, short height2) {
    if (((x <= x2+width2 && x >= x2) || (x+width <= x2+width2 && x+width >= x2)) && ((y >= y2 && y <= y2+height2) || (y+height >= y2 && y+height <= y2+height2))) {
        return true;
    }
    return false;
}

bool CheckCircleColision(float c1_x, float c1_y, float c1_radio,float c2_x, float c2_y, float c2_radio){
	int sr = c1_radio + c2_radio;
	int dx = c1_x - c2_x;
	int dy = c1_y - c2_y;
	
	if(sr*sr>=dx*dx+dy*dy) return true;
	else return false;	
}

bool CheckLineColision(esat::Vec2 d[100], int total, float scaleX, float scaleY, float x_center, float y_center){
	for(int i=0;i<total-1;i++){
		esat::Vec2 direction={d[i+1].x-d[i].x,d[i+1].y-d[i].y};
		NormalizeVector(direction.x,direction.y);
		float kk=x_center+d[i].x*scaleX,kkk=x_center+d[i+1].x*scaleX;
		float ll=y_center+d[i].y*scaleY,lll=y_center+d[i+1].y*scaleY;
		int g=player.position.x,gg=player.position.y;
		if(kk<kkk){
			for(int j=kk;j<kkk;j+=1){
				if(g>=j-2*scale_map && g<=j+4*scale_map && gg>=ll-7*scale_map && gg<=ll+7*scale_map){
					return true;
				}
				ll+=direction.y;	
			}
		}else{
			for(int j=kk;j>kkk;j-=1){
				if(g>=j-2*scale_map && g<=j+4*scale_map && gg>=ll-7*scale_map && gg<=ll+7*scale_map){
					return true;
				}
				ll+=direction.y;
			}
		}	
	}
	return false;
}

void Cuadricula(){
	esat::DrawSetStrokeColor(255,255,255,100);esat::DrawSetFillColor(255,0,255);
	esat::DrawLine(400,0,400,600);esat::DrawLine(0,300,800,300);
	int xx=0,yy=0;
	if(esat::MouseButtonDown(0)){
		xx=esat::MousePositionX();
		yy=esat::MousePositionY();
		printf("x-> %d, y-> %d\n", xx,yy);
		printf("Xplayer %f  Yplayer %f\n", player.position.x,player.position.y);
	}
}


// DRAW ANY FIGURE
void DrawFigure(esat::Mat3 figure, esat::Vec2 dots[], esat::Vec2 trans_vec[], int n, bool solidpath){
	for(int i=0;i<n;i++){
		esat::Vec3 p;
		p.x=dots[i].x;
		p.y=dots[i].y;
		p.z=1.0f;
		
		p=esat::Mat3TransformVec3(figure,p);
		trans_vec[i].x=p.x/p.z;
		trans_vec[i].y=p.y/p.z;
	}
	if(solidpath==false)esat::DrawPath(&trans_vec[0].x,n);	
	else esat::DrawSolidPath(&trans_vec[0].x,n);		
}


// MAPS FUNCTIONS
	//COUNTS
void OctagonRGB(){
	if(*(count_figure+0)<10)esat::DrawSetStrokeColor(213,61,255);
	else if(*(count_figure+0)>=10 && *(count_figure+0)<20)esat::DrawSetStrokeColor(3,241,251);
	else if(*(count_figure+0)>=20 && *(count_figure+0)<30)esat::DrawSetStrokeColor(3,251,99);
	else if(*(count_figure+0)>=30 && *(count_figure+0)<40)esat::DrawSetStrokeColor(242,244,53);
	else if(*(count_figure+0)>=40 && *(count_figure+0)<50)esat::DrawSetStrokeColor(251,45,3);
	*(count_figure+0)+=1;
	if(*(count_figure+0)>=50)*(count_figure+0)=0;
}

void LineU(){
	*(count_figure+1)+=1;
	if(*(count_figure+1)>=40)*(count_figure+1)=0;
}

void SemiArrow(){
	*(count_figure+2)+=1;
	if(*(count_figure+2)>=10)*(count_figure+2)=0;
}

void LineSize(){
	*(count_figure+3)+=1;
	if(*(count_figure+3)>=30)*(count_figure+3)=0;
}

void LineLarge(){
	*(count_figure+4)+=1;
	if(*(count_figure+4)>=12)*(count_figure+4)=0;
}

void RingPosition(){
	*(count_figure+5)+=1;
	if(*(count_figure+5)>=60)*(count_figure+5)=0;
}

void StarLines(){
	*(count_figure+6)+=1;
	if(*(count_figure+6)>=30)*(count_figure+6)=0;
}

void MazeRotation(){
	*(count_figure+7)+=0.1f;
	if(*(count_figure+7)>pi*2)*(count_figure+7)=0;
}

void CircleDots(){
	*(count_figure+8)+=1;
	if(*(count_figure+8)>=20)*(count_figure+8)=0;
}

void EyeAnimation(){
	*(count_figure+9)+=1;
	if(*(count_figure+9)>=50)*(count_figure+9)=0;
}

void BlueStar(){
	*(count_figure+10)+=1;
	if(*(count_figure+10)>=20)*(count_figure+10)=0;
}

void GreenOctagonS3(){
	*(count_figure+11)+=1;
	if(*(count_figure+11)>=12)*(count_figure+11)=0;
}

void CircleX3(){
	*(count_figure+12)+=1;
	if(*(count_figure+12)>=48)*(count_figure+12)=0;
}
	
void Bonus(int &bon){
	count_bonus++;
	
	if(count_bonus==100){
		bon-=100;
		if(bon<0)bon=0;
		count_bonus=0;
	}
}
	//RESTART PLANET POSITIONS
void RestartPlanet(){
	for(int i=0;i<15;i++){
		(planet+i)->position.x=400;
		(planet+i)->position.y=300;
	}
}
	//ZOOM
void PlanetZoom(float &actualX, float &actualY,float xx, float yy){
	// usar vector direccion para saber el movimeinto de cada planeta
	esat::Vec2 p_direction={xx-actualX,yy-actualY};
	//NormalizeVector(p_direction.x,p_direction.y);
	if((actualX<xx-7 || actualX>xx+7)  || (actualY<yy-7 || actualY>yy+7)){
		actualX+=p_direction.x*planet_speed;
		actualY+=p_direction.y*planet_speed;
	}	
	if(scale_map>0.6)planet_speed+=0.00015;
	if(scale_map>1){
		scale_map=1.000000f;
	}
}
	
void PlanetScale(float &scale){
	if(scale_map<0.6)scale+=0.025f;
	else if(scale<1)scale+=0.007f;
	if(scale_map>1)scale_map=1.000000f;
}
	
	//STARS
void StarsBackGround(){
	for(int i=0;i<400;i++){
		(stars+i)->aparition=rand()%600;
		if((stars+i)->alive==false){
			if((stars+i)->aparition<22 && (stars+i)->aparition>=20){
				(stars+i)->alive=true;
				(stars+i)->rgb[0]={rand()%255};(stars+i)->rgb[1]={rand()%255};(stars+i)->rgb[2]={rand()%255};
				(stars+i)->position.x=rand()%800;
				(stars+i)->position.y=rand()%600;
			}
		}else {
			if((stars+i)->aparition==50){
				(stars+i)->alive=false;
			}
			esat::DrawSetStrokeColor((stars+i)->rgb[0],(stars+i)->rgb[1],(stars+i)->rgb[2]);
			esat::DrawSetFillColor((stars+i)->rgb[0],(stars+i)->rgb[1],(stars+i)->rgb[2]);
			Circle(g_circle,(stars+i)->position.x,(stars+i)->position.y,0.05,0.05);
		}
	}
}
	
	// COMPLETE MAP
void MapComplete(){
	if(screen!=8){
		player.destroyed_turrets=0;
		for(int i=4;i<12;i++){
			if((enemy+i)->alive==false)player.destroyed_turrets++;		
		}
		if(player.destroyed_turrets==8)player.complete_map=true;
	}else{
		if(player.reactor==false)player.complete_map=false;
		else {player.complete_map=true;}
	}
	if(player.complete_map==true){
		switch(screen){
			case 8: change_ss=false;break;
			case 5: *(planet_alive+0)=1;break;
			case 16: *(planet_alive+0)=1;break;
			case 11: *(planet_alive+0)=1;break;
			case 15: *(planet_alive+1)=1;break;
			case 18: *(planet_alive+1)=1;break;
			case 10: *(planet_alive+1)=1;break;
			case 6: *(planet_alive+3)=1;break;
			case 17: *(planet_alive+3)=1;break;
			case 9: *(planet_alive+3)=1;break;
			case 7: *(planet_alive+4)=1;break;
			case 19: *(planet_alive+4)=1;break;
		}
	}
}

// NEW MATRIX VALUES
void ResetM(esat::Mat3 &m, esat::Mat3 &s, esat::Mat3 &r, esat::Mat3 &t){
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
}


// COMPLETE DRAW FIGURES
void DotsPlayer(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots[9], figure[9];
	dots[0]={1-1,0.5-1.5f};
	dots[1]={2-1,2.3f-1.5f};
	dots[2]={1.75-1,3-1.5};
	dots[3]={1.25-1,3-1.5};
	dots[4]={1-1,2.6f-1.5f};
	dots[5]={0.75-1,3-1.5};
	dots[6]={0.25-1,3-1.5};
	dots[7]={0-1,2.3f-1.5f};
	dots[8]={1-1,0.5-1.5f};
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 9, false);
}

void DotsTurbo(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots[3], figure[3];
	dots[0]={0.5-1,3-1.5f};
	dots[1]={1-1,3.5-1.5f};
	dots[2]={1.5-1,3-1.5};
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 3, false);
}

void DotsFuel(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	//TURBO
	esat::Vec2 dots[7], figure[7];
	dots[0]={-1-1,10-1.5f};
	dots[1]={0.25f-1,3-1.5f};
	dots[2]={1.75f-1,3-1.5};
	dots[3]={3-1,10-1.5};
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(0,255,0);
	DrawFigure(m, dots, figure, 4, false);
	// HEXAGON
	dots[0]={-0.5,-1+0.2f};
	dots[1]={0.5,-1+0.2f};
	dots[2]={1,0+0.2f};
	dots[3]={0.5,1+0.2f};
	dots[4]={-0.5,1+0.2f};
	dots[5]={-1,0+0.2f};
	dots[6]={-0.5,-1+0.2f};
	s=esat::Mat3Scale(player.scale*2,player.scale*2);
	ResetM(m,s,r,t);
	int rr=rand()%2;
	if(rr==0)esat::DrawSetStrokeColor(255,0,0);
	else esat::DrawSetStrokeColor(0,0,255);
	DrawFigure(m, dots, figure, 7, false);
}

void DotsOctagon(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots[9], figure[9];
	dots[0]={0,-2};
	dots[1]={1.5,-1.5};
	dots[2]={2,0};
	dots[3]={1.5,1.5};
	dots[4]={0,2};
	dots[5]={-1.5,1.5};
	dots[6]={-2,0};
	dots[7]={-1.5,-1.5};
	dots[8]={0,-2};
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 9, false);
}

void DotsTurret(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots[9], figure[9];
	dots[0]={1.25,-1};
	dots[1]={1.25,-1.5};
	dots[2]={0.75,-1.5};
	dots[3]={0.75,-1};
	dots[4]={0.5,-1};
	dots[5]={0,0};
	dots[6]={2,0};
	dots[7]={1.5,-1};
	dots[8]={0.5,-1};
	esat::DrawSetStrokeColor(255,0,0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 9, false);
}

void DotsOctagon2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, float x, float y, float size_line){
	esat::Vec2 dots[17], figure[17];
	dots[0]={0,-1.25};
	dots[1]={0.25,-1.75};
	dots[2]={1.4f,-1.4f};
	dots[3]={1.75,-0.25};
	dots[4]={1.25,0};
	dots[5]={1.75,0.25};
	dots[6]={1.4f,1.4f};
	dots[7]={0.25,1.75};
	dots[8]={0,1.25};
	dots[9]={-0.25,1.75};
	dots[10]={-1.4f,1.4f};
	dots[11]={-1.75f,0.25f};
	dots[12]={-1.25f,0};
	dots[13]={-1.75f,-0.25f};
	dots[14]={-1.4f,-1.4f};
	dots[15]={-0.25,-1.75};
	dots[16]={0,-1.25};
	
	esat::Mat3 t=esat::Mat3Translate(x,y);
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 17, false);
	
	esat::DrawLine(x,y-20*scale_map,x,y-45*scale_map+size_line);
	esat::DrawLine(x,y+20*scale_map,x,y+45*scale_map-size_line);
	esat::DrawLine(x-20*scale_map,y,x-45*scale_map+size_line,y);
	esat::DrawLine(x+20*scale_map,y,x+45*scale_map-size_line,y);
	
	esat::DrawLine(x-20*scale_map,y-20*scale_map,x-35*scale_map+size_line/2,y-35*scale_map+size_line/2);
	esat::DrawLine(x+20*scale_map,y-20*scale_map,x+35*scale_map-size_line/2,y-35*scale_map+size_line/2);
	esat::DrawLine(x-20*scale_map,y+20*scale_map,x-35*scale_map+size_line/2,y+35*scale_map-size_line/2);
	esat::DrawLine(x+20*scale_map,y+20*scale_map,x+35*scale_map-size_line/2,y+35*scale_map-size_line/2);
}

void DotsStar(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, float x, float y, bool lines){
	esat::Vec2 dots[9], figure[9];
	dots[0]={0,-3};
	dots[1]={0.5,-0.5};
	dots[2]={3,0};
	dots[3]={0.5,0.5};
	dots[4]={0,3};
	dots[5]={-0.5,0.5};
	dots[6]={-3,0};
	dots[7]={-0.5,-0.5};
	dots[8]={0,-3};
	
	esat::Mat3 t=esat::Mat3Translate(x,y);
	ResetM(m,s,r,t);
	DrawFigure(m, dots, figure, 9, false);
	
	if(lines==true){
		esat::DrawSetStrokeColor(255,0,0);
		if(*(count_figure+6)<10){
			esat::DrawLine(x-25*scale_map,y,x-10*scale_map,y);esat::DrawLine(x+10*scale_map,y,x+25*scale_map,y);
			esat::DrawLine(x,y-10*scale_map,x,y-25*scale_map);esat::DrawLine(x,y+10*scale_map,x,y+25*scale_map);
		}
		else if(*(count_figure+6)>=10 && *(count_figure+6)<20){
			esat::DrawLine(x-3*scale_map,y-3*scale_map,x-18*scale_map,y-18*scale_map);esat::DrawLine(x+3*scale_map,y-3*scale_map,x+18*scale_map,y-18*scale_map);
			esat::DrawLine(x-3*scale_map,y+3*scale_map,x-17*scale_map,y+18*scale_map);esat::DrawLine(x+3*scale_map,y+3*scale_map,x+18*scale_map,y+18*scale_map);
		}else {
			esat::DrawLine(x-25*scale_map,y,x-10*scale_map,y);esat::DrawLine(x+10*scale_map,y,x+25*scale_map,y);
			esat::DrawLine(x,y-10*scale_map,x,y-25*scale_map);esat::DrawLine(x,y+10*scale_map,x,y+25*scale_map);
			esat::DrawLine(x-3*scale_map,y-3*scale_map,x-18*scale_map,y-18*scale_map);esat::DrawLine(x+3*scale_map,y-3*scale_map,x+18*scale_map,y-18*scale_map);
			esat::DrawLine(x-3*scale_map,y+3*scale_map,x-18*scale_map,y+18*scale_map);esat::DrawLine(x+3*scale_map,y+3*scale_map,x+18*scale_map,y+18*scale_map);
		}
	}
}

void DotsOctagonStart(esat::Mat3 m, float x, float y){
	esat::Mat3 s=esat::Mat3Scale(13*scale_map,13*scale_map);
	esat::Mat3 r=esat::Mat3Rotate(0);
	esat::Mat3 t=esat::Mat3Translate(x,y);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(255,255,255);
	DotsOctagon(m,s,r,t);
	
	s=esat::Mat3Scale(9*scale_map,9*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate(x,y);
	OctagonRGB();
	DotsOctagon(m,s,r,t);
}

void DotsEnemy(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots1a[8], dots1b[4], figure[8];
	dots1a[0]={0.5-1.75f,1};
	dots1a[1]={1-1.75f,0.5};
	dots1a[2]={1.5-1.75f,1.25};
	dots1a[3]={2.5-1.75f,1.25};
	dots1a[4]={3-1.75f,0.5};
	dots1a[5]={3.5-1.75f,1};
	dots1a[6]={2-1.75f,2};
	dots1a[7]={0.5-1.75f,1};
	dots1b[0]={2-1.75f,0};
	dots1b[1]={2.5-1.75f,1.25};
	dots1b[2]={1.5-1.75f,1.25};
	dots1b[3]={2-1.75f,0};
	
	esat::Vec2 dots2a[6],dots2b[5], figure2[6];
	dots2a[0]={2-1.75f,0.5};
	dots2a[1]={3.5-1.75f,1};
	dots2a[2]={3-1.75f,2.5};
	dots2a[3]={1-1.75f,2.5};
	dots2a[4]={0.5-1.75f,1};
	dots2a[5]={2-1.75f,0.5};
	dots2b[0]={0.5-1.75f,1.25};
	dots2b[1]={3.5-1.75f,1.25};
	dots2b[2]={3.5-1.75f,2};
	dots2b[3]={0.5-1.75f,2};
	dots2b[4]={0.5-1.75f,1.25};
	
	if(screen==4 || screen==12 || screen==13){
		if((enemy+0)->alive==true){
			s=esat::Mat3Scale(7*scale_map,7*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((enemy+0)->position.x,(enemy+0)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,0,0);
			esat::DrawSetFillColor(255,0,0);
			DrawFigure(m, dots1a, figure, 8, false);
			esat::DrawSetStrokeColor(255,255,0);
			esat::DrawSetFillColor(255,255,0);
			DrawFigure(m, dots1b, figure, 4, false);
		}
		if((enemy+1)->alive==true){
			s=esat::Mat3Scale(7*scale_map,7*scale_map);
			t=esat::Mat3Translate((enemy+1)->position.x,(enemy+1)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,0,0);
			esat::DrawSetFillColor(255,0,0);
			DrawFigure(m, dots2a, figure2, 6, false);
			esat::DrawSetStrokeColor(255,255,255);
			esat::DrawSetFillColor(255,255,255);
			DrawFigure(m, dots2b, figure2, 5, true);
		}
	}else if(screen==14){
		if((enemy+0)->alive==true){
			s=esat::Mat3Scale(9*scale_map,9*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((enemy+0)->position.x,(enemy+0)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,0,0);
			esat::DrawSetFillColor(255,0,0);
			DrawFigure(m, dots1a, figure, 8, false);
			esat::DrawSetStrokeColor(255,255,0);
			esat::DrawSetFillColor(255,255,0);
			DrawFigure(m, dots1b, figure, 4, false);
		}
	}
}

void DotsEnemyRastreator(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::Vec2 dots[12], figure[12];
	dots[0]={1,0};
	dots[1]={1.5,0.5};
	dots[2]={2,0};
	dots[3]={3,1.25};
	dots[4]={2.5,2};
	dots[5]={2,2};
	dots[6]={2.5,1.25};
	dots[7]={0.5,1.25};
	dots[8]={1,2};
	dots[9]={0.5,2};
	dots[10]={0,1.25};
	dots[11]={1,0};
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5*scale_map,5*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((enemy+2)->position.x,(enemy+2)->position.y);
	ResetM(m,s,r,t);
	if((enemy+2)->alive==true)DrawFigure(m, dots, figure, 12, false);
	s=esat::Mat3Scale(5*scale_map,5*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((enemy+3)->position.x,(enemy+3)->position.y);
	ResetM(m,s,r,t);
	if((enemy+3)->alive==true)DrawFigure(m, dots, figure, 12, false);
}

void Title(esat::Mat3 m){
		esat::Vec2 figure[16],dotsG[16]={
			2.5f,0.5f,
			4.5f,0.25f,
			4.25f,1,
			3,1.2f,
			2,3.2f,
			3,3,
			3.25f,2.5f,
			2.5f,2.75f,
			3.25f,1.75f,
			4.25f,1.50f,
			3.5f,4.25f,
			0,5,
			2.5f,0.5f	
		},
		dotsR[16]={
			0,5,
			1,1,
			2,0.75f,
			3.5f,1.5f,
			3.5f,2.5f,
			3,2.75f,
			3.5f,3,
			3.25f,4.25f,
			2,4.5f,
			2.25f,3,
			2,3,
			2.2f,2.2f,
			2.4f,2.2f,
			1.8f,1.8f,
			1,4.75,
			0,5			
		},
		dotsRR[16]={
			0,5,
			1-1.6f,1,
			2-1.4f,0.75f,
			3.5f-1.4f,1.5f,
			3.5f-1.4f,2.5f,
			3-1.4f,2.75f,
			3.5f-1.4f,3,
			3.25f-0.0f,6.2f,
			2-0.0f,5.65f,
			2.25f-1.2f,3,
			2.2f-1.4f,3,
			2.05f-1.4f,2.2f,
			2.4f-1.4f,2.2f,
			1.8f-1.4f,1.8f,
			1,5.35f,
			0,5			
		},
		dotsAA[13]={
			0,3.70f,
			0.8f-1.0f,1.2f,
			2-1.2f,0.2f,
			3-1.2f,0,
			3-0.5f,4.2f,
			2-0.5f,4.0f,
			2.25f-1.2f,0.8f,
			1.5f-1.0f,1.4f,
			1.8f-1.0f,1.4f,
			1.8f-1.0f,2,
			1.2f-0.6f,2,
			1-0.2f,3.80f,
			0,3.70f			
		},
		dotsA[13]={
			0,4,
			0.8f-1.0f+0.4f,1.2f,
			2-1.2f+0.4f,0.2f,
			3-1.2f+0.4f,0,
			3-0.5f+0.4f,4.0f,
			2-0.5f+0.4f,4.0f,
			2.25f-1.2f+0.4f,0.8f,
			1.5f-1.0f+0.4f,1.4f,
			1.8f-1.0f+0.4f,1.4f,
			1.8f-1.0f+0.4f,2,
			1.2f-0.6f+0.4f,2,
			1-0.0f,4,
			0,4			
		},
		dotsV[12]={
			0.25,0,
			1,0,
			0.75,1.75,
			1.5,2.75,
			2.25,1.75,
			2,0,
			2.75,0,
			3,2.75,
			2,4,
			1,4,
			0,2.75,
			0.25,0,				
		},
		dotsI[5]={
			0,0,
			1,0,
			1.5,4,
			0.5,4,
			0,0			
		},
		dotsT[9]={
			0,0,
			-0.8f,-0.1f,
			-1,-1,
			2,-0.6f,
			2,0.2f,
			1,0,
			1.5f,3,
			0.5f,3,
			0,0			
		};
		
	esat::DrawSetStrokeColor(51, 236, 255);
	esat::Mat3 s=esat::Mat3Scale(30,30);
	esat::Mat3 r=esat::Mat3Rotate(0);
	esat::Mat3 t=esat::Mat3Translate(100-50,100);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsG, figure, 13, false);
	t=esat::Mat3Translate(210-50,76);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsR, figure, 16, false);
	t=esat::Mat3Translate(310-40,85);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsA, figure, 13, false);
	t=esat::Mat3Translate(405-50,85);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsV, figure, 12, false);
	t=esat::Mat3Translate(490-50,85);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsI, figure, 5, false);
	t=esat::Mat3Translate(552-50,115);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsT, figure, 9, false);
	t=esat::Mat3Translate(600-30,95);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsAA, figure, 13, false);
	t=esat::Mat3Translate(700-50,72);
	ResetM(m,s,r,t);
	DrawFigure(m, dotsRR, figure, 16, false);
}


// HUD
void Hud(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	// LIFES
	esat::DrawSetStrokeColor(25,3,251);
	int x=40;
	for(int i=0;i<player.lifes;i++){
		s=esat::Mat3Scale(10,10);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate(x,30);
		DotsPlayer(m,s,r,t);
		x+=25;
	}
	// SCORE
	//no sale score hasta que sea mayor de 0
	esat::DrawSetTextFont("./Recursos/Fonts/gravitarbold.otf");
	esat::DrawSetTextSize(25);
	esat::DrawSetFillColor(0, 254, 250);
	esat::DrawText(370,30,"Score");
	
	char w[10];int a=0;
	itoa(player.score,w,10);
	if(player.score>=9999999)a=72;
	else if(player.score<=999999 && player.score>99999)a=60;
	else if(player.score<=99999 && player.score>9999)a=48;
	else if(player.score<=9999 && player.score>999)a=36;
	else if(player.score<=999 && player.score>99)a=24;
	else if(player.score<=99 && player.score>9)a=12;
	else a=0;
	esat::DrawSetFillColor(0, 255, 54);
	esat::DrawText(270-a,30,w);
	// FUEL
	esat::DrawSetFillColor(0, 254, 250);
	esat::DrawText(380,55,"Fuel");
	
	itoa(player.fuel,w,10);
	if(player.fuel>9999)a=48;
	else if(player.fuel<=9999 && player.fuel>999)a=36;
	else if(player.fuel<=999 && player.fuel>99)a=24;
	else if(player.fuel<=99 && player.fuel>9)a=12;
	else a=0;
	esat::DrawSetFillColor(0, 255, 54);
	esat::DrawText(270-a,55,w);
	
	// BONUS
	if(screen!=1 && screen!=2 && screen!=3 && screen!=4 && screen!=12){
		esat::DrawSetFillColor(0, 254, 250);
		itoa(player.bonus,w,10);
		esat::DrawText(640,75,"BONUS");
		
		itoa(player.bonus,w,10);
		if(player.bonus>9999)a=48;
		else if(player.bonus<=9999 && player.bonus>999)a=36;
		else if(player.bonus<=999 && player.bonus>99)a=24;
		else if(player.bonus<=99 && player.bonus>9)a=12;
		else a=0;
		esat::DrawSetFillColor(0, 255, 54);
		esat::DrawText(688-a,55,w);
	}
	// PLAYER 
	esat::DrawSetFillColor(0, 254, 250);
	//esat::DrawText(360,80,"Player 1");
	// NEXT SHIP
	//esat::DrawText(345,80,"Next Ship");
	// MISSION COMPLETE 
	MapComplete();
	if(player.complete_map==true)esat::DrawText(306,80,"Mission Complete");
	else{
		esat::DrawText(345,80,"Next Ship");
		if(player.score<10000)player.next_ship=10000;
		else if(player.score<30000)player.next_ship=30000;
		else if(player.score<50000)player.next_ship=50000;
		else if(player.score<70000)player.next_ship=70000;
		else if(player.score<90000)player.next_ship=90000;
		else if(player.score<110000)player.next_ship=110000;
		else if(player.score<130000)player.next_ship=130000;
		else if(player.score<150000)player.next_ship=150000;
		else if(player.score<170000)player.next_ship=170000;
		else if(player.score<190000)player.next_ship=190000;
		else if(player.score<210000)player.next_ship=210000;
		else if(player.score<230000)player.next_ship=230000;
		else if(player.score<250000)player.next_ship=250000;
		itoa(player.next_ship,w,10);
		esat::DrawSetFillColor(0, 255, 54);
		esat::DrawText(480,80,w);
	}
}


// PLAYER FUNCTIONS
void CountSpeed(){
	if(player.count_speed<30){
		player.count_speed++;
	}
}

void PlayerShots(){
	if(esat::IsSpecialKeyDown(esat::kSpecialKey_Space) && player.total_shots<4){
		shot = InsertarNodo(player.position.x+d.x*player.scale,player.position.y+d.y*player.scale);
		player.total_shots++;
	}
	if(player.total_shots>0){
		shot=primero;
		while(shot!=NULL){
			if(shot->alive==true){
				esat::DrawSetStrokeColor(242,244,53);
				esat::DrawSetFillColor(242,244,53);
				Circle(g_circle,shot->position.x,shot->position.y,0.5,0.5);
				shot->position.x+=shot->direction.x*10;
				shot->position.y+=shot->direction.y*10;
				shot->count++;
				if(shot->count>20){
					shot->alive=false;
					player.total_shots--;
					VaciarLista(shot);
				}
			}
			shot=shot->prox;
		}
	}
}

void Gravity(float xx, float yy){
	esat::Vec2 gravity_direction={xx-player.position.x,yy-player.position.y};
	NormalizeVector(gravity_direction.x, gravity_direction.y);
	player.position.x+=gravity_direction.x*player.gravity;
	player.position.y+=gravity_direction.y*player.gravity;
}

void LastPosition(float displacementX, float displacementY){
	last_direction=d;
	player.last_screen=screen;
	player.last_position.x=player.position.x+displacementX;
	player.last_position.y=player.position.y+displacementY;
	IniStars();
	(enemy+0)->last_position.x=(enemy+0)->position.x;
	(enemy+0)->last_position.y=(enemy+0)->position.y;
	(enemy+1)->last_position.x=(enemy+1)->position.x;
	(enemy+1)->last_position.y=(enemy+1)->position.y;
	(enemy+0)->position.x=400;(enemy+0)->position.y=300;
	(enemy+1)->position.x=400;(enemy+1)->position.y=300;
}

void NewPosition(int new_screen, float xx, float yy, float new_scale){
	screen=new_screen;
	player.speed=0;
	player.acceleration=0;
	player.position.x=xx;
	player.position.y=yy;
	player.scale=new_scale;
	player.rotation=pi;
	d={0,1};
	change_direction=d;
	player.count_speed=0;
}

void LimitsRebound(){
	if(player.position.x>=800-player.scale-5){
		change_direction.x=-change_direction.x;
	}
	if(player.position.x<=0+player.scale+5){
		change_direction.x=-change_direction.x;
	}
	if(player.position.y>=600-player.scale-5){
		change_direction.y=-change_direction.y;
	}
	if(player.position.y<=0+player.scale+5){
		change_direction.y=-change_direction.y;
	}
}

void LimitsMaps(){
	if(player.position.x>=790 || player.position.x<=10
	|| player.position.y>=590 || player.position.y<=10){
		IniPlanet();
		if(screen==8){
			switch(player.last_screen){
				case 4: screen=12;break;
				case 12: screen=13;break;
				case 13: screen=4;break;
			}
			player.position.x=400;player.position.y=300;
			player.last_position.x=400;player.last_position.y=398;
			new_ss=false;AllIni();	
		}else NewPosition(player.last_screen,400,300,5);
	}
}

void ZoomIn(){
	scale_map+=0.05;
	if(scale_map>1.5)scale_map=1.5;
	player.position.y-=6;
}

void ZoomOut(){
	scale_map-=0.05;
	if(scale_map<1)scale_map=1;
	player.position.y+=10;
}

void ZoomLeft(){
	if(player.position.x+change_direction.x*player.speed<player.position.x && player.alive==true){
		player.position.x+=-(change_direction.x*player.speed);
		ppp+=1*player.speed;
		pppp+=1*player.speed;
	}
	if(player.position.x>150)zoomleft=false;
}

void ZoomRight(){
	if(player.position.x+change_direction.x*player.speed>player.position.x && player.alive==true){
		player.position.x+=-(change_direction.x*player.speed);
		ppp-=1*player.speed;
		pppp-=1*player.speed;
	}
	if(player.position.x<650)zoomright=false;
}

void LimitsMaps2(float size, float original){
	
	if(zoomin==true){
			ZoomIn();
			(planet+0)->position.y-=4;
			if(scale_map>=1.5f){
				zoomin=false;
			}	
		}
	if(zoomout==true){
		ZoomOut();
		(planet+0)->position.y+=4;
		if(scale_map<=1){
			zoomout=false;
		}
	}
	if(scale_map<1.5 && zoomout==false && zoomin==false){
		if(player.position.y>=200){
			zoomin=true;	
		}
	}else if(scale_map>=1.5 && zoomout==false && zoomin==false){
		if(player.position.y<=50){
			zoomout=true;
		}
	}
	if(player.position.x<100){
		zoomleft=true;
	}
	if(player.position.x>700){
		zoomright=true;
	}
	if(zoomright==true){
		ZoomRight();
	}
	if(zoomleft==true){
		ZoomLeft();
	}	
	
	if(ppp*scale_map>size){
		ppp=-original+5;
	}
	if(ppp*scale_map<-size){
		ppp=+original-5	;	
	}
	if(pppp*scale_map>size*2){
		pppp=0+5;
	}
	if(pppp*scale_map<0){
		pppp=original*2-5;
	}
}

void ExplosionPlayer(){
	if(player.fuel<=0){player.alive=0;player.lifes=0;}
	if(player.alive==false && player.exploding==false){
		player.exploding=true;
		player.n_explosion=rand()%11+1;
		if(player.n_explosion<=3)player.n_explosion=4;
		bool side_left=false, side_right=false;
		for(int i=0;i<player.n_explosion;i++){
			(player.explosion+i)->position.x=player.position.x;
			(player.explosion+i)->position.y=player.position.y;
			int xx=rand()%2400-800, yy=rand()%1800-600;
			if(side_left==false)xx-=800;
			if(side_right==false)xx+=800;
			if(xx<player.position.x)side_left=true;
			if(xx>player.position.x)side_right=true;
			
			(player.explosion+i)->direction={xx-player.position.x,yy-player.position.y};
			NormalizeVector((player.explosion+i)->direction.x,(player.explosion+i)->direction.y);
		}
	}
	// EXPLOSION JUGADOR
	if(player.alive==false && player.exploding==true){
		for(int i=0;i<player.n_explosion;i++){
			esat::DrawSetStrokeColor(255,255,0);
			esat::DrawSetFillColor(255,255,0);				
			Circle(g_circle,(player.explosion+i)->position.x,(player.explosion+i)->position.y,1.5,1.5);
			(player.explosion+i)->position.x+=(player.explosion+i)->direction.x*2;
			(player.explosion+i)->position.y+=(player.explosion+i)->direction.y*2;			
		}
		player.exploding_count++;
		if(player.exploding_count>20){
			if(player.lifes>0){
				player.lifes--;
				player.exploding=false;
				player.exploding_count=0;
				player.alive=true;
				player.speed=0;
				player.acceleration=0;
				(enemy+0)->shooting=false;
				(enemy+0)->shoot.count_alive=0;
				shot=primero;
				if(primero!=NULL){
					while(shot!=NULL){
						VaciarLista(shot);
						shot=shot->prox;
					}
				}
				player.total_shots=0;
				if(screen==4 || screen==12 || screen==13 || screen==14){
					d={0,-1};
					change_direction=d;
					player.rotation=0;
					player.position.x=400;
					player.position.y=398;
					for(int i=4;i<12;i++){
						(enemy+i)->shooting=false;
						(enemy+i)->shoot.count_alive=0;
					}			
					if(screen==14)screen=player.last_screen;
					switch(screen){
						case 4: (enemy+0)->position.x=115;
								(enemy+0)->position.y=288;
								(enemy+1)->position.x=100-10;
								(enemy+1)->position.y=288;
								break;
						case 12: (enemy+0)->position.x=660;
								(enemy+0)->position.y=127;
								(enemy+1)->position.x=675-10;
								(enemy+1)->position.y=127;
								break;
						case 13: (enemy+0)->position.x=130;
								(enemy+0)->position.y=296;
								(enemy+1)->position.x=145-10;
								(enemy+1)->position.y=296;
								break;
					}
				}else{
					d={0,1};
					change_direction=d;
					player.rotation=pi;
					player.position.x=400;
					player.position.y=100;
					(enemy+2)->position.x=-60;
					(enemy+2)->position.y=100;
					(enemy+3)->position.x=900;
					(enemy+3)->position.y=150;
					(enemy+3)->speed=2.5f;
					for(int i=4;i<16;i++){
						(enemy+i)->shooting=false;
						(enemy+i)->shoot.count_alive=0;
					}
				}
			}else{
				SaveScore();
				new_ss=false;
				start=false;
				change_ss=false;
				AllIni();
				screen=20;
			}
		}
	}		
}

void Movement(){
	if(player.alive==true){
		PlayerShots();
		//ROTAR
		if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)){player.rotation+=0.1f;}
		if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)){player.rotation-=0.1f;}
		if(player.rotation>=pi*2 || player.rotation<=-(pi*2))player.rotation=0;
		
		//MOVER
		if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up) && player.position.x<800-player.scale-5 && player.position.x>0+player.scale+5 &&
		player.position.y<600-player.scale-5 && player.position.y>0+player.scale+5){
			if(change_direction.x>d.x)change_direction.x-=0.05f;
			if(change_direction.x<d.x)change_direction.x+=0.05f;
			if(change_direction.y>+d.y)change_direction.y-=0.05f;
			if(change_direction.y<d.y)change_direction.y+=0.05f;
			
			if(player.scale==5){
				if(player.acceleration==0)player.acceleration=1.6;
				if(player.acceleration<5)player.acceleration+=0.05;
			}else if(player.scale==3){
				if(player.acceleration==0)player.acceleration=0.3;
				if(player.acceleration<3.5f)player.acceleration+=0.025;
			}
			player.speed=player.acceleration;
			player.turbo=true;
			player.fuel-=5;
		}else{
			if(player.scale==5){
				if(player.speed>0)player.speed-=0.025;
			}else if(player.scale==3)	{
				if(player.speed>0)player.speed-=0.007;
			}
			player.acceleration=player.speed;
			player.turbo=false;
		}
		player.position.x+=change_direction.x*player.speed;
		player.position.y+=change_direction.y*player.speed;	
	}
	ExplosionPlayer();
}

void DrawPlayer(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	if(player.score>=player.next_ship)player.lifes++;
	
	float size=0;
	if(scale_map<1)PlanetZoom(player.position.x,player.position.y,player.last_position.x,player.last_position.y);
	if(player.alive==true){
		for(int i=0;i<3;i++){
			s=esat::Mat3Scale((player.scale-size)*scale_map,(player.scale-size)*scale_map);
			r=esat::Mat3Rotate(player.rotation);
			t=esat::Mat3Translate(player.position.x,player.position.y);
			
			if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Down) && scale_map>=1){
				ResetM(m,s,r,t);
				DotsFuel(m,s,r,t);
				player.shield=true;
			}else{
				player.shield=false;
			}
			
			esat::DrawSetStrokeColor(25,3,251);
			DotsPlayer(m,s,r,t);
			if(player.turbo==true && scale_map>=1){
				esat::DrawSetStrokeColor(255,0,0);
				t=esat::Mat3Translate(player.position.x+0.4,player.position.y);
				ResetM(m,s,r,t);
				DotsTurbo(m,s,r,t);
			}
			size-=0.5;
		}
	}
	
	// VEC DIRECTION
	ResetM(m,s,r,t);
	esat::Vec2 a[2]={0,0,0,-1};
	esat::Vec2 aa[2];
	for(int i=0;i<2;i++){
		esat::Vec3 p;
		p.x=a[i].x;
		p.y=a[i].y;
		p.z=1.0f;
		
		p=esat::Mat3TransformVec3(m,p);
		aa[i].x=p.x/p.z;
		aa[i].y=p.y/p.z;
	}
	d={aa[1].x-aa[0].x,aa[1].y-aa[0].y};
	NormalizeVector(d.x,d.y);	
}


// ENEMY FUNCTIONS
void OvnisMovement(float &xx, float &yy, float ss){
	int r=rand()%40-20;
	esat::Vec2 ovni_direction={player.position.x+r-xx,player.position.y+r-yy};
	NormalizeVector(ovni_direction.x, ovni_direction.y);
	xx+=ovni_direction.x*ss;
	yy+=ovni_direction.y*ss;
}

void OvnisShoots(){
	if((enemy+0)->shooting==false){
		(enemy+0)->shoot.count_alive+=1;
		if((enemy+0)->shoot.count_alive>=15){
			int rr=rand()%80-40;
			(enemy+0)->shooting=true;
			(enemy+0)->shoot_direction={player.position.x+rr-(enemy+0)->position.x,player.position.y-(enemy+0)->position.y};
			NormalizeVector((enemy+0)->shoot_direction.x,(enemy+0)->shoot_direction.y);
			(enemy+0)->shoot.position.x=(enemy+0)->position.x;
			(enemy+0)->shoot.position.y=(enemy+0)->position.y;
		}
	}else{
		(enemy+0)->shoot.position.x+=(enemy+0)->shoot_direction.x*6;
		(enemy+0)->shoot.position.y+=(enemy+0)->shoot_direction.y*6;
		esat::DrawSetStrokeColor(255,0,0);
		Circle(g_circle,(enemy+0)->shoot.position.x,(enemy+0)->shoot.position.y,0.5,0.5);
		
		(enemy+0)->shoot.count_alive+=1;
		if((enemy+0)->shoot.count_alive>=55 || player.alive==false){
			(enemy+0)->shooting=false;
			(enemy+0)->shoot.count_alive=0;
		}	
	}
}

void Ovnis(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	DotsEnemy(m,s,r,t);
	if(scale_map<1){
		PlanetZoom((enemy+0)->position.x,(enemy+0)->position.y,(enemy+0)->last_position.x,(enemy+0)->last_position.y);
		PlanetZoom((enemy+1)->position.x,(enemy+1)->position.y,(enemy+1)->last_position.x,(enemy+1)->last_position.y);
	}
	
	if(scale_map>=1 && player.alive==true){
		if(screen!=14){
			if(((enemy+0)->alive==true && CheckCircleColision(player.position.x,player.position.y,10,
			(enemy+0)->position.x,(enemy+0)->position.y,10)) || 
			((enemy+1)->alive==true && CheckCircleColision(player.position.x,player.position.y,10,
			(enemy+1)->position.x,(enemy+1)->position.y,10))){
				LastPosition(0,0);
				NewPosition(14,0,0,5);
				(enemy+0)->alive=true;
				(enemy+0)->shooting=false;
				(enemy+0)->shoot.count_alive=0;
				int r=rand()%4;
				switch(r){
					case 0: player.position.x=50;player.position.y=100;
							(enemy+0)->position.x=750;(enemy+0)->position.y=550;
							break;
					case 1: player.position.x=750;player.position.y=100;
							(enemy+0)->position.x=50;(enemy+0)->position.y=550;
							break;
					case 2: player.position.x=50;player.position.y=550;
							(enemy+0)->position.x=750;(enemy+0)->position.y=100;
							break;
					case 3: player.position.x=750;player.position.y=550;
							(enemy+0)->position.x=50;(enemy+0)->position.y=100;
							break;
				}
			}
		}else{
			if((enemy+0)->alive==true && CheckCircleColision(player.position.x,player.position.y,10,
			(enemy+0)->position.x,(enemy+0)->position.y,10)){
				player.alive=false;
			}	
		}
		if((enemy+0)->alive==true){
			OvnisShoots();
			OvnisMovement((enemy+0)->position.x,(enemy+0)->position.y,(enemy+0)->speed);
		}
		if((enemy+1)->alive==true && screen!=14){
			OvnisMovement((enemy+1)->position.x,(enemy+1)->position.y,(enemy+1)->speed);
		}
	
		// DISPARO OVNI Y NAVE
		if(player.alive==true && (enemy+0)->alive && CheckCircleColision(player.position.x,player.position.y,10*scale_map,
		(enemy+0)->shoot.position.x,(enemy+0)->shoot.position.y,0.5*scale_map)){
			(enemy+0)->shooting=false;
			(enemy+0)->shoot.count_alive=0;
			if(player.shield==false)player.alive=false;
		}
		
		//DISPARO PLAYER Y OVNI
		if(player.total_shots>0){
			shot=primero;
			while(shot!=NULL){
				if(shot->alive==true){
					if(shot->alive==true && (enemy+0)->alive==true && CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
					(enemy+0)->position.x,(enemy+0)->position.y,12*scale_map)){
						if(screen==14){
							(enemy+0)->shooting=false;
							(enemy+0)->shoot.count_alive=0;
							NewPosition(player.last_screen,player.last_position.x,player.last_position.y,5);
							(enemy+1)->alive=false;
						}
						player.score+=100;
						shot->alive=false;
						player.total_shots--;
						VaciarLista(shot);
						(enemy+0)->alive=false;
					}	
					if(shot->alive==true && (enemy+1)->alive==true && CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
					(enemy+1)->position.x,(enemy+1)->position.y,12*scale_map)){
						player.score+=100;
						shot->alive=false;
						player.total_shots--;
						VaciarLista(shot);
						(enemy+1)->alive=false;
					}	
				}
				shot=shot->prox;
			}
		}
	}
}
	
void RastreatorMovement(esat::Mat3 m, esat::Mat3 s, esat::Mat3 r, esat::Mat3 t, float maxY){
	if((enemy+2)->alive==true && player.alive==true){
		(enemy+2)->position.x+=2.5;
		int up=rand()%500;
		if(up<200 && (enemy+2)->position.y<maxY-10) up=0;
		else if(up>200 && up<400 && (enemy+2)->position.y>80) up=1;
		else up=2;
		switch(up){
			case 0: (enemy+2)->position.y+=2.5;break;
			case 1: (enemy+2)->position.y-=2.5;break;
			case 2: (enemy+2)->position.y+=0;break;
		}
		if(player.alive==true && CheckCircleColision(player.position.x,player.position.y,10*scale_map,
		(enemy+2)->position.x,(enemy+2)->position.y,10*scale_map)){
			player.alive=false;
			(enemy+2)->alive=false;
		}
	}
	if((enemy+3)->alive==true && player.alive==true){
		(enemy+3)->position.x-=2.5;
		int up=rand()%500;
		if(up<200 && (enemy+3)->position.y<maxY-10) up=0;
		else if(up>200 && up<400 && (enemy+3)->position.y>80) up=1;
		else up=2;
		switch(up){
			case 0: (enemy+3)->position.y+=2.5;break;
			case 1: (enemy+3)->position.y-=2.5;break;
			case 2: (enemy+3)->position.y+=0;break;
		}
		if(player.alive==true && CheckCircleColision(player.position.x,player.position.y,10*scale_map,
		(enemy+3)->position.x,(enemy+3)->position.y,10*scale_map)){
			(enemy+3)->alive=false;
			player.alive=false;
		}
	}
	
	if((enemy+2)->position.x>900)(enemy+2)->position.x=-100;
	if((enemy+3)->position.x<-100)(enemy+3)->position.x=900;
	
	if(player.total_shots>0){
		shot=primero;
		while(shot!=NULL){
			if(shot->alive==true){
				if((enemy+2)->alive==true && CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
				(enemy+2)->position.x,(enemy+2)->position.y,10*scale_map)){
					player.score+=100;
					shot->alive=false;
					player.total_shots--;
					VaciarLista(shot);
					(enemy+2)->alive=false;
				}	
				if((enemy+3)->alive==true && CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
				(enemy+3)->position.x,(enemy+3)->position.y,10*scale_map)){
					player.score+=100;
					shot->alive=false;
					player.total_shots--;
					VaciarLista(shot);
					(enemy+3)->alive=false;
				}	
			}
			shot=shot->prox;
		}
	}	
	DotsEnemyRastreator(m,s,r,t);
}

void TurretsShooting(int i, float xx, float yy, float total_size){
	if((enemy+i)->alive==true && player.alive==true){
		if((enemy+i)->shooting==false && player.alive==true){
			int ss=rand()%100;
			if(ss<2){
				(enemy+i)->shooting=true;
				if((planet+i+1)->position.x+ppp*scale_map+xx>=0 && (planet+i+1)->position.x+ppp*scale_map+xx<=800){
					(enemy+i)->shoot.position.x=(planet+i+1)->position.x+ppp*scale_map+xx;
					(enemy+i)->shoot.position.y=(planet+i+1)->position.y+yy;
				}else{
					(enemy+i)->shoot.position.x=(planet+i+1)->position.x+pppp*scale_map-total_size+xx;
					(enemy+i)->shoot.position.y=(planet+i+1)->position.y+yy;
				}
				int hh=rand()%100-50;
				(enemy+i)->shoot_direction={player.position.x+hh-(enemy+i)->shoot.position.x,player.position.y-(enemy+i)->shoot.position.y};
				NormalizeVector((enemy+i)->shoot_direction.x,(enemy+i)->shoot_direction.y);
			}
		}
		if((enemy+i)->shooting==true){
			(enemy+i)->shoot.count_alive+=1;
			(enemy+i)->shoot.position.x+=(enemy+i)->shoot_direction.x*4;
			(enemy+i)->shoot.position.y+=(enemy+i)->shoot_direction.y*4;
			esat::DrawSetStrokeColor(255,0,0);
			Circle(g_circle,(enemy+i)->shoot.position.x,(enemy+i)->shoot.position.y,0.5,0.5);
			if((enemy+i)->shoot.count_alive>20 || player.alive==false){
				(enemy+i)->shooting=false;
				(enemy+i)->shoot.count_alive=0;
			}
			// DISPARO TORRETA COLISION PLAYER
			if(player.alive==true && CheckCircleColision(player.position.x,player.position.y,10*scale_map,
			(enemy+i)->shoot.position.x,(enemy+i)->shoot.position.y,0.5*scale_map)){
				(enemy+i)->shooting=false;
				(enemy+i)->shoot.count_alive=0;
				if(player.shield==false)player.alive=false;
			}	
		}
		
		// PLAYER TORRETA COLISION
		if(player.alive==true && CheckCircleColision(player.position.x,player.position.y,10*scale_map,
		(planet+i+1)->position.x+ppp*scale_map+xx,(planet+i+1)->position.y+yy,10*scale_map)){
			(enemy+i)->shooting=false;
			(enemy+i)->shoot.count_alive=0;
			player.alive=false;
		}
		// DISPARO PLAYER COLISION TORRETA 
		if(player.total_shots>0){
			shot=primero;
			while(shot!=NULL){
				if(shot->alive==true){
					if((planet+i+1)->position.x+ppp*scale_map+xx>=0 && (planet+i+1)->position.x+ppp*scale_map+xx<=800){
						if(CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
						(planet+i+1)->position.x+ppp*scale_map+xx,(planet+i+1)->position.y+yy,10*scale_map)){
							player.score+=250;
							shot->alive=false;
							player.total_shots--;
							VaciarLista(shot);
							(enemy+i)->alive=false;
						}	
					}else{
						if(CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
						(planet+i+1)->position.x+pppp*scale_map-total_size+xx,(planet+i+1)->position.y+yy,10*scale_map)){
							player.score+=250;
							shot->alive=false;
							player.total_shots--;
							VaciarLista(shot);
							(enemy+i)->alive=false;
						}
					}	
				}
				shot=shot->prox;
			}
		}	
	}	
}

void ColisionFuel(int i, float xx, float yy, float total_size){
	if((enemy+i)->alive==true && player.alive==true && player.shield==true){
		float xxx=-d.x, yyy=-d.y;
		if((planet+i-11)->position.x+ppp*scale_map+xx>=0 && (planet+i-11)->position.x+ppp*scale_map+xx<=800){
			if(CheckCircleColision(player.position.x+xxx*20,player.position.y+yyy*20,20,
			(planet+i-11)->position.x+ppp*scale_map+xx+5,(planet+i-11)->position.y+yy,15*scale_map)){
				(enemy+i)->alive=false;
				player.fuel+=1100;
			}
		}else{
			if(CheckCircleColision(player.position.x+xxx*20,player.position.y+yyy*20,20,
			(planet+i-11)->position.x+pppp*scale_map-total_size+xx+5,(planet+i-11)->position.y+yy,15*scale_map)){
				(enemy+i)->alive=false;
				player.fuel+=1100;
			}
		}
	}
}

// DRAW MAPS
	//SISTEMA SOLAR 1
void DrawMap1S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	new_ss=true;
	esat::Vec2 dots_lineU[5]={
		0-1.25,-2+1,
		2-1.25,-1.5+1,
		2.5-1.25,-1+1,
		2-1.25,-0.5+1,
		0-1.25,0+1,
	};
	esat::Vec2 lineU[5];
	
	esat::Vec2 dots_semiarrow1[7]={
		1-1,-4+2,
		1.5-1,-2+2,
		2-1,-1+2,
		1-1,0+2,
		0-1,-1+2,
		0.5-1,-2+2,
		1-1,-4+2
	};
	esat::Vec2 dots_semiarrow2[7]={
		1-1,-8+4,
		1.5-1,-2+4,
		2-1,-1+4,
		1-1,0+4,
		0-1,-1+4,
		0.5-1,-2+4,
		1-1,-8+4
	};
	esat::Vec2 semiarrow[7];
	
	esat::Vec2 dots_ring[6]={
		-1.75,-0.5,
		-3,0,
		-1.75,0.5,
		1.75,0.5,
		3,0,
		1.75,-0.5
	};
	esat::Vec2 ring[6];
	esat::DrawSetTextSize(20*scale_map);
	
	//octagono nacimiento player
	DotsOctagonStart(m,(planet+1)->position.x,(planet+1)->position.y);
	PlanetZoom((planet+1)->position.x,(planet+1)->position.y,400,400);
	char ggg[20];
	if(*(planet_alive+0)==0){
		//8000
		if(*(count_figure+1)<20){
			s=esat::Mat3Scale(5*scale_map,5*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,255,255);
			esat::Vec2 dots_star[9];
			esat::Vec2 star[9];
			bool lines=false;
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(0);
			DotsStar(m,s,r,(planet+0)->position.x,(planet+0)->position.y,lines);
		}else{
			s=esat::Mat3Scale(11*scale_map,11*scale_map);
			t=esat::Mat3Translate((planet+0)->position.x-38*scale_map,(planet+0)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,255,255);
			DrawFigure(m, dots_lineU, lineU, 5, false);
			
			s=esat::Mat3Scale(11*scale_map,11*scale_map);
			r=esat::Mat3Rotate(3.149998);
			t=esat::Mat3Translate((planet+0)->position.x+38*scale_map,(planet+0)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,255,255);
			DrawFigure(m, dots_lineU, lineU, 5, false);
		}
		
		s=esat::Mat3Scale(12*scale_map,12*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
		esat::DrawSetStrokeColor(244,82,53);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,230,112);
		
		esat::DrawSetFillColor(0, 254, 250);
		
		itoa(*(planet_bonus+0),ggg,10);
		esat::DrawText((planet+0)->position.x-60,(planet+0)->position.y-27,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+0)->position.x,(planet+0)->position.y,35)){
				LastPosition(50,0);
				AllIni();
				NewPosition(5,400,100,3);
			}
		}
	}
	if(*(planet_alive+1)==0){
		//2000
		if(*(count_figure+2)<5){
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y-22*scale_map);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,15,0);
			DrawFigure(m, dots_semiarrow1, semiarrow, 7, false);
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(3.149998);
			t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y+22*scale_map);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,255,255);
			DrawFigure(m, dots_semiarrow1, semiarrow, 7, false);
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(3.149998/2);
			t=esat::Mat3Translate((planet+2)->position.x+30*scale_map,(planet+2)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(25,3,251);
			DrawFigure(m, dots_semiarrow2, semiarrow, 7, false);
			
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(3.149998+3.149998/2);
			t=esat::Mat3Translate((planet+2)->position.x-30*scale_map,(planet+2)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(242,255,0);
			DrawFigure(m, dots_semiarrow2, semiarrow, 7, false);
		}else{
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y-30*scale_map);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,15,0);
			DrawFigure(m, dots_semiarrow2, semiarrow, 7, false);
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(pi);
			t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y+30*scale_map);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(255,255,255);
			DrawFigure(m, dots_semiarrow2, semiarrow, 7, false);
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(pi/2);
			t=esat::Mat3Translate((planet+2)->position.x+22*scale_map,(planet+2)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(25,3,251);
			DrawFigure(m, dots_semiarrow1, semiarrow, 7, false);
			
			s=esat::Mat3Scale(4*scale_map,4*scale_map);
			r=esat::Mat3Rotate(pi*1.5);
			t=esat::Mat3Translate((planet+2)->position.x-22*scale_map,(planet+2)->position.y);
			ResetM(m,s,r,t);
			esat::DrawSetStrokeColor(242,255,0);
			DrawFigure(m, dots_semiarrow1, semiarrow, 7, false);
		}
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y);
		esat::DrawSetStrokeColor(213,61,255);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+2)->position.x,(planet+2)->position.y,688,100);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+1),ggg,10);
		esat::DrawText((planet+2)->position.x+12,(planet+2)->position.y-20,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+2)->position.x,(planet+2)->position.y,35)){
				LastPosition(40,40);AllIni();
				NewPosition(15,400,300,3);
			}
		}
	}
	if(*(planet_alive+2)==0){
		//9000 OCTAGON RED
		float size_line=0;
		if(*(count_figure+3)<10)size_line=+5*scale_map;
		else if(*(count_figure+3)>=10 && *(count_figure+3)<20)size_line=-5*scale_map;
		else size_line=-15*scale_map;
		
		s=esat::Mat3Scale(15*scale_map,15*scale_map);
		r=esat::Mat3Rotate(0);
		esat::DrawSetStrokeColor(244,82,53);
		DotsOctagon2(m,s,r,(planet+3)->position.x,(planet+3)->position.y, size_line);
		PlanetZoom((planet+3)->position.x,(planet+3)->position.y,100,290);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+2),ggg,10);
		esat::DrawText((planet+3)->position.x-70,(planet+3)->position.y+20,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+3)->position.x,(planet+3)->position.y,35)){
				LastPosition(40,0);AllIni();
				NewPosition(8,400,300,3);
			}
		}
	}	
	if(*(planet_alive+3)==0){
		//6000
		esat::DrawSetStrokeColor(71,255,0);
		if(*(count_figure+4)<3)esat::DrawLine((planet+4)->position.x-20*scale_map,(planet+4)->position.y,
			(planet+4)->position.x+20*scale_map,(planet+4)->position.y);
		else if(*(count_figure+4)>=3 && *(count_figure+4)<6)esat::DrawLine((planet+4)->position.x-15*scale_map,(planet+4)->position.y-15*scale_map,
		(planet+4)->position.x+15*scale_map,(planet+4)->position.y+15*scale_map);
		else if(*(count_figure+4)>=6 && *(count_figure+4)<9)esat::DrawLine((planet+4)->position.x,(planet+4)->position.y-20*scale_map,
		(planet+4)->position.x,(planet+4)->position.y+20*scale_map);
		else esat::DrawLine((planet+4)->position.x-15*scale_map,(planet+4)->position.y+15*scale_map,
		(planet+4)->position.x+15*scale_map,(planet+4)->position.y-15*scale_map);
		
		s=esat::Mat3Scale(6*scale_map,6*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+4)->position.x,(planet+4)->position.y);
		esat::DrawSetStrokeColor(244,82,53);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+4)->position.x,(planet+4)->position.y,130,520);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+3),ggg,10);
		esat::DrawText((planet+4)->position.x-20,(planet+4)->position.y+40,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+4)->position.x,(planet+4)->position.y,15)){
				LastPosition(0,-40);AllIni();
				NewPosition(6,400,300,3);
			}
		}
	}
	if(*(planet_alive+4)==0){
		//4000
		if(*(count_figure+5)<30)r=esat::Mat3Rotate(0);
		else r=esat::Mat3Rotate(pi);
		
		s=esat::Mat3Scale(12*scale_map,12*scale_map);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		ResetM(m,s,r,t);
		esat::DrawSetStrokeColor(25,3,251);
		DrawFigure(m, dots_ring, ring, 6, false);
		
		s=esat::Mat3Scale(12*scale_map,12*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		esat::DrawSetStrokeColor(242,244,53);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+5)->position.x,(planet+5)->position.y,700,490);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+4),ggg,10);
		esat::DrawText((planet+5)->position.x+20,(planet+5)->position.y+40,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+5)->position.x,(planet+5)->position.y,35)){
				LastPosition(0,-40);AllIni();
				NewPosition(7,400,300,3);
			}
		}
	}
	//STAR
	bool lines=true;
	s=esat::Mat3Scale(4*scale_map,4*scale_map);
	r=esat::Mat3Rotate(0);
	esat::DrawSetStrokeColor(242,244,53);
	DotsStar(m,s,r,(planet+6)->position.x,(planet+6)->position.y,lines);
	PlanetZoom((planet+6)->position.x,(planet+6)->position.y,480,235);
	
	if(scale_map>=1 && CheckCircleColision(player.position.x,player.position.y,10,
	(planet+6)->position.x,(planet+6)->position.y,10)){
		player.alive=false;
	}
}
		//MAPS
void DrawMap2S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=398,(planet+1)->position.y=230;
		(planet+2)->position.x=191,(planet+2)->position.y=360;
		(planet+3)->position.x=360,(planet+3)->position.y=410;
		(planet+4)->position.x=593,(planet+4)->position.y=348;
		//5-12 turrets
		(planet+5)->position.x=442,(planet+5)->position.y=192;
		(planet+6)->position.x=227,(planet+6)->position.y=340;
		(planet+7)->position.x=292,(planet+7)->position.y=463;
		(planet+8)->position.x=330,(planet+8)->position.y=420;
		(planet+9)->position.x=395,(planet+9)->position.y=425;
		(planet+10)->position.x=530,(planet+10)->position.y=515;
		(planet+11)->position.x=633,(planet+11)->position.y=347;
		(planet+12)->position.x=556,(planet+12)->position.y=250;
		
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x,(planet+1)->position.y,10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x,(planet+2)->position.y,10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x,(planet+3)->position.y,10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x,(planet+4)->position.y,10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi+0.80);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.69);
		t=esat::Mat3Translate((planet+6)->position.x,(planet+6)->position.y);
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.26);
		t=esat::Mat3Translate((planet+7)->position.x,(planet+7)->position.y);
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+8)->position.x,(planet+8)->position.y);
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+9)->position.x,(planet+9)->position.y);
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.79);
		t=esat::Mat3Translate((planet+10)->position.x,(planet+10)->position.y);
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.77);
		t=esat::Mat3Translate((planet+11)->position.x,(planet+11)->position.y);
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0);
		t=esat::Mat3Translate((planet+12)->position.x,(planet+12)->position.y);
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,0,0,0);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,0,0,0);
		}
	}
	
	// MAP
	esat::Vec2 dots_map[49]={
		15-12,0-10,
		17-12,5-10,
		18-12,5-10,
		19-12,6-10,
		21-12,6-10,
		20-12,7-10,
		21.5-12,9-10,
		24-12,10.5-10,
		23-12,11.5-10,
		21-12,11.5-10,
		20-12,12-10,
		21-12,13-10,
		19.5-12,15-10,
		21-12,16-10,
		20-12,17-10,
		18.5-12,17-10,
		17.5-12,19-10,
		19-12,19-10,
		17.5-12,20-10,
		16-12,18-10,
		18-12,15-10,
		12-12,15-10,
		11-12,14-10,
		9-12,14-10,
		7.5-12,15.5-10,
		9-12,17-10,
		7.5-12,19-10,
		5-12,19-10,
		7-12,17-10,
		5-12,15-10,
		4-12,16-10,
		3-12,15-10,
		1-12,15-10,
		3-12,13-10,
		2-12,13-10,
		0-12,11-10,
		3-12,11-10,
		5-12,8-10,
		6-12,8-10,
		7.5-12,6-10,
		9-12,6-10,
		8-12,5-10,
		9-12,3.5-10,
		10.5-12,5-10,
		13-12,5-10,
		14.5-12,3.5-10,
		13-12,2-10,
		12-12,2-10,
		15-12,0-10
	};
	esat::Vec2 map[49];
		
	if(scale_map<1){
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,350);	
		PlanetScale(scale_map);
	}	
	s=esat::Mat3Scale(20*scale_map,20*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 49, false);
	
	if(CheckLineColision(dots_map,49,20*scale_map,20*scale_map,(planet+0)->position.x,(planet+0)->position.y)){
		player.alive=false;
	}
}

void DrawMap3S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=25*scale_map*37,original_size=25*37;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=-30,(planet+1)->position.y=553;
		(planet+2)->position.x=271,(planet+2)->position.y=553;
		(planet+3)->position.x=465,(planet+3)->position.y=535;
		(planet+4)->position.x=681,(planet+4)->position.y=554;
		//5-12 turrets
		(planet+5)->position.x=-5+13,(planet+5)->position.y=410;
		(planet+6)->position.x=105,(planet+6)->position.y=571;
		(planet+7)->position.x=242+13,(planet+7)->position.y=410;
		(planet+8)->position.x=344,(planet+8)->position.y=571;
		(planet+9)->position.x=443+13,(planet+9)->position.y=410;
		(planet+10)->position.x=568,(planet+10)->position.y=571;
		(planet+11)->position.x=673+13,(planet+11)->position.y=410;
		(planet+12)->position.x=817,(planet+12)->position.y=552;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=-140-77;*(more_y+0)=-27;
			*(more_x+1)=-66;*(more_y+1)=-25;
			*(more_x+2)=29;*(more_y+2)=-34;
			*(more_x+3)=150;*(more_y+3)=-26;
			// TURRETS
			*(more_x+4)=-104-93;*(more_y+4)=-98;
			*(more_x+5)=-46-105;*(more_y+5)=-17;
			*(more_x+6)=20-91;*(more_y+6)=-98;
			*(more_x+7)=70-103;*(more_y+7)=-17;
			*(more_x+8)=120-90;*(more_y+8)=-98;
			*(more_x+9)=81;*(more_y+9)=-17;
			*(more_x+10)=157;*(more_y+10)=-98;
			*(more_x+11)=206;*(more_y+11)=-26;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	esat::Vec2 dots_map1[10]={
		0-18.5f,0-3-4,
		7-18.5f,0-3-4,
		8-18.5f,1-3-4,
		4-18.5f,1-3-4,
		3.5-18.5f,3-3-4,
		3-18.5f,1-3-4,
		2-18.5f,1-3-4,
		1.5-18.5f,4-3-4,
		1-18.5f,1-3-4,
		0-18.5f,1-3-4		
	};
	esat::Vec2 dots_map2[10]={
		11.5-18.5f,0-3-4,
		14.5-18.5f,0-3-4,
		15-18.5f,1-3-4,
		14-18.5f,1-3-4,
		13.5-18.5f,3-3-4,
		13-18.5f,1-3-4,
		12-18.5f,1-3-4,
		11.5-18.5f,4-3-4,
		11-18.5f,1-3-4,
		11.5-18.5f,0-3-4		
	};
	esat::Vec2 dots_map3[13]={
		18-18.5f,0-3-4,
		31-18.5f,0-3-4,
		31.5-18.5f,1-3-4,
		31-18.5f,3-3-4,
		30.5-18.5f,1-3-4,
		22-18.5f,1-3-4,
		21.5-18.5f,3-3-4,
		21-18.5f,1-3-4,
		20-18.5f,1-3-4,
		19.5-18.5f,4.5-3-4,
		19-18.5f,1-3-4,
		17.5-18.5f,1-3-4,
		18-18.5f,0-3-4		
	};
	esat::Vec2 dots_map4[4]={
		37-18.5f,0-3-4,
		35-18.5f,0-3-4,
		34-18.5f,1-3-4,
		37-18.5f,1-3-4
	};
	esat::Vec2 dots_map5[51]={
		0-18.5f,7-4,
		1-18.5f,6-4,
		2-18.5f,6-4,
		2.5-18.5f,4.5-4,
		3.5-18.5f,6.5-4,
		3.75-18.5f,6-4,
		4.5-18.5f,6-4,
		5-18.5f,5-4,
		6.5-18.5f,7-4,
		7.5-18.5f,7-4,
		8-18.5f,6-4,
		8.5-18.5f,4-4,
		9-18.5f,6-4,
		10-18.5f,7-4,
		10.5-18.5f,6-4,
		11.5-18.5f,6-4,
		12.5-18.5f,7.5-4,
		13-18.5f,6-4,
		14-18.5f,6-4,
		14.5-18.5f,7-4,
		15.5-18.5f,6-4,
		16-18.5f,7-4,
		17-18.5f,7-4,
		18-18.5f,5-4,
		19-18.5f,5-4,
		19.5-18.5f,4-4,
		20-18.5f,5-4,
		20.5-18.5f,4-4,
		21-18.5f,5-4,
		21.5-18.5f,5-4,
		22-18.5f,7-4,
		22.5-18.5f,7-4,
		23-18.5f,6-4,
		23.5-18.5f,4.5-4,
		25-18.5f,7-4,
		26-18.5f,7-4,
		26.5-18.5f,5.5-4,
		27-18.5f,7-4,
		27.5-18.5f,6.5-4,
		28-18.5f,6.5-4,
		28.5-18.5f,5-4,
		29-18.5f,7-4,
		29.5-18.5f,6-4,
		30.5-18.5f,6-4,
		31.5-18.5f,7-4,
		32.5-18.5f,6-4,
		34-18.5f,6-4,
		34.5-18.5f,4.5-4,
		35-18.5f,6-4,
		36-18.5f,6-4,
		37-18.5f,7-4		
	};
	
	esat::Vec2 map1[10],map2[10],map3[13],map4[4],map5[51];
	
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,550);	
		PlanetScale(scale_map);
	}
	s=esat::Mat3Scale(25*scale_map,18*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 10, false);
	DrawFigure(m, dots_map2, map2, 10, false);
	DrawFigure(m, dots_map3, map3, 13, false);
	DrawFigure(m, dots_map4, map4, 4, false);
	DrawFigure(m, dots_map5, map5, 51, false);
	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map1, map1, 10, false);
		DrawFigure(m, dots_map2, map2, 10, false);
		DrawFigure(m, dots_map3, map3, 13, false);
		DrawFigure(m, dots_map4, map4, 4, false);
		DrawFigure(m, dots_map5, map5, 51, false);
		LimitsMaps2(total_size,original_size);
	}
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map1,10,25*scale_map,18*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,10,25*scale_map,18*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map3,13,25*scale_map,18*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map4,4,25*scale_map,18*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map5,51,25*scale_map,18*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map1,10,25*scale_map,18*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,10,25*scale_map,18*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map3,13,25*scale_map,18*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map4,4,25*scale_map,18*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map5,51,25*scale_map,18*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}	
	}
	
}

void DrawMap4S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=35*scale_map*32,original_size=35*32;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=-56,(planet+1)->position.y=510;
		(planet+2)->position.x=87,(planet+2)->position.y=456;
		(planet+3)->position.x=207,(planet+3)->position.y=526;
		(planet+4)->position.x=761,(planet+4)->position.y=334;
		//5-12 turrets
		(planet+5)->position.x=-108,(planet+5)->position.y=429;
		(planet+6)->position.x=-5,(planet+6)->position.y=370;
		(planet+7)->position.x=56,(planet+7)->position.y=369;
		(planet+8)->position.x=151,(planet+8)->position.y=500;
		(planet+9)->position.x=268,(planet+9)->position.y=353;
		(planet+10)->position.x=509,(planet+10)->position.y=400;
		(planet+11)->position.x=690,(planet+11)->position.y=352;
		(planet+12)->position.x=879,(planet+12)->position.y=362;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=-209;*(more_y+0)=-5;
			*(more_x+1)=-143;*(more_y+1)=-30;
			*(more_x+2)=-73;*(more_y+2)=3;
			*(more_x+3)=204;*(more_y+3)=-91;
			// TURRETS
			*(more_x+4)=-262;*(more_y+4)=-53;
			*(more_x+5)=-261+64;*(more_y+5)=-74+3;
			*(more_x+6)=-173;*(more_y+6)=-81;
			*(more_x+7)=-135;*(more_y+7)=-17;
			*(more_x+8)=-68-290+315;*(more_y+8)=-85+7;
			*(more_x+9)=349-288;*(more_y+9)=-54-12;
			*(more_x+10)=155;*(more_y+10)=-70;
			*(more_x+11)=232;*(more_y+11)=-62;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.32);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.28);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.32);
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.20);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.08);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.32);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.62);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.32);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.28);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.32);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.20);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.08);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.32);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.62);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	esat::Vec2 dots_map1[35]={
		0-16,2-2.75f,
		0.5-16,3-2.75f,
		1-16,2-2.75f,
		2-16,3.5-2.75f,
		1-16,5-2.75f,
		4-16,5-2.75f,
		5.5-16,2-2.75f,
		4-16,0.5-2.75f,
		4.5-16,0-2.75f,
		5.5-16,0-2.75f,
		6.5-16,1.5-2.75f,
		6-16,3.5-2.75f,
		8-16,3.5-2.75f,
		8.5-16,1.5-2.75f,
		8-16,0-2.75f,
		9-16,0-2.75f,
		10-16,1-2.75f,
		8.5-16,4.5-2.75f,
		10-16,5.5-2.75f,
		12-16,5.5-2.75f,
		13.5-16,2.5-2.75f,
		12-16,0.5-2.75f,
		14-16,1-2.75f,
		16-16,3-2.75f,
		18-16,3-2.75f,
		20-16,1-2.75f,
		20.5-16,2-2.75f,
		22-16,2.5-2.75f,
		24-16,5-2.75f,
		29-16,5-2.75f,
		27.5-16,2.5-2.75f,
		29-16,2.5-2.75f,
		30-16,0-2.75f,
		31-16,2-2.75f,
		32-16,2-2.75f		
	};
	esat::Vec2 dots_map2[6]={
		24-16,0-2.75f,
		28-16,0-2.75f,
		26-16,3-2.75f,
		24.5-16,2.5-2.75f,
		25-16,1.5-2.75f,
		24-16,0-2.75f
	};
	
	esat::Vec2 map1[35],map2[6];
	
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,450);	
		PlanetScale(scale_map);
	}
	
	s=esat::Mat3Scale(35*scale_map,35*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 35, false);
	DrawFigure(m, dots_map2, map2, 6, false);
	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map1, map1, 35, false);
		DrawFigure(m, dots_map2, map2, 6, false);
		LimitsMaps2(total_size,original_size);
	}
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map1,35,35*scale_map,35*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,6,35*scale_map,35*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map1,35,35*scale_map,35*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,6,35*scale_map,35*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}
}

void DrawMap5S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	// CUANDO ACTIVAS EL REACTOR SE ACTIVAN TORRETAS
	esat::Vec2 dots_reactor[10]={
		1-2.5,0,
		0-2.5,2.5,
		1-2.5,4,
		4-2.5,4,
		5-2.5,2.5,
		4-2.5,0,
		0-2.5,2.5,
		2.5-2.5,4,
		5-2.5,2.5,
		1-2.5,0
	};
	esat::Vec2 map1[21],reactor[10];
	
	if(scale_map>=1){
		if(player.reactor==true){
			//5-12 turrets
			(planet+5)->position.x=180,(planet+5)->position.y=259;
			(planet+6)->position.x=108,(planet+6)->position.y=403;
			(planet+7)->position.x=290,(planet+7)->position.y=520;
			(planet+8)->position.x=372,(planet+8)->position.y=558;
			(planet+9)->position.x=472,(planet+9)->position.y=515;
			(planet+10)->position.x=692,(planet+10)->position.y=336;
			(planet+11)->position.x=607,(planet+11)->position.y=238;
			(planet+12)->position.x=362,(planet+12)->position.y=302;
			// TORRETAS
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*0.75);
			t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
			ResetM(m,s,r,t);
			if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*0.19);
			t=esat::Mat3Translate((planet+6)->position.x,(planet+6)->position.y);
			ResetM(m,s,r,t);
			if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*0.19);
			t=esat::Mat3Translate((planet+7)->position.x,(planet+7)->position.y);
			ResetM(m,s,r,t);
			if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(0);
			t=esat::Mat3Translate((planet+8)->position.x,(planet+8)->position.y);
			ResetM(m,s,r,t);
			if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi);
			t=esat::Mat3Translate((planet+9)->position.x,(planet+9)->position.y);
			ResetM(m,s,r,t);
			if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*1.28);
			t=esat::Mat3Translate((planet+10)->position.x,(planet+10)->position.y);
			ResetM(m,s,r,t);
			if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
			
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*1.28);
			t=esat::Mat3Translate((planet+11)->position.x,(planet+11)->position.y);
			ResetM(m,s,r,t);
			if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
			
			
			s=esat::Mat3Scale(8*scale_map,8*scale_map);
			r=esat::Mat3Rotate(pi*0.22);
			t=esat::Mat3Translate((planet+12)->position.x,(planet+12)->position.y);
			ResetM(m,s,r,t);
			if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
			
			for(int i=4;i<12;i++){
				TurretsShooting(i,0,0,0);
			}
			for(int i=12;i<16;i++){
				ColisionFuel(i,0,0,0);
			}
		}
		
		s=esat::Mat3Scale(5,3.5);
		t=esat::Mat3Translate(531,363);
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		if(player.reactor==false)esat::DrawSetStrokeColor(254,0,251);
		else esat::DrawSetStrokeColor(0,100,251);
		DrawFigure(m, dots_reactor, reactor, 10, false);
		
		if(player.total_shots>0){
			shot=primero;
			while(shot!=NULL){
				if(shot->alive==true){
					if(CheckCircleColision(shot->position.x,shot->position.y,0.5*scale_map,
					531,363,10*scale_map)){
						player.reactor=true;
						//player.score+=player.bonus;
					}
				}
				shot=shot->prox;
			}
		}	
	}
	
	esat::Vec2 dots_map1[21]={
		1-6,0,
		3-6,2,
		0-6,6,
		5-6,10,
		9-6,10,
		12-6,6,
		9.5f-6,2.5f,
		6-6,2.5,
		5-6,4,
		7.5-6,6.5f,
		9-6,6.5,
		9.5-6,6,
		8.5f-6,4.5f,
		7.5f-6,4.5f,
		7-6,4,
		9-6,4,
		10.5f-6,6,
		8-6,9,
		5.7f-6,9,
		2-6,6,
		7-6,0
	};
	
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,80);	
		PlanetScale(scale_map);
	}
	
	s=esat::Mat3Scale(55*scale_map,45*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 21, false);
	
	if(CheckLineColision(dots_map1,21,55*scale_map,45*scale_map,(planet+0)->position.x,(planet+0)->position.y)){
		//player.alive=false;
	}
}

void DrawMap6S1(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=50*scale_map*17, original_size=50*17;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=197,(planet+1)->position.y=429;
		(planet+2)->position.x=423,(planet+2)->position.y=555;
		(planet+3)->position.x=691,(planet+3)->position.y=480;
		(planet+4)->position.x=789,(planet+4)->position.y=429;
		//5-12 turrets
		(planet+5)->position.x=41,(planet+5)->position.y=452;
		(planet+6)->position.x=197,(planet+6)->position.y=431;
		(planet+7)->position.x=321,(planet+7)->position.y=454;
		(planet+8)->position.x=353,(planet+8)->position.y=494;
		(planet+9)->position.x=490,(planet+9)->position.y=514;
		(planet+10)->position.x=605,(planet+10)->position.y=449;
		(planet+11)->position.x=646,(planet+11)->position.y=451;
		(planet+12)->position.x=791,(planet+12)->position.y=430;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=-94;*(more_y+0)=-43;
			*(more_x+1)=0;*(more_y+1)=17;
			*(more_x+2)=147;*(more_y+2)=-19;
			*(more_x+3)=198;*(more_y+3)=-43;
			// TURRETS
			*(more_x+4)=-185;*(more_y+4)=-36;
			*(more_x+5)=-111;*(more_y+5)=-45;
			*(more_x+6)=-42;*(more_y+6)=-32;
			*(more_x+7)=-29;*(more_y+7)=-16;
			*(more_x+8)=50;*(more_y+8)=-7;
			*(more_x+9)=85;*(more_y+9)=-15;
			*(more_x+10)=116;*(more_y+10)=-39;
			*(more_x+11)=204;*(more_y+11)=-42;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	// MAP
	esat::Vec2 dots_map[15]={
		0-8.5,0,
		1-8.5,0,
		2-8.5,1.5,
		3-8.5,1.5,
		4-8.5,0,
		6.5-8.5,0,
		8.5-8.5,2.5,
		9.5-8.5,2.5,
		11-8.5,1,
		12-8.5,1,
		13-8.5,0,
		14-8.5,1,
		15-8.5,1,
		16-8.5,0,
		17-8.5,0
	};
	esat::Vec2 map[15];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,450);	
		PlanetScale(scale_map);
	}
	s=esat::Mat3Scale(50*scale_map,50*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 15, false);
	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x+pppp*scale_map-total_size,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map, map, 15, false);
		LimitsMaps2(total_size,original_size);
	}
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map,15,50*scale_map,50*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map,15,50*scale_map,50*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}
}
	
	//SISTEMA SOLAR 2
void DrawMap1S2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	new_ss=true;
	char ggg[20];
	esat::DrawSetTextSize(20*scale_map);
	player.last_screen=12;
	//OCTAGON START
	DotsOctagonStart(m,(planet+6)->position.x,(planet+6)->position.y);
	PlanetZoom((planet+6)->position.x,(planet+6)->position.y,400,400);
	
	//STAR
	bool lines=true;
	s=esat::Mat3Scale(4*scale_map,4*scale_map);
	r=esat::Mat3Rotate(0);
	esat::DrawSetStrokeColor(242,244,53);
	DotsStar(m,s,r,(planet+0)->position.x,(planet+0)->position.y,lines);
	PlanetZoom((planet+0)->position.x,(planet+0)->position.y,267,260);
	if(scale_map>=1 && CheckCircleColision(player.position.x,player.position.y,10,
	(planet+0)->position.x,(planet+0)->position.y,10)){
		player.alive=false;
	}
	
	if(*(planet_alive+2)==0){
		//9000 RED OCTAGON
		*(count_figure+3)+=1;
		float size_line=0;
		if(*(count_figure+3)<10)size_line=+5*scale_map;
		else if(*(count_figure+3)>=10 && *(count_figure+3)<20)size_line=-5*scale_map;
		else size_line=-15*scale_map;
		
		s=esat::Mat3Scale(15*scale_map,15*scale_map);
		r=esat::Mat3Rotate(0);
		esat::DrawSetStrokeColor(244,82,53);
		DotsOctagon2(m,s,r,(planet+1)->position.x,(planet+1)->position.y, size_line);
		PlanetZoom((planet+1)->position.x,(planet+1)->position.y,676,120);

		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+0),ggg,10);
		esat::DrawText((planet+1)->position.x+34,(planet+1)->position.y-45,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+1)->position.x,(planet+1)->position.y,35)){
				LastPosition(-40,0);AllIni();
				NewPosition(8,400,100,3);
			}
		}
	}
	if(*(planet_alive+1)==0){
		//9000 MAZE
		esat::Vec2 dots_maze[15]={
			4-3.5f,4-3.5f,
			3-3.5f,4-3.5f,
			3-3.5f,3-3.5f,
			5-3.5f,3-3.5f,
			5-3.5f,5-3.5f,
			2-3.5f,5-3.5f,
			2-3.5f,2-3.5f,
			6-3.5f,2-3.5f,
			6-3.5f,6-3.5f,
			1-3.5f,6-3.5f,
			1-3.5f,1-3.5f,
			7-3.5f,1-3.5f,
			7-3.5f,7-3.5f,
			0-3.5f,7-3.5f,
			0-3.5f,0-3.5f
		};
		
		esat::Vec2 maze[15];
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(*(count_figure+7));
		t=esat::Mat3Translate((planet+2)->position.x,(planet+2)->position.y);
		ResetM(m,s,r,t);
		esat::DrawSetStrokeColor(242,244,53);
		DrawFigure(m, dots_maze, maze, 15, false);
		PlanetZoom((planet+2)->position.x,(planet+2)->position.y,400,152);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+1),ggg,10);
		esat::DrawText((planet+2)->position.x-20,(planet+2)->position.y-38,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+2)->position.x,(planet+2)->position.y,35)){
				LastPosition(0,40);AllIni();
				NewPosition(18,400,100,3);
			}
		}
	}
	if(*(planet_alive+0)==0){
		//9000 OCTAGON PINK
		//animacion rara
		esat::DrawSetStrokeColor(249, 0, 255);
		esat::DrawLine((planet+3)->position.x-8*scale_map,(planet+3)->position.y-8*scale_map,(planet+3)->position.x-15*scale_map,(planet+3)->position.y-17*scale_map);
		esat::DrawLine((planet+3)->position.x+8*scale_map,(planet+3)->position.y-8*scale_map,(planet+3)->position.x+15*scale_map,(planet+3)->position.y-17*scale_map);
		esat::DrawLine((planet+3)->position.x-8*scale_map,(planet+3)->position.y+8*scale_map,(planet+3)->position.x-15*scale_map,(planet+3)->position.y+17*scale_map);
		esat::DrawLine((planet+3)->position.x+8*scale_map,(planet+3)->position.y+8*scale_map,(planet+3)->position.x+15*scale_map,(planet+3)->position.y+17*scale_map);
		s=esat::Mat3Scale(10*scale_map,11*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+3)->position.x,(planet+3)->position.y);
		DotsOctagon(m,s,r,t);
		s=esat::Mat3Scale(6*scale_map,7*scale_map);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+3)->position.x,(planet+3)->position.y,90,420);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+2),ggg,10);
		esat::DrawText((planet+3)->position.x-65,(planet+3)->position.y,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+3)->position.x,(planet+3)->position.y,20)){
				LastPosition(40,00);AllIni();
				NewPosition(16,400,100,3);
			}
		}
	}
	if(*(planet_alive+3)==0){
		//9000 EYE
		//animacion rara
		esat::DrawSetStrokeColor(255, 255, 255);
		
		if(*(count_figure+9)<25){
			
		}else if(*(count_figure+9)>=25){
			esat::DrawLine((planet+4)->position.x+17*scale_map,(planet+4)->position.y,(planet+4)->position.x+25*scale_map,(planet+4)->position.y);
			esat::DrawLine((planet+4)->position.x+17*scale_map,(planet+4)->position.y,(planet+4)->position.x,(planet+4)->position.y+18*scale_map);
		}
		s=esat::Mat3Scale(12*scale_map,9*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+4)->position.x,(planet+4)->position.y);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+4)->position.x,(planet+4)->position.y,580,330);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+3),ggg,10);
		esat::DrawText((planet+4)->position.x+35,(planet+4)->position.y,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+4)->position.x,(planet+4)->position.y,20)){
				LastPosition(-40,0);AllIni();
				NewPosition(17,400,100,3);
			}
		}
	}
	if(*(planet_alive+4)==0){
		//9000 OCTAGON GREEN
		esat::DrawSetStrokeColor(242,244,53);
		esat::DrawLine((planet+5)->position.x-20*scale_map,(planet+5)->position.y-5*scale_map,
		(planet+5)->position.x+20*scale_map,(planet+5)->position.y+5*scale_map);
		
		esat::DrawSetStrokeColor(255,0,0);
		esat::DrawSetFillColor(255,255,255);
		if(*(count_figure+8)<5)Circle(g_circle,(planet+5)->position.x+8,(planet+5)->position.y-14,1.5,1.5);
		else if(*(count_figure+8)>=5 && *(count_figure+8)<10)Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y-14,1.5,1.5);
		else if(*(count_figure+8)>=10 && *(count_figure+8)<15)Circle(g_circle,(planet+5)->position.x-8,(planet+5)->position.y-14,1.5,1.5);
		
		esat::DrawSetStrokeColor(0, 255, 0);
		s=esat::Mat3Scale(6*scale_map,6*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+5)->position.x,(planet+5)->position.y,460,540);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+4),ggg,10);
		esat::DrawText((planet+5)->position.x-20,(planet+5)->position.y+30,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+5)->position.x,(planet+5)->position.y,15)){
				LastPosition(0,-40);AllIni();
				NewPosition(19,400,100,3);
			}
		}
	}
}
		//MAPS
void DrawMap2S2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=30*scale_map*24;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=130,(planet+1)->position.y=370;
		(planet+2)->position.x=242,(planet+2)->position.y=579;
		(planet+3)->position.x=599,(planet+3)->position.y=369;
		(planet+4)->position.x=533,(planet+4)->position.y=505;
		//5-12 turrets
		(planet+5)->position.x=291,(planet+5)->position.y=176;
		(planet+6)->position.x=199,(planet+6)->position.y=193;
		(planet+7)->position.x=158,(planet+7)->position.y=312;
		(planet+8)->position.x=235,(planet+8)->position.y=449;
		(planet+9)->position.x=403,(planet+9)->position.y=366;
		(planet+10)->position.x=471,(planet+10)->position.y=299;
		(planet+11)->position.x=537,(planet+11)->position.y=326;
		(planet+12)->position.x=606,(planet+12)->position.y=469;
		
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x,(planet+1)->position.y,10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x,(planet+2)->position.y,10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x,(planet+3)->position.y,10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x,(planet+4)->position.y,10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.32);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.70);
		t=esat::Mat3Translate((planet+6)->position.x,(planet+6)->position.y);
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+7)->position.x,(planet+7)->position.y);
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.28);
		t=esat::Mat3Translate((planet+8)->position.x,(planet+8)->position.y);
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+9)->position.x,(planet+9)->position.y);
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+10)->position.x,(planet+10)->position.y);
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x,(planet+11)->position.y);
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.73);
		t=esat::Mat3Translate((planet+12)->position.x,(planet+12)->position.y);
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,0,0,0);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,0,0,0);
		}
	}
	// MAP
	esat::Vec2 dots_map[40]={
		0-12,11,
		2-12,9,
		6-12,0,
		8-12,0,
		10-12,2,
		8-12,4,
		10-12,7,
		8-12,7,
		6-12,4,
		4-12,7,
		6-12,7,
		2-12,11,
		4-12,11,
		2-12,13,
		6-12,18,
		8-12,18,
		10-12,15.5,
		8-12,15.5,
		6-12,13,
		10-12,13,
		16-12,7,
		17.5-12,7,
		16-12,9,
		18-12,11,
		19.5-12,11,
		18-12,13,
		12-12,13,
		14-12,15.5,
		18-12,15.5,
		21.5-12,11,
		20-12,9,
		18-12,9,
		19.5-12,6.5,
		17.5-12,4.5,
		13.5-12,4.5,
		12-12,7,
		10-12,4.5,
		14-12,0,
		17-12,0,
		24-12,12		
	};
	esat::Vec2 map[40];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,00);	
		PlanetScale(scale_map);
	}
	s=esat::Mat3Scale(30*scale_map,30*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 40, false);	
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map,40,30*scale_map,30*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map,40,30*scale_map,30*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}
}

void DrawMap3S2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=15*scale_map*60,original_size=15*60;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=74,(planet+1)->position.y=436;
		(planet+2)->position.x=190,(planet+2)->position.y=436;
		(planet+3)->position.x=388,(planet+3)->position.y=496;
		(planet+4)->position.x=765,(planet+4)->position.y=377;
		//5-12 turrets
		(planet+5)->position.x=46,(planet+5)->position.y=401;
		(planet+6)->position.x=94,(planet+6)->position.y=280;
		(planet+7)->position.x=215,(planet+7)->position.y=291;
		(planet+8)->position.x=270,(planet+8)->position.y=397;
		(planet+9)->position.x=323,(planet+9)->position.y=329;
		(planet+10)->position.x=398,(planet+10)->position.y=496;
		(planet+11)->position.x=617,(planet+11)->position.y=355;
		(planet+12)->position.x=726,(planet+12)->position.y=350;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=-140-77+72;*(more_y+0)=-27+75;
			*(more_x+1)=-66-20;*(more_y+1)=-25+71;
			*(more_x+2)=29;*(more_y+2)=-34+110;
			*(more_x+3)=150+56;*(more_y+3)=-26+42;
			// TURRETS
			*(more_x+4)=-104-93+12;*(more_y+4)=-98+134;
			*(more_x+5)=-46-95;*(more_y+5)=-17-12;
			*(more_x+6)=20-91-31;*(more_y+6)=-98+78;
			*(more_x+7)=70-103-8;*(more_y+7)=-17+66;
			*(more_x+8)=120-90-83;*(more_y+8)=-98+78;
			*(more_x+9)=81-78;*(more_y+9)=-17+92;
			*(more_x+10)=157-48;*(more_y+10)=-98+102;
			*(more_x+11)=206-32;*(more_y+11)=-26+15;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.30);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		r=esat::Mat3Rotate(pi*0.75);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.30);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.28);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	// MAP
	esat::Vec2 dots_map[17]={
		0-7.5,2,
		2-7.5,0,
		3-7.5,1,
		1-7.5,3,
		6-7.5,3,
		4-7.5,1,
		5-7.5,0,
		7-7.5,2,
		8.5-7.5,2,
		7-7.5,4,
		8-7.5,4,
		9.5-7.5,2,
		11.5-7.5,2,
		10.5-7.5,1,
		13.5-7.5,1,
		12.5-7.5,2,
		15-7.5,2
	};
	esat::Vec2 map[17];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,250);	
		PlanetScale(scale_map);
	}
	
	s=esat::Mat3Scale(60*scale_map,60*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 17, false);	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map, map, 17, false);
		LimitsMaps2(total_size,original_size);
	}
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map,17,60*scale_map,60*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map,17,60*scale_map,60*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}	
	}
}

void DrawMap4S2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=28*scale_map*25,original_size=28*25;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=224-40,(planet+1)->position.y=315;
		(planet+2)->position.x=356-40,(planet+2)->position.y=391;
		(planet+3)->position.x=601-40,(planet+3)->position.y=378;
		(planet+4)->position.x=665-40,(planet+4)->position.y=328;
		//5-12 turrets
		(planet+5)->position.x=204-40,(planet+5)->position.y=396;
		(planet+6)->position.x=256-40,(planet+6)->position.y=278;
		(planet+7)->position.x=360-40,(planet+7)->position.y=281;
		(planet+8)->position.x=316-40,(planet+8)->position.y=341;
		(planet+9)->position.x=502-40,(planet+9)->position.y=375;
		(planet+10)->position.x=566-40,(planet+10)->position.y=337;
		(planet+11)->position.x=621-40,(planet+11)->position.y=299;
		(planet+12)->position.x=684-40,(planet+12)->position.y=370;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=-134;*(more_y+0)=26;
			*(more_x+1)=-69;*(more_y+1)=62;
			*(more_x+2)=58;*(more_y+2)=58;
			*(more_x+3)=96;*(more_y+3)=32;
			// TURRETS
			*(more_x+4)=-146;*(more_y+4)=84;
			*(more_x+5)=-11-100;*(more_y+5)=4;
			*(more_x+6)=-50-12;*(more_y+6)=13;
			*(more_x+7)=-88;*(more_y+7)=17;
			*(more_x+8)=8;*(more_y+8)=-16;
			*(more_x+9)=51;*(more_y+9)=30;
			*(more_x+10)=58;*(more_y+10)=2;
			*(more_x+11)=108;*(more_y+11)=61;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.65);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.65);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.62);
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.38);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.28);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.34);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.65);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.65);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.62);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.38);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.28);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.75);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.34);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	// MAP
	esat::Vec2 dots_map[18]={
		0-14,11,
		2-14,11,
		4-14,7,
		2-14,7,
		3.5-14,5.5,
		4.5-14,5.5,
		7-14,0,
		9-14,0,
		10.5-14,1.5,
		9-14,5,
		7-14,5,
		8.5-14,8.5,
		10.5-14,8.5,
		12-14,12,
		14-14,12,
		16-14,10,
		27-14,10,
		28-14,11
	};
	esat::Vec2 dots_map2[21]={
		17-14,5,
		14-14,5,
		15.5-14,6.5,
		14-14,6.5,
		16-14,9,
		21-14,9,
		20-14,8,
		16-14,8,
		19-14,5,
		21-14,7,
		22-14,7,
		22.5-14,8,
		22-14,9,
		24-14,9,
		22.5-14,6,
		21-14,6,
		19-14,4,
		17.5-14,0.5,
		16.5-14,0.5,
		15.5-14,1.5,
		17-14,5
	};
	esat::Vec2 map[18],map2[21];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,440,160);	
		PlanetScale(scale_map);
		ppp=40;pppp=40;
	}
	
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 18, false);
	DrawFigure(m, dots_map2, map2, 21, false);	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map, map, 18, false);
		DrawFigure(m, dots_map2, map2, 21, false);
		LimitsMaps2(total_size,original_size);
	}
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map,18,25*scale_map,25*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,21,25*scale_map,25*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map,18,25*scale_map,25*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,21,25*scale_map,25*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}	
	}
}

void DrawMap5S2(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	// MAP
	esat::Vec2 dots_map[53]={
		0-14.5,0,
		2-14.5,0,
		0.5-14.5,1.5,
		3.5-14.5,5,
		6.5-14.5,5,
		8-14.5,3,
		8.5-14.5,3,
		9-14.5,2.5,
		10-14.5,2.5,
		8-14.5,0.5,
		6-14.5,3,
		5-14.5,3,
		3-14.5,0,
		11-14.5,0,
		11.5-14.5,0.5,
		11-14.5,1,
		13-14.5,2,
		12-14.5,3,
		11.5-14.5,2,
		11-14.5,2,
		10-14.5,4,
		10.5-14.5,4.5,
		11-14.5,4.5,
		11.5-14.5,4,
		13-14.5,4,
		14.5-14.5,1.5,
		13-14.5,0,
		14.5-14.5,0,
		16-14.5,3,
		18-14.5,3.5,
		19-14.5,4.5,
		20-14.5,4.5,
		20.5-14.5,3.5,
		21.5-14.5,3.5,
		22.5-14.5,2.5,
		23.5-14.5,2.5,
		22-14.5,1,
		20-14.5,1,
		19.5-14.5,1.5,
		18.5-14.5,1.5,
		18-14.5,2,
		17.5-14.5,2,
		16-14.5,1,
		15.5-14.5,0,
		23.5-14.5,0,
		25-14.5,3,
		26-14.5,3,
		26.5-14.5,2.5,
		28.5-14.5,2.5,
		27-14.5,1,
		25-14.5,1,
		26-14.5,0,
		29-14.5,0
	};
	esat::Vec2 map[53];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,400);	
		PlanetScale(scale_map);
	}
	float total_size=29*scale_map*30,original_size=29*30;
	s=esat::Mat3Scale(30*scale_map,30*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	m = esat::Mat3Identity();
	m = esat::Mat3Multiply(s, m);
	m = esat::Mat3Multiply(r, m);
	m = esat::Mat3Multiply(t, m);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map, map, 53, false);
	
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map, map, 53, false);
		LimitsMaps2(total_size,original_size);
	}	
}

	//SISTEMA SOLAR 3
void DrawMap1S3(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	new_ss=true;
	char ggg[20];
	esat::DrawSetTextSize(20*scale_map);
	player.last_screen=13;
	//OCTAGON START
	DotsOctagonStart(m,(planet+0)->position.x,(planet+0)->position.y);
	PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,400);
	
	if(*(planet_alive+0)==0){
		//9000 BLUE STAR
		esat::Vec2 dots_star[6]={
			7.5-7.5f,0-6.5f,
			12-7.5f,13-6.5f,
			1-7.5f,5-6.5f,
			14-7.5f,5-6.5f,
			3-7.5f,13-6.5f,
			7.5-7.5f,0-6.5f
		};
		esat::Vec2 star[6];
		esat::DrawSetStrokeColor(0, 245, 255);
		s=esat::Mat3Scale(3*scale_map,3*scale_map);
		if(*(count_figure+10)<10){r=esat::Mat3Rotate(pi*0.10);}
		else{r=esat::Mat3Rotate(pi*0.20);}
		t=esat::Mat3Translate((planet+1)->position.x,(planet+1)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_star, star, 6, false);
		s=esat::Mat3Scale(2.5*scale_map,2.5*scale_map);
		if(*(count_figure+10)<10){r=esat::Mat3Rotate(pi*0.10);}
		else{r=esat::Mat3Rotate(pi*0.20);}
		ResetM(m,s,r,t);
		DrawFigure(m, dots_star, star, 6, false);
		s=esat::Mat3Scale(2*scale_map,2*scale_map);
		if(*(count_figure+10)<10)r=esat::Mat3Rotate(pi*0.10);
		else{r=esat::Mat3Rotate(pi*0.20);}
		ResetM(m,s,r,t);
		DrawFigure(m, dots_star, star, 6, false);
		PlanetZoom((planet+1)->position.x,(planet+1)->position.y,650,500);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+0),ggg,10);
		esat::DrawText((planet+1)->position.x+15,(planet+1)->position.y+40,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+1)->position.x,(planet+1)->position.y,30)){
				(planet+0)->position.x=0;(planet+0)->position.y=500;			
				LastPosition(-40,0);AllIni();
				NewPosition(11,400,100,3);
			}
		}
	}
	//STAR
	bool lines=true;
	s=esat::Mat3Scale(4*scale_map,4*scale_map);
	r=esat::Mat3Rotate(0);
	esat::DrawSetStrokeColor(242,244,53);
	DotsStar(m,s,r,(planet+2)->position.x,(planet+2)->position.y,lines);
	PlanetZoom((planet+2)->position.x,(planet+2)->position.y,480,235);
	if(scale_map>=1 && CheckCircleColision(player.position.x,player.position.y,10,
	(planet+2)->position.x,(planet+2)->position.y,10)){
		player.alive=false;
	}
	
	if(*(planet_alive+2)==0){
		//9000 RED OCTAGON
		*(count_figure+3)+=1;
		float size_line=0;
		if(*(count_figure+3)<10)size_line=+5*scale_map;
		else if(*(count_figure+3)>=10 && *(count_figure+3)<20)size_line=-5*scale_map;
		else size_line=-15*scale_map;
		
		s=esat::Mat3Scale(15*scale_map,15*scale_map);
		r=esat::Mat3Rotate(0);
		esat::DrawSetStrokeColor(244,82,53);
		DotsOctagon2(m,s,r,(planet+3)->position.x,(planet+3)->position.y, size_line);
		PlanetZoom((planet+3)->position.x,(planet+3)->position.y,130,300);

		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+1),ggg,10);
		esat::DrawText((planet+3)->position.x-70,(planet+3)->position.y+20,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+3)->position.x,(planet+3)->position.y,35)){
				LastPosition(40,0);AllIni();
				NewPosition(8,400,100,3);
			}
		}
	}
	if(*(planet_alive+1)==0){
		//9000 GREEN OCTAGON CONCAVO
		esat::Vec2 dots_semicirle[4]={
			-1-2,0-1.5f,
			2-2,1-1.5f,
			2-2,2-1.5f,
			5-2,3-1.5f
		};
		esat::Vec2 dots_semicirle2[4]={
			5-2,0-1.5f,
			2-2,1-1.5f,
			2-2,2-1.5f,
			-1-2,3-1.5f
		};
		esat::Vec2 semicirle[4];
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(0);
		
		
		if(*(count_figure+11)<6){
			esat::DrawSetStrokeColor(255, 255, 255);
			t=esat::Mat3Translate((planet+4)->position.x,(planet+4)->position.y);
			ResetM(m,s,r,t);
			DrawFigure(m, dots_semicirle, semicirle, 4, false);
			esat::DrawSetStrokeColor(255, 0, 0);
			esat::DrawLine((planet+4)->position.x,(planet+4)->position.y-14*scale_map,(planet+4)->position.x+25*scale_map,(planet+4)->position.y-22*scale_map);
			esat::DrawLine((planet+4)->position.x,(planet+4)->position.y+14*scale_map,(planet+4)->position.x-25*scale_map,(planet+4)->position.y+22*scale_map);
			
		}else{
			esat::DrawSetStrokeColor(255, 255, 255);
			t=esat::Mat3Translate((planet+4)->position.x,(planet+4)->position.y-13);
			ResetM(m,s,r,t);
			DrawFigure(m, dots_semicirle2, semicirle, 4, false);
			esat::DrawSetStrokeColor(255, 0, 0);
			esat::DrawLine((planet+4)->position.x,(planet+4)->position.y-14*scale_map,(planet+4)->position.x-25*scale_map,(planet+4)->position.y-22*scale_map);
			esat::DrawLine((planet+4)->position.x,(planet+4)->position.y+14*scale_map,(planet+4)->position.x+25*scale_map,(planet+4)->position.y+22*scale_map);
		}
		
		s=esat::Mat3Scale(7*scale_map,7*scale_map);
		r=esat::Mat3Rotate(0);
		t=esat::Mat3Translate((planet+4)->position.x,(planet+4)->position.y);
		esat::DrawSetStrokeColor(32, 255, 0);
		DotsOctagon(m,s,r,t);
		PlanetZoom((planet+4)->position.x,(planet+4)->position.y,140,520);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+2),ggg,10);
		esat::DrawText((planet+4)->position.x-20,(planet+4)->position.y+40,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+4)->position.x,(planet+4)->position.y,30)){
				LastPosition(0,-40);AllIni();
				NewPosition(10,400,100,3);
			}
		}
	}
	if(*(planet_alive+3)==0){
		//9000 3 CIRCLE 
		if(*(count_figure+12)<8){
			esat::DrawSetStrokeColor(255, 0, 0);
			esat::DrawSetFillColor(0,0,0);
			esat::DrawSetFillColor(0, 0, 0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,20*scale_map,3*scale_map);
		}else if(*(count_figure+12)>=8 && *(count_figure+12)<16){
			esat::DrawSetStrokeColor(255, 0, 0);
			esat::DrawSetFillColor(0,0,0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,20*scale_map,3*scale_map);
			esat::DrawSetStrokeColor(255, 255, 255);
			Circle3(g_circle,(planet+5)->position.x,(planet+5)->position.y+10*scale_map,20/2*scale_map,40/2*scale_map);
		}else if(*(count_figure+12)>=16 && *(count_figure+12)<24){
			esat::DrawSetStrokeColor(255, 0, 0);
			esat::DrawSetFillColor(0,0,0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,20*scale_map,3*scale_map);
			esat::DrawSetStrokeColor(255, 255, 255);
			Circle3(g_circle,(planet+5)->position.x,(planet+5)->position.y+10*scale_map,20/2*scale_map,40/2*scale_map);
			Circle2(g_circle,(planet+5)->position.x,(planet+5)->position.y-10*scale_map,20/2*scale_map,40/2*scale_map);
		}else if(*(count_figure+12)>=24 && *(count_figure+12)<32){
			esat::DrawSetStrokeColor(174, 0, 255);
			esat::DrawSetFillColor(0,0,0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,3*scale_map,20*scale_map);
		}else if(*(count_figure+12)>=32 && *(count_figure+12)<40){
			esat::DrawSetStrokeColor(174, 0, 255);
			esat::DrawSetFillColor(0,0,0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,3*scale_map,20*scale_map);
			esat::DrawSetStrokeColor(255, 255, 255);
			Circle2(g_circle,(planet+5)->position.x,(planet+5)->position.y-10*scale_map,20/2*scale_map,40/2*scale_map);
		}else{
			esat::DrawSetStrokeColor(174, 0, 255);
			esat::DrawSetFillColor(0,0,0);
			Circle(g_circle,(planet+5)->position.x,(planet+5)->position.y,3*scale_map,20*scale_map);
			esat::DrawSetStrokeColor(255, 255, 255);
			Circle2(g_circle,(planet+5)->position.x,(planet+5)->position.y-10*scale_map,20/2*scale_map,40/2*scale_map);
			Circle3(g_circle,(planet+5)->position.x,(planet+5)->position.y+10*scale_map,20/2*scale_map,40/2*scale_map);
		}
		PlanetZoom((planet+5)->position.x,(planet+5)->position.y,250,130);
		
		esat::DrawSetFillColor(0, 254, 250);
		itoa(*(planet_bonus+3),ggg,10);
		esat::DrawText((planet+5)->position.x-70,(planet+5)->position.y-20,ggg);
		
		if(scale_map>=1){
			if(CheckCircleColision(player.position.x,player.position.y,20,
			(planet+5)->position.x,(planet+5)->position.y,35)){
				LastPosition(0,40);AllIni();
				NewPosition(9,400,100,3);
			}
		}
	}
}
		//MAPS
void DrawMap6S3(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	float total_size=22*scale_map*40,original_size=22*40;
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=364+87,(planet+1)->position.y=529-52;
		(planet+2)->position.x=463+87,(planet+2)->position.y=485-52;
		(planet+3)->position.x=563+87,(planet+3)->position.y=540-52;
		(planet+4)->position.x=619+87,(planet+4)->position.y=540-52;
		//5-12 turrets
		(planet+5)->position.x=43+87,(planet+5)->position.y=558-52;
		(planet+6)->position.x=100+87,(planet+6)->position.y=429-52;
		(planet+7)->position.x=209+87,(planet+7)->position.y=429-52;
		(planet+8)->position.x=280+87,(planet+8)->position.y=558-52;
		(planet+9)->position.x=348+87,(planet+9)->position.y=468-52;
		(planet+10)->position.x=502+87,(planet+10)->position.y=446-52;
		(planet+11)->position.x=667+87,(planet+11)->position.y=555-52;
		(planet+12)->position.x=845-29+87,(planet+12)->position.y=453+20-52;
		
		float *more_x=(float*)calloc(12,sizeof(float)),
			*more_y=(float*)calloc(12,sizeof(float));
		if(scale_map<1.25){
			// QUADS
			*(more_x+0)=0;*(more_y+0)=0;
			*(more_x+1)=0;*(more_y+1)=0;
			*(more_x+2)=0;*(more_y+2)=0;
			*(more_x+3)=0;*(more_y+3)=0;
			// TURRETS
			*(more_x+4)=0;*(more_y+4)=0;
			*(more_x+5)=0;*(more_y+5)=0;
			*(more_x+6)=0;*(more_y+6)=0;
			*(more_x+7)=0;*(more_y+7)=0;
			*(more_x+8)=0;*(more_y+8)=0;
			*(more_x+9)=0;*(more_y+9)=0;
			*(more_x+10)=0;*(more_y+10)=0;
			*(more_x+11)=0;*(more_y+11)=0;
		}else{
			// QUADS
			*(more_x+0)=13-21;*(more_y+0)=-1+27;
			*(more_x+1)=24;*(more_y+1)=27-24;
			*(more_x+2)=78;*(more_y+2)=33;
			*(more_x+3)=104;*(more_y+3)=32;
			// TURRETS
			*(more_x+4)=-167;*(more_y+4)=38;
			*(more_x+5)=-132;*(more_y+5)=-16;
			*(more_x+6)=-68;*(more_y+6)=3;
			*(more_x+7)=-58;*(more_y+7)=52;
			*(more_x+8)=-8;*(more_y+8)=6;
			*(more_x+9)=64;*(more_y+9)=-6;
			*(more_x+10)=140;*(more_y+10)=34;
			*(more_x+11)=218;*(more_y+11)=0;
		} 
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+ppp*scale_map+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+ppp*scale_map+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+ppp*scale_map+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+ppp*scale_map+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		if((enemy+12)->alive==true)Quad((planet+1)->position.x+pppp*scale_map-total_size+*(more_x+0),(planet+1)->position.y+*(more_y+0),10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x+pppp*scale_map-total_size+*(more_x+1),(planet+2)->position.y+*(more_y+1),10*scale_map,-10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x+pppp*scale_map-total_size+*(more_x+2),(planet+3)->position.y+*(more_y+2),10*scale_map,-10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x+pppp*scale_map-total_size+*(more_x+3),(planet+4)->position.y+*(more_y+3),10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.68);
		t=esat::Mat3Translate((planet+5)->position.x+ppp*scale_map+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+6)->position.x+ppp*scale_map+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);;
		t=esat::Mat3Translate((planet+7)->position.x+ppp*scale_map+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+8)->position.x+ppp*scale_map+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+9)->position.x+ppp*scale_map+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.31);
		t=esat::Mat3Translate((planet+10)->position.x+ppp*scale_map+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+11)->position.x+ppp*scale_map+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+12)->position.x+ppp*scale_map+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.68);
		t=esat::Mat3Translate((planet+5)->position.x+pppp*scale_map-total_size+*(more_x+4),(planet+5)->position.y+*(more_y+4));
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+6)->position.x+pppp*scale_map-total_size+*(more_x+5),(planet+6)->position.y+*(more_y+5));
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+7)->position.x+pppp*scale_map-total_size+*(more_x+6),(planet+7)->position.y+*(more_y+6));
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+8)->position.x+pppp*scale_map-total_size+*(more_x+7),(planet+8)->position.y+*(more_y+7));
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+9)->position.x+pppp*scale_map-total_size+*(more_x+8),(planet+9)->position.y+*(more_y+8));
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.31);
		t=esat::Mat3Translate((planet+10)->position.x+pppp*scale_map-total_size+*(more_x+9),(planet+10)->position.y+*(more_y+9));
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+11)->position.x+pppp*scale_map-total_size+*(more_x+10),(planet+11)->position.y+*(more_y+10));
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.29);
		t=esat::Mat3Translate((planet+12)->position.x+pppp*scale_map-total_size+*(more_x+11),(planet+12)->position.y+*(more_y+11));
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,*(more_x+i),*(more_y+i),total_size);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,*(more_x+i-12),*(more_y+i-12),total_size);
		}
	}
	esat::Vec2 dots_map1[25]={
		36-16,0,
		2-16,0,
		0-16,3,
		1-16,3,
		2.5-16,1,
		5-16,4,
		7.5-16,1,
		10-16,4.5,
		8-16,7,
		10-16,7,
		14-16,3,
		15-16,4.5,
		16-16,4.5,
		18-16,2,
		21-16,2,
		22.5-16,4.5,
		23.5-16,4.5,
		25-16,2,
		27-16,2,
		30-16,6,
		32-16,3,
		33.5-16,5,
		35-16,3,
		36-16,4,
		33-16,9		
	};
	esat::Vec2 dots_map2[22]={
		-4-16,0,
		-1-16,0,
		-2.5-16,3,
		0-16,6,
		2-16,5,
		5-16,5.5,
		7-16,4,
		8-16,5,
		5-16,7,
		1-16,7,
		0-16,9,
		10-16,9,
		13-16,6.5,
		16-16,6.5,
		18-16,4.5,
		21-16,4.5,
		23-16,7,
		28.5-16,7,
		30-16,9,
		31-16,7,
		32.5-16,7,
		30-16,11
	};
	
	esat::Vec2 map1[25],map2[22];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,480,340);	
		PlanetScale(scale_map);
	}
	s=esat::Mat3Scale(22*scale_map,22*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x+ppp*scale_map,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 25, false);
	DrawFigure(m, dots_map2, map2, 22, false);
	if(scale_map>=1){
		t=esat::Mat3Translate((planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_map1, map1, 25, false);
		DrawFigure(m, dots_map2, map2, 22, false);
		LimitsMaps2(total_size,original_size);
	}
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map1,25,22*scale_map,22*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,22,22*scale_map,22*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map1,25,22*scale_map,22*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,22,22*scale_map,22*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}	
	}
}

void DrawMap7S3(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	if(scale_map>=1){
		// 1-4 Quads
		(planet+1)->position.x=304-4,(planet+1)->position.y=525-18;
		(planet+2)->position.x=483-2,(planet+2)->position.y=525-18;
		(planet+3)->position.x=269,(planet+3)->position.y=576-18;
		(planet+4)->position.x=522,(planet+4)->position.y=576-18;
		//5-12 turrets
		(planet+5)->position.x=189-8,(planet+5)->position.y=399-1;
		(planet+6)->position.x=201+14,(planet+6)->position.y=525-1;
		(planet+7)->position.x=287+8,(planet+7)->position.y=548;
		(planet+8)->position.x=316-15,(planet+8)->position.y=185-4;
		(planet+9)->position.x=470+17,(planet+9)->position.y=170;
		(planet+10)->position.x=515,(planet+10)->position.y=545-19;
		(planet+11)->position.x=588-6,(planet+11)->position.y=399;
		(planet+12)->position.x=608+15,(planet+12)->position.y=208;
		
		// QUADS
		esat::DrawSetStrokeColor(0,20,250);
		if((enemy+12)->alive==true)Quad((planet+1)->position.x,(planet+1)->position.y,10*scale_map,10*scale_map);
		if((enemy+13)->alive==true)Quad((planet+2)->position.x,(planet+2)->position.y,10*scale_map,10*scale_map);
		if((enemy+14)->alive==true)Quad((planet+3)->position.x,(planet+3)->position.y,10*scale_map,10*scale_map);
		if((enemy+15)->alive==true)Quad((planet+4)->position.x,(planet+4)->position.y,10*scale_map,10*scale_map);
		
		// TORRETAS
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.65);
		t=esat::Mat3Translate((planet+5)->position.x,(planet+5)->position.y);
		ResetM(m,s,r,t);
		if((enemy+4)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+6)->position.x,(planet+6)->position.y);
		ResetM(m,s,r,t);
		if((enemy+5)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.35);
		t=esat::Mat3Translate((planet+7)->position.x,(planet+7)->position.y);
		ResetM(m,s,r,t);
		if((enemy+6)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.75);
		t=esat::Mat3Translate((planet+8)->position.x,(planet+8)->position.y);
		ResetM(m,s,r,t);
		if((enemy+7)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.25);
		t=esat::Mat3Translate((planet+9)->position.x,(planet+9)->position.y);
		ResetM(m,s,r,t);
		if((enemy+8)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.65);
		t=esat::Mat3Translate((planet+10)->position.x,(planet+10)->position.y);
		ResetM(m,s,r,t);
		if((enemy+9)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*0.65);
		t=esat::Mat3Translate((planet+11)->position.x,(planet+11)->position.y);
		ResetM(m,s,r,t);
		if((enemy+10)->alive==true)DotsTurret(m,s,r,t);
		s=esat::Mat3Scale(8*scale_map,8*scale_map);
		r=esat::Mat3Rotate(pi*1.25);
		t=esat::Mat3Translate((planet+12)->position.x,(planet+12)->position.y);
		ResetM(m,s,r,t);
		if((enemy+11)->alive==true)DotsTurret(m,s,r,t);
		
		for(int i=4;i<12;i++){
			TurretsShooting(i,0,0,0);
		}
		for(int i=12;i<16;i++){
			ColisionFuel(i,0,0,0);
		}
	}
	float total_size=20*scale_map*25;
	esat::Vec2 dots_map1[34]={
		8-10,0,
		9-10,2,
		8-10,4,
		6-10,6,
		4-10,6,
		8-10,2,
		4-10,2,
		0-10,6,
		6-10,10.5,
		4-10,15,
		2-10,11,
		0-10,15,
		4-10,19,
		6-10,19,
		5-10,17,
		8-10,17,
		8-10,17,
		10-10,19,
		12-10,17,
		15-10,17,
		14-10,19,
		16-10,19,
		20-10,15,
		18-10,11,
		16-10,15,
		14-10,10.5,
		20-10,6,
		16-10,2,
		12-10,2,
		16-10,6,
		14-10,6,
		12-10,4,
		11-10,2,
		12-10,0
	};
	esat::Vec2 dots_map2[8]={
		10-10,8,
		8-10,10.5,
		10-10,13,
		12-10,10.5,
		10-10,8,
		10-10,13,
		8-10,10.5,
		12-10,10.5
	};
	
	esat::Vec2 map1[34],map2[8];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,400,50);	
		PlanetScale(scale_map);
	}
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 34, false);
	DrawFigure(m, dots_map2, map2, 8, false);
	
	if((planet+0)->position.x+ppp*scale_map>=0 && (planet+0)->position.x+ppp*scale_map<=800){
		if(CheckLineColision(dots_map1,34,25*scale_map,25*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,8,25*scale_map,25*scale_map,(planet+0)->position.x+ppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}else{
		if(CheckLineColision(dots_map1,34,25*scale_map,25*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
		if(CheckLineColision(dots_map2,8,25*scale_map,25*scale_map,(planet+0)->position.x-(total_size)+pppp*scale_map,(planet+0)->position.y)){
			player.alive=false;
		}
	}
}
// NO LO HAGO
void DrawMap8S3(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r, esat::Mat3 t){
	esat::DrawSetStrokeColor(0,20,250);
	Quad(48,425,5,5);
	Quad(262,425,5,5);
	Quad(396,470,5,5);
	Quad(575,470,5,5);
	Quad(679,376,5,5);

	s=esat::Mat3Scale(5*scale_map,5*scale_map);
	r=esat::Mat3Rotate(pi*1.25);
	t=esat::Mat3Translate(140,412);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5*scale_map,5*scale_map);
	r=esat::Mat3Rotate(0);
	t=esat::Mat3Translate(204,425);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*0.75);
	t=esat::Mat3Translate(272,434);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*1.25);
	t=esat::Mat3Translate(379,480);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*0.75);
	t=esat::Mat3Translate(469,322);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*0.75);
	t=esat::Mat3Translate(567,330);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*1.25);
	t=esat::Mat3Translate(569,480);
	DotsTurret(m,s,r,t);
	
	esat::DrawSetStrokeColor(255,0,0);
	s=esat::Mat3Scale(5,5);
	r=esat::Mat3Rotate(pi*1.25);
	t=esat::Mat3Translate(667,388);
	DotsTurret(m,s,r,t);

	esat::Vec2 dots_triangle[6]={
		0-2,0,
		4-2,0,
		3-2,1,
		2-2,3,
		1-2,1,
		0-2,0,
	};
	esat::Vec2 dots_map1[2]={
		0-5,0,
		10-5,0,		
	};
	
	esat::Vec2 map1[2],triangle[6];
	if(scale_map<1){
		PlanetZoom(player.position.x,player.position.y,400,50);
		PlanetZoom((planet+0)->position.x,(planet+0)->position.y,0,500);	
		PlanetScale(scale_map);
	}
	float total_size=800*scale_map,original_size=800;
	s=esat::Mat3Scale(80*scale_map,25*scale_map);
	t=esat::Mat3Translate((planet+0)->position.x+400+ppp*scale_map,(planet+0)->position.y);
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	esat::DrawSetStrokeColor(71,255,0);
	DrawFigure(m, dots_map1, map1, 2, false);
	
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	t=esat::Mat3Translate(20+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-425));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(130+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-402));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	t=esat::Mat3Translate(190+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-425));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(275+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-336));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(310+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(370+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(530+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-326));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(560+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(10*scale_map,10*scale_map);
	t=esat::Mat3Translate(707+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-455));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	t=esat::Mat3Translate(380+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-310));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	s=esat::Mat3Scale(25*scale_map,25*scale_map);
	t=esat::Mat3Translate(655+(planet+0)->position.x+30+ppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-376));
	r=esat::Mat3Rotate(0);
	ResetM(m,s,r,t);
	DrawFigure(m, dots_triangle, triangle, 6, false);
	
	if(scale_map>=1){
		s=esat::Mat3Scale(80*scale_map,25*scale_map);
		t=esat::Mat3Translate((planet+0)->position.x+400-(total_size)+pppp*scale_map,(planet+0)->position.y);
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		esat::DrawSetStrokeColor(71,255,0);
		DrawFigure(m, dots_map1, map1, 2, false);
		
		s=esat::Mat3Scale(25*scale_map,25*scale_map);
		t=esat::Mat3Translate(20+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-425));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(130+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-402));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(25*scale_map,25*scale_map);
		t=esat::Mat3Translate(190+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-425));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(275+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-336));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(310+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(370+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(530+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-326));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(560+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-470));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(10*scale_map,10*scale_map);
		t=esat::Mat3Translate(707+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-455));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(25*scale_map,25*scale_map);
		t=esat::Mat3Translate(380+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-310));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		
		s=esat::Mat3Scale(25*scale_map,25*scale_map);
		t=esat::Mat3Translate(655+(planet+0)->position.x+30-(total_size)+pppp*scale_map,(planet+0)->position.y-((planet+0)->position.y-376));
		r=esat::Mat3Rotate(0);
		ResetM(m,s,r,t);
		DrawFigure(m, dots_triangle, triangle, 6, false);
		LimitsMaps2(total_size,original_size);
	}	
}


// SCREENS
	//SISTEMA SOLAR 1
void ScreenG4(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	Hud(m,s,r,t);
	LimitsRebound();
	LineU();
	SemiArrow();
	LineSize();
	LineLarge();
	RingPosition();
	StarLines();
	DrawPlayer(m,s,r,t);
	Ovnis(m,s,r,t);
	if(scale_map>=1){
		Movement();
		player.gravity=1;
		Gravity(480,235);
		StarsBackGround();
	}
	DrawMap1S1(m,s,r,t);
	PlanetScale(scale_map);
}

void ScreenG5(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	player.bonus=*(planet_bonus+2);
	Hud(m,s,r,t);
	DrawMap2S1(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+0));
		
		LimitsMaps();
		Movement();
		DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);
	}
	PlanetScale(scale_map);
}

void ScreenG6(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	player.bonus=*(planet_bonus+3);
	LimitsMaps();
	Hud(m,s,r,t);
	DrawMap3S1(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+3));
		Movement();
		DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);
		RastreatorMovement(m,s,r,t,281);
	}
}

void ScreenG7(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	player.bonus=*(planet_bonus+4);
	LimitsMaps();
	Hud(m,s,r,t);
	DrawMap4S1(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+4));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);
		RastreatorMovement(m,s,r,t,237);
	}
}

void ScreenG8(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	player.bonus=*(planet_bonus+2);
	LimitsMaps();
	Hud(m,s,r,t);
	DrawMap5S1(m,s,r,t);
	if(scale_map>=1){
		if(player.last_screen==4){
			Bonus(*(planet_bonus+2));
			player.bonus=*(planet_bonus+2);
		}
		else if(player.last_screen==12){
			Bonus(*(planet_bonus+0));player.bonus=*(planet_bonus+0);
		}
		else if(player.last_screen==13){
			Bonus(*(planet_bonus+1));player.bonus=*(planet_bonus+1);
		}
		Movement();
		DrawPlayer(m,s,r,t);
		if(player.alive==true)Gravity(player.position.x,600);
	}
}

void ScreenG15(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	player.bonus=*(planet_bonus+1);
	LimitsMaps();
	Hud(m,s,r,t);
	DrawMap6S1(m,s,r,t);
	if(scale_map>=1){	
		Bonus(*(planet_bonus+1));
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
		Movement();DrawPlayer(m,s,r,t);
		RastreatorMovement(m,s,r,t,384);
	}
}

	//SISTEMA SOLAR 2
void ScreenG12(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	Hud(m,s,r,t);
	LimitsRebound();
	CircleDots();
	EyeAnimation();
	MazeRotation();
	LineSize();
	StarLines();
	DrawPlayer(m,s,r,t);
	Ovnis(m,s,r,t);
	if(scale_map>=1){
		
		Movement();
		player.gravity=1;
		Gravity(267,260);
		StarsBackGround();
	
	}
	DrawMap1S2(m,s,r,t);
	PlanetScale(scale_map);
}
	
void ScreenG16(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+2);
	Hud(m,s,r,t);
	DrawMap2S2(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+2));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);
	}
}

void ScreenG17(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+3);
	Hud(m,s,r,t);
	DrawMap3S2(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+3));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
		RastreatorMovement(m,s,r,t,213);
	}
}

void ScreenG18(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+1);
	Hud(m,s,r,t);
	DrawMap4S2(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+1));
		player.gravity=0.6f;
		DrawPlayer(m,s,r,t);
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
		Movement();
	}
}

void ScreenG19(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+4);
	Hud(m,s,r,t);
	DrawMap5S2(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+4));
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
		Movement();DrawPlayer(m,s,r,t);
		RastreatorMovement(m,s,r,t,341);
	}
}
	
	//SISTEMA SOLAR 3
void ScreenG13(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	Hud(m,s,r,t);
	LimitsRebound();
	BlueStar();
	StarLines();
	LineSize();
	GreenOctagonS3();
	CircleX3();
	DrawPlayer(m,s,r,t);
	Ovnis(m,s,r,t);
	if(scale_map>=1){
		
		Movement();
		player.gravity=1;
		Gravity(480,235);
		StarsBackGround();
		
	}
	DrawMap1S3(m,s,r,t);
	PlanetScale(scale_map);
}

void ScreenG11(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+0);
	Hud(m,s,r,t);
	DrawMap8S3(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+0));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
	}
}

void ScreenG10(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+2);
	Hud(m,s,r,t);
	DrawMap7S3(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+2));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
	}
}

void ScreenG9(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	LimitsMaps();player.bonus=*(planet_bonus+3);
	Hud(m,s,r,t);
	DrawMap6S3(m,s,r,t);
	if(scale_map>=1){
		Bonus(*(planet_bonus+3));
		Movement();DrawPlayer(m,s,r,t);
		player.gravity=0.6f;
		if(player.alive==true)Gravity(player.position.x,600);Gravity(player.position.x,600);
		RastreatorMovement(m,s,r,t,290);
	}
}	
	//OVNI FIGHT
void ScreenG14(esat::Mat3 m, esat::Mat3 s,esat::Mat3 r,esat::Mat3 t){
	Hud(m,s,r,t);
	Movement();
	DrawPlayer(m,s,r,t);
	LimitsRebound();
	Ovnis(m,s,r,t);
}

// GAME SCREENS
void ScreensR(){
	esat::Mat3 s = esat::Mat3Identity(), t = esat::Mat3Identity(), r = esat::Mat3Identity();
	esat::Mat3 m = esat::Mat3Identity();
	switch(screen){
		case 1: ScreenR1();Title(m);esat::ResetBufferdKeyInput();break;
		case 2: ScreenR2();esat::ResetBufferdKeyInput();AllIni();break;
		case 3: ScreenR3();esat::ResetBufferdKeyInput();AllIni();break;
		case 4: ScreenG4(m,s,r,t);break;
		case 5: ScreenG5(m,s,r,t);break;
		case 6: ScreenG6(m,s,r,t);break;
		case 7: ScreenG7(m,s,r,t);break;
		case 8: ScreenG8(m,s,r,t);break;
		case 9: ScreenG9(m,s,r,t);break;
		case 10: ScreenG10(m,s,r,t);break;
		case 11: ScreenG11(m,s,r,t);break;
		case 12: ScreenG12(m,s,r,t);break;
		case 13: ScreenG13(m,s,r,t);break;
		case 14: ScreenG14(m,s,r,t);break;
		case 15: ScreenG15(m,s,r,t);break;
		case 16: ScreenG16(m,s,r,t);break;
		case 17: ScreenG17(m,s,r,t);break;
		case 18: ScreenG18(m,s,r,t);break;
		case 19: ScreenG19(m,s,r,t);break;
		case 20: ScreenR5();esat::ResetBufferdKeyInput();AllIni();break;
	}
	
}


int esat::main(int argc, char **argv) {
	esat::WindowInit(WindowX,WindowY);
	WindowSetMouseVisibility(true);
		
	srand(time(NULL));
	AllIni();
	  
	while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {
		last_time = esat::Time();
		esat::DrawBegin();
		esat::DrawClear(0,0,0);

		ScreensR();
		
		esat::DrawEnd();  
		//Control fps
		do{
			current_time = esat::Time();
		}while((current_time-last_time)<=1000.0/fps);		
		esat::WindowFrame();
	}
	esat::WindowDestroy();
  
	return 0;  
}