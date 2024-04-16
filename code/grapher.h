#ifndef grapher_h
#define grapher_h

typedef struct{
	int x;
	int y;
} point_t;


int mapToNode(point_t, point_t);

int getDirection(point_t);

#endif
