#include<stdlib.h>
#include<stdio.h>

#include "grapher.h"
#include "fileoperator.h"
#include "pathsaver.h"
#include "preprocesor.h"



// Konwertuje plik tekstowy reprezentujący labirynt na plik binarny
// zawierający reprezentację grafu labiryntu.
// Parametry:
// - input_file: nazwa pliku wejściowego z reprezentacją labiryntu
// - size: rozmiar labiryntu (liczba wierzchołków w jednym wymiarze)
void graphToBin(char* input_file, Point_t size){
    // Inicjalizacja wektora w pliku binarnym "graph.bin" 
    // z wartościami początkowymi -1 (brak krawędzi między wierzchołkami)
    int n_nodes = size.x * size.y;
    initVector("graph.bin", 4 * n_nodes, -1);
	
    // Rozmiar labiryntu w postaci Point_t (liczba wierzchołków w obu wymiarach)
    Point_t maze_size = {size.x * 2 + 1, size.y * 2 + 1};
	
    // Otwarcie pliku wejściowego
    FILE* f = fopen(input_file, "r");
	
    // Zmienna pomocnicza do iteracji po labiryncie
    int i = 0;
    Point_t crt;
    char c;
    int node;
    while(i < maze_size.x * maze_size.y){
        // Współrzędne aktualnie przetwarzanego wierzchołka
        crt.y = i / maze_size.x;
        crt.x = i % maze_size.x;
		
        // Odczyt znaku z pliku wejściowego
        c = fgetc(f);
        if(c == '\n')
            continue;
		
        // Obsługa wierzchołków reprezentujących ściany pionowe
        if(crt.y % 2 == 1 && crt.x % 2 == 0 && c == ' '){
            if (crt.x > 0){
                // Wyznaczenie indeksu wierzchołka leżącego na lewo od aktualnego
                node = size.x * (crt.y - 1) / 2 + (crt.x - 2) / 2;
                // Aktualizacja wektora grafu, dodanie krawędzi do sąsiada z lewej strony
                updateVector("graph.bin", node * 4 + 1, node + 1);
            }
            if (crt.x < maze_size.x){
                // Wyznaczenie indeksu wierzchołka leżącego na prawo od aktualnego
                node = size.x * (crt.y - 1) / 2 + (crt.x) / 2;
                // Aktualizacja wektora grafu, dodanie krawędzi do sąsiada z prawej strony
                updateVector("graph.bin", node * 4, node - 1);
            }
        }
        // Obsługa wierzchołków reprezentujących ściany poziome
        if(crt.y % 2 == 0 && crt.x % 2 == 1 && c == ' '){
            if (crt.y > 0){
                // Wyznaczenie indeksu wierzchołka leżącego nad aktualnym
                node = size.x * (crt.y - 2) / 2 + (crt.x - 1) / 2;
                // Aktualizacja wektora grafu, dodanie krawędzi do sąsiada z góry
                updateVector("graph.bin", node * 4 + 3, node + size.x);
            }
            if (crt.y < maze_size.y){
                // Wyznaczenie indeksu wierzchołka leżącego pod aktualnym
                node = size.x * (crt.y) / 2 + (crt.x - 1) / 2;
                // Aktualizacja wektora grafu, dodanie krawędzi do sąsiada z dołu
                updateVector("graph.bin", node * 4 + 2, node - size.x);
            }
        }
        i++;
    }
    // Zamknięcie pliku wejściowego
    fclose(f);
}

// Mapuje współrzędne punktu na indeks wierzchołka w grafie.
// Wierzchołki labiryntu mają przypisane indeksy według schematu:
// - Wierzchołki brzegowe labiryntu mają indeksy dodatnie.
// - Wierzchołki wewnętrzne labiryntu mają indeksy nieujemne.
// Parametry:
// - coords: współrzędne punktu, który ma być zmapowany
// - maze_size: rozmiar labiryntu w postaci Point_t (liczba wierzchołków w obu wymiarach)
// Zwraca:
// Indeks wierzchołka w grafie reprezentującym labirynt
int mapToNode(Point_t coords, Point_t maze_size) {
    int x = coords.x;
    int y = coords.y;

    // Jeśli współrzędna x jest równa 0 lub maze_size.x - 1, to punkt znajduje się na krawędzi labiryntu
    if (coords.x == 0) x++;
    else if (coords.x == maze_size.x - 1) x--;

    // Jeśli współrzędna y jest równa 0 lub maze_size.y - 1, to punkt znajduje się na krawędzi labiryntu
    if (coords.y == 0) y++;
    else if (coords.y == maze_size.y - 1) y--;

    // Wyznaczenie indeksu wierzchołka na podstawie przeskalowanych współrzędnych
    int node = (x - 1) / 2 + (y - 1) / 2 * ((maze_size.x - 1) / 2);

    return node;
}



int getDirection(Point_t dir) {
    switch (dir.x) {
        case -1:
            return 0; // Lewo
        case 1:
            return 2; // Prawo
    }

    switch (dir.y) {
        case -1:
            return 1; // Góra
        case 1:
            return 3; // Dół
    }

    // Jeśli żaden z warunków nie został spełniony, zwracamy -1 jako wartość domyślną
    return -1; // Brak kierunku
}



int max(int a, int b){
	if(a > b)
		return a;
	return b;
}

int min(int a, int b){
	if(a < b)
		return a;
	return b;
}