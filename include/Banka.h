#ifndef BANKA_H
#define BANKA_H

#include "stdio.h"
#include "stdlib.h"

#include "cJSON.h"
#include "Dosya.h"
#include "Emirler.h"

struct BANKA{
	Dosya superDosya; //Dosya yapısını kullanabilmek için
	Emirler superEmirler; //Emirler yapısını kullanabilmek için
};
typedef struct BANKA* Banka;

Banka BankaOlustur();
void BankaBasla(const Banka);
void BankaYoket(Banka);

#endif