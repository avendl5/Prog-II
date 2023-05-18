#ifndef HEADER_H
#define HEADAER_H



typedef struct artikl {
	int id;
	char ime[50];
	int cijena;

	
	

}ARTIKL;

void ispis_izbornika();
void dodaj_artikl();
void citaj_artikle();
void ispisi_artikle();
void pronadi_artikl();
void brisanje_artikala();



#endif
