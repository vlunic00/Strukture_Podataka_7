#include<stdio.h>
#include<stdlib.h>

struct stog;
typedef struct stog* Position;
typedef struct stog {
	int br;
	Position next;
}_stack;

int ucitaj(char[20]);
Position newElement();
void putIntoStack(Position, Position);
void calculate(Position, char);
void printResult(Position);

int main() {
	_stack head;
	head.next = NULL;
	int err = 0;
	err = ucitaj("postfix.txt", &head);
	if (!err)
		return -1;

	printResult(&head);
}

int ucitaj(char dat[20], Position p) {
	FILE* ulz = fopen(dat, "r");
	if (ulz == NULL) {
		printf("Greska pri otvaranju datoteke");
		return -1;
	}

	int i = 0;
	char temp = ' ';
	while (!feof(ulz)) {
		fscanf(ulz, "%c", &temp);
		i++;
	}

	rewind(ulz);
	char* buffer = NULL;
	buffer = (char*)malloc(sizeof(char) * i);
	i = 0;

	while (!feof(ulz)) {
		fscanf(ulz, "%c", (buffer + i));
		i++;
	}
	fclose(ulz);

	int lenght = 0;
	int returnValue = 1;
	int read = 0;

	while (returnValue) {
		Position q = newElement();
		if (q == NULL) {
			printf("Greska pri alokaciji");
			return -2;
		}
		char op = ' ';

		returnValue = sscanf(buffer + lenght, "%d%n", &q->br, &read);

		if (returnValue == 0) {
			returnValue = sscanf(buffer + lenght, " %c%n", &op, &read);
			calculate(p, op);
		}
		else
			putIntoStack(p, q);

		lenght += read;
	}

	return 1;
}
Position newElement() {
	Position p = NULL;
	p = (Position)malloc(sizeof(Position));
	
	return p;
}

void putIntoStack(Position p, Position q) {
	q->next = p->next;
	p->next = q;
}

void calculate(Position p, char op) {
	Position operand1 = NULL;
	Position operand2 = NULL;

	if (p->next == NULL || p->next->next == NULL) {
		printf("Stog nije pravilno popunjen");
		return;
	}

	operand2 = p->next;
	operand1 = p->next->next;

	switch (op) {
		case '+':
			p->next->br = operand1->br + operand2->br;
			break;

		case '-':
			p->next->br = operand1->br - operand2->br;
			break;

		case '*':
			p->next->br = operand1->br * operand2->br;
			break;

		case '/':
			p->next->br = operand1->br / operand2->br;
			break;

		default:
			printf("Nepoznata operacija\n");
			break;
	}

	p->next = operand1->next;
	free(operand1);
}

void printResult(Position p) {
	p = p->next;
	printf("Konacni rezultat je %d\n", p->br);
}