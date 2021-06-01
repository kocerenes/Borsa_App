#include "Hisseler.h"

Hisseler HisselerOlustur(char* Dizi){
	Hisseler this;
	this = (Hisseler)malloc(sizeof(struct HISSELER)); //Hisseler yapısı için ramde yer ayırdım
	this->Dizi = Dizi;
	this->yoketHisseler = &HisselerYoket; //fonksiyon işaretçisinin neyi işaret ettiğini belirttim
	return this;
}

//eğer emirler dosyamdaki bi sembol hisselerde de varsa hisseler dosyamdaki fiyatını döndürmeye yarayan fonksiyon.
double GetHisseFiyat(const Hisseler this,char* SembolEmir){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Hisseler"); //dosyanın başındaki Hisseler yazısından itibaren okudum
    int moons_count = cJSON_GetArraySize(moons);
    
	int i;
    for (i = 0; i < moons_count; i++) {

        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolHisseler = cJSON_GetObjectItem(moon, "Sembol")->valuestring; //sembolü değişkene attım
        double fiyatHisseler = cJSON_GetObjectItem(moon, "Fiyat")->valuedouble; //fiyatı değişkene attım
		
		int kontrol = strcmp(sembolHisseler,SembolEmir); //emirler ve hisseler dosyalarımdaki sembollerin aynı olup olmadıgını bulmak için strcmp fonksiyonunu kullandım.
		//eğer aynıysa int tipinde 0 döndürücek
		
		if(kontrol == 0){
			return fiyatHisseler;
		}
    }
 
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);	
}

void HisselerYoket(Hisseler this){
	if(this == NULL) return;
	free(this); //Hisseler yapısının çöpünü yok ettim
}
