#pragma once
#include"lista.h"

typedef struct {
	List* carList;
	List* undoList;
}CarStore;

CarStore createCarStore();
void destroyCarStore(CarStore* store);

int addCar(CarStore* store, int nr, char* model, char* categorie);
int updateCar(CarStore* store, int nr, char* model, char* categorie);
int rentCar(CarStore* store, int nrInmatriculare);
int returnCar(CarStore* store, int nrInmatriculare);
int undo(CarStore* store);

int compareModelAsc(Car * car1, Car * car2);


int compareModelDes(Car* car1, Car* car2);
int compareCategorieAsc(Car* car1, Car* car2);
int compareCategorieDes(Car* car1, Car* car2);
List* sortByModelAsc(List* lista);
List* sortByModelDes(List* lista);
List* sortByCategorieAsc(List* lista);
List* sortByCategorieDes(List* lista);

List* findModel(List * lista, char * model);

List* findCategorie(List * lista, char * categorie);
List* findDisponibile(List * lista);
List* getAll(CarStore* store);