#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void displayHelp(){
	printf("\nUżycie: ./out [plik_z_labiryntem] [dodatkowy_argumemnt] \n\n");

	printf("Program jest używany do rozwiązania problemu znalezienia ścieżki we wczytanym labiryncie. Umożliwia użytkownikowi wczytanie labiryntu z pliku tekstowego, a następnie znajduje ścieżkę od punktu wejścia do punktu wyjścia. \n\n");
	printf("Program generuje także listę kroków, które należy wykonać, aby przejść przez labirynt. Ostatecznie, program jest przeznaczony dla osób poszukujących efektywnego rozwiązania problemu nawigacji przez labirynt.\n\n");	
	
	printf("Możliwe dodatkowe argumenty: \n");
	printf("-s, --shortest: Określa, że użytkownik chce znaleźć najkrótszą ścieżkę przez labirynt.\n");
	printf("-l, --longest: Wskazuje, że użytkownik poszukuje najdłuższej możliwej ścieżki w labiryncie.\n");
	printf("-a, --all: Wyszukuje i wyświetla wszystkie możliwe ścieżki, nie tylko jedną.\n");
	printf("-r, --random: Wybiera losową ścieżkę z dostępnych możliwości.\n");
	printf("-t, --time: Pomiar czasu działania programu od wczytania do znalezienia ścieżki.\n");
	printf("-d, --details: Wyświetla dodatkowe szczegóły dotyczące procesu znajdowania ścieżki.\n");
	printf("-c, --count: Liczy liczbę kroków potrzebnych do przejścia przez znalezioną ścieżkę.\n");
	printf("-f, --file <output_file>: Zapisuje znalezioną ścieżkę do pliku tekstowego o podanej nazwie.\n\n");
}

int main(int argc, char *argv[]){
	for (int i = 1; i < argc; i++) {
           if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
              displayHelp();
              exit(EXIT_SUCCESS);
           }
    	}

	printf("Użyj -h aby sprawdzić opcje programu\n");

	return 0;
}
