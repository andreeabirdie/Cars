#pragma once
#include"car.h"
typedef void* Telem;
/*
function type for releasing an element
*/
typedef void(*DestroyFct) (Telem);

/*
  function type for copy an element
*/
typedef Telem (*CopyFct) (Telem);

typedef struct {
	int total;
	Telem* elements;
	int size;
	DestroyFct dfnc;
}List;

List* listInit(DestroyFct f);

int listSize(List *lista);

void listResize(List *lista, int size);

int listAdd(List *lista, Telem item);

int listSet(List *lista,int nr,  Telem item); 

Telem listGetElement(List *v, int index);

Telem removeLast(List* lista);

List* listCopy(List * lista, CopyFct copyFct);

void listFree(List *v);