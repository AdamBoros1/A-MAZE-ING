#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "grapher.h"
#include "pathfinder.h"
#include "fileoperator.h"
#include "pathsaver.h"
#include "preprocesor.h"


void displayHelp(){
	printf("\nUżycie: ./out -i (plik wejściowy) -o (plik wyjściowy) \n\n");

	printf("Ten program służy do rozwiązania problemu znajdowania ścieżki w wczytanym labiryncie. Pozwala użytkownikowi wczytać labirynt z pliku tekstowego, a następnie znajduje ścieżkę od punktu wejścia do punktu wyjścia. \n\n");
	printf("Program generuje także listę kroków (w podanym pliku tekstowym lub na stdout), które należy wykonać, aby przejść przez labirynt.\n\n");
}

int main(int argc, char** argv){
    char* input = NULL;
    char* output = "stdout";

    // Użycie getopt do analizy argumentów 
    int opt;
    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
            case 'i':
                input = optarg;
                break;
            case 'o':
                output = optarg;
                break;
			 case 'h':
                displayHelp();
				return 1;
                break;
            default: 
                fprintf(stderr, "Użycie: %s -i (plik wejściowy) -o (plik wyjściowy)\n", argv[0]);
				return -1;
		}
    }


	
	if(input == NULL){
		printf("Nie podano pliku wejściowego\n");
		return 1;
	}
	//Sprawdzenie, czy plik wyjściowy jest binarny czy tekstowy
	int binary_output = 0;
	if(strstr(output, ".bin") != NULL){
			binary_output = 1;
	}
	//Dalej poddaliśmy się z czytaniem pliku binarnego


	//Obsługa pliku wejściowego w formacie tekstowym
	Point_t maze_size, start, end;
	int start_dir; 
	int maze_flag = mazeToTxt(input, &maze_size, &start, &end, &start_dir);
	
	if(maze_flag == 1){
		printf("Nie można otworzyć pliku wejściowego\n");
		return 1;
	}
	else if(maze_flag == -1){
		printf("Użyto niepoprawnych znaków w labiryncie!\n");
		return 1;
	}
	
	int start_node = mapToNode(start, maze_size);
	int end_node = mapToNode(end, maze_size);
	Point_t full_size = {(maze_size.x-1)/2, (maze_size.y-1)/2};



	// Tworzenie grafu na podstawie labiryntu i zapisanie go w pliku "graph.bin" 
	graphToBin(input, full_size);
	

	// Przechodzenie przez labirynt i zapisywanie ścieżki
	int path;
	path = navigate(start_node, end_node, full_size);
	if(path){
		printf("Brak ścieżki w labiryncie\n");
		return 1;
	}
	

	// Wyświetlanie rozwiązania
	int	output_flag = pathToTxt(output, start_node, end_node, full_size, start_dir);

	if(output_flag == 1){
		printf("Nie mogę utworzyć pliku wyjściowego\n");
		return 1;
	}

	// Usuwanie plików tymczasowych
	char* TEMPS[] = {"graph.bin", "master.bin", "path.bin"};
	deleteTemps(TEMPS, 3);
	
	return 0;
}
