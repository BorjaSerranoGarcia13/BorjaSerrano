/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#include "head.h"

void CollisionPlayer_Enemy() {
	for (int i = 0; i < kTotalEnemies; i++) {
		if ((p_enemy + i)->hp == 1) {
			if (CheckRectangleCollision(player.position.x, player.position.y,kPlayerWidth, kPlayerHeight, 
      (p_enemy + i)->position.x, 
      (p_enemy + i)->position.y, kEnemyWidth,kEnemyHeight) 
      || (p_enemy + i)->position.y > 580) {
					Reset();
				}
		}
	}
}

void CollisionPlayer_ShotEnemy() {
	for (int i = 0; i < kTotalEnemies; i++) {
		if ((p_enemy + i)->shot.hp==1) {
			if (CheckRectangleCollision(player.position.x, player.position.y, kPlayerWidth, kPlayerHeight,
				(p_enemy + i)->shot.position.x, (p_enemy + i)->shot.position.y,kEnemyShotWidth, kEnemyShotHeight)) {
					Reset();
				}
		}
	}
}

void AliveEnemy() {
	int total_enemies = 0;
	for (int h = 0; h < kTotalEnemies; h++) {
		if ((p_enemy + h)->hp == 1) total_enemies++;
	}
	if (total_enemies == 0) Reset();		
}

void CollisionPlayerShot_Enemy() {
	for (int i = 0; i < kPlayerTotalShots; i++) {
		if ((player.p_shot + i)->hp == 1) {
			for (int j = 0; j < kTotalEnemies; j++) {
				if ((p_enemy + j)->hp==1) {
					if(CheckRectangleCollision((player.p_shot + i)->position.x, (player.p_shot+i)->position.y, kPlayerShotWidth, kPlayerShotHeight,
					(p_enemy + j)->position.x, (p_enemy + j)->position.y, kEnemyWidth,kEnemyHeight)) {
						(p_enemy+j)->hp = 0;
						(player.p_shot + i)->hp = 0;
						AliveEnemy();						
					}
				}
			}
		}
	}
}

void CollisionPlayerShot_EnemyShot() {
	for (int i = 0; i < kPlayerTotalShots; i++) {
		if ((player.p_shot + i)->hp == 1) {
			for (int j = 0; j < kTotalEnemies; j++) {
				if ((p_enemy + i)->shot.hp == 1) {
					if (CheckRectangleCollision((player.p_shot + i)->position.x, (player.p_shot + i)->position.y, kPlayerShotWidth, kPlayerShotHeight, (p_enemy + j)->shot.position.x, (p_enemy + j)->shot.position.y, kEnemyShotWidth, kEnemyShotHeight)) {
						(p_enemy + i)->shot.hp = 0;
						(player.p_shot + i)->hp = 0;		
					}
				}
			}
		}
	}
}

void CollisionPlayerShot_Shield() {
	
	for (int i = 0; i < kPlayerTotalShots; i++) {
		if ((player.p_shot + i)->hp == 1) {
			for (int j = 0; j < kTotalShields; j++) {
				if ((p_shield + i)->hp > 0) {
					if (CheckRectangleCollision((player.p_shot + i)->position.x, (player.p_shot + i)->position.y, kPlayerShotWidth, kPlayerShotHeight,
						(p_shield + j)->position.x, (p_shield + j)->position.y,
						kShieldWidth, kShieldHeight)) {
						(p_shield + j)->hp--;
						(player.p_shot + i)->hp = 0;
					}
				}
			}
		}
	}

}

void CollisionEnemyShot_Shield() {

	for (int i = 0; i < kPlayerTotalShots; i++) {
		if ((p_enemy + i)->shot.hp > 0) {
			for (int j = 0; j < kTotalShields; j++) {
				if ((p_shield + i)->hp > 0) {
					if (CheckRectangleCollision((p_enemy + i)->shot.position.x, (p_enemy + i)->shot.position.y, kEnemyShotWidth, kEnemyShotHeight,
						(p_shield + j)->position.x, (p_shield + j)->position.y,
						kShieldWidth, kShieldHeight)) {
						(p_shield + j)->hp--;
						(p_enemy + i)->shot.hp = 0;
					}
				}
			}
		}
	}

}

void CollisionEnemyShield() {

	for (int i = 0; i < kTotalEnemies; i ++) {
		if ((p_enemy + i)->hp == 1) {
			for (int j = 0; j < kTotalShields; j++) {
				if ((p_shield + i)->hp > 0) {
					if (CheckRectangleCollision((p_enemy + i)->position.x, (p_enemy + i)->position.y,
						kEnemyWidth, kEnemyHeight,
						(p_shield + j)->position.x, (p_shield + j)->position.y,
						kShieldWidth, kShieldHeight)) {
						(p_shield + j)->hp = 0;
					}
				}
			}
		}
	}

}


void AllCollisions() {
	CollisionEnemyShield();
	CollisionEnemyShot_Shield();
	CollisionPlayerShot_Shield();
	CollisionPlayer_Enemy();
	//CollisionPlayer_ShotEnemy();
	CollisionPlayerShot_Enemy();
	//CollisionPlayerShot_EnemyShot();
	
}