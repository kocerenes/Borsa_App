#ifndef PORTFOY_H
#define PORTFOY_H

#include "stdio.h"
#include "stdlib.h"
#include "cJSON.h"

#include <string.h> //strcmp fonksiyonunu kullanmak için ekledim

struct PORTFOY{
	char* Dizi;
	void (*yoketPortfoy)(struct PORTFOY*); //PortfoyYoket foksiyonu için işaretçi
};
typedef struct PORTFOY* Portfoy;

Portfoy PortfoyOlustur(char*);
double GetPortfoyMaliyet(const Portfoy,char*);
int GetPortfoyAdet(const Portfoy,char*);
void PortfoyYoket(Portfoy);

#endif