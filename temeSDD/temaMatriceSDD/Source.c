/*Considerati codul de la task-ul precedent.

Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create. Asezarea in fisier a elementelor o faceti la libera alegere.

Scrieti intr-un program C functia care sa citeasca obiectele din fisier si sa le salveze intr-un vector.

Creati o functie care sa copieze (deep copy) elementele din vector intr-o matrice alocată dinamic. Asezarea in matrice pe linii a obiectelor o faceti dupa un criteriu aplicat unui atribut. Astfel veti obține mai multe clustere reprezentate de liniile matricei.

Scrieti o functie care muta liniile din matrice, astfel incat acestea sa fie sortate dupa numarul de elemente de pe linie.

Scrieti o functie care sa afiseze elementele dintr-o matrice.

*/

#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>


struct Biblioteca {
	int id;
	char* nume;
	int nrCarti;
};
//Scrieti intr - un program C functia care sa citeasca 
//obiectele din fisier si sa le salveze intr - un vector.
struct Biblioteca initializareBiblioteca(int i, const char* nume, int nrCarti) {
	struct Biblioteca b;
	b.id = i;
	b.nume = malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	return b;
}
void afisareBiblioteca(struct Biblioteca b) {
	printf("Id: %d Nume: %s NrCarti: %d\n", b.id, b.nume, b.nrCarti);

}

void afisareVector(struct Biblioteca* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareBiblioteca(vector[i]);
	}

}

void inserareBibliotecaVector(struct Biblioteca** vector, int* dim, struct Biblioteca b) {
	struct Biblioteca* copie;
	copie = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * (*dim + 1));

	for (int i = 0; i < (*dim); i++) {
		copie[i] = (*vector)[i];
	}

	copie[*dim] = b;

	free(*vector);
	*vector = copie;
	(*dim)++;
}



void citesteFisier(const char* numeFis, struct Biblioteca** vector, int* dimVect) {
	if (numeFis != NULL && strlen(numeFis) > 0) {
		FILE* f = fopen(numeFis, "r");
		if (f != NULL) {
			(*dimVect) = 0;
			char buffer[100];
			char delimitatoare[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitatoare);
				struct Biblioteca b;
				b.id = atoi(token);
				token = strtok(NULL, delimitatoare);
				b.nume = (char*)malloc(strlen(token) + 1);
				strcpy(b.nume, token);
				token = strtok(NULL, delimitatoare);
				b.nrCarti = atoi(token);



				inserareBibliotecaVector(vector, dimVect, b);
			}
			fclose(f);
		}
	}
}

struct Biblioteca** copiereVectorInMatrice(struct Biblioteca* vector, int dim, int* dimMatrice) {
	// Determinăm numărul maxim de cărți pentru alocarea matricei
	int maxNrCarti = 0;
	for (int i = 0; i < dim; i++) {
		if (vector[i].nrCarti > maxNrCarti) {
			maxNrCarti = vector[i].nrCarti;
		}
	}

	// Alocăm matricea
	*dimMatrice = dim;
	struct Biblioteca** matrice = (struct Biblioteca**)malloc(sizeof(struct Biblioteca*) * dim);
	for (int i = 0; i < dim; i++) {
		matrice[i] = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * maxNrCarti);
	}

	// Copiem elementele din vector în matrice
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < vector[i].nrCarti; j++) {
			matrice[i][j] = vector[i];
		}
	}

	return matrice;
}

// Funcție pentru a afișa matricea
void afisareMatrice(struct Biblioteca** matrice, int dimMatrice) {
	for (int i = 0; i < dimMatrice; i++) {
		printf("Linia %d: ", i + 1);
		for (int j = 0; j < matrice[i]->nrCarti; j++) {
			printf("%s ", matrice[i][j].nume);
		}
		printf("\n");
	}
}


void main() {
	struct Biblioteca b;
	b = initializareBiblioteca(2, "dhsjkala", 34);
	afisareBiblioteca(b);

	printf("\n\n");
	struct Biblioteca* vector = NULL;
	int dimInitiala = 0;
	citesteFisier("biblioteci.txt", &vector, &dimInitiala);
	afisareVector(vector, dimInitiala);


	int dimMatrice;
	struct Biblioteca** matrice = copiereVectorInMatrice(vector, dimInitiala, &dimMatrice);

	// Afișăm matricea
	afisareMatrice(matrice, dimMatrice);

	// Eliberăm memoria alocată pentru matrice
	for (int i = 0; i < dimMatrice; i++) {
		free(matrice[i]);
	}
	free(matrice);


}