/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#include "head.h"

void IniPlayer() {
	
  player.hp = kPlayerHp;
	player.position.x = 400 - kPlayerHalfWidth;
	player.position.y = 540 - kPlayerHalfHeight;
	
	player.p_shot = (TShot*)calloc(kPlayerTotalShots, sizeof(TShot));

	for (int i = 0; i < kPlayerTotalShots; i++) {
		(player.p_shot + i)->hp = 0;
	}

}

void MovementPlayer() {
	if (player.position.x < 785) {
		if (ControlInput() == 0) {
			player.position.x += kPlayerSpeed;
		}
	}

	if(player.position.x > 15) {
		if (ControlInput() == 1) {
			player.position.x -= kPlayerSpeed;
		}
	}
}

void ShotsPlayer() {

	if (esat::IsSpecialKeyDown(esat::kSpecialKey_Space)) {
		int free_shot = 10;

		for (int i = kPlayerTotalShots - 1; i >= 0; i--){
			if((player.p_shot + i)->hp == 0) free_shot = i;
		}

		if (free_shot != 10) {
			(player.p_shot + free_shot)->hp = 1;
			(player.p_shot + free_shot)->position.x = player.position.x + kPlayerHalfWidth - kPlayerShotHalfWidth;
			(player.p_shot + free_shot)->position.y = player.position.y - kPlayerShotHalfHeight;
		}		
	}
}

void DrawPlayer() {

	// PLAYER 
	esat::DrawSetStrokeColor(255,0,255);	
  Quad(player.position.x, player.position.y, kPlayerWidth, kPlayerHeight);

	// PLAYER SHOTS
	for (int i = 0; i < kPlayerTotalShots; i++) {
		if ((player.p_shot + i)->hp == 1) {			
      (player.p_shot + i)->position.y -= kPlayerShotSpeed;
		
    	if ((player.p_shot + i)->position.y < 0) (player.p_shot + i)->hp = 0;
			
			esat::DrawSetStrokeColor(0,0,255);
			
      Quad((player.p_shot + i)->position.x, (player.p_shot + i)->position.y, kPlayerShotWidth, kPlayerShotHeight);
		}
	}	
	
	MovementPlayer ();
	ShotsPlayer();

}