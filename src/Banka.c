#include "Banka.h"

Banka BankaOlustur(){
	Banka this;
	this = (Banka)malloc(sizeof(struct BANKA)); //banka yapısı için yer ayırdım
	this->superDosya = DosyaOlustur("doc/emirler.json");
	char* diziEleman = DosyaDiziAktar(this->superDosya);
	this->superEmirler = EmirlerOlustur(diziEleman); //emirler yapısından nesne olusturdum.
	return this;
}

void BankaBasla(const Banka this){
	
	
	
	printf("-------------------\n");
	GetEmirlerVeriler(this->superEmirler);//emirler.json un verilerini aldım
	printf("-------------------\n");
	GetKarZarar(this->superEmirler);  //kar zararı hesaplayıp ekrana yazdıran fonksiyonu cagırdım.
	printf("\n-------------------\n");
	printf("\nGüncel Portföy:\n");
	printf("-------------------\n");
	GetGuncelPortfoy(this->superEmirler); //portfoyu güncelleyip ekrana yazdırdım.
	printf("-------------------\n");
}

void BankaYoket(Banka this){
	if(this == NULL) return;
	this->superDosya->yoketDosya(this->superDosya); // bu yapıda dosya structını kullandıgım için çöpünü yok etme metodunu çağırdım
	this->superEmirler->yoketEmirler(this->superEmirler); // bu yapıda Emirler structını kullandıgım için çöpünü yok etme metodunu çağırdım
	free(this); //Banka yapısının çöpünü yok ettim
}
