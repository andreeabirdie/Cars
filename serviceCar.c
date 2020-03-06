#include <stdio.h>
#include"sortari.h"
#include "serviceCar.h"
#include<string.h>

CarStore createCarStore()
{
	CarStore rez;
	rez.carList = listInit(destroyCar);
	rez.undoList = listInit(listFree);
	return rez;
}

void destroyCarStore(CarStore * store)
{
	listFree(store->carList);
	listFree(store->undoList);
}

int addCar(CarStore* store, int nr, char* model, char* categorie) {
	/*Functia adauga o masina in lista de masini
	in:	lista- de tip lista, 
		nr- intreg(numarul de inmatriculare al masinii),
		model - sir de caractere(modelul masinii),
		categorie - sir de caractere (categoria masinii)
	out:1 daca masina a fost adaugata cu succes, 0 altfel
	*/
	int i;
	Car* newCar = createCar(nr, model, categorie);
	//List* oldList = listCopy(lista,copyCar);
	if (listSize(store->carList) != 0) {
		for (i = 0; i < listSize(store->carList); i++) {
			Car* car = listGetElement(store->carList, i);
			if (newCar->nrInmatriculare == car->nrInmatriculare) {
				destroyCar(newCar);
		
				return 0;
			}

		}
		listAdd(store->undoList, listCopy(store->carList, copyCar));
		listAdd(store->carList, newCar);
		return 1;
	}
	listAdd(store->undoList, listCopy(store->carList, copyCar));
	listAdd(store->carList, newCar);
	return 1;
	

}

int updateCar(CarStore* store, int nr, char* model, char* categorie) {
	/*Functia actualizeaza o masina selectata dupa numarul de inmatriculare
	in:	lista- de tip lista,
		nr- intreg(numarul de inmatriculare al masinii care trebuie actualizate),
		model - sir de caractere(modelul masinii actualizat),
		categorie - sir de caractere (categoria masinii actualizat)
	out:1 daca masina a fost aactualizata cu succes, 0 altfel
	pre:
	*/
	int i;
	Car* newCar = createCar(nr, model, categorie);
	List* oldList = listCopy(store->carList, copyCar);
		for (i = 0; i < listSize(store->carList); i++) {
			Car* car = listGetElement(store->carList, i);
			if (newCar->nrInmatriculare == car->nrInmatriculare) {
				listSet(store->carList,i,newCar);
				listAdd(store->undoList, oldList);
				destroyCar(car);
				return 1;
			}

		}
		destroyCar(newCar);
		return 0;

}

int rentCar(CarStore* store, int nrInmatriculare) {
	/*Functia inchiriaza o masina daca este disponibila
	in:	lista- de tip lista,
		nrInmatriculare- intreg(numarul de inmatriculare al masinii),
	out:1 daca masina a fost inchiriata cu succes, 0 altfel
	pre:
	*/
	int i;
	Car* car;
	List* oldList = listCopy(store->carList, copyCar);
	for (i = 0; i < listSize(store->carList); i++) {
		car = listGetElement(store->carList, i);
		if (car->nrInmatriculare == nrInmatriculare) {
			if (car->disponibilitate == 1) {
				carAvailable(car);
				listAdd(store->undoList, oldList);
				return 1;
			}
		}
	}
	return 0;
}

int returnCar(CarStore* store, int nrInmatriculare) {
	/*Functia returneaza o masina daca este inchiriata
	in:	lista- de tip lista,
		nrInmatriculare- intreg(numarul de inmatriculare al masinii),
	out:1 daca masina a fost returnata cu succes, 0 altfel
	pre:
	*/
	int i;
	Car* car;
	List* oldList = listCopy(store->carList, copyCar);
	for (i = 0; i < listSize(store->carList); i++) {
		car = listGetElement(store->carList, i);
		if (car->nrInmatriculare == nrInmatriculare) {
			if (car->disponibilitate == 0) {
				carAvailable(car);
				listAdd(store->undoList, oldList);
				return 1;
			}
		}
	}
	return 0;
}

int undo(CarStore* store) {
	//printf("%d ", listSize(lista));
	//printf("%d",listSize(undoList));
	if (listSize(store->undoList) == 0) {
		return 0;
	}
	List* oldList = removeLast(store->undoList);
	listFree(store->carList);
	store->carList = oldList;
	return 1;
}


int compareModelAsc(Car* car1, Car* car2) {
	/*Functia compara modelul a doua masini 
	*/
	return strcmp(car1->model, car2->model);

}

int compareModelDes(Car* car1, Car* car2) {
	/*Functia compara modelul a doua masini 
	*/
	return -1*strcmp(car1->model, car2->model);

}

int compareCategorieAsc(Car* car1, Car* car2) {
	/*Functia compara categoriile a doua masini 
	*/
	return strcmp(car1->categorie, car2->categorie);
}

int compareCategorieDes(Car* car1, Car* car2) {
	/*Functia compara categoriile a doua masini 
	*/
	return -1*strcmp(car1->categorie, car2->categorie);
}

List* sortByModelAsc(List* lista) {
	/*Functia returneaza o lista cu masini sortata ascendent dupa model
	in:	lista- de tip lista,

	out:listSorted -lista sortata ascendent dupa model
	pre:
	*/
	List* listSorted = listCopy(lista,copyCar);
	sort(listSorted, compareModelAsc);
	return listSorted;
}

List* sortByModelDes(List* lista) {
	/*Functia returneaza o lista cu masini sortata descendent dupa model
	in:	lista- de tip lista,

	out:listSorted -lista sortata descendent dupa model
	pre:
	*/
	List* listSorted = listCopy(lista,copyCar);
	sort(listSorted, compareModelDes);
	return listSorted;
}

List* sortByCategorieAsc(List* lista) {
	/*Functia returneaza o lista cu masini sortata ascendent dupa categorie
	in:	lista- de tip lista,

	out:listSorted -lista sortata ascendent dupa categorie
	pre:
	*/
	List* listSorted = listCopy(lista,copyCar);
	
	sort(listSorted, compareCategorieAsc);
	return listSorted;
}

List* sortByCategorieDes(List* lista) {
	/*Functia returneaza o lista cu masini sortata descendent dupa categorie
	in:	lista- de tip lista,
		
	out:listSorted -lista sortata descendent dupa categorie
	pre:
	*/
	List* listSorted = listCopy(lista,copyCar);

	sort(listSorted, compareCategorieDes);
	return listSorted;
}

List* findModel(List* lista, char* model) {
	/*Functia returneaza o lista cu masini care au acelasi model ca si cel specificat
	in:	lista- de tip lista,
	model- char*
	out:selected -lista care contine doar masiniile cu modelul selectat
	*/
	List* selected = listInit(destroyCar); int i; Car *car;
	for (i = 0; i < listSize(lista); i++) {
		car = listGetElement(lista, i);
		if (strcmp(car->model,model)==0) {
			listAdd(selected, copyCar(car));
		}
	}
	return selected;
}

List* findCategorie(List* lista, char* categorie) {
	/*Functia returneaza o lista cu masini care au aceasi categorie ca si cea specificata
	in:	lista- de tip lista,
	categorie- char* 	
	out:selected -lista care contine doar masiniile cu categoria selectata
	*/
	List* selected = listInit(destroyCar); int i; Car* car;
	for (i = 0; i < listSize(lista); i++) {
		car = listGetElement(lista, i);
		if (strcmp(car->categorie, categorie) == 0) {
			listAdd(selected, copyCar(car));
		}
	}
	return selected;
}

List* findDisponibile(List* lista) {
	/*Functia returneaza o lista cu masini care au acelasi nr matricol ca si cel specificat
	in:	lista- de tip lista,
	categorie- char*
	out:selected -lista care contine doar masiniile cu categoria selectata
	*/
	List* selected = listInit(destroyCar); int i; Car* car;
	for (i = 0; i < listSize(lista); i++) {
		car = listGetElement(lista, i);
		if (car->disponibilitate == 1) {
			listAdd(selected, copyCar(car));
		}
	}
	return selected;
}

