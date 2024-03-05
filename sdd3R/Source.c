#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};
void inserareLocuinta(struct Locuinta** vector, int* dim, struct Locuinta l) {
	struct Locuinta* copie;
	copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * (*dim + 1)); // Allocați memorie pentru un element în plus

	// Copiați datele din vectorul original în noul vector
	for (int i = 0; i < *dim; i++) {
		copie[i] = (*vector)[i];
	}

	// Adăugați noua locuință la sfârșitul noului vector
	copie[*dim] = l;

	// Eliberați memoria pentru vectorul original
	free(*vector);

	// Actualizați pointerul către noul vector și dimensiunea
	*vector = copie;
	(*dim)++;
}


void afisareLocuinta(struct Locuinta l) {
	printf("Id: %d Strada: %s Numarul: %d\n", l.id, l.strada, l.numar);
}

void afisareVectorLocuinta(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareLocuinta(vector[i]);
	}
}


void stergereLocuintaDupaId(struct Locuinta** vector, int* dim, int id) {
	int flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) { // avem locuința de șters
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * ((*dim) - 1));
		int j = 0;
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;

		// Eliberăm memoria pentru vectorul original
		free(*vector);

		// Actualizăm pointerul către noul vector
		*vector = copie;
	}
}


void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitatoare[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitatoare);
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitatoare);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitatoare);
				locuinta.numar = atoi(token);
				inserareLocuinta(vector, dim, locuinta);

			}
			fclose(f);

		}

	}

}







void main() {
	struct Locuinta* vectorLocuinte = NULL;
	int dim = 0;
	citesteFisier("locuinte.txt", &vectorLocuinte, &dim);
	printf("Lista de locuinte (fisier):\n");
	afisareVectorLocuinta(vectorLocuinte, dim);
	printf("Aici trebuie sa fie stergerea: \n");
	stergereLocuintaDupaId(&vectorLocuinte, &dim, 19);
	printf("Vector dupa stergere\n");
	afisareVectorLocuinta(vectorLocuinte, dim);
}