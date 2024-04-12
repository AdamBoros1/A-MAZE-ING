#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grapher.h"

// Funkcja tworząca nowy wierzchołek
Node* createNode(int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

// Funkcja tworząca nowy graf
Graph* createGraph(int size) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = size;
    graph->adjacency_list = (Node**)malloc(size * sizeof(Node*));
    for (int i = 0; i < size; ++i) {
        graph->adjacency_list[i] = NULL;
    }
    return graph;
}

// Funkcja dodająca krawędź do grafu
void addEdge(Graph* graph, int x1, int y1, int x2, int y2) {
    int index = y1 * graph->size + x1;
    Node* newNode = createNode(x2, y2);
    newNode->next = graph->adjacency_list[index];
    graph->adjacency_list[index] = newNode;
}

// Funkcja wczytująca labirynt z pliku i przekształcająca go na graf
Graph* labirynth_to_graph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Błąd podczas otwierania pliku.\n");
        exit(EXIT_FAILURE);
    }

    // Zliczanie liczby wierszy i kolumn w labiryncie
    int rows = 0, cols = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            ++rows;
        } else if (rows == 0 && ch != '\r') {
            ++cols;
        }
    }
    rewind(file);

    // Tworzenie grafu
    Graph* graph = createGraph(rows * cols);

    // Wczytywanie labiryntu i tworzenie krawędzi w grafie
    int x = 0, y = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            ++y;
            x = 0;
        } else if (ch != '\r') {
            if (ch == ' ' || ch == 'P') {
                // Dodawanie krawędzi do wolnych pól (spacja lub P)
                if (x > 0 && (x - 1) < cols && (y) < rows && (x - 1) >= 0 && (y) >= 0 && (y * cols + x - 1) < (rows * cols))
                    addEdge(graph, x, y, x - 1, y);
                if (x < cols && (x + 1) < cols && (y) < rows && (x + 1) >= 0 && (y) >= 0 && (y * cols + x + 1) < (rows * cols))
                    addEdge(graph, x, y, x + 1, y);
                if (y > 0 && (x) < cols && (y - 1) < rows && (x) >= 0 && (y - 1) >= 0 && ((y - 1) * cols + x) < (rows * cols))
                    addEdge(graph, x, y, x, y - 1);
                if (y < rows && (x) < cols && (y + 1) < rows && (x) >= 0 && (y + 1) >= 0 && ((y + 1) * cols + x) < (rows * cols))
                    addEdge(graph, x, y, x, y + 1);
            }
            ++x;
        }
    }

    fclose(file);
    return graph;
}

// Funkcja zwalniająca pamięć po grafie
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->size; ++i) {
        Node* current = graph->adjacency_list[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjacency_list);
    free(graph);
}

int main() {
    Graph* graph = labirynth_to_graph("maze.txt");

    // Wyświetlenie listy incydencji
    for (int i = 0; i < graph->size; ++i) {
        printf("(%d,%d): ", i % (graph->size / 2), i / (graph->size / 2));
        Node* current = graph->adjacency_list[i];
        while (current != NULL) {
            printf("(%d,%d) ", current->x, current->y);
            current = current->next;
        }
        printf("\n");
    }

    // Zwolnienie pamięci po grafie
    freeGraph(graph);

    return 0;
}
