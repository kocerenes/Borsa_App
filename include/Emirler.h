#ifndef EMIRLER_H
#define EMIRLER_H

#include "stdio.h"
#include "stdlib.h"

#include "cJSON.h"
#include "Dosya.h"
#include "Portfoy.h"
#include "Hisseler.h"

struct EMIRLER{
	Dosya superDosya; //Dosya yapısını kullanabilmek için
	Portfoy superPortfoy; //Portfoy yapısını kullanabilmek için
	Hisseler superHisseler; //Hisseler yapısını kullanabilmek için
	
	char* Dizi;
	
	void (*yoketEmirler)(struct EMIRLER*); //EmirlerYoket foksiyonu için işaretçi
};
typedef struct EMIRLER* Emirler;

Emirler EmirlerOlustur(char*);
void GetEmirlerVeriler(const Emirler);
void GetKarZarar(const Emirler);
void GetGuncelPortfoy(const Emirler);
void EmirlerYoket(Emirler);

#endif
