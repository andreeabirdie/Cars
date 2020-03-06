#include "car.h"
#include <string.h>
#include <assert.h>
#include<stdlib.h>

Car* createCar(int nrInmatriculare, char* model, char* categorie) {
	/*Creeaza o masina
	in:nrInmatriculare - int
	model - sir de caractere 
	categorie- sir de caractere 
	out:newCar -masina creeata
	pre:
	*/
	Car* newCar=malloc(sizeof(Car));
	int nrC;
	
	newCar->nrInmatriculare = nrInmatriculare;

	nrC = strlen(categorie)+1;
	newCar->categorie = malloc(sizeof(char)*nrC);
	strcpy_s(newCar->categorie,nrC, categorie);

	nrC = strlen(model)+1;
	newCar->model = malloc(sizeof(char)*nrC);
	strcpy_s(newCar->model,nrC, model);

	newCar->disponibilitate = 1;

	return newCar;
}
void carAvailable(Car* car) {
	/*Modifica disponibilitatea unui element din lista
	in:lista- List*
		index - int
	out:
	pre:
	*/
	if (car->disponibilitate == 1)
		car->disponibilitate = 0;
	else
		car->disponibilitate = 1;
}
void destroyCar(Car* car) {
	/* Reseteaza o masina
	in:car - Car*
	out:
	pre:
	*/
	free(car->model);
	free(car->categorie);
	car->model = NULL;
	car->categorie = NULL;
	car->nrInmatriculare = -1;
	car->disponibilitate = 0;
	free(car);
}
Car* copyCar(Car * car) {
	/*
	Functia returneaza un element de tip car cu aceleasi atribute ca a celui primit ca paramentru
	*/
	return createCar(car->nrInmatriculare,car->model,car->categorie);
}
