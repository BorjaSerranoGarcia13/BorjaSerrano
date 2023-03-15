

struct TNodo{
	int dato;
	char *name;
	TNodo *prox,*ant;
};

enum posicion{
	anterior,
	actual
};

TNodo *primero=NULL;
TNodo *ultimo=NULL;

void InsertarNodo(TNodo *lista, int contenido){
	lista=(TNodo*)malloc(1+sizeof(TNodo));
	lista->name=(char*)malloc(40+sizeof(char));
	if(primero==NULL){
		// Se asigna lista a primero y a ultimo para saber cuando vuelvo
		primero=lista;
		lista->dato=contenido;
		primero->prox=primero;
		ultimo=primero;
		primero->ant=NULL;
	}else{
		// si no es 1er nodo ultimo prox que seria lista anterior apunta a lista nueva
		lista->ant=ultimo;
		ultimo->prox=lista;
		// prox de lista apunta al 1o para circular
		lista->prox=primero;
		lista->dato=contenido;
		//actualizar ultimo a ultima lista
		ultimo=lista;
		lista=primero;
		lista->ant=ultimo;
	}	
}

void MostrarLista(TNodo *lista){
	lista=primero;
	if(primero==NULL){
		do{
			printf("LISTA VACIA");
		}while(lista!=primero);
	}else{
		// con do se hace una vez y se recorre hasta que vuelva
		do{
			printf("%d\t",lista->dato);
			printf("%s\n",lista->name);
			lista=lista->prox;
		}while(lista!=primero);
	}
}
/*
int main(){
	TNodo *lista1=NULL;
	
	InsertarNodo(lista1,0);InsertarNodo(lista1,1);InsertarNodo(lista1,2);
	MostrarLista(lista1);
	
	return 0;
}*/