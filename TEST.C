#include"car.h"
#include"console.h"
#include"lista.h"
#include"serviceCar.h"
#include<assert.h>
#include"sortari.h"
#include<string.h>
#include<stdio.h>



void test_listInit() {
	List* lista = listInit(destroyCar);
	assert(lista->size == 10);
	assert(lista->total == 0);
	listFree(lista);
}
void test_listSize() {
	List* lista = listInit(destroyCar);
	lista->total = 2;
	assert(listSize(lista) == 2);
	lista->total = 4;
	assert(listSize(lista) == 4);
	lista->total = 0;
	listFree(lista);

}
void test_listAdd() {
	Car* car = createCar(2, "da12", "da12");
	Car* cCar;
	
	List* lista = listInit(destroyCar);
	listAdd(lista, car);
	
	assert(listSize(lista) == 1);
	cCar = listGetElement(lista,0);
	assert(strcmp(cCar->categorie, car->categorie)==0);
	assert(strcmp(cCar->model, car->model)==0);
	assert(cCar->disponibilitate == car->disponibilitate);
	assert(cCar->nrInmatriculare == car->nrInmatriculare);
	listFree(lista);
	

	
}
void test_addCar() {
	
	CarStore store = createCarStore();
	assert(1==addCar(&store, 1, "da1", "da1"));
	assert(0 == addCar(&store, 1, "da1", "d1a"));
	destroyCarStore(&store);
	
}
void test_updateCar() {
	Car* car = createCar(1, "da1", "da1");
	CarStore store = createCarStore();
	addCar(&store, 1, "da1", "da1");
	assert(1 == updateCar(&store, 1, "223", "d23a"));
	assert(0 == updateCar(&store, 2, "d1a", "d1a"));
	destroyCarStore(&store);
	destroyCar(car);
}
void test_rentCar() {
	Car* car = createCar(1, "da1", "da1");
	CarStore store = createCarStore();
	addCar(&store, 1, "da1", "da1");
	assert(1 == rentCar(&store, 1));
	assert(0 == rentCar(&store, 2));
	assert(0 == rentCar(&store, 1));
	destroyCarStore(&store);
	destroyCar(car);
	
}
void test_returnCar() {
	
	
	CarStore store = createCarStore();
	addCar(&store, 1, "da1", "da1");
	rentCar(&store, 1);
	assert(1 == returnCar(&store, 1));
	assert(0 == returnCar(&store, 2));
	assert(0 == returnCar(&store, 1));
	destroyCarStore(&store);
	
	
}
void test_createCar() {
	Car* car = createCar(1, "da1", "da1");
	assert(strcmp(car->categorie,"da1") == 0);
	assert(strcmp(car->model, "da1") == 0);
	assert(car->nrInmatriculare == 1);
	assert(car->disponibilitate == 1);
	destroyCar(car);
}
void test_listSet() {
	

	Car* car1 = createCar(1, "da1", "da1");
	CarStore store = createCarStore();
	addCar(&store, 1, "da122", "da121");
	Car* cCar2 = listGetElement(store.carList, 0);
	listSet(store.carList,0, car1);
	Car* cCar;
	
	
	cCar = listGetElement(store.carList, 0);
	assert(strcmp(cCar->categorie, car1->categorie) == 0);
	assert(strcmp(cCar->model, car1->model) == 0);
	assert(cCar->disponibilitate == car1->disponibilitate);
	assert(cCar->nrInmatriculare == car1->nrInmatriculare);
	destroyCarStore(&store);
	destroyCar(cCar2);
	
}
void test_GetElement() {
	Car* car = createCar(1, "da1", "da1");
	List* lista = listInit(destroyCar);
	listAdd(lista, car);
	assert(listSize(lista) == 1);
	Car* cCar;

	cCar = listGetElement(lista, 0);
	assert(strcmp(cCar->categorie, car->categorie) == 0);
	assert(strcmp(cCar->model, car->model) == 0);
	assert(cCar->disponibilitate == car->disponibilitate);
	assert(cCar->nrInmatriculare == car->nrInmatriculare);
	listFree(lista);
	
}
void test_destroyCar() {
	Car* car = createCar(1, "da1", "da1");
	destroyCar(car);
	
	
}
void test_listFree() {
	
	List* lista = listInit(destroyCar);
	
	listFree(lista);
	
	
}
void test_listCopy() {
	
	CarStore store = createCarStore();
	List* lista1;
	addCar(&store, 1, "da1", "da1");
	lista1 = listCopy(store.carList,copyCar);
	Car* cCar;
	Car* cCar1;

	cCar = listGetElement(store.carList, 0);
	cCar1= listGetElement(lista1, 0);
	assert(strcmp(cCar->categorie, cCar1->categorie) == 0);
	assert(strcmp(cCar->model, cCar1->categorie) == 0);
	assert(cCar->disponibilitate == cCar1->disponibilitate);
	assert(cCar->nrInmatriculare == cCar1->nrInmatriculare);
	
	
	listFree(lista1);
	destroyCarStore(&store);

}
void test_sort() {
	CarStore store = createCarStore();
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "a", "c");
	addCar(&store, 3, "b", "a");
	List* lista1 = listCopy(store.carList,copyCar);

	sort(lista1, compareModelAsc);
	Car* cCar;
	Car* cCar1;

	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->model, "b") == 0);
	listFree(lista1);
	lista1 = listCopy(store.carList,copyCar);
	sort(lista1, compareCategorieAsc);
	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->categorie, "b") == 0);
	assert(strcmp(cCar->categorie, "a") == 0);
	listFree(lista1);
	destroyCarStore(&store);
}
void test_sortBy() {
	CarStore store = createCarStore();
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "a", "c");
	addCar(&store, 3, "b", "a");
	List* lista1 = sortByModelAsc(store.carList);
	Car* cCar;
	Car* cCar1;

	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->model, "b") == 0);
	listFree(lista1);
	lista1 = sortByModelDes(store.carList);
	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->model, "b") == 0);
	listFree(lista1);
	lista1 = sortByCategorieAsc(store.carList);
	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->categorie, "b") == 0);
	assert(strcmp(cCar->categorie, "a") == 0);
	listFree(lista1);
	lista1 = sortByCategorieDes(store.carList);
	cCar = listGetElement(lista1, 0);
	cCar1 = listGetElement(lista1, 1);
	assert(strcmp(cCar1->categorie, "b") == 0);
	assert(strcmp(cCar->categorie, "c") == 0);
	listFree(lista1);
	destroyCarStore(&store);
}
void test_find() {
	CarStore store = createCarStore();
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "a", "c");
	addCar(&store, 3, "b", "a");
	char a[] = "a";
	List* lista1 = findModel(store.carList, a);
	Car* cCar;
	

	cCar = listGetElement(lista1, 0);

	assert(cCar->nrInmatriculare == 2);
	listFree(lista1);
	char b[] = "c";
	lista1 = findCategorie(store.carList, b);
	cCar = listGetElement(lista1, 0);
	assert(cCar->nrInmatriculare == 2);
	listFree(lista1);
	lista1 = findDisponibile(store.carList);
	assert(listSize(lista1) == 3);

	listFree(lista1);
	destroyCarStore(&store);
	
}
void test_resize() {

	CarStore store = createCarStore();
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "c", "b");
	addCar(&store, 3, "c", "b");
	addCar(&store, 4, "c", "b");
	addCar(&store, 5, "c", "b");
	addCar(&store, 6, "c", "b");
	addCar(&store, 7, "c", "b");
	addCar(&store, 8, "c", "b");
	addCar(&store, 9, "c", "b");
	addCar(&store, 10, "c", "b");
	addCar(&store, 11, "c", "b");
	addCar(&store, 12, "c", "b");
	listResize(store.carList, 30);
	assert(store.carList->size == 30);
	destroyCarStore(&store);
}
void test_carAvailable() {

	Car* car;
	car= createCar(1, "da", "nu");
	assert(car->disponibilitate == 1);
	carAvailable(car);
	assert(car->disponibilitate ==	0);
	destroyCar(car);
}


void test_undo() {
	CarStore store = createCarStore();
	assert(undo(&store) == 0);

	
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "c", "a");
	assert(undo(&store) == 1);

	//addCar(lista, 1, "c", "b", undoList);
	//assert(undo(undoList, lista) == 1);

	destroyCarStore(&store);
	
}

/*
void test_undoUpdate() {

	List* lista = listInit(destroyCar);
	List* undoList = listInit(listFree);

	addCar(lista, 1, "c", "b", undoList);
	updateCar(lista, 1, "a", "c", undoList);
	Car* car = listGetElement(lista, 0);
	assert(strcmp(car->model, "a") == 0);
	assert(strcmp(car->categorie, "b") == 0);
	undo(lista, undoList);
	assert(strcmp(car->model, "b") == 0);
	assert(strcmp(car->categorie, "c") == 0);

	listFree(lista);
	listFree(undoList);
}
*/

void testRun() {
	test_listInit(destroyCar);
	test_listSize();
	test_listAdd();
	test_addCar();
	test_updateCar();
	test_rentCar();
	test_returnCar();
	test_createCar();
	test_listSet();
	test_GetElement();
	test_destroyCar();
	test_listFree();
	test_listCopy();
	test_sort();
	test_sortBy();
	test_find();
	test_resize();
	test_carAvailable();
	test_undo();
	//test_undoUpdate();
}
