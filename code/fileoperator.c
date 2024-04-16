#include <stdlib.h>
#include <stdio.h>

//inicjalizacja wektora przechowywanego w pliku binarnym o wielkosci size i wartosciach value
void initVector(char* filename, int size, int value){
	FILE* file = fopen(filename, "wb");
	if(file == NULL){
		printf("Nie moge otworzyc pliku %s\n", filename);
		exit(EXIT_FAILURE);
	}
	
	for(int i =  0; i < size; i++)
		fwrite(&value, sizeof(int), 1, file);
	
	fclose(file);
}

// wczytanie do wektora danych z pliku binarnego od indeksu  offset w liczbie size 
int* readVector(char* filename, int offset, int size) {
    FILE* f = fopen(filename, "rb");
	if(f == NULL){
		printf("Nie moge otworzyc pliku %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(f, offset*sizeof(int), SEEK_SET);
     
	int* vec = malloc(sizeof(int) * (size));
	if(fread(vec, sizeof(int), size, f) != size){
		printf("Nie moge czytac indeksow %d-%d pliku %s\n", offset, offset+size, filename);
		fclose(f);
		free(vec);
		exit(EXIT_FAILURE);
	}

    fclose(f);
    return vec;
}

// wczytanie pozycji z pliku binarnego 
int readPosition(char* filename, int offset){
	FILE* file = fopen(filename, "rb");
	if(file == NULL){
		printf("Nie moge otworzyc pliku %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(file, offset*sizeof(int), SEEK_SET);
	
	int value;
	if(fread(&value, sizeof(int), 1, file) != 1){
		printf("Nie moge czytac indeksu %d pliku %s\n", offset, filename);
		fclose(file);
		exit(EXIT_FAILURE);
	}

    fclose(file);
    return value;
}

// zamiana pozycji offset na wartosc value w pliku binarnym 
void updateVector(char* filename, int offset, int value){
	FILE* file = fopen(filename, "r+b");
	if(file == NULL){
		printf("Nie moge otworzyc pliku %s\n", filename);
		exit(EXIT_FAILURE);
	}
	fseek(file, offset*sizeof(int), SEEK_SET);
	
	if(fwrite(&value, sizeof(int), 1, file) != 1){
		printf("Nie moge pisac do indeksu %d pliku %s\n", offset, filename);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	fclose(file);
}

//usuniecie plikow tymczasowych 
void deleteTemps(char** temp_files, int n_files){
	for(int i = 0; i < n_files; i++){
		if(remove(temp_files[i]) != 0){
			fprintf(stderr, "Nie moge usunac pliku %s\n", temp_files[i]);
			exit(EXIT_FAILURE);
		}
	}
}