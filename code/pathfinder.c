#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grapher.h"
#include "fileoperator.h"
#include "pathsaver.h"
#include "preprocesor.h"

#define INTERNAL_QUEUE_SIZE 1000
#define EXTERNAL_QUEUE_SIZE 1048576

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
Queue_t* init_queue(int internal_capacity, int external_capacity) {
    Queue_t* queue = (Queue_t*)malloc(sizeof(Queue_t));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation failed for queue.\n");
        exit(EXIT_FAILURE);
    }
    queue->internal_size = 0;
    queue->external_size = 0;
    queue->internal_capacity = internal_capacity;
    queue->external_capacity = external_capacity;
    queue->external_offset = 0;
    queue->top = NULL;
    return queue;
}

// Dodawanie elementu do kolejki
void push(Queue_t* queue, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    if (queue->top == NULL) {
        queue->top = new_node;
    } else {
        node_t* current = queue->top;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    queue->internal_size++;
}

// Usuwanie elementu z kolejki
int pop(Queue_t* queue) {
    if (queue->top == NULL) {
        fprintf(stderr, "Queue is empty.\n");
        exit(EXIT_FAILURE);
    }
    node_t* temp = queue->top;
    int value = temp->value;
    queue->top = temp->next;
    free(temp);
    queue->internal_size--;
    return value;
}

// Wyświetlanie kolejki (do debugowania)
void display(Queue_t* queue) {
    node_t* current = queue->top;
    printf("Queue elements: ");
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

// Niszczenie kolejki i zwalnianie pamięci
void destroy_queue(Queue_t* queue) {
    while (queue->top != NULL) {
        node_t* temp = queue->top;
        queue->top = queue->top->next;
        free(temp);
    }
    free(queue);
}

// Funkcja wczytująca dane rodzica
void loadParent(int** parent, int* min_parent, int* max_parent, int crt, int n_nodes, int HELD_PARENTS) {
    if (crt < *min_parent || crt >= *max_parent) {
        *min_parent = max(0, crt - HELD_PARENTS / 2);
        *max_parent = min(n_nodes, *min_parent + HELD_PARENTS);
        free(*parent);
        *parent = readVector("master.bin", *min_parent, *max_parent - *min_parent);
    }
}

// Funkcja wczytująca graf
void loadGraph(int** graph, int* min_node, int* max_node, int crt, int n_nodes, int HELD_NODES) {
    if (crt < *min_node || crt >= *max_node) {
        *min_node = max(0, crt - HELD_NODES / 2);
        *max_node = min(*min_node + HELD_NODES, n_nodes);
        free(*graph);
        *graph = readVector("graph.bin", 4 * (*min_node), (*max_node - *min_node) * 4);
    }
}

// Funkcja przechodząca po labiryncie działająca na zasadzie BFS
int navigate(int start, int end, Point_t size) {
    int totalNodes = size.x * size.y;
    int parentsLimit = 60000; 
    int nodesLimit = 60000; 
    if (totalNodes < start + parentsLimit)
        parentsLimit = totalNodes - start; 
    if (totalNodes < start + nodesLimit)
        nodesLimit = totalNodes - start; 
    int minNode = start, maxNode = nodesLimit; 
    int minParent = start, maxParent = parentsLimit; 
    
    Queue_t* queue = init_queue(INTERNAL_QUEUE_SIZE, EXTERNAL_QUEUE_SIZE); 

    int currentNode = start, nextNode;
    int EMPTY = size.x * size.y + 1; 

    initVector("master.bin", totalNodes, EMPTY); 
    updateVector("master.bin", currentNode, currentNode);	 
    push(queue, currentNode); 
	
    int* parent = readVector("master.bin", currentNode, parentsLimit); 
    int* graph = readVector("graph.bin", currentNode * 4, 4 * nodesLimit); 
    while (queue->internal_size > 0) {
        currentNode = pop(queue); 

        if (currentNode == end) { 
            free(graph);
            free(parent);
            destroy_queue(queue);
            return 0;
        }

        loadGraph(&graph, &minNode, &maxNode, currentNode, totalNodes, nodesLimit); 
		
        for (int i = 0; i < 4; i++) {
            if (graph[(currentNode - minNode) * 4 + i] != -1) {
                nextNode = graph[(currentNode - minNode) * 4 + i];
                
                loadParent(&parent, &minParent, &maxParent, nextNode, totalNodes, parentsLimit); 
                
                if (parent[nextNode - minParent] == EMPTY) {
                    updateVector("master.bin", nextNode, currentNode); 
                    parent[nextNode - minParent] = currentNode;
                    push(queue, nextNode); 
                }
            }
        }
    }

    free(graph);
    free(parent);
    destroy_queue(queue);

    return 1; 
}

