#ifndef grapher_h
#define grapher_h

typedef struct Node {
    int x;
    int y;
    struct Node* next;
} Node;

typedef struct Graph {
    int size;
    Node** adjacency_list;
} Graph;


Node* createNode(int x, int y);

Graph* createGraph(int size);

void addEdge(Graph* graph, int x1, int y1, int x2, int y2);

Graph* labirynth_to_graph(const char* filename);

void freeGraph(Graph* graph);


#endif
