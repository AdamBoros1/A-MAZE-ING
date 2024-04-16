#ifndef pathfinderh
#define pathfinderh

#include "grapher.h"

#define MAX_SIZE 100

int navigate(int, int, Point_t);

void loadParent(int** parent, int* min_parent, int* max_parent, int crt, int n_nodes, int HELD_PARENTS);

void loadGraph(int** graph, int* min_node, int* max_node, int crt, int n_nodes, int HELD_NODES);

#endif
