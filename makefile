hepsi:derle calistir

derle:
	gcc -I ./include/ -o ./lib/cJSON.o -c ./src/cJSON.c 
	gcc -I ./include/ -o ./lib/Dosya.o -c ./src/Dosya.c 
	gcc -I ./include/ -o ./lib/Portfoy.o -c ./src/Portfoy.c 
	gcc -I ./include/ -o ./lib/Emirler.o -c ./src/Emirler.c 
	gcc -I ./include/ -o ./lib/Hisseler.o -c ./src/Hisseler.c 
	gcc -I ./include/ -o ./lib/Banka.o -c ./src/Banka.c 
	gcc -I ./include/ -o ./bin/Test ./lib/cJSON.o ./lib/Dosya.o ./lib/Portfoy.o ./lib/Emirler.o ./lib/Hisseler.o ./lib/Banka.o ./src/Test.c
calistir:
	./bin/Test