/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/time.h>

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#include "head.h"

#include "player.cc"
#include "enemies.cc"
#include "shields.cc"
#include "collisions.cc"
#include "common_functions.cc"


double current_time;
double last_time;



void AllIni() {
	ReadFile();
	IniPlayer();
	IniEnemy();
	IniShield();

}

void AllDraw() {

	DrawPlayer();
	DrawEnemy();
	DrawShield();
	AllCollisions();
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

		AllDraw();
		
		esat::DrawEnd();  
		//Control fps
		do{
			current_time = esat::Time();
		}while((current_time-last_time)<=1000.0/fps);		
		esat::WindowFrame();
	}

	free(p_enemy);
	
	esat::WindowDestroy();
  
	return 0; 

}