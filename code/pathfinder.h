#ifndef pathfinderh
#define pathfinderh

#include "grapher.h"
#include "fileoperator.h"
#include "pathsaver.h"
#include "preprocesor.h"

// Struktura zawierająca informacje o elemencie kolejki
typedef struct node {
    int value;
    struct node* next;
} node_t;

// Struktura kolejki
typedef struct {
    int internal_size;      
    int external_size;      
    int internal_capacity;  
    int external_capacity;  
    int external_offset;    
    node_t* top;
} Queue_t;

// Inicjalizacja kolejki
Queue_t* init_queue(int internal_capacity, int external_capacity);

// Dodawanie elementu do kolejki
void push(Queue_t* queue, int value);

// Usuwanie elementu z kolejki
int pop(Queue_t* queue);

// Wyświetlanie kolejki (do debugowania)
void display(Queue_t* queue);

// Niszczenie kolejki i zwalnianie pamięci
void destroy_queue(Queue_t* queue);

// Funkcja wczytująca dane rodzica
void loadParent(int** parent, int* min_parent, int* max_parent, int crt, int n_nodes, int HELD_PARENTS);

// Funkcja wczytująca graf
void loadGraph(int** graph, int* min_node, int* max_node, int crt, int n_nodes, int HELD_NODES);

// Funkcja przechodząca po labiryncie działająca na zasadzie BFS
int navigate(int start, int end, Point_t size);

#endif 
