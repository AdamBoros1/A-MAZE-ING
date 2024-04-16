#ifndef grapherh
#define grapherh

typedef struct{
	int x;
	int y;
} Point_t;



int mapToNode(Point_t, Point_t);

int getDirection(Point_t);

void graphToBin(char*, Point_t);

int max(int, int);

int min(int, int);

#endif
