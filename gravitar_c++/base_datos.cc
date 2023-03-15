#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/time.h>
#include <esat/sprite.h>

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const float pi = 3.141592f;
float g_circle[62] = { 0.0f };

int screen=1;
int quad_writting=20; bool secret_password=false;bool c_register=false;
int count_wrong_register=0;

struct TRegister{
	char *name, *surname, *birthday, *province, *country,
	*username, *password, *secret_password, *mail, *credits;
};

TRegister *user=NULL;


//TAREAS
/*
- MENSAJE AVISO si usuario esta registrado en sign up y menasej de aviso si usuario o contraseña es incorrecto en sign in
-GUARDAR EN FICHERO CUANDO DOY A SIGN UP
-BUSQUEDA EN FICHERO PARA INICIO SESION
-@ en sign up
-Modificar usuario cuando entro en el juego
-Mirar si birthday puedo hacer day month year y asi dejar las barras fijas y luego concateno cadenas
- añadir barra horizontal por donde escribo o que parpadee la letra
*/
/*
REGISTRADO // REGISTRARSE
PANTALLA JUEGO
- START GAME
- SCORES
- MODIFICAR USUARIO 
------------------------
para usuarios hacer lista
-----------
preguntar por el arroba
*/

void IniTRegister(){
	user=(TRegister*)calloc(1,sizeof(TRegister));
	user->name=(char*)calloc(20,sizeof(TRegister));
	user->surname=(char*)calloc(20,sizeof(TRegister));
	user->birthday=(char*)calloc(20,sizeof(TRegister));
	user->province=(char*)calloc(20,sizeof(TRegister));
	user->country=(char*)calloc(20,sizeof(TRegister));
	user->username=(char*)calloc(20,sizeof(TRegister));
	user->password=(char*)calloc(20,sizeof(TRegister));
	user->secret_password=(char*)calloc(20,sizeof(TRegister));
	user->mail=(char*)calloc(20,sizeof(TRegister));
	user->credits=(char*)calloc(20,sizeof(TRegister));
}

// GENERATE QUAD
void Quad(int x, int y, int width, int height){
	float p[10];
	p[0]=x;p[1]=y;
	p[2]=x+width;p[3]=y;
	p[4]=x+width;p[5]=y+height;
	p[6]=x;p[7]=y+height;
	p[8]=p[0];p[9]=p[1];
	
	esat::DrawPath(p,5);
}

// GENERATE CIRCLE
void Circle(float g_circle[], float g_center_x, float g_center_y, float g_radius_x, float g_radius_y) {
  for (int i = 0; i < (30 + 1); i++) {
    g_circle[i * 2] = cos(((pi * 2.0f) / 30) * i) * g_radius_x + g_center_x;
    g_circle[i * 2 + 1] = sin(((pi * 2.0f) / 30) * i) * g_radius_y + g_center_y;
  }
  esat::DrawSolidPath(g_circle, 30 + 1, true);
}
float pp=0;
void Circle2(float g_circle[], float g_center_x, float g_center_y, float g_radius_x, float g_radius_y) {
  for (int i = 0; i < (30 + 1); i++) {
    g_circle[i * 2] = cos(((pi*1) / 30) * i) * g_radius_x + g_center_x;
    g_circle[i * 2 + 1] = sin(((pi*(0.3f+pp)) / 30) * i) * g_radius_y + g_center_y;
	pp+=0.01f;
  }
  pp=0;
  esat::DrawSolidPath(g_circle, 30 + 1, true);
}

void Circle3(float g_circle[], float g_center_x, float g_center_y, float g_radius_x, float g_radius_y) {
  for (int i = 0; i < (30 + 1); i++) {
    g_circle[i * 2] = cos(((pi*1) / 30) * i) * g_radius_x + g_center_x;
    g_circle[i * 2 + 1] = sin(((pi*(-0.30f-pp)) / 30) * i) * g_radius_y + g_center_y;
	pp+=0.01f;
  }
  pp=0;
  esat::DrawSolidPath(g_circle, 30 + 1, true);
}


// DETECT MOUSE QUAD
bool DetectMouseQuad(int x, int y, int width, int height){
	if(esat::MousePositionX()>x && esat::MousePositionX()<x+width &&
	esat::MousePositionY()>y && esat::MousePositionY()<y+height){
		return true;
	}
	return false;
}


// WRITE
void WriteWord(char *&word){
	char letter;
	letter = esat::GetNextPressedKey();
	int position_letter=0;
	// recorro la palabra para saber ultima posicion libre
	while(*(word+position_letter)!='\0'){
		position_letter++;
	}
	// PONER SOLO SI DETECTO NUMERO O LETRA 48 57 numero, 65-90 mayus, 97-122 min
	int n=letter;
	if(letter!=0 && position_letter<20){
		if(quad_writting==0 || quad_writting==1 || quad_writting==3 ||quad_writting==4){
			if((letter>=65 && letter <=90) || (letter>=97 && letter <=122)){
				*(word+position_letter)=letter;
				position_letter++;
				*(word+position_letter)='\0';
			}
		}else if(quad_writting==2){
			if(letter>=48 && letter <=57 && position_letter<10){
				*(word+position_letter)=letter;
				position_letter++;
				if(position_letter==2 || position_letter==5){
					*(word+position_letter)='/';
					position_letter++;
				}
				*(word+position_letter)='\0';
			}
		}else if(quad_writting==7){
			if((letter>=48 && letter <=57) || (letter>=65 && letter <=90) ||
			(letter>=97 && letter <=122) || letter==64){
				*(word+position_letter)=letter;
				position_letter++;
				*(word+position_letter)='\0';
			}
		}else{
			if((letter>=48 && letter <=57) || (letter>=65 && letter <=90) ||
			(letter>=97 && letter <=122)){
				*(word+position_letter)=letter;
				position_letter++;
				*(word+position_letter)='\0';
			}
		}
	}
	if(position_letter>0 &&	(esat::IsSpecialKeyDown(esat::kSpecialKey_Delete) ||
	esat::IsSpecialKeyDown(esat::kSpecialKey_Backspace))){
		if(quad_writting==2 &&(position_letter==3 || position_letter==6)){
				*(word+position_letter-2)='\0';
		}else *(word+position_letter-1)='\0';
	}
}

// SIGN UP COMPLETE
bool CompleteSignUp(){
	// MAIL CONTIENE @ Y CUMPLE TIENE 10 DIGITOS 11/11/1111
	/*bool mail=false;int position_letter=0;
	while(*(user->mail+position_letter)!='\0'){
		position_letter++;
	}
	for(int i=0;i<position_letter;i++){
		if(*(user->mail+i)=='@'){mail=true;}
	}*/
	if(*(user->name+0)!='\0' && *(user->surname+0)!='\0' &&
	*(user->birthday+9)!='\0' && *(user->province+0)!='\0' &&
	*(user->country+0)!='\0' && *(user->username+0)!='\0' &&
	*(user->password+0)!='\0' && *(user->mail+0)!='\0' /*&& mail==false*/){
		return true;
	}else return false;
}

// SIGN IN COMPLETE
bool CompleteSignIn(){
	FILE *pf=fopen("base.txt","rb");
	if(pf!=NULL){
		if(*(user->username+0)!='\0' && *(user->password+0)!='\0'){
			char *us=(char*)calloc(20,sizeof(TRegister));
			bool correct_user=false,correct_password=false;
			int tt=0;
			while(!feof(pf)){
				fgets(us,20,pf);
				int position_letter=0;
				// recorro la palabra para saber ultima posicion libre
				int p=0;
				while(*(us+p)!='\0'){
					p++;
				}
				p--;
				*(us+p)='\0';
				
				if(correct_user==true && tt<1){
					if(strcmp(user->password,us)==0){
						correct_password=true;	
					}
					tt++;
				}
				if(strcmp(user->username,us)==0){
					correct_user=true;	
				}			
			}
			
			if(correct_user==true && correct_password==true){
				return true;
			}else{
				c_register=true;
				return false;
			}
		}else{
			c_register=true;
			return false;
		}
	}else{
		c_register=true;
		return false;
	}
}


void SecretPassword(){
	int position_letter=0;
	// recorro la palabra para saber ultima posicion libre
	while(*(user->password+position_letter)!='\0'){
		*(user->secret_password+position_letter)=43;
		position_letter++;
	}*(user->secret_password+position_letter)='\0';
}

//SIGN IN - SIGN UP
void ScreenR1(){
	esat::DrawSetTextFont("./Recursos/Fonts/Font2.ttf");
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	
	esat::DrawSetTextSize(100);
	//esat::DrawText(100,205,"GRAVITAR");
	
	esat::DrawSetTextSize(40);
	if(DetectMouseQuad(140,450,180,70)){
		esat::DrawSetFillColor(200,0,200);
		// CREO NUEVO USUARIO Y SI GUARDA LO GUARDO SI RETROCEDE LO ELIMINO
		if(esat::MouseButtonDown(0)){screen=3;IniTRegister();}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(160,505,"Sign in");
	
	if(DetectMouseQuad(400,450,180,70)){
		esat::DrawSetFillColor(200,0,200);
		// CREO TREGISTER USER PARA COMPROBAR SI EXISTE, LUEGO LIBERO EL PUNTERO
		if(esat::MouseButtonDown(0)){screen=2;IniTRegister();}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(420,505,"Sign Up");
}

// SIGN UP
void ScreenR2(){
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	esat::DrawSetTextSize(22);
	esat::DrawText(100,50,"Name");
	esat::DrawText(100,105,"Surname");
	esat::DrawText(100,160,"Date of birth");
	esat::DrawText(100,215,"Province");
	esat::DrawText(100,270,"Country");
	esat::DrawText(100,325,"User");
	esat::DrawText(100,380,"Password");
	esat::DrawText(100,435,"E-mail");
	esat::DrawText(100,490,"Credits");
	esat::DrawSetTextSize(17);
	
	int y=0;
	for(int i=0;i<9;i++){
		if(DetectMouseQuad(100,10+y,580,50) && i<8){
			esat::DrawSetStrokeColor(200,0,200);
			esat::DrawSetFillColor(200,0,200);
			if(esat::MouseButtonDown(0)){
				quad_writting=i;
			}	
		}
		else{
			esat::DrawSetStrokeColor(255,255,255);
			esat::DrawSetFillColor(255,255,255);
		} 
		Circle(g_circle,80,35+y,5,5);
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter))quad_writting=20;
		if(quad_writting==i)esat::DrawSetStrokeColor(200,0,200);
		else esat::DrawSetStrokeColor(255,255,255);	
		Quad(280,10+y,400,50);
		y+=55;
	}	
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	SecretPassword();
	switch(quad_writting){
		case 0: WriteWord(user->name);break;
		case 1: WriteWord(user->surname);break;
		case 2: WriteWord(user->birthday);break;
		case 3: WriteWord(user->province);break;
		case 4: WriteWord(user->country);break;
		case 5: WriteWord(user->username);break;
		case 6: WriteWord(user->password);break;
		case 7: WriteWord(user->mail);break;
	}
	user->credits="10";
	esat::DrawText(300,50,user->name);esat::DrawText(300,105,user->surname);
	esat::DrawText(300,160,user->birthday);esat::DrawText(300,215,user->province);
	esat::DrawText(300,270,user->country);esat::DrawText(300,325,user->username);
	esat::DrawText(300,435,user->mail);
	esat::DrawText(300,490,user->credits);
	if(DetectMouseQuad(690,355,50,30) && esat::MouseButtonDown(0)){
		if(secret_password==true)secret_password=false;
		else secret_password=true;
	}
	if(secret_password==true){esat::DrawSetTextSize(17);esat::DrawText(300,380,user->password);esat::DrawText(700,380,"See");}
	else {esat::DrawSetTextSize(22);esat::DrawText(300,380,user->secret_password); esat::DrawText(700,380,"See");}
	Quad(690,355,50,30);
	
	esat::DrawSetTextSize(40);
	if(DetectMouseQuad(180,490,200,105)){
		esat::DrawSetFillColor(200,0,200);
		// AÑADO USER A LA LISTA
		if(esat::MouseButtonDown(0) && CompleteSignUp()==true){
			screen=20;quad_writting=20;
			FILE *pf;
			pf=fopen("base.txt","ab");
			fputs(user->username,pf);fputs("\n",pf);
			fputs(user->password,pf);fputs("\n",pf);
			fputs(user->name,pf);fputs("\n",pf);
			fputs(user->surname,pf);fputs("\n",pf);
			fputs(user->birthday,pf);fputs("\n",pf);
			fputs(user->province,pf);fputs("\n",pf);
			fputs(user->country,pf);fputs("\n",pf);
			
			fputs(user->mail,pf);fputs("\n",pf);
			fputs(user->credits,pf);fputs("\n",pf);
			fclose(pf);
		}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(200,560,"Sign Up");
	
	if(DetectMouseQuad(420,490,140,105)){
		esat::DrawSetFillColor(200,0,200);
		if(esat::MouseButtonDown(0)){screen=1;quad_writting=20;secret_password=false;}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(440,560,"Back");
}

// SIGN IN
void ScreenR3(){
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	esat::DrawSetTextSize(40);
	esat::DrawText(70,155,"User");
	esat::DrawText(70,315,"Password");
	int y=0;
	for(int i=9;i<11;i++){
		if(DetectMouseQuad(70,105+y,750,70)){
			esat::DrawSetStrokeColor(200,0,200);
			esat::DrawSetFillColor(200,0,200);
			if(esat::MouseButtonDown(0)){
				quad_writting=i;
			}	
		}
		else{
			esat::DrawSetStrokeColor(255,255,255);
			esat::DrawSetFillColor(255,255,255);
		} 
		Circle(g_circle,50,130+y,5,5);
		if(esat::IsSpecialKeyDown(esat::kSpecialKey_Enter))quad_writting=20;
		if(quad_writting==i)esat::DrawSetStrokeColor(200,0,200);
		else esat::DrawSetStrokeColor(255,255,255);	
		Quad(320,105+y,450,70);
		y+=160;
	}
	
	switch(quad_writting){
		case 9: WriteWord(user->username);break;
		case 10: WriteWord(user->password);break;
	}
	
	esat::DrawSetStrokeColor(255,255,255);
	esat::DrawSetFillColor(255,255,255);
	SecretPassword();
	if(DetectMouseQuad(690,355,50,30) && esat::MouseButtonDown(0)){
		if(secret_password==true)secret_password=false;
		else secret_password=true;
	}
	if(secret_password==true){esat::DrawSetTextSize(28);esat::DrawText(332,315,user->password);esat::DrawSetTextSize(17);esat::DrawText(700,380,"See");}
	else {esat::DrawSetTextSize(34);esat::DrawText(332,315,user->secret_password);esat::DrawSetTextSize(17);esat::DrawText(700,380,"See");}
	Quad(690,355,50,30);
	esat::DrawSetTextSize(28);
	esat::DrawText(332,155,user->username);

	esat::DrawSetTextSize(60);
	if(DetectMouseQuad(150,420,200,105)){
		esat::DrawSetFillColor(200,0,200);
		if(esat::MouseButtonDown(0) && CompleteSignIn()==true){screen=20;quad_writting=20;}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(170,505,"Login");
	if(DetectMouseQuad(420,420,200,105)){
		esat::DrawSetFillColor(200,0,200);
		if(esat::MouseButtonDown(0)){screen=1;quad_writting=20;secret_password=false;}
	}else{
		esat::DrawSetStrokeColor(255,255,255);
		esat::DrawSetFillColor(255,255,255);
	}
	esat::DrawText(440,505,"Back");	
	if(c_register==true){
		esat::DrawSetTextSize(50);
		esat::DrawSetStrokeColor(255,255,0);
		esat::DrawSetFillColor(255,255,0);
		esat::DrawText(100,80,"INCORRECT REGISTER");
		count_wrong_register++;
		if(count_wrong_register>=30){
			count_wrong_register=0;
			c_register=false;
		}
	}
}








