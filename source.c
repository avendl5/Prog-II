#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#define NOOP() do {} while(0)
static int brojArtikala = 0, i, j, br = 0;//4,5

int makro() {//7
	NOOP();  
	return 0;
}



int izbornik() {//8

	int opcija = 0; //1
	static ARTIKL* polje = NULL;


	printf("IZBORNIK\n\n");
	printf("' 1 ' Dodaj artikl\n");
	printf("' 2 ' Uredi postojeci artikl\n");
	printf("' 3 ' Ispis artikala\n");
	printf("' 4 ' Trazilica\n");
	printf("' 5 ' Sortiraj artikle po cijeni\n");
	printf("' 6 ' Izlaz iz programa\n");

	scanf("%d", &opcija);
	system("cls");


	switch (opcija) {
	case 1:
		ucitavanjeArtikala();
		if (brojArtikala == 0) {
			kreiranjeDat();
		}
		dodavanjeArtikala();
		break;
	case 2:
		prepravljanje();
		break;
	case 3:
		if (polje != NULL) {
			free(polje);
			polje = NULL;
		}
		polje = (ARTIKL*)ucitavanjeArtikala();
		ispisivanje(polje);
		break;
	case 4:
		while (opcija != 90) {
			opcija = izbornikSrch();
		}
		break;
	case 5:
		while (opcija != 91)
			opcija = izbornikSrt();
		break;
	case 6:
		izlaz(polje);
		return 101;
		break;
	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

izbornikSrch() {
	int opcija = 0;
	ARTIKL* polje = NULL;//10
	polje = (ARTIKL*)ucitavanjeArtikala();//9
	printf("Pretrazi po:\n");
	printf("\t' 1 ' Imenu artikla\n");
	printf("\t' 2 ' Cijeni\n");
	printf("\t' 3 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		SearchImeArtikla(polje);
		break;
	case 2:
		SearchCijena(polje);
		break;
	case 3:
		return 90;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

int izbornikSrt() {
	int opcija = 0;
	ARTIKL* polje = NULL;
	polje = (ARTIKL*)ucitavanjeArtikala();
	printf("Sortiraj prema:\n");
	printf("\t' 1 ' Cijeni uzlazno\n");
	printf("\t' 2 ' Cijeni silazno\n");
	printf("\t' 3 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		selectionSortCijenaUzl(polje);
		break;
	case 2:
		selectionSortCijenaSil(polje);
		break;
	case 3:
		return 91;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("artikli.bin", "wb");//16
	if (fp == NULL) {
		perror("Kreiranje");//19
	}
	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

void dodavanjeArtikala() {
	FILE* fp = NULL;
	fp = fopen("artikli.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Trenutni broj artikala: %d\n", brojArtikala);

	ARTIKL artikl;
	artikl.id = brojArtikala;
	br++;
	getchar();
	printf("Unesite ime artikla: ");
	scanf("%24[^\n]", artikl.ime_artikla);
	getchar();
	printf("Unesite raspolozivost(da/ne): ");
	scanf("%3[^\n]", artikl.raspolozivost);
	getchar();
	printf("Unesite cijenu proizvoda: ");
	scanf("%f", &artikl.cijena);
	getchar();
	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);//17
	fwrite(&artikl, sizeof(ARTIKL), 1, fp);
	rewind(fp);
	brojArtikala++;
	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}

void prepravljanje() {
	FILE* fp = NULL;
	int reload;
	fp = fopen("artikli.bin", "rb+");
	if (fp == NULL)
		printf("Niste unijeli niti jedan proizvod.\n");
	else {
		printf("Unesi id artikla kojeg zelite ispraviti:\n");
		scanf("%d", &reload);
		fseek(fp, sizeof(int) + (sizeof(ARTIKL) * (reload - 1)), SEEK_SET);
		ARTIKL ispravljenProizvod;
		ispravljenProizvod.id = reload;
		getchar();
		printf("Unesite ispravljeno ime artikla: ");
		scanf("%24[^\n]", ispravljenProizvod.ime_artikla);
		getchar();
		printf("Unesite ispravljenu raspolozivost: ");
		scanf("%3[^\n]", ispravljenProizvod.raspolozivost);
		getchar();
		printf("Unesite ispravljenu cijenu proizvoda: ");
		scanf("%f", &ispravljenProizvod.cijena);
		getchar();
		fwrite(&ispravljenProizvod, sizeof(ARTIKL), 1, fp);
		rewind(fp);
		fwrite(&brojArtikala, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void* ucitavanjeArtikala() {
	FILE* fp = fopen("artikli.bin", "rb");
	if (fp == NULL) {
		printf("Niste unijeli niti jedan artikl.\n");
		return NULL;
	}
	fread(&brojArtikala, sizeof(int), 1, fp);
	ARTIKL* polje = NULL;
	polje = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));//13,14
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(ARTIKL), brojArtikala, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(ARTIKL* polje) {
	for (i = 0; i < brojArtikala; i++) {
		printf("Ime artikla:%s  Raspolozivost:%s  Cijena: %f\n", (polje + i)->ime_artikla, (polje + i)->raspolozivost, (polje + i)->cijena);
	}
}

void* SearchImeArtikla(ARTIKL* polje) {//21
	char reqName[25];
	int br = 0;

	printf("Upisite ime trazenog artikla:\n");
	getchar();
	scanf("%24[^\n]", reqName);

	for (i = 0; i < brojArtikala; i++) {
		if (!strcmp(reqName, (polje + i)->ime_artikla)) {
			printf("\nIme artikla : % s  Raspolozivost : % s  Cijena : % f\n", (polje + i)->ime_artikla, (polje + i)->raspolozivost, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nArtikl pod ovim imenom nije pronaden\n");
	return NULL;
}



void* SearchCijena(ARTIKL* polje) {//21
	int reqPrice, br = 0;

	printf("Unesite broj cijene koju trazite:\n");
	scanf("%d", &reqPrice);

	for (i = 0; i < brojArtikala; i++) {
		if (reqPrice == (polje + i)->cijena) {
			printf("\nIme artikla : % s  Raspolozivost : % s  Cijena : % f\n", (polje + i)->ime_artikla, (polje + i)->raspolozivost, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena cijena nije pronadjena.\n");
	return NULL;
}

void subs(ARTIKL* veci, ARTIKL* manji) {
	ARTIKL temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}

void subs2(ARTIKL* manji, ARTIKL* veci) {//12
	ARTIKL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortCijenaUzl(ARTIKL* polje) {//20
	for (int j = 0; j < brojArtikala; j++) {
		for (int i = 0; i < brojArtikala - 1; i++) {
			if (polje[i].cijena > polje[i + 1].cijena) {
				subs2((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojArtikala; i++) {
		printf("\nID: %d Ime artikla:%s  Raspolozivost:%s  Cijena: %f\n", (polje + i)->id, (polje + i)->ime_artikla, (polje + i)->raspolozivost, (polje + i)->cijena);
	}
	printf("\n");
}

void selectionSortCijenaSil(ARTIKL* polje) {
	for (int j = 0; j < brojArtikala; j++) {
		for (int i = 0; i < brojArtikala - 1; i++) {
			if (polje[i].cijena < polje[i + 1].cijena) {
				subs((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojArtikala; i++) {
		printf("\nID: %d Ime artikla:%s  Raspolozivost:%s  Cijena: %f\n", (polje + i)->id, (polje + i)->ime_artikla, (polje + i)->raspolozivost, (polje + i)->cijena);
	}
	printf("\n");
}
void izlaz(ARTIKL* polje) {
	printf("Zelite li pri izlasku programa izbrisati datoteku ili zadrzati?\n");
	printf("Ako zelite izbrisati datoteku napisite obrisi, ako ne zelite napisite zadrzi\n");

	char uvjet[7] = { '\0' };
	scanf("%6s", uvjet);
	if (!strcmp("obrisi", uvjet)) {
		remove("artikli.bin") == 0 ? printf("Izbrisali ste datoteku artikli.bin.\n") : printf("Datoteka neuspjesno izbrisani ili ona ne postoji.\n");//18
		printf("\nIzlaz iz programa.\n");
		free(polje);//15
	}
	else printf("\nZadrzali ste datoteku.\nIzlaz iz programa\n");
}
