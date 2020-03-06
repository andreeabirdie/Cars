#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


List * listInit(DestroyFct f) {
	/*Creeaza o lista noua
	in:
	out:list- List lista creata
	pre:
	*/
	List *list=malloc(sizeof(List));
	list->total = 0;
	list->size = 10;
	list->dfnc = f;
	list->elements = malloc(sizeof(Telem) * list->size);
	return list;
}



int listSize(List *list){
	/* returneaza numarul de elemente din lista
	in:lista- List* 
	out:list->total - numarul de elemente din lista
	pre:
	*/
	return list->total;
}

 void listResize(List *list, int size){
	/*redimenzioneaza lista primita ca parametru 
	in:lista- List*
		size- intreg
	out:list'- lista redimensionata
	pre:
	*/
	Telem* nElems = malloc(sizeof(Telem)*size);

	for (int i = 0; i < list->total; i++) {
		nElems[i] = list->elements[i];}
	//dealocate old vector
	free(list->elements);
	list->elements = nElems;
	list->size = size;
	

}

int listAdd(List *lista, Telem item){
	/*adauga un element in lista
	in:lista- List*
		item- Telem
	out:1 daca s-a adaugat cu succes, 0 altfel
	pre:
	*/
	if (lista->total == lista->size - 1) {
		listResize(lista, lista->size *2);
	}
	
				
	lista->elements[lista->total] = item;
	lista->total++;
	
	return 1;
}

int listSet(List *lista, int i,Telem item){
	/*actualizeaza un element din lista
	in:lista- List*
		item- Telem
	out:1 daca s-a actualizat cu succes, 0 altfel
	pre:
	*/
	
	lista->elements[i] = item;
	return 1;
		
}

Telem listGetElement(List *lista, int index) {
	/*returneaza un element din liste
	in:lista- List*
		index- int
	out:elementul din lista cu indexul index
	pre:
	*/

	return lista->elements[index];
}



List* listCopy(List * lista,CopyFct copyFct) {
	/*Functia copiaza o lista primita ca parametru si returneaza noua lista
	*/
	List* newList =listInit(lista->dfnc);
	for (int i = 0; i < listSize(lista); i++) {//*
		Telem element = listGetElement(lista,i);
		listAdd(newList, copyFct(element));
		
	}
	return newList;
}

void listFree(List *lista){
	/*elibereaza memoria alocata listei
	in:lista- List*
	out:
	pre:
	*/
	int i;
	for (i = 0; i < lista->total; i++) {
		
		lista->dfnc(lista->elements[i]);
	}
	free(lista->elements);
	free(lista);
}

Telem removeLast(List* lista) {
	//printf("%d", lista->total);
	Telem result = lista->elements[lista->total - 1];
	lista->total -= 1;
	return result;
}