#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "grapher.h"
#include "fileoperator.h"
#include "pathsaver.h"
#include "preprocesor.h"
#include "queue.h"


#define INTERNAL_QUEUE_SIZE 1000
#define EXTERNAL_QUEUE_SIZE 1048576

void loadParent(int** parent, int* min_parent, int* max_parent, int crt, int n_nodes, int HELD_PARENTS){
		if (crt < *min_parent || crt >= *max_parent){
			*min_parent = max(0, crt - HELD_PARENTS / 2);
			*max_parent = min(n_nodes, *min_parent + HELD_PARENTS);
			
			free(*parent);
			
			*parent = readVector("master.bin", *min_parent, *max_parent - *min_parent);
		}
}

void loadGraph(int** graph, int* min_node, int* max_node, int crt, int n_nodes, int HELD_NODES){
		if (crt < *min_node || crt >= *max_node){
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

    return 1; 
}

