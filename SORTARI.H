#pragma once
#include "lista.h"
/*
   Tipul functie de comparare pentru 2 elemente
   returneaza 0 daca sunt egale, 1 daca o1>o2, -1 altfel
*/
typedef int(*FunctieComparare)(Car* o1, Car* o2);


void sort(List* lista, FunctieComparare cmpF);