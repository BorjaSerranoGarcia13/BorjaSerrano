/* 
	AUTHOR - BORJA SERRANO 
	MAIL - serranoga@esat-alumni.com
*/

#ifndef __HEAD_H__
#define __HEAD_H__ 1

// ESTRUCTURAS
struct TCoord {
  float x;
  float y;
};

struct TColor {
	short int rgb[3];
};

struct TShot {
  TCoord position;
  //TColor color;
  short int hp;
};

struct TPlayer {
  TCoord position;
 // TColor color;
  TShot *p_shot=NULL;
  short int hp;
} player;

struct TEnemy {
	TCoord position;
	//TColor color;
	TShot shot;
  short int direction;
  short int hp;
} *p_enemy = NULL;

struct TShield {
	TCoord position;
	TColor color;
	short int hp;
} *p_shield = NULL;


// CONSTANTES

  // CONST GAME
const unsigned char fps = 25;
const int WindowX = 800; 
const int WindowY = 600;

  // CONST ENEMIES
short int kTotalEnemies = 30;
const short int kEnemyHp = 1;
const short int kEnemySpeed = 5;
const short int kEnemyWidth = 24;
const short int kEnemyHalfWidth = kEnemyWidth/2;
const short int kEnemyHeight = 10;
const short int kEnemyHalfHeight = kEnemyHeight/2;
const short int kEnemySpaceX = 50;
const short int kEnemySpaceY = 30;


const short int kEnemyShotHp = 1;
const short int kEnemyShotSpeed = 5;
const short int kEnemyShotWidth = 4;
const short int kEnemyShotHeight = 6;

const short int kEnemyShotWidthPosition = kEnemyHalfWidth-kEnemyShotWidth/2;
const short int kEnemyShotHeightPosition = kEnemyHalfHeight-kEnemyShotHeight/2;

  // CONST PLAYER
const short int kPlayerHp = 3;
short int kPlayerSpeed = 5;
const short int kPlayerWidth = 30;
const short int kPlayerHalfWidth = kPlayerWidth/2;
const short int kPlayerHeight = 16;
const short int kPlayerHalfHeight = kPlayerHeight/2;

const short int kPlayerShotHp = 1;
const short int kPlayerTotalShots = 5;
const short int kPlayerShotSpeed = 8;
const short int kPlayerShotWidth = 4;
const short int kPlayerShotHalfWidth = kPlayerShotWidth/2;
const short int kPlayerShotHeight = 6;
const short int kPlayerShotHalfHeight = kPlayerShotHeight/2;


// CONST SHIELDS
short int kTotalShields = 4;
const short int kShieldHp = 2;
const short int kShieldWidth = 60;
const short int kShieldHeight = 20;
const short int kShieldSpaceX = 100;
const short int kShieldPositionY = 450;

// COMMON FUNCTIONS
void Quad(int x, int y, int width, int height);

bool CheckRectangleCollision(short x, short y, short width, short height, short x2, short y2, short width2, short height2);

void ReadFile(int total[2]);

void Reset();

int ControlInput();

//void AllIni();

//void AllDraw();

#endif