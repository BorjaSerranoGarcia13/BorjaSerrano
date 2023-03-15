/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#include "head.h"

void IniEnemy() {
	
  p_enemy = (TEnemy*)malloc(kTotalEnemies*sizeof(TEnemy));
	
  short int column = 0;
  short int row = 0;

  for (int element = 0; element < kTotalEnemies; element++) {
    (p_enemy + element)->position.x = kEnemySpaceX * (column + 1);
		(p_enemy + element)->position.y = kEnemySpaceY * (row + 1);
    (p_enemy + element)->direction = 0;
		(p_enemy + element)->hp = kEnemyHp;
		(p_enemy + element)->shot.hp = 0;
		column += 1;
		
    if (column == 5) {  
      row += 1;
      column = 0;
		}
	}
}

void MovementEnemy() {

	for (int i = kTotalEnemies - 1; i >= 0; i--) {		
		switch((p_enemy + i)->direction) {
			case 0: (p_enemy + i)->position.x += kEnemySpeed;
        break;
			case 1: (p_enemy + i)->position.x -= kEnemySpeed;
        break;
		}	
	}

	short int change_direction = 5;

 for (int element = 0; element < kTotalEnemies; element++) {
		if ((p_enemy + element)->direction == 0 && 
		(p_enemy + element)->position.x + kEnemyHalfWidth > 750 &&
		(p_enemy + element)->hp > 0 ) change_direction = 1;
		
		if ((p_enemy + element)->direction ==1 && 
		(p_enemy + element)->position.x + kEnemyHalfWidth < 50 && 
		(p_enemy + element)->hp > 0 ) change_direction = 0;
		
		if ((p_enemy + element)->position.y + kEnemyHeight > 600) Reset();	
		}	
	
	for (int element = 0; element < kTotalEnemies; element++) {
		if(change_direction != 5) {
			(p_enemy + element)->position.y += 30;
			(p_enemy + element)->direction = change_direction;
		}
	}			
}

void ShotsEnemy() {

	for (int element = 0; element < kTotalEnemies; element++) {
		if ((p_enemy + element)->hp == 1) {
			// enemy no shooting
			if ((p_enemy + element)->shot.hp == 0) {
				int shooting = rand()%800;
			
				if (shooting == 5) {
					(p_enemy + element)->shot.hp = 1;
					(p_enemy + element)->shot.position.x = (p_enemy + element)->position.x + kEnemyShotWidthPosition;
					(p_enemy + element)->shot.position.y = (p_enemy + element)->position.y+ kEnemyShotHeightPosition;
				}
			}

			// enemy shooting
			if ((p_enemy + element)->shot.hp == 1) {
				(p_enemy + element)->shot.position.y += kEnemyShotSpeed;
			
				if ((p_enemy + element)->shot.position.y > 600) {
					(p_enemy + element)->shot.hp = 0;
				}
			
				esat::DrawSetStrokeColor(100,0,255);
				
				Quad ((p_enemy + element)->shot.position.x, 
				(p_enemy + element)->shot.position.y, 
				kEnemyShotWidth, kEnemyShotHeight);
			}
		}
	}	

}

void DrawEnemy() {

	for (int element = 0; element < kTotalEnemies; element++) {
		if ((p_enemy + element)->hp == 1) {
			esat::DrawSetStrokeColor(255,0,0);
			esat::DrawSetFillColor(255,0,0);
		
			Quad((p_enemy + element)->position.x,(p_enemy + element)->position.y,kEnemyWidth, kEnemyHeight);
		} 
	}

	MovementEnemy();
	ShotsEnemy();
	
}