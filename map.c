#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/*
 * loadMap
 * Opens the file, reads map size and contents
 * and allocates memory dynamically for 2D array
 */

int** loadMap(char* filename, int* rows, int* cols)
{
	FILE* file;
	int** map;
	int i, j;
	
	/* attempt to open file */
	file = fopen(filename, "r"); 
	
	if(file == NULL)
	{
		printf("Error: Cannot open file\n");
		return NULL;
	}
	
	/* read map dimensions */
	fscanf(file, "%d %d", rows, cols); 
	
	/* allocate memory for rows */
	map = (int**)malloc((*rows) * sizeof(int*));  
	
	/* allocate memory for each row (columns) */
	for(i = 0; i < *rows; i++) 
	{
		map[i] = (int*)malloc((*cols)* sizeof(int));
	}

	/* read map values into 2D array */
	for(i = 0; i< *rows; i++) 
	{
		for(j = 0; j< *cols; j++)
		{
			fscanf(file, "%d" , &map[i][j]);
		}
	}

	fclose(file);

	return map;
}

/*
 * freeMap
 * Frees all allocated memory for the 2D map
 */

void freeMap(int** map, int rows)
{
	int i;
	
	/* free each row */
	for(i = 0; i < rows; i++) 
	{
		free(map[i]);
	}

	/* free main pointer */
	free(map); 
}


