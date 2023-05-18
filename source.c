#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "header.h"


void ispis_izbornika() {
	printf("IZBORNIK:\n\n");
	printf("1.Dodavanje novih artikala\n");
	printf("2.Citanje artikala iz datoteke(abecedno)\n");
	printf("3.Ispisivanje podataka o svim artiklima(abecedno)\n");
	printf("4.Pretrazi artikl po ID\n");
	printf("5.Izlazak iz programa\n\n");
}

int generiraj_novi_id() {
	FILE* f = fopen("artikli.txt", "r");
	if (f == NULL) {
		return 1;
	}
	ARTIKL c;
	int max_id = 0;
	while (fread(&c, sizeof(c), 1, f) == 1) {
		if (c.id > max_id) {
			max_id = c.id;
		}
	}
	fclose(f);

	return max_id + 1;
}

void dodaj_artikl() {
	FILE* f = fopen("artikli.txt", "a");
	if (f == NULL) {
		printf("Ne mogu otvoriti datoteku\n");
		return;
	}
	ARTIKL c;
	c.id = generiraj_novi_id();
	printf("Unesite ime: ");
	scanf("%s", c.ime);
	printf("Unesite cijenu: ");
	scanf("%d", &c.cijena);	
	
	fwrite(&c, sizeof(c), 1, f);

	fclose(f);
	printf("Artikl dodan u bazu podataka.\n\n");
}

void citaj_artikle() {
	FILE* f = fopen("artikli.txt", "r");
	if (f == NULL) {

		printf("Ne mogu otvoriti datoteku\n");
		return;
	}
	ARTIKL c;
	while (fread(&c, sizeof(c), 1, f)) {
		printf("%d %s %d  \n", c.id, c.ime,c.cijena );

	}

	fclose(f);

}
void ispisi_artikle() {
	FILE* f = fopen("artikli.txt", "r");
	if (f == NULL) {
		printf("Ne mogu otvoriti datoteku\n");
		return;
	}
	ARTIKL c;

	
	
	fclose(f);
}
void pronadi_artikl() {

	int id;
	printf("Unesite ID artikla kojeg zelite pronaci:\n ");
	scanf("%d", &id);

	FILE* f = fopen("artikli.txt", "r");
	if (f == NULL) {

		printf("Ne mogu otvoriti datoteku\n");
		return;
	}
	ARTIKL c;
	int pronaden = 0;
	while (fread(&c, sizeof(c), 1, f)) {
		if (c.id == id) {
			printf("Pronaden artikl:\n");
			printf("ID: %d\nIme: %f\n Cijena:\n\n", c.id, c.ime, c.cijena);
			pronaden = 1;
			break;
		}
	}

	if (!pronaden) {
		printf("Nema artikla s ID-om %d\n", id);
	}
	fclose(f);
}
