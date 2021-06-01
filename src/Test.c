#include <stdio.h>
#include <windows.h>

#include "Banka.h"

int main(int argc, char **argv){
	SetConsoleOutputCP(65001);
	
	Banka banka = BankaOlustur();
	BankaBasla(banka);
	BankaYoket(banka);

	return 0;
}