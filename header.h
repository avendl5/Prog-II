#ifndef Header_H
#define Header_H

typedef struct artikl {//2,3
	float cijena;//1
	char ime_artikla[25];//1,4
	char raspolozivost[3];//1
	int id;//1
}ARTIKL;

int izbornik();
int izbornikSrch();
int izbornikSrt();
int makro();
void kreiranjeDat();
void dodavanjeArtikala();
void prepravljanje();
void* ucitavanjeArtikala();
void ispisivanje(ARTIKL*);
void* SearchImeArtikla(ARTIKL*);
void* SearchCijena(ARTIKL*);
void subs(ARTIKL*, ARTIKL*);
void subs2(ARTIKL*, ARTIKL*);
void selectionSortCijenaUzl(ARTIKL*);
void selectionSortCijenaSil(ARTIKL*);
void brisanjeArtikala(ARTIKL*);
void izlaz(ARTIKL*);

#endif //Header_H
