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

#include "lista_circular.cc"

/*
----TAREAS----
- CUANDO AL GIRAR HACIA UN LADO COLISIONO QUE CAMBIE EL SPRITE HACIA ESE LADO LA DIRECCION DEL PERSONAJE
- CRASHEA ALGUNA VEZ DESCUBRIR POR QUE
- DAR SPECIAL TRUE AL GENERAR SAND Y LUEGO DESACTIVARLO porq todo se genera encima sand
- En inventario solo moverme si tengo los pokemon
- Liberar listas en reset
- No capturar hasta que acaben animaciones de pokemon en combate
- Guardar partida
- Limite de 6 pokemon, cuando llego decir no puedes capturar, en inventario boton para soltar pokemon liberar lista
AÑADOR EM TNODO ANTERIOR PARA HACER TODO FACIL
*/
unsigned char fps=25;
double current_time,last_time;
const int WindowX=420, WindowY=300;

struct TCoord{
	float x,y;
};

struct TPlayer{
	TCoord pos, battle;
	int direction, sprite, animation, count, count_battle, speed, menu;
	bool activate_battle, run, capture, inventory, election;
};

struct TPokemon{
	TCoord pos;
	int direction, sprite;
	bool appear;
	char *name;
};

struct TPokedex{
	char *name, *n;
	bool caught, seen;
	TCoord pos;
};

struct TMap{
	TCoord pos;
	int type, sprite;
	bool special_sprite;
};

TPlayer player; TPokemon pokemon;  TPokedex *p;
TMap *map;
TNodo *lista1=NULL;

int total_map=(WindowX+600)/20*(WindowY+600)/20, adjust_mapX=0, adjust_mapY=0, n_screen=0, n_pokedex=0;
int min=0,max=6;

esat::SpriteHandle *spritesheet, *s_map, *s_player, *s_pokemon;

// LOADS
void LoadMap(esat::SpriteHandle s, esat::SpriteHandle ss, esat::SpriteHandle sss){
	s_map = (esat::SpriteHandle*) malloc(120*sizeof(esat::SpriteHandle));
	int x=80,y=40,width=20,height=20;
	// WATER
	*(s_map+1) = esat::SubSprite(s,x,y,width,height);
	// NORMAL GRASS
	x=80,y=127;
	*(s_map+0) = esat::SubSprite(s,x,y,width,height);
	// SAVAGE GRASS
	x=280,y=200;
	*(s_map+2) = esat::SubSprite(s,x,y,width,height);
	// BACKGROUND BATTLE
	*(s_map+3) = esat::SpriteFromFile("./recursos/imagenes/battle.png");
	// BUILD AGUJERO SUELO
	x=176,y=352,width=20,height=20;//esq up izq
	*(s_map+4) = esat::SubSprite(ss,x,y,width,height);
	x=206,y=352;//up
	*(s_map+5) = esat::SubSprite(ss,x,y,width,height);
	x=236,y=352;//esq up right
	*(s_map+6) = esat::SubSprite(ss,x,y,width,height);
	x=176,y=372;//left
	*(s_map+7) = esat::SubSprite(ss,x,y,width,height);
	x=176,y=380;//esq dwn left
	*(s_map+8) = esat::SubSprite(ss,x,y,width,height);
	x=236,y=372;//right
	*(s_map+9) = esat::SubSprite(ss,x,y,width,height);
	x=236,y=380;//esq dwn right
	*(s_map+10) = esat::SubSprite(ss,x,y,width,height);
	x=216,y=380;//dwn
	*(s_map+11) = esat::SubSprite(ss,x,y,width,height);
	x=204,y=376;//center
	*(s_map+12) = esat::SubSprite(ss,x,y,width,height);
	// SAVAGE GRASS 2
	x=520,y=340;
	*(s_map+13) = esat::SubSprite(s,x,y,width,height);
	// ROCA AGUA
	x=520,y=3; // esq up left
	*(s_map+14) = esat::SubSprite(s,x,y,width,height);
	x=540,y=3; // esq up right
	*(s_map+15) = esat::SubSprite(s,x,y,width,height);
	x=520,y=43; // esq down left
	*(s_map+16) = esat::SubSprite(s,x,y,width,height);
	x=540,y=43; // esq down right
	*(s_map+17) = esat::SubSprite(s,x,y,width,height);
	//BORDE
	x=238,y=539,height=4; // dwn
	*(s_map+18) = esat::SubSprite(ss,x,y,width,height);
	x=236,y=496; // up
	*(s_map+21) = esat::SubSprite(ss,x,y,width,height);
	x=225,y=501,width=4,height=20; // lft
	*(s_map+19) = esat::SubSprite(ss,x,y,width,height);
	x=267,y=501; // rgt
	*(s_map+20) = esat::SubSprite(ss,x,y,width,height);
	//FLOWER
	x=160,y=124,width=20,height=20;//red
	*(s_map+22) = esat::SubSprite(ss,x,y,width,height);
	x=160,y=60;//blue
	*(s_map+23) = esat::SubSprite(ss,x,y,width,height);
	//ADDS FLOOR
	x=32,y=0,width=16,height=16;//flor blanca
	*(s_map+24) = esat::SubSprite(ss,x,y,width,height);
	x=48;//setas
	*(s_map+25) = esat::SubSprite(ss,x,y,width,height);
	x=64;//plantita
	*(s_map+26) = esat::SubSprite(ss,x,y,width,height);
	x=80;//flor rojas
	*(s_map+27) = esat::SubSprite(ss,x,y,width,height);
	// MARKET
	x=528,y=506,width=20,height=20; // esq up lft
	*(s_map+28) = esat::SubSprite(ss,x,y,width,height);
	x=528,y=526; // lft 1
	*(s_map+29) = esat::SubSprite(ss,x,y,width,height);
	x=528,y=535; // left 2
	*(s_map+30) = esat::SubSprite(ss,x,y,width,height);
	x=528,y=555; // left 3
	*(s_map+31) = esat::SubSprite(ss,x,y,width,height);
	x=528,y=575; // esq dnw lft
	*(s_map+32) = esat::SubSprite(ss,x,y,width,height);
	x=548,y=506; // up a 1
	*(s_map+33) = esat::SubSprite(ss,x,y,width,height);
	x=548,y=511; // up a 2
	*(s_map+34) = esat::SubSprite(ss,x,y,width,height);
	x=548,y=535; // up a 3
	*(s_map+35) = esat::SubSprite(ss,x,y,width,height);
	x=548,y=555; // up a 4
	*(s_map+36) = esat::SubSprite(ss,x,y,width,height);
	x=548,y=575; // up a 5
	*(s_map+37) = esat::SubSprite(ss,x,y,width,height);
	x=568,y=506; // up b 1
	*(s_map+38) = esat::SubSprite(ss,x,y,width,height);
	x=568,y=511; // up b 2
	*(s_map+39) = esat::SubSprite(ss,x,y,width,height);
	x=568,y=535; // up b 3
	*(s_map+40) = esat::SubSprite(ss,x,y,width,height);
	x=568,y=555; // up b 4
	*(s_map+41) = esat::SubSprite(ss,x,y,width,height);
	x=568,y=575; // up b 5
	*(s_map+42) = esat::SubSprite(ss,x,y,width,height);
	x=588,y=506; // rgt 1
	*(s_map+43) = esat::SubSprite(ss,x,y,width,height);
	x=588,y=526; // rgt 2
	*(s_map+44) = esat::SubSprite(ss,x,y,width,height);
	x=588,y=535; // rgt 3
	*(s_map+45) = esat::SubSprite(ss,x,y,width,height);
	x=588,y=555; // rgt 4
	*(s_map+46) = esat::SubSprite(ss,x,y,width,height);
	x=588,y=575; // rgt 5
	*(s_map+47) = esat::SubSprite(ss,x,y,width,height);
	// POKEMON CENTER
	x=624,y=498,width=20,height=20; // lft 1
	*(s_map+48) = esat::SubSprite(ss,x,y,width,height);
	x=624,y=518; // lft 2
	*(s_map+49) = esat::SubSprite(ss,x,y,width,height);
	x=624,y=518; // left 3
	*(s_map+50) = esat::SubSprite(ss,x,y,width,height);
	x=624,y=551; // left 4
	*(s_map+51) = esat::SubSprite(ss,x,y,width,height);
	x=624,y=571; // lft 5
	*(s_map+52) = esat::SubSprite(ss,x,y,width,height);
	x=624,y=591; // lft 6
	*(s_map+53) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=498; // up a 1
	*(s_map+54) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=519; // up a 2
	*(s_map+55) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=531; // up a 3
	*(s_map+56) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=551; // up a 4
	*(s_map+57) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=571; // up a 5
	*(s_map+58) = esat::SubSprite(ss,x,y,width,height);
	x=643,y=591; // up a 6
	*(s_map+59) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=498; // up b 1
	*(s_map+60) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=519; // up b 2
	*(s_map+61) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=531; // up b 3
	*(s_map+62) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=551; // up b 4
	*(s_map+63) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=571; // up b 5
	*(s_map+64) = esat::SubSprite(ss,x,y,width,height);
	x=663,y=591; // up b 6
	*(s_map+65) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=498; // up c 1
	*(s_map+66) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=519; // up c 2
	*(s_map+67) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=531; // up c 3
	*(s_map+68) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=551; // up c 4
	*(s_map+69) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=571; // up c 5
	*(s_map+70) = esat::SubSprite(ss,x,y,width,height);
	x=683,y=591; // up c 6
	*(s_map+71) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=498,width=20,height=20; // rgt 1
	*(s_map+72) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=518; // rgt 2
	*(s_map+73) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=518; // rgt 3
	*(s_map+74) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=551; // rgt 4
	*(s_map+75) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=571; // rgt 5
	*(s_map+76) = esat::SubSprite(ss,x,y,width,height);
	x=700,y=591; // rgt 6
	*(s_map+77) = esat::SubSprite(ss,x,y,width,height);

	//SUELO CON ARENA
	x=212,y=36; // up lf
	*(s_map+78) = esat::SubSprite(ss,x,y,width,height);
	x=212,y=56; // dw l
	*(s_map+79) = esat::SubSprite(ss,x,y,width,height);
	x=232,y=36; // u r
	*(s_map+80) = esat::SubSprite(ss,x,y,width,height);
	x=232,y=56; // dwn rg
	*(s_map+81) = esat::SubSprite(ss,x,y,width,height);
	x=212,y=45; // lf
	*(s_map+82) = esat::SubSprite(ss,x,y,width,height);
	x=232,y=45; // rg
	*(s_map+83) = esat::SubSprite(ss,x,y,width,height);
	x=222,y=36; // up
	*(s_map+84) = esat::SubSprite(ss,x,y,width,height);
	x=222,y=56; // dwn
	*(s_map+85) = esat::SubSprite(ss,x,y,width,height);
	x=221,y=47; // center
	*(s_map+86) = esat::SubSprite(ss,x,y,width,height);

	// FONDO POKEDEX
	*(s_map+87) = esat::SpriteFromFile("./recursos/imagenes/pika2.jpg");

	// POKEBALL POKEDEX
	x=69,y=20,width=8,height=8; // center
	*(s_map+88) = esat::SubSprite(ss,x,y,width,height);

	// FONDO BLANCO
	*(s_map+89) = esat::SpriteFromFile("./recursos/imagenes/white.jpg");
	// POKE BALL
	*(s_map+90) = esat::SpriteFromFile("./recursos/imagenes/poke.png");
	// GRASS 3
	x=160,y=90,width=20,height=20;
	*(s_map+91) = esat::SubSprite(sss,x,y,width,height);
	// TREE
	x=40,y=125;
	*(s_map+92) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+93) = esat::SubSprite(sss,x,y,width,height);
	x+=20,y=125;
	*(s_map+94) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+95) = esat::SubSprite(sss,x,y,width,height);
	// HOUSE 4x4
	x=180,y=30;
	*(s_map+96) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+97) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+98) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+99) = esat::SubSprite(sss,x,y,width,height);

	x+=20,y=30;
	*(s_map+100) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+101) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+102) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+103) = esat::SubSprite(sss,x,y,width,height);

	x+=20,y=30;
	*(s_map+104) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+105) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+106) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+107) = esat::SubSprite(sss,x,y,width,height);

	x+=20,y=30;
	*(s_map+108) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+109) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+110) = esat::SubSprite(sss,x,y,width,height);
	y+=20;
	*(s_map+111) = esat::SubSprite(sss,x,y,width,height);

	// MINI GRASS 3
	x=143,y=64,width=18,height=8;
	*(s_map+112) = esat::SubSprite(sss,x,y,width,height);
	x=141,y=64,width=18,height=8;
	*(s_map+113) = esat::SubSprite(sss,x,y,width,height);
	//MINI GRASS 2
	x=640,y=347,width=18,height=8;
	*(s_map+114) = esat::SubSprite(s,x,y,width,height);
	x=642;
	*(s_map+115) = esat::SubSprite(s,x,y,width,height);
	// MOUNTAIN
	x=192,y=160,width=48,height=48;
	*(s_map+116) = esat::SubSprite(ss,x,y,width,height);
	// AGUJERO AGUA
	x=288,y=1,width=80,height=60;
	*(s_map+117) = esat::SubSprite(ss,x,y,width,height);
	// QUIEN ES ESTE POKEMON
	*(s_map+118) = esat::SpriteFromFile("./recursos/imagenes/duda.png");
}

void LoadPlayer(esat::SpriteHandle s){
	s_player = (esat::SpriteHandle*) malloc(13*sizeof(esat::SpriteHandle));
	int x=197,y=4,width=20,height=26;
	// UP
	*(s_player+0) = esat::SubSprite(s,x,y,width,height);
	x=261,y=3,height=28;
	*(s_player+1) = esat::SubSprite(s,x,y,width,height);
	x=229,y=99;
	*(s_player+2) = esat::SubSprite(s,x,y,width,height);
	// LEFT
	x=200,y=36,width=18,height=26;
	*(s_player+4) = esat::SubSprite(s,x,y,width,height);
	x=200,y=69,height=25;
	*(s_player+3) = esat::SubSprite(s,x,y,width,height);
	x=200,y=100,height=26;
	*(s_player+5) = esat::SubSprite(s,x,y,width,height);
	// RIGHT
	x=230,y=5,height=25;
	*(s_player+6) = esat::SubSprite(s,x,y,width,height);
	x=230,y=36,width=18,height=26;
	*(s_player+7) = esat::SubSprite(s,x,y,width,height);
	x=230,y=68;
	*(s_player+8) = esat::SubSprite(s,x,y,width,height);
	// DOWN
	x=262,y=36,width=20,height=26;
	*(s_player+9) = esat::SubSprite(s,x,y,width,height);
	x=262,y=67,height=28;
	*(s_player+10) = esat::SubSprite(s,x,y,width,height);
	x=262,y=99;
	*(s_player+11) = esat::SubSprite(s,x,y,width,height);
	// COMBAT PLAYER
	x=262,y=99;
	*(s_player+12) = esat::SpriteFromFile("./recursos/imagenes/maximo.png");
}

void LoadPokemon(esat::SpriteHandle s){
	s_pokemon = (esat::SpriteHandle*) malloc(16*sizeof(esat::SpriteHandle));

	*(s_pokemon+0) = esat::SpriteFromFile("./recursos/imagenes/regirock.png");
	*(s_pokemon+1) = esat::SpriteFromFile("./recursos/imagenes/regice.png");
	*(s_pokemon+2) = esat::SpriteFromFile("./recursos/imagenes/registeel.png");
	*(s_pokemon+3) = esat::SpriteFromFile("./recursos/imagenes/blaziken.png");
	*(s_pokemon+4) = esat::SpriteFromFile("./recursos/imagenes/deoxys.png");
	*(s_pokemon+5) = esat::SpriteFromFile("./recursos/imagenes/groudon.png");
	*(s_pokemon+6) = esat::SpriteFromFile("./recursos/imagenes/jirachi.png");
	*(s_pokemon+7) = esat::SpriteFromFile("./recursos/imagenes/kyogre.png");
	*(s_pokemon+8) = esat::SpriteFromFile("./recursos/imagenes/latias.png");
	*(s_pokemon+9) = esat::SpriteFromFile("./recursos/imagenes/latios.png");
	*(s_pokemon+10) = esat::SpriteFromFile("./recursos/imagenes/mew.png");
	*(s_pokemon+11) = esat::SpriteFromFile("./recursos/imagenes/mewtwo.png");
	*(s_pokemon+12) = esat::SpriteFromFile("./recursos/imagenes/rayquaza.png");
	*(s_pokemon+13) = esat::SpriteFromFile("./recursos/imagenes/sceptile.png");
	*(s_pokemon+14) = esat::SpriteFromFile("./recursos/imagenes/swampert.png");
	*(s_pokemon+15) = esat::SpriteFromFile("./recursos/imagenes/arceus.png");
}

void LoadFont(){
	esat::DrawSetTextFont("./Recursos/fonts/PokemonGb.ttf");
}

void AllLoads(){
	spritesheet = (esat::SpriteHandle*) malloc(6*sizeof(esat::SpriteHandle));

	*(spritesheet+0) = esat::SpriteFromFile("./recursos/imagenes/characters.png");
	*(spritesheet+1) = esat::SpriteFromFile("./recursos/imagenes/map.png");
	*(spritesheet+2) = esat::SpriteFromFile("./recursos/imagenes/tiles.png");
	*(spritesheet+3) = esat::SpriteFromFile("./recursos/imagenes/pokemon.png");
	*(spritesheet+4) = esat::SpriteFromFile("./recursos/imagenes/map2.png");

	LoadPlayer(*(spritesheet+0));
	LoadMap(*(spritesheet+1),*(spritesheet+2),*(spritesheet+4));
	LoadPokemon(*(spritesheet+3));
	LoadFont();
}

// INIS
void IniPlayer(){
	lista1=NULL;
	player.direction=0;
	player.sprite=0;
	player.animation=0;
	player.count=0;
	player.pos.x=400/2;
	player.pos.y=300/2-20;
	player.battle.x=0;
	player.battle.y=0;
	player.count_battle=0;
	player.activate_battle=false;
	player.run=false;
	player.capture=false;
	player.inventory=false;
	player.speed=1;
	player.menu=0;
	player.election=false;
	adjust_mapX=0;adjust_mapY=0;
}

void IniPokemon(){
	pokemon.name = (char*) malloc(80*sizeof(char));
	pokemon.appear=false;
}

void IniPokedex(){
	p = (TPokedex*)calloc(16,sizeof(TPokedex));
	int x=30,y=70;
	for(int i=0;i<16;i++){
		(p+i)->name = (char*) malloc(80*sizeof(char));
		(p+i)->n = (char*) malloc(10*sizeof(char));
		// NOMBRE POKEMON
		switch(i){
			case 0: (p+i)->name="REGIROCK";(p+i)->n="001\0";break;
			case 1: (p+i)->name="REGICE";(p+i)->n="002\0";break;
			case 2: (p+i)->name="REGISTEEL";(p+i)->n="003\0";break;
			case 3: (p+i)->name="BLAZIKEN";(p+i)->n="004\0";break;
			case 4: (p+i)->name="DEOXYS";(p+i)->n="005\0";break;
			case 5: (p+i)->name="GROUDON";(p+i)->n="006\0";break;
			case 6: (p+i)->name="JIRACHI";(p+i)->n="007\0";break;
			case 7: (p+i)->name="KYOGRE";(p+i)->n="008\0";break;
			case 8: (p+i)->name="LATIAS";(p+i)->n="009\0";break;
			case 9: (p+i)->name="LATIOS";(p+i)->n="010\0";break;
			case 10: (p+i)->name="MEW";(p+i)->n="011\0";break;
			case 11: (p+i)->name="MEWTWO";(p+i)->n="012\0";break;
			case 12: (p+i)->name="RAYQUAZA";(p+i)->n="013\0";break;
			case 13: (p+i)->name="SCEPTILE";(p+i)->n="014\0";break;
			case 14: (p+i)->name="SWAMPERT";(p+i)->n="015\0";break;
			case 15: (p+i)->name="ARCEUS";(p+i)->n="016\0";break;
		}
		if(i==14){x=30;y+=40;}
		(p+i)->pos.x=(float)x;
		(p+i)->pos.y=(float)y;
		x+=130;if(x>360){x=30;y+=40;}
		(p+i)->seen=false;(p+i)->caught=false;
	}
}

void HoleFloor(int i, int x, int y){
	//no coindida y no limites
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147  && i+3!=1147  && i+4!=1147 && i+5!=1147 &&
	i+51!=1147 && i+52!=1147  && i+53!=1147  && i+54!=1147  && i+55!=1147 && i+56!=1147 &&
	i+102!=1147 && i+103!=1147  && i+104!=1147  && i+105!=1147  && i+106!=1147 && i+107!=1147 &&
	i+153!=1147 && i+154!=1147  && i+155!=1147  && i+156!=1147  && i+157!=1147  && i+158!=1147 &&
	i+204!=1147 && i+205!=1147  && i+206!=1147  && i+207!=1147  && i+208!=1147 && i+209!=1147 &&
	i+255!=1147 && i+256!=1147  && i+257!=1147  && i+258!=1147  && i+259!=1147 && i+260!=1147
	){//activar agujero
		int r=rand()%2;
		if(r==0){
			//asigno sprite
			(map+i)->sprite=4;(map+i+1)->sprite=5;(map+i+2)->sprite=5;(map+i+3)->sprite=6;
			(map+i+51)->sprite=7;(map+i+52)->sprite=12;(map+i+53)->sprite=12;(map+i+54)->sprite=9;
			(map+i+102)->sprite=7;(map+i+103)->sprite=12;(map+i+104)->sprite=9;
			(map+i+153)->sprite=8;(map+i+154)->sprite=11;(map+i+155)->sprite=10;
			// special true
			(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;
			(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;
			(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;
			(map+i+153)->special_sprite=true;(map+i+154)->special_sprite=true;(map+i+155)->special_sprite=true;
		}else{
			//asigno sprite
			(map+i)->sprite=4;(map+i+1)->sprite=5;(map+i+2)->sprite=5;(map+i+3)->sprite=6;
			(map+i+51)->sprite=7;(map+i+52)->sprite=12;(map+i+53)->sprite=12;(map+i+54)->sprite=9;
			(map+i+102)->sprite=7;(map+i+103)->sprite=12;(map+i+104)->sprite=12;(map+i+105)->sprite=9;
			(map+i+153)->sprite=8;(map+i+154)->sprite=11;(map+i+155)->sprite=11;(map+i+156)->sprite=10;
			//asigno sprite
			(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;
			(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;
			(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;(map+i+105)->special_sprite=true;
			(map+i+153)->special_sprite=true;(map+i+154)->special_sprite=true;(map+i+155)->special_sprite=true;(map+i+156)->special_sprite=true;
		}
	}else{(map+i)->sprite=0;}
}

void MarketBuild(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<420 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true &&
	(map+i-204)->special_sprite!=true && (map+i-203)->special_sprite!=true && (map+i-202)->special_sprite!=true && (map+i-201)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147  && i+3!=1147  && i+4!=1147 && i+5!=1147 &&
	i+51!=1147 && i+52!=1147  && i+53!=1147  && i+54!=1147  && i+55!=1147 && i+56!=1147 &&
	i+102!=1147 && i+103!=1147  && i+104!=1147  && i+105!=1147  && i+106!=1147 && i+107!=1147 &&
	i+153!=1147 && i+154!=1147  && i+155!=1147  && i+156!=1147  && i+157!=1147  && i+158!=1147 &&
	i+204!=1147 && i+205!=1147  && i+206!=1147  && i+207!=1147  && i+208!=1147 && i+209!=1147 &&
	i+255!=1147 && i+256!=1147  && i+257!=1147  && i+258!=1147  && i+259!=1147 && i+260!=1147
	){
		(map+i)->sprite=28;(map+i+1)->sprite=33;(map+i+2)->sprite=38;(map+i+3)->sprite=43;
		(map+i+51)->sprite=29;(map+i+52)->sprite=34;(map+i+53)->sprite=39;(map+i+54)->sprite=44;
		(map+i+102)->sprite=30;(map+i+103)->sprite=35;(map+i+104)->sprite=40;(map+i+105)->sprite=45;
		(map+i+153)->sprite=31;(map+i+154)->sprite=36;(map+i+155)->sprite=41;(map+i+156)->sprite=46;
		(map+i+204)->sprite=32;(map+i+205)->sprite=37;(map+i+206)->sprite=42;(map+i+207)->sprite=47;
								(map+i+256)->sprite=0;
		(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;
		(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;
		(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;(map+i+105)->special_sprite=true;
		(map+i+153)->special_sprite=true;(map+i+154)->special_sprite=true;(map+i+155)->special_sprite=true;(map+i+156)->special_sprite=true;
		(map+i+204)->special_sprite=true;(map+i+205)->special_sprite=true;(map+i+206)->special_sprite=true;(map+i+207)->special_sprite=true;
	}else{(map+i)->sprite=0;}
}

void PokemonCenter(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-240 && y<400 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true && (map+i-4)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true && (map+i-47)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true && (map+i-98)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true && (map+i-149)->special_sprite!=true &&
	(map+i-204)->special_sprite!=true && (map+i-203)->special_sprite!=true && (map+i-202)->special_sprite!=true && (map+i-201)->special_sprite!=true && (map+i-200)->special_sprite!=true &&
	(map+i-255)->special_sprite!=true && (map+i-254)->special_sprite!=true && (map+i-253)->special_sprite!=true && (map+i-252)->special_sprite!=true && (map+i-251)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147  && i+3!=1147  && i+4!=1147 && i+5!=1147 &&
	i+51!=1147 && i+52!=1147  && i+53!=1147  && i+54!=1147  && i+55!=1147 && i+56!=1147 &&
	i+102!=1147 && i+103!=1147  && i+104!=1147  && i+105!=1147  && i+106!=1147 && i+107!=1147 &&
	i+153!=1147 && i+154!=1147  && i+155!=1147  && i+156!=1147  && i+157!=1147  && i+158!=1147 &&
	i+204!=1147 && i+205!=1147  && i+206!=1147  && i+207!=1147  && i+208!=1147 && i+209!=1147 &&
	i+255!=1147 && i+256!=1147  && i+257!=1147  && i+258!=1147  && i+259!=1147 && i+260!=1147
	){
		(map+i)->sprite=48;(map+i+1)->sprite=54;(map+i+2)->sprite=60;(map+i+3)->sprite=66;(map+i+4)->sprite=72;
		(map+i+51)->sprite=49;(map+i+52)->sprite=55;(map+i+53)->sprite=61;(map+i+54)->sprite=67;(map+i+55)->sprite=73;
		(map+i+102)->sprite=50;(map+i+103)->sprite=56;(map+i+104)->sprite=62;(map+i+105)->sprite=68;(map+i+106)->sprite=74;
		(map+i+153)->sprite=51;(map+i+154)->sprite=57;(map+i+155)->sprite=63;(map+i+156)->sprite=69;(map+i+157)->sprite=75;
		(map+i+204)->sprite=52;(map+i+205)->sprite=58;(map+i+206)->sprite=64;(map+i+207)->sprite=70;(map+i+208)->sprite=76;
		(map+i+255)->sprite=53;(map+i+256)->sprite=59;(map+i+257)->sprite=65;(map+i+258)->sprite=71;(map+i+259)->sprite=77;
								(map+i+308)->sprite=0;

		(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;(map+i+4)->special_sprite=true;
		(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;(map+i+55)->special_sprite=true;
		(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;(map+i+105)->special_sprite=true;(map+i+106)->special_sprite=true;
		(map+i+153)->special_sprite=true;(map+i+154)->special_sprite=true;(map+i+155)->special_sprite=true;(map+i+156)->special_sprite=true;(map+i+157)->special_sprite=true;
		(map+i+204)->special_sprite=true;(map+i+205)->special_sprite=true;(map+i+206)->special_sprite=true;(map+i+207)->special_sprite=true;(map+i+208)->special_sprite=true;
		(map+i+255)->special_sprite=true;(map+i+256)->special_sprite=true;(map+i+257)->special_sprite=true;(map+i+258)->special_sprite=true;(map+i+259)->special_sprite=true;
	}else{(map+i)->sprite=0;}
}

void SandFloor(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true
	){
		int r=rand()%2;
		if(r==0){
			//asigno sprite
			(map+i)->sprite=78;(map+i+1)->sprite=80;
			(map+i+51)->sprite=79;(map+i+52)->sprite=81;

		}else{
			//asigno sprite
			(map+i)->sprite=78;(map+i+1)->sprite=84;(map+i+2)->sprite=84;(map+i+3)->sprite=80;
			(map+i+51)->sprite=82;(map+i+52)->sprite=86;(map+i+53)->sprite=86;(map+i+54)->sprite=83;
			(map+i+102)->sprite=79;(map+i+103)->sprite=85;(map+i+104)->sprite=85;(map+i+105)->sprite=81;
		}
	}else{(map+i)->sprite=0;}
}

void Grass1(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true &&
	(map+i)->sprite!=78 &&(map+i-1)->sprite!=78 && (map+i-2)->sprite!=78 && (map+i-3)->sprite!=78 &&
	(map+i-51)->sprite!=78 && (map+i-50)->sprite!=78 && (map+i-49)->sprite!=78 && (map+i-48)->sprite!=78 &&
	(map+i-102)->sprite!=78 && (map+i-101)->sprite!=78 && (map+i-100)->sprite!=78 && (map+i-99)->sprite!=78 &&
	(map+i-153)->sprite!=78 && (map+i-152)->sprite!=78 && (map+i-151)->sprite!=78 && (map+i-150)->sprite!=78
	){
		int r=rand()%2;
		if(r==0){
			//asigno sprite
			(map+i)->sprite=91;(map+i+1)->sprite=91;(map+i+2)->sprite=91;
			(map+i+51)->sprite=91;(map+i+52)->sprite=91;(map+i+53)->sprite=91;
			(map+i+102)->sprite=91;(map+i+103)->sprite=91;(map+i+104)->sprite=91;
			(map+i+153)->sprite=91;(map+i+154)->sprite=91;(map+i+155)->sprite=91;

		}else{
			//asigno sprite
			(map+i)->sprite=91;(map+i+1)->sprite=91;(map+i+2)->sprite=91;(map+i+3)->sprite=91;
			(map+i+51)->sprite=91;(map+i+52)->sprite=91;(map+i+53)->sprite=91;(map+i+54)->sprite=91;
			(map+i+102)->sprite=91;(map+i+103)->sprite=91;(map+i+104)->sprite=91;(map+i+105)->sprite=91;
		}
	}else{(map+i)->sprite=0;}
}

void Grass2(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true
	){
		int r=rand()%2;
		if(r==0){
			//asigno sprite
			(map+i)->sprite=13;(map+i+1)->sprite=13;(map+i+2)->sprite=13;
			(map+i+51)->sprite=13;(map+i+52)->sprite=13;(map+i+53)->sprite=13;
			(map+i+102)->sprite=13;(map+i+103)->sprite=13;(map+i+104)->sprite=13;
			(map+i+153)->sprite=13;(map+i+154)->sprite=13;(map+i+155)->sprite=13;
		}else{
			//asigno sprite
			(map+i)->sprite=13;(map+i+1)->sprite=13;(map+i+2)->sprite=13;(map+i+3)->sprite=13;
			(map+i+51)->sprite=13;(map+i+52)->sprite=13;(map+i+53)->sprite=13;(map+i+54)->sprite=13;
			(map+i+102)->sprite=13;(map+i+103)->sprite=13;(map+i+104)->sprite=13;(map+i+105)->sprite=13;
		}
	}else{(map+i)->sprite=0;}
}

void Tree(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true &&
	i!=1147 && i+1!=1147  &&
	i+51!=1147 && i+52!=1147
	){
		//asigno sprite
		(map+i)->sprite=92;(map+i+1)->sprite=94;
		(map+i+51)->sprite=93;(map+i+52)->sprite=95;
		(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;
		(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;
	}
}

void House(int i, int x, int y){
	//no coindida y no limites
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	(map+i-153)->special_sprite!=true && (map+i-152)->special_sprite!=true && (map+i-151)->special_sprite!=true && (map+i-150)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147  && i+3!=1147  && i+4!=1147 && i+5!=1147 &&
	i+51!=1147 && i+52!=1147  && i+53!=1147  && i+54!=1147  && i+55!=1147 && i+56!=1147 &&
	i+102!=1147 && i+103!=1147  && i+104!=1147  && i+105!=1147  && i+106!=1147 && i+107!=1147 &&
	i+153!=1147 && i+154!=1147  && i+155!=1147  && i+156!=1147  && i+157!=1147  && i+158!=1147
	){//activar agujero
	//asigno sprite
			(map+i)->sprite=96;(map+i+1)->sprite=100;(map+i+2)->sprite=104;(map+i+3)->sprite=108;
			(map+i+51)->sprite=97;(map+i+52)->sprite=101;(map+i+53)->sprite=105;(map+i+54)->sprite=109;
			(map+i+102)->sprite=98;(map+i+103)->sprite=102;(map+i+104)->sprite=106;(map+i+105)->sprite=110;
			(map+i+153)->sprite=99;(map+i+154)->sprite=103;(map+i+155)->sprite=107;(map+i+156)->sprite=111;
									(map+i+205)->sprite=0;
			//asigno sprite
			(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;
			(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;
			(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;(map+i+105)->special_sprite=true;
			(map+i+153)->special_sprite=true;(map+i+154)->special_sprite=true;(map+i+155)->special_sprite=true;(map+i+156)->special_sprite=true;
	}else{(map+i)->sprite=0;}
}

void HoleWater(int i, int x, int y){
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true && (map+i-3)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true && (map+i-48)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true && (map+i-99)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147  && i+3!=1147  &&
	i+51!=1147 && i+52!=1147  && i+53!=1147  && i+54!=1147  &&
	i+102!=1147 && i+103!=1147  && i+104!=1147  && i+105!=1147
	){//activar agujero
		(map+i)->sprite=117;(map+i+1)->sprite=0;(map+i+2)->sprite=0;
		(map+i+51)->sprite=0;(map+i+52)->sprite=0;(map+i+53)->sprite=0;
		(map+i+102)->sprite=0;(map+i+103)->sprite=0;(map+i+104)->sprite=0;
		//asigno sprite
		(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;(map+i+3)->special_sprite=true;
		(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;(map+i+54)->special_sprite=true;
		(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;(map+i+105)->special_sprite=true;
	}else{(map+i)->sprite=0;}
}

void Mountain(int i, int x, int y){
	//no coindida y no limites
	if(x>=-240 && x<620 && y>=-260 && y<=480 &&
	(map+i)->special_sprite!=true &&(map+i-1)->special_sprite!=true && (map+i-2)->special_sprite!=true &&
	(map+i-51)->special_sprite!=true && (map+i-50)->special_sprite!=true && (map+i-49)->special_sprite!=true &&
	(map+i-102)->special_sprite!=true && (map+i-101)->special_sprite!=true && (map+i-100)->special_sprite!=true &&
	i!=1147 && i+1!=1147  && i+2!=1147 &&
	i+51!=1147 && i+52!=1147  && i+53!=1147 &&
	i+102!=1147 && i+103!=1147  && i+104!=1147
	){
	//asigno sprite
		(map+i)->sprite=116;(map+i+1)->sprite=0;(map+i+2)->sprite=0;
		(map+i+51)->sprite=0;(map+i+52)->sprite=0;(map+i+53)->sprite=0;
		(map+i+102)->sprite=0;(map+i+103)->sprite=0;(map+i+104)->sprite=0;
		//asigno sprite
		(map+i)->special_sprite=true;(map+i+1)->special_sprite=true;(map+i+2)->special_sprite=true;
		(map+i+51)->special_sprite=true;(map+i+52)->special_sprite=true;(map+i+53)->special_sprite=true;
		(map+i+102)->special_sprite=true;(map+i+103)->special_sprite=true;(map+i+104)->special_sprite=true;
	}else{(map+i)->sprite=0;}
}

void IniMap(){
	// filas 50 columnas 45
	map = (TMap*) calloc(total_map,sizeof(TMap));
	int x=-300,y=-300;
	for(int i=0;i<total_map;i++){
		(map+i)->sprite=1;(map+i)->special_sprite=false;
	}

	for(int i=0;i<total_map;i++){
		(map+i)->pos.x=x;(map+i)->pos.y=y;
		x+=20;
		if(x>=WindowX+300){
			x=-300;y+=20;
		}
		// si aun no tiene type asignado
		if((map+i)->sprite==1){
			(map+i)->type=rand()%500;
			// HIERBA ALTA 1
			if((map+i)->type>=0 && (map+i)->type<80){(map+i)->sprite=91;
			// HIERBA ALTA 2
			}else if((map+i)->type>=80 && (map+i)->type<160){(map+i)->sprite=13;
			// SUELO 2
			}else if((map+i)->type>=160 && (map+i)->type<200){(map+i)->sprite=24;
			// SUELO 3
			}else if((map+i)->type>=200 && (map+i)->type<210){(map+i)->sprite=25;
			// SUELO 4
			}else if((map+i)->type>=240 && (map+i)->type<280){(map+i)->sprite=26;
			// SUELO 5
			}else if((map+i)->type>=280 && (map+i)->type<320){(map+i)->sprite=27;
			// MARKET && POKEMON CENTER
			}else if((map+i)->type>=320 && (map+i)->type<322){
				int r=rand()%2;
				if(r==0){MarketBuild(i,x,y);
				}else{PokemonCenter(i,x,y);}
			// SUELO ARENA
			}else if((map+i)->type>=322 && (map+i)->type<324){SandFloor(i,x,y);
			// GRUPO HIERBA 1
			}else if((map+i)->type>=324 && (map+i)->type<325){Grass1(i,x,y);
			// GRUPO HIERBA 2
			}else if((map+i)->type>=326 && (map+i)->type<328){Grass2(i,x,y);
			// AGUJERO TIERRA
			}else if((map+i)->type>=328 && (map+i)->type<330){HoleFloor(i,x,y);
			// ARBOL
			}else if((map+i)->type>=330 && (map+i)->type<332){Tree(i,x,y);
			// CASA
			}else if((map+i)->type>=332 && (map+i)->type<334){House(i,x,y);
			// AGUJERO AGUA
			}else if((map+i)->type>=334 && (map+i)->type<336){HoleWater(i,x,y);
			// MONTAÑA
			}else if((map+i)->type>=336 && (map+i)->type<338){Mountain(i,x,y);
			// SUELO NORMAL
			}else if((map+i)->type>=338)(map+i)->sprite=0;
		}
		if((map+i)->sprite==1)(map+i)->sprite=0;
		if(y<-260 || y>540 || x<-240 || x>680)(map+i)->sprite=1;
	}
}

void AllIni(){
	IniPlayer();
	IniMap();
	IniPokemon();
	IniPokedex();
}

// GENERAL COLISION QUAD
bool CheckRectangleColision(short x, short y, short width, short height, short x2, short y2, short width2, short height2) {
    if (((x <= width2 && x >= x2) || (width <= width2 && width >= x2)) && ((y >= y2 && y <= height2) || (height >= y2 && height <= height2))) {
        return true;
    }
    return false;
}

bool ColisionPlayerMap(int side){
	for(int i=0;i<total_map;i++){
		// 0-> Down , 1-> UP , 2-> LEFT , 3-> RIGHT
		int control=player.speed;
		if(control==2)control=4;
		else control=2;
		switch(side){
			case 1:	if(CheckRectangleColision(player.pos.x+4,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation))/2+2,
					player.pos.x+esat::SpriteWidth(*(s_player+player.sprite+player.animation))-4,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation)),
					(map+i)->pos.x+adjust_mapX+4,(map+i)->pos.y+adjust_mapY+12,
					(map+i)->pos.x+16+adjust_mapX,(map+i)->pos.y+20+adjust_mapY+control) && ((map+i)->sprite==1 || (map+i)->special_sprite==true)){
						return true;
					}
					break;
			case 0:	if(CheckRectangleColision(player.pos.x+4,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation))/2+2,
					player.pos.x+esat::SpriteWidth(*(s_player+player.sprite+player.animation))-4,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation)),
					(map+i)->pos.x+adjust_mapX+4,(map+i)->pos.y+adjust_mapY-control,
					(map+i)->pos.x+16+adjust_mapX,(map+i)->pos.y+8+adjust_mapY) && ((map+i)->sprite==1 || (map+i)->special_sprite==true)){
						return true;
					}
					break;
			case 2:	if(CheckRectangleColision(player.pos.x,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation))/2+2,
					player.pos.x+esat::SpriteWidth(*(s_player+player.sprite+player.animation)),player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation)),
					(map+i)->pos.x+adjust_mapX+12,(map+i)->pos.y+adjust_mapY+3,
					(map+i)->pos.x+20+adjust_mapX+control,(map+i)->pos.y+17+adjust_mapY) && ((map+i)->sprite==1 || (map+i)->special_sprite==true)){
						return true;
					}
					break;
			case 3: if(CheckRectangleColision(player.pos.x,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation))/2+2,
					player.pos.x+esat::SpriteWidth(*(s_player+player.sprite+player.animation)),player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation)),
					(map+i)->pos.x+adjust_mapX-control,(map+i)->pos.y+adjust_mapY+3,
					(map+i)->pos.x+8+adjust_mapX,(map+i)->pos.y+17+adjust_mapY) && ((map+i)->sprite==1 || (map+i)->special_sprite==true)){
						return true;
					}
					break;
		}
	}
	return false;
}

void ColisionPlayerGrass(){
	for(int i=0;i<total_map;i++){
		if(CheckRectangleColision(player.pos.x+10,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation))/2+2,
			player.pos.x+esat::SpriteWidth(*(s_player+player.sprite+player.animation))-8,player.pos.y+esat::SpriteHeight(*(s_player+player.sprite+player.animation)),
			(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY,
			(map+i)->pos.x+20+adjust_mapX,(map+i)->pos.y+20+adjust_mapY-8) && ((map+i)->sprite==91||(map+i)->sprite==13)){
				int a=player.animation;
				if(a>1)a=0;
				if((map+i)->sprite==91)esat::DrawSprite(*(s_map+112+a),player.pos.x, player.pos.y+20);
				else esat::DrawSprite(*(s_map+114+a),player.pos.x, player.pos.y+20);
				int r=rand()%100;
				if(r==10 && (esat::IsSpecialKeyPressed(esat::kSpecialKey_Down)||
				esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)||
				esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)||
				esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)))player.activate_battle=true;
		}
	}
}

// PLAYER
void MovementSprite(){
	switch(player.direction){
		case 0: player.sprite=9;
				break;
		case 1: player.sprite=0;
				break;
		case 2: player.sprite=3;
				break;
		case 3: player.sprite=6;
				break;
	}
}

void MovementAnimation(){
	if(player.speed==1){
		if(player.count<4)player.animation=0;
		if(player.count>=4 && player.count<8)player.animation=1;
		if(player.count>=8 && player.count<12)player.animation=2;
		player.count++;
		if(player.count>=10)player.count=0;
	}else{
		if(player.count<2)player.animation=0;
		if(player.count>=2 && player.count<4)player.animation=1;
		if(player.count>=4 && player.count<6)player.animation=2;
		player.count++;
		if(player.count>=6)player.count=0;
	}
}

void MovementPlayer(){
	MovementSprite();ColisionPlayerGrass();
	if(esat::IsKeyPressed('B'))player.speed=2;
	else player.speed=1;
	// 0-> Down , 1-> UP , 2-> LEFT , 3-> RIGHT
	if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Down) && !ColisionPlayerMap(0)){
		if(player.direction!=0){player.count=0;player.animation=0;}
		else{
			if(player.sprite>=9 && player.sprite<=11){MovementAnimation();}
			if(adjust_mapY>-300 && player.pos.y<=150-20+3 && player.pos.y>=150-20-3)adjust_mapY-=3*player.speed;
			else player.pos.y+=3*player.speed;
		}
		player.direction=0;
	}else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Up)&& !ColisionPlayerMap(1)){
		if(player.direction!=1){player.count=0;player.animation=0;}
		else{
			if(player.sprite>=0 && player.sprite<=2){MovementAnimation();}
			if(adjust_mapY<300 && player.pos.y<=150-20+3 && player.pos.y>=150-20-3)adjust_mapY+=3*player.speed;
			else player.pos.y-=3*player.speed;
		}
		player.direction=1;
	}else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Left)&& !ColisionPlayerMap(2)){
		if(player.direction!=2){player.count=0;player.animation=0;}
		else{
			if(player.sprite>=3 && player.sprite<=5){MovementAnimation();}
			if(adjust_mapX<300 && player.pos.x<=200+3 && player.pos.x>=200-3)adjust_mapX+=3*player.speed;
			else player.pos.x-=3*player.speed;
		}
		player.direction=2;
	}else if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Right)&& !ColisionPlayerMap(3)){
		if(player.direction!=3){player.count=0;player.animation=0;}
		else{
			if(player.sprite>=6 && player.sprite<=8){MovementAnimation();}
			if(adjust_mapX>-300 && player.pos.x<=200+3 && player.pos.x>=200-3)adjust_mapX-=3*player.speed;
			else player.pos.x+=3*player.speed;
		}
		player.direction=3;
	}

}

void DrawPlayer(){
	esat::DrawSprite(*(s_player+player.sprite+player.animation),player.pos.x, player.pos.y);
	if(player.activate_battle==false && player.inventory==false)MovementPlayer();
}

// MAP
void DrawMap(){
	for(int i=0;i<total_map;i++){
		esat::DrawSprite(*(s_map+0),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY);
	}
	int x=-340,y=-320, t=0;
	for(int i=0;i<200;i++){
		if(t!=2)x+=20;
		if(x>720 && t!=2){
			if(t==1){t=2;y=-320;x=-320;}
			if(t==0){y=600;x=-320;t=1;}
		}
		if(t==2){
			y+=20;
			if(y==620){x=720;y=-320;}
		}
		esat::DrawSprite(*(s_map+1),x+adjust_mapX,y+adjust_mapY);
	}

	for(int i=0;i<total_map;i++){
		esat::DrawSprite(*(s_map+(map+i)->sprite),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY);
		// LIMITES AGUA
		if((map+i)->pos.y==-260 && (map+i)->pos.x>=-260 && (map+i)->pos.x<680){
			esat::DrawSprite(*(s_map+21),(map+i)->pos.x+adjust_mapX-4,(map+i)->pos.y+adjust_mapY-4);
		}esat::DrawSprite(*(s_map+21),680+adjust_mapX-16,-260+adjust_mapY-4);
		if((map+i)->pos.y==560 && (map+i)->pos.x>=-260 && (map+i)->pos.x<680){
			esat::DrawSprite(*(s_map+18),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY);
		}
		if((map+i)->pos.x==-260 && (map+i)->pos.y>=-260 && (map+i)->pos.y<540){
			esat::DrawSprite(*(s_map+19),(map+i)->pos.x+adjust_mapX-4,(map+i)->pos.y+adjust_mapY-4);
		}esat::DrawSprite(*(s_map+19),-260+adjust_mapX-4,540+adjust_mapY-4);esat::DrawSprite(*(s_map+19),-260+adjust_mapX-4,540+adjust_mapY+4);
		if((map+i)->pos.x==680 && (map+i)->pos.y>=-260 && (map+i)->pos.y<=540){
			esat::DrawSprite(*(s_map+20),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY-4);
		}esat::DrawSprite(*(s_map+20),680+adjust_mapX,540+adjust_mapY-4);esat::DrawSprite(*(s_map+20),680+adjust_mapX,540+adjust_mapY+4);
		// DIBUJAR TIERRA PARA MONTAÑA
		if((map+i)->sprite==116)esat::DrawSprite(*(s_map+0),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY);
	}
	for(int i=0;i<total_map;i++){
		if((map+i)->sprite==117)esat::DrawSprite(*(s_map+(map+i)->sprite),(map+i)->pos.x+adjust_mapX,(map+i)->pos.y+adjust_mapY);
		if((map+i)->sprite==116)esat::DrawSprite(*(s_map+(map+i)->sprite),(map+i)->pos.x+adjust_mapX+6,(map+i)->pos.y+adjust_mapY+6);
	}
	esat::DrawSetStrokeColor(0,0,0);
	esat::DrawSetFillColor(0,0,0);
	esat::DrawSetTextSize(12);
	esat::DrawText(310,270,"B SPRINT");
	esat::DrawText(310,290,"A MENU");
}

// POKEMON BATTLE
void PokemonAppear(){
	// ELECCION POKEMON Y MOV PLAYER
	if(pokemon.appear==false){
		pokemon.sprite=rand()%16;
		pokemon.pos.x=-150;pokemon.pos.y=-10;
		player.battle.x=400;player.battle.y=160;
		(p+pokemon.sprite)->seen=true;
	}
	pokemon.appear=true;
	// NOMBRE POKEMON
	switch(pokemon.sprite){
		case 0: pokemon.name="REGIROCK";break;
		case 1: pokemon.name="REGICE";break;
		case 2: pokemon.name="REGISTEEL";break;
		case 3: pokemon.name="BLAZIKEN";break;
		case 4: pokemon.name="DEOXYS";break;
		case 5: pokemon.name="GROUDON";break;
		case 6: pokemon.name="JIRACHI";break;
		case 7: pokemon.name="KYOGRE";break;
		case 8: pokemon.name="LATIAS";break;
		case 9: pokemon.name="LATIOS";break;
		case 10: pokemon.name="MEW";break;
		case 11: pokemon.name="MEWTWO";break;
		case 12: pokemon.name="RAYQUAZA";break;
		case 13: pokemon.name="SCEPTILE";break;
		case 14: pokemon.name="SWAMPERT";break;
		case 15: pokemon.name="ARCEUS";break;
	}
	// BARRA VIDA
	float p8[10]={
		20,121,184,121,184,131,20,131,20,121
	};
	// MOV POKEMON Y MOV PLAYER
	if(pokemon.pos.x<215)pokemon.pos.x+=10;
	if(player.battle.x>10)player.battle.x-=10;
	// CAPTURE OR RUN
	if(esat::IsKeyDown('Z') && player.run==false){if(min<6)player.capture=true;}
	if(esat::IsKeyDown('X') && player.capture==false){player.run=true;}
	// DIBUJADO PANTALLA
	esat::DrawSprite(*(s_map+3),-5,0);
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(0,255,0);
	esat::DrawSolidPath(p8,5);

	esat::DrawSetStrokeColor(0,0,0);
	esat::DrawSetFillColor(0,0,0);
	esat::DrawSetTextSize(18);
	esat::DrawText(20,100,pokemon.name);
	esat::DrawSetTextSize(8);
	esat::DrawSetFillColor(255,0,0);esat::DrawText(90,115,"Ps");esat::DrawSetFillColor(0,0,0);esat::DrawText(110,115,"300");
	esat::DrawSetFillColor(0,0,255);esat::DrawText(140,115,"Nv");esat::DrawSetFillColor(0,0,0);esat::DrawText(160,115,"100");

	if(player.run==false && player.capture==false){
		esat::DrawSetTextSize(17);
		esat::DrawText(240,250,"Z CATCH ");
		esat::DrawText(240,280,"X RUN");
	}else if(player.run==true){
		esat::DrawSetTextSize(15);
		esat::DrawText(240,250,"YOU ESCAPE!");
		player.count_battle++;
	}else{
		(p+pokemon.sprite)->caught=true;
		esat::DrawSetTextSize(15);
		esat::DrawText(240,250,"GOTCHA!!");
		player.count_battle++;
	}

	esat::DrawSprite(*(s_pokemon+pokemon.sprite),pokemon.pos.x, pokemon.pos.y);
	esat::DrawSprite(*(s_player+12),player.battle.x,player.battle.y);
	if(player.count_battle>=20){
		if(player.capture==true){InsertarNodo(lista1,pokemon.sprite);min++;}
		n_screen=0;pokemon.appear=false;player.count_battle=0;
	}
}

// MENU
void Inventary(){
	if(esat::IsKeyDown('A')){
		if(player.inventory==false)player.inventory=true;
		else player.inventory=false;
	}
	if(player.inventory==true){
		// CUADRADO INVENTARIO
		float p[10]={
			200-170,130-90,
			200-10,130-90,
			200-10,130+70,
			200-170,130+70,
			200-170,130+70
		};

		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(255,255,255);
		esat::DrawSolidPath(p,5);

		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSetTextSize(12);
		esat::DrawText(60,65,"INVENTORY");
		esat::DrawText(60,105,"POKEDEX");
		esat::DrawText(60,145,"SAVE GAME");
		esat::DrawText(60,185,"RESET GAME");
		// FLECHA IVENTARIO
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down)){if(player.menu!=3)player.menu+=1;else player.menu=0;}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up)){if(player.menu!=0)player.menu-=1;else player.menu=3;}
		float y=0;
		if(player.menu==0){y=0;}
		else if(player.menu==1){y=40;}
		else if(player.menu==2){y=80;}
		else if(player.menu==3){y=120;}
		float p2[8]={
			200-160,130-75+y,
			200-150,130-70+y,
			200-160,130-65+y,
			200-160,130-75+y
		};
		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSolidPath(p2,4);
	}
}

void Quad(float p[],int x, int y){
	p[0]=20+x;p[1]=60+y;
	p[2]=40+x;p[3]=40+y;
	p[4]=190+x;p[5]=40+y;
	p[6]=190+x;p[7]=100+y;
	p[8]=20+x;p[9]=100+y;
	p[10]=20+x;p[11]=60+y;
}

void QuadLife(float p[],int x, int y){
	p[0]=60+x;p[1]=70+y;
	p[2]=175+x;p[3]=70+y;
	p[4]=175+x;p[5]=80+y;
	p[6]=60+x;p[7]=80+y;
	p[8]=60+x;p[9]=70+y;
}

void ChoosePokemon(int a,char *n, char *name){
	if((p+a)->seen==true){
		esat::DrawSprite(*(s_map+89),0,0);
		esat::DrawSetStrokeColor(255,255,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSetTextSize(20);
		esat::DrawText(90,60,n);
		esat::DrawText(190,60,name);
		esat::DrawSprite(*(s_pokemon+a),110, 70);

		if((p+a)->caught==true){esat::DrawSprite(*(s_map+90),158,42);}

		float p2[8]={
			80,150,
			60,160,
			80,170,
			80,150
		};
		float p3[8]={
			340,150,
			360,160,
			340,170,
			340,150
		};
		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSolidPath(p2,4);
		esat::DrawSolidPath(p3,4);
	}else{
		esat::DrawSprite(*(s_map+118),-50,0);
	}
	if(esat::IsKeyDown('M')){player.election=false;}
	esat::DrawSetTextSize(10);esat::DrawText(340,275,"M-BACK");
}

void PokemonInventory(){
	if(player.election==false){
		if(primero==NULL)n_pokedex=10;
		esat::DrawSetFillColor(0,120,0);
		float p1[12],p2[12],p3[12],p4[12],p5[12],p6[12],p7[12],p8[12],p9[12],p10[12],p11[12],p12[12];
		float x=0,y=0,w=1;
		if(n_pokedex!=0){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
		Quad(p1,x,y);esat::DrawSolidPath(p1,6);x=0;y=80;
		if(n_pokedex!=2){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
			Quad(p2,x,y);esat::DrawSolidPath(p2,6);x=0;y=160;
		if(n_pokedex!=4){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
			Quad(p3,x,y);esat::DrawSolidPath(p3,6);x=210;y=0;
		if(n_pokedex!=1){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
			Quad(p4,x,y);esat::DrawSolidPath(p4,6);x=210;y=80;
		if(n_pokedex!=3){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
			Quad(p5,x,y);esat::DrawSolidPath(p5,6);x=210;y=160;
		if(n_pokedex!=5){esat::DrawSetStrokeColor(0,255,0);}else{esat::DrawSetStrokeColor(255,0,0);x+=10;y-=10;}
			Quad(p6,x,y);esat::DrawSolidPath(p6,6);
		// LEER LISTA PARA ENSEÑARLOS
		TNodo *lista;
		lista=primero;
		if(primero!=NULL){
			int xx=0,yy=0;
			x=0;y=0;min=0;
			do{
				esat::DrawSetStrokeColor(0,0,0);
				esat::DrawSetFillColor(0,255,0);
				switch(min){
					case 0: x=0;y=0;xx=60;yy=60;if(n_pokedex==0){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p7,x,y);esat::DrawSolidPath(p7,5);break;
					case 2: x=0;y=80;xx=60;yy=140;if(n_pokedex==2){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p8,x,y);esat::DrawSolidPath(p8,5);break;
					case 4: x=0;y=160;xx=60;yy=220;if(n_pokedex==4){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p9,x,y);esat::DrawSolidPath(p9,5);break;
					case 1: x=210;y=0;xx=270;yy=60;if(n_pokedex==1){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p10,x,y);esat::DrawSolidPath(p10,5);break;
					case 3: x=210;y=80;xx=270;yy=140;if(n_pokedex==3){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p11,x,y);esat::DrawSolidPath(p11,5);break;
					case 5: x=210;y=160;xx=270;yy=220;if(n_pokedex==5){x+=10;y-=10;xx+=10;yy-=10;}QuadLife(p12,x,y);esat::DrawSolidPath(p12,5);break;
				}
				esat::DrawSetStrokeColor(255,255,255);
				esat::DrawSetFillColor(255,255,255);
				esat::DrawSetTextSize(13);
				esat::DrawText(xx,yy,(p+lista->dato)->name);
				lista=lista->prox;
				min++;
			}while(lista!=primero);
		}
		// CHOOSE OPTION
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down)){
			if(n_pokedex==4)n_pokedex=0;
			else if(n_pokedex==5)n_pokedex=1;
			else n_pokedex+=2;
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up)){
			if(n_pokedex==0)n_pokedex=4;
			else if(n_pokedex==1)n_pokedex=5;
			else n_pokedex-=2;
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left)){
			if(n_pokedex==0 || n_pokedex==2 || n_pokedex==4)n_pokedex+=1;
			else n_pokedex-=1;
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right)){
			if(n_pokedex==1 || n_pokedex==3 || n_pokedex==5)n_pokedex-=1;
			else n_pokedex+=1;
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter) && n_pokedex<min && min>0 && player.inventory==true ){player.election=true;}
		player.inventory=true;
	}else{
		TNodo *lista;
		lista=primero;int cc=0;
		// Buaco dato en lista hasta que llego a la lista requerida, no leo todas
		while(n_pokedex!=cc){
			cc++;
			lista=lista->prox;
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left)){if(lista==primero)n_pokedex=min-1; else n_pokedex-=1;}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right)){if(lista==ultimo)n_pokedex=0; else n_pokedex+=1;}
		ChoosePokemon(lista->dato,(p+lista->dato)->n,(p+lista->dato)->name);
	}
}

void Pokedex(){
	if(player.election==false){
		esat::DrawSprite(*(s_map+87),-60,0);
		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(255,0,0);
		float p5[10]={
			-5,-5,
			425,-5,
			425,45,
			-5,45,
			-5,-5
		};
		esat::DrawSolidPath(p5,5);
		esat::DrawSetStrokeColor(255,255,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSetTextSize(15);
		esat::DrawText(30,30,"POKEDEX");esat::DrawSetTextSize(10);esat::DrawText(300,30,"M-EXIT");
		esat::DrawSetStrokeColor(0,0,255);
		esat::DrawSetFillColor(0,0,0);

		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(0,0,0);
		esat::DrawSetTextSize(10);
		for(int i=0;i<16;i++){
			if(n_pokedex==i)esat::DrawSetFillColor(255,0,0);
			else esat::DrawSetFillColor(0,0,0);
			if((p+i)->seen==true)esat::DrawText((p+i)->pos.x,(p+i)->pos.y,(p+i)->name);
			else esat::DrawText((p+i)->pos.x,(p+i)->pos.y,"????");
			if((p+i)->caught==true){esat::DrawSprite(*(s_map+88),(p+i)->pos.x+90,(p+i)->pos.y-8);}
		}

		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Down)){
			if(n_pokedex>=11 && n_pokedex<14){n_pokedex+=2;}
			else if(n_pokedex==14){n_pokedex=0;}
			else if(n_pokedex==15){n_pokedex=1;}
			else{n_pokedex+=3;}
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Up)){
			if(n_pokedex== 14 || n_pokedex==15){n_pokedex-=2;}
			else if(n_pokedex==0){n_pokedex=14;}
			else if(n_pokedex==1 || n_pokedex==2){n_pokedex=15;}
			else{n_pokedex-=3;}
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left)){
			if(n_pokedex!=0){n_pokedex-=1;}
			else{n_pokedex=15;}
		}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right)){
			if(n_pokedex!=15){n_pokedex+=1;}
			else{n_pokedex=0;}
		}
		float p2[8]={
			(p+n_pokedex)->pos.x-15,(p+n_pokedex)->pos.y-10,
			(p+n_pokedex)->pos.x-5,(p+n_pokedex)->pos.y-5,
			(p+n_pokedex)->pos.x-15,(p+n_pokedex)->pos.y-0,
			(p+n_pokedex)->pos.x-15,(p+n_pokedex)->pos.y-10
		};
		esat::DrawSetStrokeColor(0,0,0);
		esat::DrawSetFillColor(255,0,0);
		esat::DrawSolidPath(p2,4);
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter) && player.inventory==true){player.election=true;}
		player.inventory=true;
	}else{
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Left)){if(n_pokedex!=0)n_pokedex-=1;else n_pokedex=15;}
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Right)){if(n_pokedex!=15)n_pokedex+=1;else n_pokedex=0;}
		ChoosePokemon(n_pokedex,(p+n_pokedex)->n,(p+n_pokedex)->name);
	}
}

// SCREENS
void ScreenGameplay(){
	DrawMap();
	DrawPlayer();
	Inventary();
}

void ScreenBattle(){
	PokemonAppear();
}

void ScreenPokemonCaught(){
	PokemonInventory();
}

void ScreenPokedex(){
	Pokedex();
}

void ChangeScreen(){
	// CAMBIO A MODO BATALLA
	if(player.activate_battle==true){
		player.run=false;player.capture=false;
		if(player.count_battle<20){
			player.count_battle++;
			if(player.count_battle%2!=0){
				n_screen=10;
			}else n_screen=0;
		}else{
			player.activate_battle=false;
			player.count_battle=0;
			n_screen=1;
		}
	}
	//CAMBIO A INVENTARIO / POKEDEX
	if(player.inventory==true && n_screen==0){
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter)){
			switch(player.menu){
				case 0: n_pokedex=0;n_screen=2;break; // INVENTORY
				case 1: n_pokedex=0;n_screen=3;break; // POKEDEX
				case 2: ;break; // SAVE
				case 3: AllIni();n_screen=0;break; // RESET
			}
			player.inventory=false;player.menu=0;
		}
	}
	// CAMBIO A GAMEPLAY
	if(((n_screen==2 && player.election==false) || (n_screen==3 && player.election==false)) && esat::IsKeyDown('M')){
		n_screen=0;player.inventory=false;
	}
}

// ALL DRAWS
void AllDraw(){
	ChangeScreen();
	/* N_SCREEN
	0-> GAMEPLAY
	1-> BATTLE
	2-> INVENTORY POKEMON
	3-> POKEDEX
	*/
	switch(n_screen){
		case 0: ScreenGameplay();break;
		case 1: ScreenBattle();break;
		case 2: ScreenPokemonCaught();break;
		case 3: ScreenPokedex();break;
	}
}

int esat::main(int argc, char **argv) {


	esat::WindowInit(WindowX,WindowY);
	WindowSetMouseVisibility(true);

	srand(time(NULL));
	AllLoads();
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


  esat::WindowDestroy();

return 0;

}
