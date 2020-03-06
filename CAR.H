#pragma once

typedef struct {
	int nrInmatriculare;
	char* model;
	char* categorie;
	int disponibilitate;
}Car;

Car* createCar(int nrInmatriculare, char* model, char* categorie);
void carAvailable(Car * car);
void destroyCar(Car* car);

Car* copyCar(Car * car);
