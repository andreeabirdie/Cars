#include "sortari.h"


/**
* Sorteaza in place
* cmpf - relatia dupa care se sorteaza
*/
void sort(List* lista, FunctieComparare cmpF) {
	int i, j;
	for (i = 0; i < listSize(lista)-1; i++) {
		for (j = i + 1; j < listSize(lista); j++) {
			Telem obj1 = listGetElement(lista, i);
			Telem obj2 = listGetElement(lista, j);
			
			if (cmpF(obj1, obj2) > 0) {
				
				lista->elements[i] = obj2;
				lista->elements[j] = obj1;
				
			}
		}
	}
}