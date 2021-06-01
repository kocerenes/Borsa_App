#include "Portfoy.h"

Portfoy PortfoyOlustur(char* Dizi){
	Portfoy this;
	this = (Portfoy)malloc(sizeof(struct PORTFOY)); //PORTFOY yapısı için ramde yer ayırdım
	this->Dizi = Dizi;
	this->yoketPortfoy = &PortfoyYoket; //fonksiyon işaretçisinin neyi işaret ettiğini belirttim
	return this;
}

//emirlerde ve portfoyde bulunan işlemlerin sembol adı aynı olanların maliyetini döndüren fonksiyon.
double GetPortfoyMaliyet(const Portfoy this,char* SembolEmir){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Portfoy");
    int moons_count = cJSON_GetArraySize(moons);
   
    int i;
    for (i = 0; i < moons_count; i++) {

        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolPortfoy = cJSON_GetObjectItem(moon, "Sembol")->valuestring; // portfoydeki sembolü değişkene attım
		double maliyetPortfoy = cJSON_GetObjectItem(moon, "Maliyet")->valuedouble; // portfoydeki maliyeti değişkene attım
        int adetPortfoy = cJSON_GetObjectItem(moon, "Adet")->valueint; // portfoydeki adeti değişkene attım
		
		int kontrol = strcmp(sembolPortfoy,SembolEmir);//emirler ve portfoy dosyalarımdaki sembollerin aynı olup olmadıgını bulmak için strcmp fonksiyonunu kullandım.
		//eğer aynıysa int tipinde 0 döndürücek
		
		if(kontrol == 0){
			return maliyetPortfoy;
		}
    }
 
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);
}

//portfoydeki adeti döndürdüğüm fonksiyon.
int GetPortfoyAdet(const Portfoy this,char* SembolEmir){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Portfoy");
    int moons_count = cJSON_GetArraySize(moons);
    
	int i;
    for (i = 0; i < moons_count; i++) {

        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
		char *sembolPortfoy = cJSON_GetObjectItem(moon, "Sembol")->valuestring;
        int adetPortfoy = cJSON_GetObjectItem(moon, "Adet")->valueint;
		
		int kontrol = strcmp(sembolPortfoy,SembolEmir);
		
		if(kontrol == 0){
			return adetPortfoy;
		}
    }
 
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);
}

void PortfoyYoket(Portfoy this){
	if(this == NULL) return;
	free(this); //Portfoy yapısının çöpünü yok ettim
}
