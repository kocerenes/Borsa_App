#ifndef DOSYA_H
#define DOSYA_H

#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

struct DOSYA{
	char *DosyaYol;
	void (*yoketDosya)(struct DOSYA*); //DosyaYoket foksiyonu için işaretçi
};
typedef struct DOSYA* Dosya;

Dosya DosyaOlustur(char*);
char* DosyaDiziAktar(const Dosya);
void DosyaYoket(Dosya);

#endif