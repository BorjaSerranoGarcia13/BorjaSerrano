struct TCoord{
	float x,y;
};

struct TNodo{
	TCoord position;
	esat::Vec2 direction;
	int count;
	bool alive;
	TNodo *prox;	
};

TNodo *primero=NULL,*ultimo=NULL;
esat::Vec2 d, change_direction={0,-1}, last_direction={0,0};

TNodo *InsertarNodo(float xx, float yy){
	TNodo *lista=(TNodo*)malloc(1+sizeof(TNodo));
	
	lista->prox=NULL;
	
	if(primero==NULL){
		primero=lista;
		ultimo=primero;
		lista->position.x=xx;
		lista->position.y=yy;
		lista->alive=true;
		lista->count=0;
		lista->direction.x=d.x;
		lista->direction.y=d.y;
	}else{
		ultimo->prox=lista;
		ultimo=lista;
		lista->position.x=xx;
		lista->position.y=yy;	
		lista->alive=true;
		lista->count=0;
		lista->direction.x=d.x;
		lista->direction.y=d.y;
	}
	return lista;
}

void VaciarLista(TNodo *lista){
	if(lista==primero){
		if(lista->prox!=NULL)primero=lista->prox;
		else primero=NULL;			
	}else if(lista!=ultimo){
		TNodo *anterior=(TNodo*)malloc(1+sizeof(TNodo)),
		*siguiente=(TNodo*)malloc(1+sizeof(TNodo)),
		*apuntador=(TNodo*)malloc(1+sizeof(TNodo));
		
		apuntador=primero;
		while(apuntador->prox!=lista){
			apuntador=apuntador->prox;
		}
		anterior=apuntador;
		siguiente=lista->prox;
		anterior->prox=siguiente;
	}else{
		TNodo *anterior=(TNodo*)malloc(1+sizeof(TNodo)),
		*apuntador=(TNodo*)malloc(1+sizeof(TNodo));
		
		apuntador=primero;
		while(apuntador->prox!=lista){
			apuntador=apuntador->prox;
		}
		anterior=apuntador;
		anterior->prox=NULL;
		ultimo=anterior;
	}
	free(lista);
}