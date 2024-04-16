#include<stdlib.h>
#include<stdio.h>

#include "grapher.h"
#include "consts.h"


int mapToNode(point_t coords, point_t lab_size) {
    int x = coords.x;
	int y = coords.y;

    if (coords.x == 0) x++;
    else if (coords.y == 0) y++;
    else if (coords.x == lab_size.x - 1) x--;
    else if (coords.y == lab_size.y - 1) y--;

    int node = (x - 1) / 2 + (y - 1) / 2 * ((lab_size.x - 1) / 2);

    return node;
}


int getDirection(point_t dir) {
    switch (dir.x) {
        case -1:
            return 0;
        case 1:
            return 2;
    }

    switch (dir.y) {
        case -1:
            return 1;
        case 1:
            return 3;
    }
}
