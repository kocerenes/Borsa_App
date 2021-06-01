#include "Dosya.h"

Dosya DosyaOlustur(char* DosyaYol){
	Dosya this;
	this = (Dosya)malloc(sizeof(struct DOSYA));
	this->DosyaYol = DosyaYol;
	this->yoketDosya = &DosyaYoket; //fonksiyon işaretçisinin neyi işaret ettiğini belirttim
	return this;
}

//dosyayı satır satır okuyup içindekileri diziye aldıgım fonksiyon
char* DosyaDiziAktar(const Dosya this){
	
	FILE *file;
    int uzunluk;
    char* dosyaDizi;

    file=fopen(this->DosyaYol,"rb"); //okuycağım dosyayı parametre olarak verdim
    fseek(file,0,SEEK_END);
    uzunluk=ftell(file);
    fseek(file,0,SEEK_SET);
    dosyaDizi=(char*)malloc(uzunluk+1);
    fread(dosyaDizi,1,uzunluk,file);
    fclose(file);
    return dosyaDizi;
}

void DosyaYoket(Dosya this){
	if(this == NULL) return;
	free(this); // Dosya yapısının çöpünü yok ettim
}
