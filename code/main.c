#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "pathfinder.h"

void displayHelp(){
	printf("\nUżycie: ./out -i (plik wejsciowy) -o (plik wyjsciowy) \n\n");

	printf("Program jest używany do rozwiązania problemu znalezienia ścieżki we wczytanym labiryncie. Umożliwia użytkownikowi wczytanie labiryntu z pliku tekstowego, a następnie znajduje ścieżkę od punktu wejścia do punktu wyjścia. \n\n");
	printf("Program generuje także listę kroków (w podanym pliku tesktowym lub na stdout), które należy wykonać, aby przejść przez labirynt.\n\n");
}


int main(int argc, char** argv){
    char* input = NULL;
    char* output = "stdout";
 
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
                fprintf(stderr, "Uzycie: %s -i (plik wejsciowy) -o (plik wyjsciowy)\n", argv[0]);
				return -1;
		    }
    }


	
	if(input == NULL){
		printf("nie podano pliku wejsciowego\n");
		return 1;
	}
	
	int binary_output = 0;
	if(strstr(output, ".bin") != NULL){
			binary_output = 1;
	}
	
	return 0;
}
