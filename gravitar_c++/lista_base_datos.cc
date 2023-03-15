struct TRegister{
	char *name, *surname, *birthday, *province, *country,
	*username, *password, *mail, *credits;
	//TRegister *prox;
};

TRegister *first=NULL, *last=NULL;

void IniTRegister(TRegister *user){
	user=(TRegister*)calloc(1,sizeof(TRegister));
	user->name=(char*)calloc(20,sizeof(TRegister));
	user->surname=(char*)calloc(20,sizeof(TRegister));
	user->birthday=(char*)calloc(20,sizeof(TRegister));
	user->province=(char*)calloc(20,sizeof(TRegister));
	user->country=(char*)calloc(20,sizeof(TRegister));
	user->username=(char*)calloc(20,sizeof(TRegister));
	user->password=(char*)calloc(20,sizeof(TRegister));
	user->mail=(char*)calloc(20,sizeof(TRegister));
	user->credits=(char*)calloc(20,sizeof(TRegister));
}

void InsertarNodo(TNodo *lista, int contenido){
	IniTRegister(lista);
	if(first==NULL){
		// Se asigna lista a primero y a ultimo para saber cuando vuelvo
		first=lista;
		lista->dato=contenido;
		first->prox=first;
		last=first;
		first->ant=NULL;
	}else{
		// si no es 1er nodo ultimo prox que seria lista anterior apunta a lista nueva
		lista->ant=ultimo;
		last->prox=lista;
		// prox de lista apunta al 1o para circular
		lista->prox=first;
		lista->dato=contenido;
		//actualizar ultimo a ultima lista
		last=lista;
		lista=first;
		lista->ant=last;
	}	
}

void MostrarLista(TNodo *lista){
	lista=first;
	if(first==NULL){
		do{
			printf("LISTA VACIA");
		}while(lista!=first);
	}else{
		// con do se hace una vez y se recorre hasta que vuelva
		do{
			printf("%d\t",lista->dato);
			printf("%s\n",lista->name);
			lista=lista->prox;
		}while(lista!=first);
	}
}
/*
int main(){
	TNodo *lista1=NULL;
	
	InsertarNodo(lista1,0);InsertarNodo(lista1,1);InsertarNodo(lista1,2);
	MostrarLista(lista1);
	
	return 0;
}*/