#include "Emirler.h"

Emirler EmirlerOlustur(char* Dizi){
	Emirler this;
	this = (Emirler)malloc(sizeof(struct EMIRLER)); //bellekte EMIRLER yapısı için yer ayırdım
	
	this->superDosya = DosyaOlustur("doc/portfoy.json");//portfoy dosyasını aldım
	char* diziPortfoy = DosyaDiziAktar(this->superDosya);//portfoy dosyasını diziye attım
	
	this->superDosya = DosyaOlustur("doc/hisseler.json"); //hisseler dosyasını aldım
	char* diziHisseler = DosyaDiziAktar(this->superDosya); //hisseler dosyasını dziye attım
	
	this->superPortfoy = PortfoyOlustur(diziPortfoy); //portfoy dizisini parametre olarak verip portfoy olusturdum.
	this->superHisseler = HisselerOlustur(diziHisseler);//hisseler dizisini parametre olarak verip hisseleri olusturdum.
	
	this->Dizi = Dizi;
	this->yoketEmirler = &EmirlerYoket; //fonksiyon işaretçisinin neyi işaret ettiğini belirttim
	return this;
}

//satışlardan elde edilen kar/zararı yazdırmak ve toplam kar/zararı yazdırmak için yazdığım metod
void GetKarZarar(const Emirler this){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Emirler");
    int moons_count = cJSON_GetArraySize(moons);
    
	int i;
    for (i = 0; i < moons_count; i++){

        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolEmirler = cJSON_GetObjectItem(moon, "Sembol")->valuestring;
		char *islemEmirler = cJSON_GetObjectItem(moon, "Islem")->valuestring;
        int adetEmirler = cJSON_GetObjectItem(moon, "Adet")->valueint;
		
		double portfoyMaliyet = GetPortfoyMaliyet(this->superPortfoy, sembolEmirler); //portfoy yapımdaki fonksiyonu kullanarak portfoydeki maliyeti değişkene attım.
		double hisseFiyat = GetHisseFiyat(this->superHisseler, sembolEmirler); //Hisseler yapımdaki fonksiyonu kullanarak Hisse fiyatını değişkene attım.
		
		double toplamTutar = adetEmirler*hisseFiyat; //toplam tutarı değişkene attım
		double toplamMaliyet = adetEmirler*portfoyMaliyet; //toplam maliyeti değişkene attım
		
		double karZarar = toplamTutar-toplamMaliyet; //işlemden gelen toplam tutardan maliyeti cıkarıp kar/zarar hesabı için değişkene attım
		
		//SATIS işlemleri için yazdıgım şart bloğu.
		if(!strcmp(islemEmirler,"SATIS")){
			
			printf("\n%s için kar/zarar hesabı:\n",sembolEmirler);
			printf("%0.2f-%0.2f = %0.2f",toplamTutar,toplamMaliyet,karZarar);
			
			//satış sonucu kar mı zarar mı oldugunu belirten şart bloğum
			if(karZarar < 0)
				printf(" Zarar\n");
			else if(karZarar > 0)
				printf(" Kar\n");
		}
    }
	
	//Satışlar Kar/Zarar 'ı yazdırmak için döngü
	double toplamKarZarar=0;
	printf("\nSatışlar Kar/Zarar:\n");
	for(i = 0; i < moons_count; i++){
		
		cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolEmirler = cJSON_GetObjectItem(moon, "Sembol")->valuestring; //Sembolü aldım
		char *islemEmirler = cJSON_GetObjectItem(moon, "Islem")->valuestring; //yapılan işlemin türünü aldım
        int adetEmirler = cJSON_GetObjectItem(moon, "Adet")->valueint; //adeti aldım
		 
		double portfoyMaliyet = GetPortfoyMaliyet(this->superPortfoy, sembolEmirler);
		double hisseFiyat = GetHisseFiyat(this->superHisseler, sembolEmirler);
		
		double toplamTutar = adetEmirler*hisseFiyat;
		double toplamMaliyet = adetEmirler*portfoyMaliyet;
		
		double karZarar = toplamTutar-toplamMaliyet;
		
		if(!strcmp(islemEmirler,"SATIS")){
			toplamKarZarar = toplamKarZarar + karZarar;
			if(karZarar > 0)
				printf("%s : %0.2f TL Kar\n",sembolEmirler,karZarar);
			else if(karZarar < 0)
				printf("%s : %0.2f TL Zarar\n",sembolEmirler,karZarar);
		}
	}
	printf("Toplam Kar/Zarar : %0.2f TL",toplamKarZarar);
 
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);
	
}

//portfoyumde yaptıgım satış ve alış işlemlerindeki güncel fiyat,maliyet ve yeni maliyetini yazdırdıgım fonksiyon.
void GetEmirlerVeriler(const Emirler this){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Emirler");
    int moons_count = cJSON_GetArraySize(moons); // toplam satır sayısını aldım
    
	int i;
    for (i = 0; i < moons_count; i++){
        
        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolEmirler = cJSON_GetObjectItem(moon, "Sembol")->valuestring;
		char *islemEmirler = cJSON_GetObjectItem(moon, "Islem")->valuestring;
        int adetEmirler = cJSON_GetObjectItem(moon, "Adet")->valueint;
		
		double portfoyMaliyet = GetPortfoyMaliyet(this->superPortfoy, sembolEmirler);
		double hisseFiyat = GetHisseFiyat(this->superHisseler, sembolEmirler);
		
		int portfoyAdet = GetPortfoyAdet(this->superPortfoy, sembolEmirler);
		
		double toplamTutar = adetEmirler*hisseFiyat;
		double toplamMaliyet = adetEmirler*portfoyMaliyet;
		double yeniMaliyet = (portfoyAdet*portfoyMaliyet) + (adetEmirler*hisseFiyat);
		
		//emirlerdeki satıs ve alış işlemlerine uygun işlemleri birbirinden ayırmak için yazdığım şart bloğum
		if(!strcmp(islemEmirler,"SATIS")){
			printf("%s hissesi için satış :\n",sembolEmirler);
			
			printf("Güncel fiyat:%0.2f  ",hisseFiyat);
			printf("%dx%0.2f = %0.2f TL\n",adetEmirler,hisseFiyat,toplamTutar);
			
			printf("Maliyet:%0.2f ",portfoyMaliyet);
			printf("%dx%0.2f = %0.2f TL\n\n",adetEmirler,portfoyMaliyet,toplamMaliyet);
		}
		else if(!strcmp(islemEmirler,"ALIS")){
			printf("%s hissesi için alış :\n",sembolEmirler);
			
			printf("Güncel fiyat:%0.2f ",hisseFiyat);
			printf("%dx%0.2f = %0.2f TL\n",adetEmirler,hisseFiyat,toplamTutar);
			
			printf("Maliyet Hesabı: Önceden %d adet ve maliyeti %0.2f TL idi.\n",portfoyAdet,portfoyMaliyet);
			printf("Yeni maliyet %dx%0.2f+%dx%0.2f=%0.2f => 6572.5/750 = 8.76 TL olacaktır\n\n",portfoyAdet,portfoyMaliyet,adetEmirler,hisseFiyat,yeniMaliyet); 
		}
		
    }
 
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);
}

//portfoyumde satış ve alış işlemi yaptıgım hisseleri güncelleyerek yazmama yarayan fonksiyon
void GetGuncelPortfoy(const Emirler this){
	
	cJSON *root = cJSON_Parse(this->Dizi);
	cJSON *moons = cJSON_GetObjectItem(root, "Emirler");
    int moons_count = cJSON_GetArraySize(moons); // toplam satır sayısını aldım
    
	int i;
    for (i = 0; i < moons_count; i++){
		
        cJSON *moon = cJSON_GetArrayItem(moons, i); // dosyadaki değerleri indexe göre aldım
        char *sembolEmirler = cJSON_GetObjectItem(moon, "Sembol")->valuestring;
		char *islemEmirler = cJSON_GetObjectItem(moon, "Islem")->valuestring;
        int adetEmirler = cJSON_GetObjectItem(moon, "Adet")->valueint;
		
		double portfoyMaliyet = GetPortfoyMaliyet(this->superPortfoy, sembolEmirler);
		double hisseFiyat = GetHisseFiyat(this->superHisseler, sembolEmirler);
		
		int portfoyAdet = GetPortfoyAdet(this->superPortfoy, sembolEmirler);
		
		double toplamTutar = adetEmirler*hisseFiyat;
		double toplamMaliyet = adetEmirler*portfoyMaliyet;
		double yeniMaliyet = (portfoyAdet*portfoyMaliyet) + (adetEmirler*hisseFiyat);
		
		int kalanAdet = portfoyAdet-adetEmirler;
		int alisSonrasiAdet = portfoyAdet + adetEmirler;
		
		//eğer yaptıgım işlem "SATIS" ise gerçekleşecek durumları yazdıgım şart bloğu
		if(!strcmp(islemEmirler,"SATIS")){
			
			if(kalanAdet>0){
				printf("Hisse: %s\n",sembolEmirler);
				printf("Adet: %d\n",kalanAdet);
				printf("Maliyet: %0.2f\n\n",portfoyMaliyet);
			}

		}
		//eğer yaptıgım işlem "ALIS" ise gerçekleşecek durumları yazdıgım şart bloğu
		else if(!strcmp(islemEmirler,"ALIS")){	
			printf("Hisse: %s\n",sembolEmirler);
			printf("Adet: %d\n",alisSonrasiAdet);
			printf("Maliyet: %0.2f\n",portfoyMaliyet);

		}
    }
	
    // parçalayıp kullandıgım dosyanın ramde ayırdığı alanı sildim.
    cJSON_Delete(root);
}

void EmirlerYoket(Emirler this){
	if(this == NULL) return;
	this->superDosya->yoketDosya(this->superDosya); // bu yapıda dosya structını kullandıgım için çöpünü yok etme metodunu çağırdım
	this->superPortfoy->yoketPortfoy(this->superPortfoy); // bu yapıda portfoy structını kullandıgım için çöpünü yok etme metodunu çağırdım
	this->superHisseler->yoketHisseler(this->superHisseler); // bu yapıda hisseler structını kullandıgım için çöpünü yok etme metodunu çağırdım
	free(this); // Emirler yapısının çöpünü yok ettim.
}


