#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdio.h>


struct Biblioteca {
	int id;
	char* nume;
	int nrCarti;
};

struct Nod {
	struct Biblioteca info;
	struct Nod* next;
};

struct Nod* inserareLista(struct Nod* head, struct Biblioteca b) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod));
	nou->info = b;
	nou->next = head;
	return nou;
};

void afisareLista(struct Nod* head) {
	while (head) {
		printf("%d %c %d\n", head->info.id, head->info.nume, head->info.nrCarti);
		head = head->next;
	}
}


struct Nod* citireFisier(const char* numeFis, struct Nod* prim) {
	struct Biblioteca b;
	FILE* f;
	char buffer[100];
	char* token;
	char delimitatoare[] = ",\n";

	f = fopen(numeFis, "r");
	if (f == NULL) {
		printf("Eroare deschidere fisier");
		return prim;
	}
	while (fgets(buffer, 100, f) != NULL) {
		token = strtok(buffer, delimitatoare);
		b.id = atoi(token);
		token = strtok(NULL, delimitatoare);
		b.nume = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(b.nume, token);
		token = strtok(NULL, delimitatoare);
		b.nrCarti = atoi(token);

		prim = inserareLista(prim, b);
	}
	fclose(f);
	return prim;
}

void main() {
	struct Nod* lista = NULL;
	lista = citireFisier("biblioteci.txt", lista);
	afisareLista(lista);
}