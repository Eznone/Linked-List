//Enzo Tres Mediano
//2211731
//Objectivo: Para organizar uma lista de pacientes 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct--------------------------------------------------------------------------------
typedef struct patient Patient;
struct patient {
	int queue;
	char* status;
	Patient* next;
};
//prototypos----------------------------------------------------------------------------
Patient* insertToList(Patient* lNode, int queue, char* status);
Patient* createNode(int queue, char* status);
int checkPriority(char* old, char* new, int oldq, int newq);
void printList(Patient* l);
void freeList(Patient* l);
Patient* removePatient(Patient* lNode, int queue, char* status);
//main----------------------------------------------------------------------------------
int main(void) {
	int listQueues[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	char* listStatus[] = { "Green", "Red", "Green", "Yellow", "Red", "Red", "Green", "Red"};
	Patient* lNode = (Patient*)malloc(sizeof(Patient));
	lNode = NULL;
	for (int i = 0; i < 8; i++) {
		lNode = insertToList(lNode, listQueues[i], listStatus[i]);
	}
	//Primeira print
	printList(lNode);

	//Segunda print
	lNode = removePatient(lNode, 5, "Red");
	printList(lNode);

	//Terceira print
	lNode = removePatient(lNode, 4, "Yellow");
	printList(lNode);

	//Quarta print
	for (int i = 0; i < 4; i++) {
		listQueues[i] = i + 9;
		listStatus[i] = (i == 1 || i == 3) ? "Yellow" : (i == 0) ? "Green" : "Red";
	}
	for (int i = 0; i < 4; i++) {
		lNode = insertToList(lNode, listQueues[i], listStatus[i]);
	}
	printList(lNode);

	//Quinta print
	lNode = removePatient(lNode, 2, "Red");
	lNode = removePatient(lNode, 6, "Red");
	printList(lNode);

	//Sexta print
	lNode = removePatient(lNode, 3, "Green");
	printList(lNode);

	freeList(lNode);
	return 0;
}
//funcoes-------------------------------------------------------------------------------
Patient* insertToList(Patient* fNode, int queue, char* status) {
	Patient* newNode;
	Patient* Node = fNode;
	Patient* before = NULL;
	while (Node != NULL && (checkPriority(Node->status, status, Node->queue, queue) == 1)) {
		before = Node;
		Node = Node->next;
	}

	newNode = createNode(queue, status);

	if (before == NULL) {
		newNode->next = fNode;
		fNode = newNode;
	}
	else {
		newNode->next = before->next;
		before->next = newNode;
	}
	return fNode;
}

//Esse funcao vai criar um novo Node vvv
Patient* createNode(int queue, char* status) {
	Patient* newNode = (Patient*)malloc(sizeof(Patient));
	if (newNode == NULL) {
		printf("Error allocating space");
		exit(2);
	}
	char* nStatus = (char*)malloc(sizeof(char) * strlen(status));
	if (nStatus == NULL) {
		printf("Error allocating space");
		exit(2);
	}
	strcpy(nStatus, status);
	newNode->status = nStatus;
	newNode->queue = queue;
	newNode->next = NULL;
	return newNode;
}

//Esse funcao e pra ver aonde o novo patiente vai na lista vvv
int checkPriority(char* old, char* new, int oldq, int newq) {
	if (strcmp(old, new) == 0) {
		if (newq > oldq) {
			return 1;
		}
	}
	if (wordToColor(new) > wordToColor(old)) {
		return 1;
	}
	return -1;
}

//Para que n tenho muito conficoes em qual cor vai em frente do outro, eu accosiei as palavras como numeros, dai seria se um numero era maior de que
//o outro significa que tem que ir na proxima pos na lista vvv
int wordToColor(char* word) {
	if (strcmp(word, "Red") == 0) {
		return 1;
	}
	if (strcmp(word, "Yellow") == 0) {
		return 2;
	}
	if (strcmp(word, "Green") == 0) {
		return 3;
	}
	printf("Color Not Found");
	exit(2);
}

void printList(Patient* l) {
	printf("Lista atualizada:\n");
	Patient* current = l;
	while (current != NULL){
		printf("Condicao: %s \tNumero: %d\n", current->status, current->queue);
		current = current->next;
	}
	printf("\n");
}

Patient* removePatient(Patient* lNode, int queue, char* status) {
	Patient* current = lNode;
	Patient* before = NULL;
	
	//Causo seja a primeira posicao
	if (current != NULL && strcmp(status, current->status) == 0) {
		if (queue == current->queue) {
			lNode = current->next;
			free(current);
			return lNode;
		}
	}

	while (current != NULL) {
		if (strcmp(status, current->status) == 0) {
			if (queue == current->queue) {
				before->next = current->next;
				free(current);
				return lNode;
			}
		}
		before = current;
		current = current->next;
	}
	printf("Patient not found\n");
	return lNode;
}

void freeList(Patient* l) {
	Patient* bef = l;
	Patient* aft;
	while (bef != NULL) {
		aft = bef->next;
		free(bef);
		bef = aft;
	}
}

//Conclusao, Tudo ta funcionando como deveria