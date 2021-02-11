#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct stog;
typedef struct stog* Pozicija;
typedef struct stog {
	int br;
	Pozicija next;
}_st;

void ucitaj(Pozicija p, char[50]);
Pozicija stvoriClan();
void izracunaj(Pozicija, char);
void push(Pozicija, Pozicija);
int pop(Pozicija);
void ispisi(Pozicija);

int main() {
	_st head1;

	head1.next = NULL;
	ucitaj(&head1, "postfix.txt");
	ispisi(&head1);
	return 0;

}

Pozicija stvoriClan() {
	Pozicija p;
	p = (Pozicija)malloc(sizeof(struct stog));
	if (p == NULL)
		return NULL;
	return p;
}

void push(Pozicija p, Pozicija q) {
	q->next = p->next;
	p->next = q;
}

int pop(Pozicija p) {
	Pozicija q;
	int a;
	q = p->next;
	a = q->br;
	p->next = q->next;

	free(q);
	return a;
}

void ucitaj(Pozicija p, char pom[50]) {
	FILE* ulz;
	int n = 0;
	int i = 0;
	char c;
	char* buffer;

	ulz = fopen(pom, "r");
	if (ulz == NULL) {
		printf("Pogreska pri otvaranju datoteke.\n");
		return;
	}

	while (!feof(ulz)) {
		fscanf(ulz, "%c", &c);
		n++;
	}

	buffer = (char*)malloc(sizeof(char) * n);

	rewind(ulz);

	while (!feof(ulz)) {
		fscanf(ulz, "%c", buffer + i);
		i++;
	}
	
	//for (i; i < strlen(buffer); i++) {
	//	*(buffer + i) = '\0';
	//}

	fclose(ulz);

	int returnValue = 1;
	int lenght = 0;
	int read;
	while (returnValue) {
		Pozicija q;
		q = stvoriClan();

		returnValue = sscanf(buffer + lenght, " %d%n", &q->br, &read);

		if (returnValue == 0) {
			returnValue = sscanf(buffer + lenght, " %c%n", &c, &read);
			if (lenght < n)
				izracunaj(p, c);
			else
				break;
		}
		else {
			push(p, q);
		}
		lenght += read;
	}
}

void izracunaj(Pozicija p, char c) {
	int a, b, d;
	Pozicija r;

	if (c == '+') {
		a = pop(p);
		b = pop(p);
		d = b + a;
		r = stvoriClan();
		r->br = d;
		push(p, r);
	}
	else if (c == '-') {
		a = pop(p);
		b = pop(p);
		d = b - a;
		r = stvoriClan();
		r->br = d;
		push(p, r);
	}
	else if (c == '*') {
		a = pop(p);
		b = pop(p);
		d = b * a;
		r = stvoriClan();
		r->br = d;
		push(p, r);
	}
	else if (c == '/') {
		a = pop(p);
		b = pop(p);
		d = b / a;
		r = stvoriClan();
		r->br = d;
		push(p, r);
	}
}
void ispisi(Pozicija p) {
	printf("%d", p->next->br);
}
