#ifndef MAP_H
#define MAP_H

/* Reads the map file and stores it into a dynamically 2D array */
int** loadMap(char* filename, int* rows, int* cols); 

/* Frees the dynamically allocated 2D map array */
void freeMap(int** map, int rows); 

#endif
