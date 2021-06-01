#ifndef HISSELER_H
#define HISSELER_H

#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

#include <string.h> //strcmp fonksiyonunu kullanmak için ekledim

struct HISSELER{
	char* Dizi;
	void (*yoketHisseler)(struct HISSELER*); //HisselerYoket foksiyonu için işaretçi
};
typedef struct HISSELER* Hisseler;

Hisseler HisselerOlustur(char*);
double GetHisseFiyat(const Hisseler,char*);
void HisselerYoket(Hisseler);

#endif