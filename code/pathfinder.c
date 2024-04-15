#include <stdio.h>
#include <stdlib.h>
#include <pathfinder.h>

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

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (QueueNode*)malloc(queue->capacity * sizeof(QueueNode));
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, QueueNode item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size += 1;
}

QueueNode dequeue(Queue* queue) {
    QueueNode item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size -= 1;
    return item;
}

int isValid(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

int isDestination(Point pt, Point dest) {
    return (pt.row == dest.row && pt.col == dest.col);
}

int BFS(char maze[ROWS][COLS], Point src, Point dest) {
    if (!isValid(src.row, src.col) || !isValid(dest.row, dest.col)) {
        return -1;
    }

    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    int visited[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            visited[i][j] = 0;
        }
    }

    visited[src.row][src.col] = 1;

    Queue* queue = createQueue(ROWS * COLS);

    QueueNode srcNode = {{src.row, src.col}, 0};
    enqueue(queue, srcNode);

    while (!isEmpty(queue)) {
        QueueNode current = dequeue(queue);
        Point pt = current.parent;

        if (isDestination(pt, dest)) {
            free(queue);
            return current.distance;
        }

        for (int i = 0; i < 4; i++) {
            int row = pt.row + rowNum[i];
            int col = pt.col + colNum[i];

            if (isValid(row, col) && maze[row][col] != 'X' && !visited[row][col]) {
                visited[row][col] = 1;
                QueueNode adjacentNode = {{row, col}, current.distance + 1};
                enqueue(queue, adjacentNode);
            }
        }
    }

    free(queue);
    return -1;
}