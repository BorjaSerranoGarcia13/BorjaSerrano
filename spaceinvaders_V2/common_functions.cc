/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#include "head.h"

void Quad(int x, int y, int width, int height) {

	float p[10];
	p[0] = x; 
  p[1] = y;
	p[2] = x + width;
  p[3] = y;
	p[4] = x + width;
  p[5] = y + height;
	p[6]= x ;
  p[7] = y + height;
	p[8] = p[0];
  p[9] = p[1];
	
	esat::DrawSolidPath(p,5);

}

bool CheckRectangleCollision(short x, short y, short width, short height, short x2, short y2, short width2, short height2) {

  if (((x <= x2 + width2 && x >= x2) || (x + width <= x2 + width2 && x + width >= x2)) && ((y >= y2 && y <= y2 + height2) || (y + height >= y2 && y+height <= y2+height2))) 
  {
    return true;
  }
  return false;

}

void ReadFile() {

	FILE *p = fopen("options.txt", "r");
	if (p != NULL) {
		char *us = (char*)calloc(20, sizeof(char));
		short int count = 0;
		while (!feof(p)) {
			fgets(us, 20, p);
			int ia = 'us';
			int pointer = 0;
			while (*(us + pointer) != ' ') {
				pointer++;
			}
			*(us + (pointer)) = '\0';
			switch (count) {
				case 0: kTotalEnemies = atoi(us);
					break;
				case 1: kTotalShields = atoi(us);
					break;
				case 2: kPlayerSpeed = atoi(us);
			}
			count++;
		}
	}

	fclose(p);
}

int ControlInput() {
	if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)) return 0;
	if (esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)) return 1;
	return 5;
}



void Reset() {
	IniPlayer();
	IniEnemy();
}

/*
void AllIni() {
	
	IniPlayer();
	IniEnemy();
}

void AllDraw() {

	DrawPlayer();
	DrawEnemy();
	//AllCollisions();
}*/