#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grapher.h"
#include "preprocesor.h"
#include "fileoperator.h"

// Funkcja odwracająca ścieżkę w grafie od węzła końcowego do początkowego
int reversePath(int start_node, int end_node, Point_t full_size){
    int crt = end_node;
    int read;
	 
    initVector("path.bin", full_size.x * full_size.y, -1); // Inicjalizacja pliku binarnego do przechowywania ścieżki
	
    // Przepisanie ścieżki do pliku binarnego
    int node_cnt = 0;
    while(crt != start_node){
        read = readPosition("master.bin", crt);
		 
        updateVector("path.bin", node_cnt, crt);
		
        crt = read;
        node_cnt++;
    }
    updateVector("path.bin", node_cnt, crt);

    return node_cnt;
}

// Funkcja zapisująca znalezioną ścieżkę do pliku tekstowego
int pathToTxt(char* output_filename, int start_node, int end_node, Point_t full_size, int start_dir){
    int node_cnt = reversePath(start_node, end_node, full_size);	
	
    FILE* output;
    if(strstr(output_filename, "stdout") == NULL)
        output = fopen(output_filename, "ab");
    else
        output = stdout;
    if(output == NULL)
        return 1;

    int x, y, prev_x, prev_y, steps = 0;
    Point_t dir;
    int dir_index, prev_dir_index;
    char turn[20];
	
    // Zapisanie komunikatu "START" na początku pliku lub na standardowym wyjściu
    fprintf(output, "START\n");
	
    // Zapisanie ścieżki w postaci kroków do pliku path.txt
    int crt = readPosition("path.bin", node_cnt);
    prev_x = crt % full_size.x;
    prev_y = crt / full_size.x;
    node_cnt--;

    if(start_dir)
        prev_dir_index = 2;
    else
        prev_dir_index = 3;
    while(node_cnt >= 0){
        crt = readPosition("path.bin", node_cnt);
        // Obliczenie koordynatów danego wierzchołka
        x = crt % full_size.x; 
        y = crt / full_size.x;
		
        // Obliczenie wektora przesunięcia na podstawie pozycji aktualnej i poprzedniej
        dir.x = x - prev_x;
        dir.y = y - prev_y;
		
        dir_index = getDirection(dir); // Sprawdzenie indeksu wektora przesunięcia
		
        // Jeśli kierunek ten sam co poprzednio, zwiększenie liczby kroków
        if(prev_dir_index == dir_index)
            steps++;
        else{
            // W przeciwnym wypadku sprawdzenie kierunku skrętu i wypisanie liczby kroków
            if(dir_index - prev_dir_index == 1 || dir_index - prev_dir_index == -3)
                strcpy(turn, "TURNRIGHT");
            else
                strcpy(turn, "TURNLEFT");
			
            if(steps > 0)
                fprintf(output, "FORWARD %d\n%s\n", steps, turn);
            else
                fprintf(output, "%s\n", turn);

            steps = 1;
        }

        prev_dir_index = dir_index;
        prev_x = x;
        prev_y = y;

        node_cnt--;
    }

    // Wypisanie ostatniej prostej
    fprintf(output, "FORWARD %d\n", steps);

    // Zapisanie komunikatu "STOP" na końcu pliku lub na standardowym wyjściu
    fprintf(output, "STOP\n");

    fclose(output);

    return 0;
}

