#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


struct Biblioteca {
	char* nume;
	int nrCarti;
	int nrLocuri;
};

struct Biblioteca initializeazaBiblioteca(const char* nume, int nrCarti, int nrLocuri) {
	struct Biblioteca b;
	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.nrLocuri = nrLocuri;

	return b;
}

void afisareBiblioteca(struct Biblioteca b) {
	printf("Biblioteca %s are un nr de %d carti si %d locuri!\n", b.nume, b.nrCarti, b.nrLocuri);

}

struct Biblioteca citireTastaturaBiblioteca() {
	struct Biblioteca b;
	char nume[100];

	printf("Introduceti nume Biblioteca: ");
	scanf_s("%99s", nume, sizeof(nume));

	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);

	printf("Introduceti nr de carti din biblioteca: ");
	scanf_s("%d", &b.nrCarti);
	printf("Introduceti nr de locuri din biblioteca: ");
	scanf_s("%d", &b.nrLocuri);

	return b;
}

float mediaCartiPersoana(struct Biblioteca b) {
	// Convertem cel puțin unul dintre operanzi la tip float pentru a obține rezultatul corect
	return (float)b.nrCarti / b.nrLocuri;
}

void updateLocuri(struct Biblioteca* b, int nouNrLocuri) {
	b->nrLocuri = nouNrLocuri;
}


struct Biblioteca* creareVector(int nrBib) {
	return malloc(sizeof(struct Biblioteca) * nrBib);
}

void eliberareVector(struct Biblioteca* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		free(vector[i].nume);
	}
	free(vector);
}

void afisareVectorBiblioteci(struct Biblioteca* vector, int lungime) {
	for (int i = 0; i < lungime; i++) {
		afisareBiblioteca(vector[i]);
	}


}

struct Biblioteca* copiereVectCond(struct Biblioteca* vector, int lungime, int conditie) {
	struct Biblioteca* vectorNou = NULL;
	int lungimeNou = 0;
	for (int i = 0; i < lungime; i++) {
		if (conditie == 1 && vector[i].nrLocuri > 20) {
			vectorNou = realloc(vectorNou, sizeof(struct Biblioteca) * (lungimeNou + 1));
			vectorNou[lungimeNou++] = vector[i];
		}
		else if(conditie == 2 && vector[i].nrCarti > 40) {
			vectorNou = realloc(vectorNou, sizeof(struct Biblioteca) * (lungimeNou + 1));
			vectorNou[lungimeNou++] = vector[i];
		}
	}
	return vectorNou;
}


struct Biblioteca* concatenareVectori(struct Biblioteca* vector1,int lungime1, int lungime2, struct Biblioteca* vector2) {
	struct Biblioteca* vectorMare = malloc(sizeof(struct Biblioteca) * (lungime1 + lungime2));
	for (int i = 0; i < lungime1; i++) {
		vectorMare[i] = vector1[i];
	}
	for (int i = 0; i < lungime2; i++) {
		vectorMare[lungime1+i] = vector2[i];
	}
	return vectorMare;
}

void afisareVector(struct Biblioteca* vector, int lungime) {
	printf("Vectorul de biblioteci:\n");
	for (int i = 0; i < lungime; ++i) {
		afisareBiblioteca(vector[i]);
	}
}

struct Biblioteca* citireFisierBiblioteca(const char* numeFisier, int* nrBiblioteci) {
	FILE* fisier = fopen(numeFisier, "r");
	if (fisier == NULL) {
		printf("Nu s-a putut deschide fisierulPrim.");
		exit(EXIT_FAILURE);
	}

	struct Biblioteca* vectorBiblioteci = NULL;
	*nrBiblioteci = 0;

	char linie[100];
	while (fgets(linie, sizeof(linie), fisier)) {
		char* nume = strtok(linie, ",");
		int nrCarti = atoi(strtok(NULL, ","));
		int nrLocuri = atoi(strtok(NULL, ",\n"));

		vectorBiblioteci = realloc(vectorBiblioteci, (*nrBiblioteci + 1) * sizeof(struct Biblioteca));
		vectorBiblioteci[*nrBiblioteci] = initializeazaBiblioteca(nume, nrCarti, nrLocuri);
		(*nrBiblioteci)++;
	}

	fclose(fisier);
	return vectorBiblioteci;
}

void salvareBibliotecaInFisier(struct Biblioteca b, const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "a");
	if (fisier == NULL) {
		printf("Nu s-a putut deschide fisierulUnO.");
		exit(EXIT_FAILURE);
	}

	fprintf(fisier, "%s, %d, %d\n", b.nume, b.nrCarti, b.nrLocuri);
	fclose(fisier);
}

void salvareVectorBiblioteciInFisier(struct Biblioteca* vector, int lungime, const char* numeFisier) {
	FILE* fisier = fopen(numeFisier, "w");
	if (fisier == NULL) {
		printf("Nu s-a putut deschide fisierulSalvare.");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < lungime; i++) {
		fprintf(fisier, "%s, %d, %d\n", vector[i].nume, vector[i].nrCarti, vector[i].nrLocuri);
	}

	fclose(fisier);
}

void main() {
	//task1
	//struct Biblioteca b = initializeazaBiblioteca("Libris", 30, 40);
	/*struct Biblioteca b2=citireTastaturaBiblioteca();
	afisareBiblioteca(b);
	afisareBiblioteca(b2);

	float media = mediaCartiPersoana(b);
	printf("Media de carti per persoana: %.2f\n", media);

	int nouNrLocuri;
	printf("Introduceti noul numar de locuri: ");
	scanf_s("%d", &nouNrLocuri);

	updateLocuri(&b, nouNrLocuri);
	printf("Numarul de locuri actualizat: %d\n", b.nrLocuri);
	afisareBiblioteca(b);*/

	//task2
	//int lungimeVector = 5;
	//struct Biblioteca* vectorBiblioteci = creareVector(lungimeVector);
	//for (int i = 0; i < lungimeVector; i++) {
	//	printf("Introduceti date pentru biblioteca: %d\n", i);
	//	vectorBiblioteci[i] = citireTastaturaBiblioteca();
	//}
	//afisareVectorBiblioteci(vectorBiblioteci, lungimeVector);


	//struct Biblioteca* vectorIndeplinit1 = copiereVectCond(vectorBiblioteci, lungimeVector, 1);
	//int lungimeVectIndep1 = lungimeVector;
	//afisareVectorBiblioteci(vectorIndeplinit1, lungimeVectIndep1);
	//struct Biblioteca* vectorCond1 = copiereVectCond(vectorBiblioteci, lungimeVector, 1);
	//int lungimeVectorCond1 = lungimeVector;
	//afisareVector(vectorCond1, lungimeVectorCond1);

	//// Mutarea obiectelor care îndeplinesc o altă condiție într-un nou vector
	//struct Biblioteca* vectorCond2 = copiereVectCond(vectorBiblioteci, lungimeVector, 2);
	//int lungimeVectorCond2 = lungimeVector;
	//afisareVector(vectorCond2, lungimeVectorCond2);

	//// Concatenarea a doi vectori
	//struct Biblioteca* vectorConcatenat = concatenareVectori(vectorCond1, lungimeVectorCond1, vectorCond2, lungimeVectorCond2);
	//int lungimeVectorConcatenat = lungimeVectorCond1 + lungimeVectorCond2;
	//afisareVector(vectorConcatenat, lungimeVectorConcatenat);

	//// Eliberarea memoriei
	//eliberareVector(vectorBiblioteci, lungimeVector);
	//eliberareVector(vectorCond1, lungimeVectorCond1);
	//eliberareVector(vectorCond2, lungimeVectorCond2);
	//free(vectorConcatenat);
	// Eliberam memoria
	//free(b.nume);
	int lungimeVector;
	struct Biblioteca* vectorBiblioteci = citireFisierBiblioteca("bibli.txt", &lungimeVector);

	// Testare afișare vector de biblioteci citit din fișier
	printf("Vectorul de biblioteci citit din fisier:\n");
	for (int i = 0; i < lungimeVector; i++) {
		afisareBiblioteca(vectorBiblioteci[i]);
	}

	// Testare salvare obiect în fișier
	struct Biblioteca b1 = initializeazaBiblioteca("Test", 10, 20);
	salvareBibliotecaInFisier(b1, "bibli.txt");

	// Testare salvare vector de biblioteci în fișier
	salvareVectorBiblioteciInFisier(vectorBiblioteci, lungimeVector, "biblioteci2.txt");

	// Eliberare memorie
	for (int i = 0; i < lungimeVector; i++) {
		free(vectorBiblioteci[i].nume);
	}
	free(vectorBiblioteci);


}