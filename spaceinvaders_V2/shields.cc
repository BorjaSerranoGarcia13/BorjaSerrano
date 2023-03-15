/*
	AUTHOR - BORJA SERRANO
	MAIL - serranoga@esat-alumni.com
*/

#include "head.h"

void IniShield() {

	p_shield = (TShield*)malloc(kTotalShields * sizeof(TShield));

	short int row = 0;
	
	for (int i = 0; i < kTotalShields; i++) {
		(p_shield + i)->position.x = kShieldSpaceX * (row + 1);
		(p_shield + i)->position.y = kShieldPositionY;
		(p_shield + i)->hp = kShieldHp;
		row++;
	}

	
}

void DrawShield() {

	esat::DrawSetStrokeColor(0, 255, 0);
	esat::DrawSetFillColor(0, 255, 0);

	for (int i = 0; i < kTotalShields; i++) {
		if ((p_shield + i)->hp > 1) {
			esat::DrawSetStrokeColor(0, 255, 0);
			esat::DrawSetFillColor(0, 255, 0);
		}
		else {
			esat::DrawSetStrokeColor(0, 60, 0);
			esat::DrawSetFillColor(0, 60, 0);
		}
		if ((p_shield + i)->hp > 0) {
			Quad((p_shield + i)->position.x, (p_shield + i)->position.y, kShieldWidth, kShieldHeight);
		}
	}

}





































