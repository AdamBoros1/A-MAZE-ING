#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grapher.h"
#include "fileoperator.h"

// Funkcja znajdująca liczbę kolumn i wierszy
// reprezentujących labirynt w pliku .txt
int mazeToTxt(char* filename, Point_t* maze_size, Point_t* start, Point_t* end, int* start_dir){
    FILE* f = fopen(filename, "r");
    if(f == NULL){
        fprintf(stderr, "Nie mogę czytać pliku %s\n", filename);
        return 1;
    }
	
    // Znalezienie rozmiaru pliku
    int c;
    int x = 0, y = 0;
    int row_len_found = 0;
    while((c = fgetc(f)) != EOF){
        if(c != '\n' && c != 'X' && c != ' ' && c != 'P' && c != 'K')
            return -1; 

        if(c == '\n' && !row_len_found){
            maze_size->x = x;
            row_len_found = 1;
        }
        if(c == '\n'){
            y += 1;
        }
        x += 1;
    }
    maze_size->y = y + 1;
	
    // Znalezienie wejścia i wyjścia
    x = 0, y = 0;
    fseek(f, 0, SEEK_SET);
    while((c = fgetc(f)) != EOF){
        if((x == 0 || y == 0) && c == 'P'){
            if(x == 0)
                *start_dir = 1;
            else
                *start_dir = 0;
            start->x = x;
            start->y = y;
        }
        if((x == maze_size->x - 1 || y == maze_size->y - 1) && c == 'K'){
            end->x = x;
            end->y = y;
        }

        x += 1;
        if(c == '\n'){
            y += 1;
            x = 0;
        }
    }
	
    fclose(f);

    return 0;
}