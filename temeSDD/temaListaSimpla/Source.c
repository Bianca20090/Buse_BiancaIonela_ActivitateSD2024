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

typedef struct Nod Nod;
typedef struct Biblioteca Biblioteca;


void afisareLista(struct Nod* head) {
	while (head) {
		printf("%d %s %d\n", head->info.id, head->info.nume, head->info.nrCarti);
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



// Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri 
//decat index-ul dat, nu se realizeaza stergerea.



struct Nod* stergereNodIndex(struct Nod* prim, int index) {
	struct Nod* temp = prim; //un pointer cu care parcurgem lista
	struct Nod* prev = NULL; 
	int count = 0;
	if (index == 0) {
		prim = temp->next;
		free(temp->info.nume);
		free(temp);
		return prim;
	}

	while (temp != NULL && count < index) {
		prev = temp;
		temp = temp->next;
		count++;
	}

	if (temp == NULL) {
		printf("Lista nu are suficiente noduri\n");
		return prim;
	}

	prev->next = temp->next;
	free(temp->info.nume);
	free(temp);
	return prim;
}

//2. Implementati o functie care sa insereze
//  elementele in cadrul listei simplu inlantuite astfel incat acestea a fie 
//sortate crescator dupa un camp la alegerea voastra.

void insertSorted(struct Nod* head, struct Biblioteca b) {
	head = inserareLista(head, b);
	if (head != NULL) {

		struct Nod* temp = NULL;
		for (temp = head; temp; temp=temp->next) {
			for (struct Nod* next = temp; next; next = next->next) {
				if (temp->info.nrCarti > next->info.nrCarti) {
					struct Biblioteca b2 = temp->info;
					temp->info = next->info;
					next->info = b2;
				}
			}
		}
	}
}


// Implementati o functie care 
// salveaza intr-un vector toate obiectele care indeplinesc o conditie stabilita de voi. Realizati deep copy, astfel incat elementele
//  din vector sa fie diferentiate de cele din lista. Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti
//pentru cate elemente veti aloca spatiu.

struct Biblioteca initializeazaBibl(const char* nume, int id, int nrCarti){
	struct Biblioteca b;
	b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(b.nume, nume);
	b.nrCarti = nrCarti;
	b.id = id;

	return b;

}

struct Biblioteca* adaugaInVector(struct Nod* head) {
	int numar = 0;
	struct Nod* temp = head;

	// Numără elementele care îndeplinesc condiția
	while (temp) {
		if (temp->info.nrCarti <= 30) {
			numar++;
		}
		temp = temp->next;
	}

	// Alocă spațiu pentru vectorul de Biblioteci
	struct Biblioteca* vectorBiblioteci = (struct Biblioteca*)malloc(sizeof(struct Biblioteca) * numar);

	// Resetăm temporarul pentru a itera din nou peste lista
	temp = head;
	int index = 0;
	while (temp) {
		if (temp->info.nrCarti <= 30) {
			// Realizează o deep copy pentru fiecare obiect
			vectorBiblioteci[index] = initializeazaBibl(temp->info.nume, temp->info.id, temp->info.nrCarti);
			index++;
		}
		temp = temp->next;
	}

	return vectorBiblioteci;
}

void afisareBiblioteca(struct Biblioteca b) {
	printf("%d %s %d\n", b.id, b.nume, b.nrCarti);
}

void afisareVector(struct Biblioteca* vector, int nr) {
	if (vector != NULL) {
		for (int i = 0; i < nr; i++) {
			afisareBiblioteca(vector[i]);
		}
	}
}

//exercitiul 4:


void interschimbarePozitii(struct Nod* prim, int pozitie1, int pozitie2) {
	// Verificăm dacă pozițiile sunt valide
	if (pozitie1 == pozitie2 || pozitie1 < 0 || pozitie2 < 0) {
		printf("Poziții invalide pentru interschimbare.\n");
		return;
	}

	struct Nod* prev1 = NULL;
	struct Nod* temp1 = prim;

	// Parcurgem lista până la prima poziție
	for (int i = 0; temp1 && i < pozitie1; i++) {
		prev1 = temp1;
		temp1 = temp1->next;
	}

	struct Nod* prev2 = NULL;
	struct Nod* temp2 = prim;

	// Parcurgem lista până la a doua poziție
	for (int i = 0; temp2 && i < pozitie2; i++) {
		prev2 = temp2;
		temp2 = temp2->next;
	}

	// Verificăm dacă am ajuns la capătul listei
	if (!temp1 || !temp2) {
		printf("Una dintre poziții este în afara listei.\n");
		return;
	}

	// Dacă primul element este la prima poziție, actualizăm începutul listei
	if (prev1 == NULL)
		prim = temp2;
	else
		prev1->next = temp2;

	// Dacă al doilea element este la prima poziție, actualizăm începutul listei
	if (prev2 == NULL)
		prim = temp1;
	else
		prev2->next = temp1;

	// Schimbăm legăturile pentru nodurile interschimbate
	struct Nod* temp = temp2->next;
	temp2->next = temp1->next;
	temp1->next = temp;
}




void dezalocare(struct Nod* head) {
	struct Nod* temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		free(temp->info.nume);
		free(temp);
	}
}

void main() {
	struct Nod* lista = NULL;
	lista = citireFisier("biblioteci.txt", lista);
	printf("Lista inainte de stergere:\n");
	afisareLista(lista);
	printf("Lista dupa stergere:\n");
	lista = stergereNodIndex(lista, 3);
	afisareLista(lista);


	struct Biblioteca b1 = { 200, "BibliotecaInserata", 30 };
	insertSorted(lista, b1);
	printf("\n\n");
	afisareLista(lista);

	printf("\nEXERCITIUL 3-----------------\n");
	struct Biblioteca* vector = NULL;
	int* dim = 0;
	vector = adaugaInVector(lista);
	afisareVector(vector, 5);


	printf("\nEX 4-----------------");
	printf("Afisatrea listei inainte de interschimbare:\n");
	afisareLista(lista);
	interschimbarePozitii(lista, 1, 2);
	printf("Afisatrea listei dupa de interschimbare:\n");
	afisareLista(lista);

}