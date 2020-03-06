#include<stdio.h>
#include"console.h"
#include"car.h"
#include"lista.h"
#include"serviceCar.h"
#include<stdlib.h>

void printMenu() {
	/*Functia  afiseaza meniul principal al aplicatiei
	in:
	out:
	pre:
	*/
	printf("\n1) adaugare de masini\n2) actualizare masina existenta\n3) inchiriere masina/returnare masina\n4) afiseaza masini\n5) sorteaza masini\n6) vezi masini\n7) Undo\n8) Exit\n\nIntroduceti comanda>> ");
}
int inchiriere(CarStore* store) {
	/*Functia citeste de la tastatura un numar de inmatriculare si apeleaza functia de inchiriere
	in:carList - list*
	out:1 daca masina a fost inchiriata 0 altfef
	pre:datele introduse de la tastatura trebuie sa fie valide
	*/
	int nrInmatriculare;
	printf("\nIntroduceti nr de inamtriculare:");
	scanf_s("%d", &nrInmatriculare);
	return rentCar(store, nrInmatriculare);
}
int returnare(CarStore* store) {
	/*Functia citeste de la tastatura un numar de inmatriculare si apeleaza functia de returnare
	in:carList - list*
	out:1 daca masina a fost returnata 0 altfef
	pre:datele introduse de la tastatura trebuie sa fie valide
	*/
	int nrInmatriculare;
	printf("\nIntroduceti nr de inamtriculare:");
	scanf_s("%d", &nrInmatriculare);
	return returnCar(store, nrInmatriculare);
}
void readCar(CarStore* store) {
	/*Functia citeste caracteristicile unei masini
	in:lista - de tip List*
	out:
	pre:datele introduse de la tastatura trebuie sa fie valide
	*/
	printf("\nNumar de inmatriculare:");
	int nr;
	scanf("%d", &nr);
	printf("\nModel:");
	char model[30];
	scanf("%s", model);
	printf("\nCategorie:");
	char categorie[30];
	scanf("%s", categorie);
	if(addCar(store,nr,model,categorie))
		printf("masina inregistrata.\n");
	else
		printf("masina este deja in sistem.\n");
}

void updCar(CarStore* store) {
	/*Functia citeste numarul de inmatriculare si caracteristicile actualizate ale unei masini
	in:lista - de tip List*
	out:
	pre:datele introduse de la tastatura trebuie sa fie valide
	*/
	printf("\nNumar de inmatriculare:");
	int nr;
	scanf("%d", &nr);
	printf("\nModel nou:");
	char model[30];
	scanf("%s", model);
	printf("\nCategorie noua:");
	char categorie[30];
	scanf("%s", categorie);
	if (updateCar(store, nr, model, categorie))
		printf("masina actualizata.\n");
	else
		printf("masina nu este in sistem.\n");
}

void printAllCars(List* lista) {
	/*Functia afiseaza toate masinile din lista
	in:lista - list*
	out:
	pre:
	*/

	int i;
	Car* car;
	for (i = 0; i < listSize(lista); i++) {
		car = listGetElement(lista, i);
		printf("\nNr inmatriculare: %d	Model: %s	Categorie: %s\n",car->nrInmatriculare,car->model,car->categorie);
	}
}
void printUndoList(List* undoList) {
	for (int j = 0; j < listSize(undoList); j++) {
		List* list = listGetElement(undoList, j);
		printAllCars(list);
		printf("\n");
	}
}

void printSubMenu1() {
	/*Functia afiseaza submeniul sectiunii inchiriere/returnare masini
	in:
	out:
	pre:
	*/
	printf("\n1) inchiriere\n2) returnare\nIntroduceti comanda>> ");
}
void printSubMenu2() {
	/*Functia afiseaza submeniul sectiunii vezi masini
	in:
	out:
	pre:
	*/
	printf("\n1) model\n2) categorie\n3) masini disponibile\nIntroduceti comanda>> ");
}
void printSubMenu3() {
	/*Functia afiseaza submeniul sectiunii sorteaza masini
	in:
	out:
	pre:
	*/
	printf("\n1) ascendent model\n2) descendent model\n3) ascendent categorie\n4) descendent categorie\nIntroduceti comanda>> ");
}

void run() {
	/*Functia citeste si interpreteaza comenzi
	in:
	out:
	pre:datele introduse de la tastatura trebuie sa fie valide
	*/
	//system("clear");
	int comanda, ruleaza = 1;
	CarStore store = createCarStore();

	List* sorted;List* selected;
	addCar(&store, 1, "c", "b");
	addCar(&store, 2, "a", "c");
	addCar(&store, 3, "b", "a");
	while (ruleaza) {
		//printUndoList(undoList);
		printMenu();
		
		scanf_s("%d", &comanda);
		switch (comanda) {
		case 1:
		{readCar(&store);
		break; }
		case 2:
		{updCar(&store);
			break; }
		case 3:
		{
			printSubMenu1();
			scanf_s("%d", &comanda);

			if (comanda == 1) {
				
				if (inchiriere(&store) )
					printf("\nMasina a fost inchiriata!");
		
				else 
					printf("\nMasina nu se poate inchiria!");
			}
			else {
				
				if (returnare(&store)) 
					printf("\nMasina a fost returnata!");

				else 
					printf("\nMasina nu se poate returna!");
			}
			break;
		}		
		case 4:
		{	
			printAllCars(store.carList);
			break;
		}
		case 8:
		{

			ruleaza = 0;
			destroyCarStore(&store);
			break;
		}
		case 5:
		{	
			printSubMenu3();
			scanf_s("%d", &comanda);

			if (comanda == 1)
			{
				sorted = sortByModelAsc(store.carList);
				printAllCars(sorted);
				listFree(sorted);
			}
			if (comanda == 2)
			{
				sorted = sortByModelDes(store.carList);
				printAllCars(sorted);
				listFree(sorted);
			}
				
			if (comanda == 3)
			{
				sorted = sortByCategorieAsc(store.carList);
				printAllCars(sorted);
				listFree(sorted);
			}
				
			if (comanda == 4)
			{
				sorted = sortByCategorieDes(store.carList);
				printAllCars(sorted);
				listFree(sorted);
			}
			break;
		}
		case 6:
		{
			printSubMenu2();
			scanf("%d", &comanda);
			if (comanda == 1)
			{	
				printf("\nModel:");
				char model[30];
				scanf("%s", model);
				
				selected = findModel(store.carList,model);
				printAllCars(selected);
				listFree(selected);
			}
			if (comanda == 2)
			{
				printf("\nCategorie:");
				char categorie[30];
				scanf("%s", categorie);
				selected = findCategorie(store.carList,categorie);
				printAllCars(selected);
				listFree(selected);

			}

			if (comanda == 3)
			{

				selected = findDisponibile(store.carList);
				printAllCars(selected);
				listFree(selected);

			}
			
			break;
		}
		case 7:
		{	
			if (undo(&store) == 0) printf("\n Lista de undo este goala\n");
			else printf("\nUndo a fost realizat cu succes!\n");
			break;
		}
		default:
			printf("comanda invalida!\n");
		}
	}
}