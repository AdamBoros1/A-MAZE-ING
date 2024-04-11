#ifndef PATHFINDER_H
#define PATHFINDER_H

#define ROWS 11
#define COLS 11

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    Point parent;
    int distance;
} QueueNode;

typedef struct {
    QueueNode *array;
    int front, rear, size;
    unsigned capacity;
} Queue;

Queue* createQueue(unsigned capacity);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, QueueNode item);
QueueNode dequeue(Queue* queue);
int isValid(int row, int col);
int isDestination(Point pt, Point dest);
int BFS(char maze[ROWS][COLS], Point src, Point dest);

#endif