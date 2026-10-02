#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "color.h"
#include "random.h"

/* 
 * printMap
 * Converts integer map into visual characters and print it with borders
 */
void printMap(int** map, int rows, int cols, int enemyDirection, int furiousMode)
{
        int i, j;

        /* print top border */
        for(j = 0; j < cols + 2; j++)
        {
                printf("*");
        }
        printf("\n");

        /* print map content */
        for(i = 0; i < rows; i++)
        {
                printf("*"); /* left border */

                for(j = 0; j < cols; j++)
                {
                        if(map[i][j] == 0)
			{
                                printf(" "); /* Empty space */
			}
                        if(map[i][j] == 1)
			{
                                setBackground("white");
				printf(" "); /* Wall */
				setBackground("reset");
			}
                        if(map[i][j] == 2)
			{
                                setForeground("green");
				printf("G"); /* Goal */
				setForeground("reset");
			}
                        if(map[i][j] == 3)
			{
				setForeground("yellow");
                                printf("T"); /* Treasure */
				setForeground("reset");
			}
                        if(map[i][j] == 4)
			{
				setForeground("blue");
                                printf("P"); /* Player */
				setForeground("reset");
			}
                	
			if(map[i][j] == 5)
			{
				if(furiousMode == 1)
    				{
        				setBackground("red");
        				setForeground("white");
    				}
    				else
    				{
        				setForeground("red");
    				}

    				if(enemyDirection == 0)
    				{
        				printf("^");
    				}
    				else if(enemyDirection == 1)
    				{
        				printf(">");
    				}
    				else if(enemyDirection == 2)
    				{
        				printf("v");
    				}
    				else
    				{
        				printf("<");
    				}

    				if(furiousMode == 1)
    				{
        				setBackground("reset");
        				setForeground("reset");
    				}
    				else
    				{
        			setForeground("reset");
    				}
			}
		}

        printf("*"); /* right border */
        printf("\n");
        }

        /* print bottom border */
        for(j = 0; j < cols + 2; j++)
        {
                printf("*");
        }

        printf("\n");
}

/* 
 * findPlayer
 * Search the entire map to locate the Player (value = 4)
 * When found, it will store the position into pr (row) and pc (column)
 * Cannot return two values so use pointer 
 */

void findPlayer(int **map, int rows, int cols, int*  pr, int* pc)
{
	int i, j;

	/* loop through every cells in the map */
	for(i = 0; i < rows; i++)
 	{
		for(j = 0; j < cols; j++)
		{
			/* check current cell is Player */
			if(map[i][j] == 4)
			{
				/* store player position using pointer */
				*pr = i;
				*pc = j;
			}
		}
	}

}


/*
 * findEnemy
 * Finds the current position of the Enemy
 */

void findEnemy(int** map, int rows, int cols, int* er, int* ec)
{
	int i, j;
	
	for(i = 0; i< rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(map[i][j] == 5)
			{
				*er = i;
				*ec = j;
			}
		}
	}
}

/* findTreasure
 * Find the current treasure position
 * Store the treasure when found
 * tr and tc remain as -1 if not found
 */

void findTreasure(int** map, int rows, int cols, int* tr, int* tc)
{
	int i, j;
	
	/* initialize position as not found */
	*tr = -1;
	*tc = -1;
	
	/* loop through every cell in the map */
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{	
			/* check if current cell is teasure */
			if(map[i][j] == 3)
			{	
				/* store treasure position using pointer */
				*tr = i;
				*tc = j;
			}
		}
	}
}

/* save Treasure state */

/* movePlayer
 * Move the player by using input (a/s/d/w) to control
 * The player's old position will be cleared and updated to a new position
 * Prevents moving into the walls and outside the map
 */

void movePlayer(int** map, int rows, int cols, char input, int* treasureCollected, int* gameWon, int* gameOver)
{
	int pr, pc;
	int newr, newc;

	/* find current player position */
	findPlayer(map, rows, cols, &pr, &pc);

	/* start with current position */
	newr = pr;
	newc = pc;

	/* update position based on input */
	if(input == 'w')
	{
		newr = pr - 1; /* move up */
	}
	else if(input == 's')
	{
		newr = pr + 1; /* move down */
	}
	else if(input == 'a')
	{
		newc = pc - 1; /* move left */
	}
	else if(input == 'd')
	{
		newc = pc + 1; /* move right */
	}
	
	/* check boundary to prevent going outside map */
	if(newr < 0 || newr >= rows || newc < 0 || newc >= cols)
	{
		return; /* do nothing if out of bounds */
	}

	/* check wall to prevent walking into wall */
	if(map[newr][newc] == 1)
	{
		return;
	}

	/* check Treasure */
	if(map[newr][newc] == 3)
	{
    		*treasureCollected = 1;
	}

	/* check Goal */
	if(map[newr][newc] == 2)
	{
    		/* cannot enter Goal before collecting Treasure */
    		if(*treasureCollected == 0)
    		{
        		return;
    		}
    		else
    		{
        		*gameWon = 1;
    		}
	}

	/* check Enemy collision */
	if(map[newr][newc] == 5)
	{
		*gameOver = 1; /* player loses */
		return; /* stop movement immediately */
	}

	/* move player if valid */
        map[pr][pc] = 0; /* clear old position */
        map[newr][newc] = 4; /* set new position */

}


/* isBlocked
 * Check whether a position is blocked for the enemy
 * Wall, Goal, Treasure and Border are blocked
 */

int isBlocked(int** map, int rows, int cols, int r, int c)
{
	int blocked;
	blocked = 0;

	if(r < 0 || r >= rows || c < 0 || c>= cols)
	{
		blocked = 1;
	}
	else if(map[r][c] == 1 || map[r][c] == 2 || map[r][c] == 3)
	{
		blocked = 1;
	}

	return blocked;
}


/* getNextPosition
 * Calculates the next row and column based on direction
 * 0 = up, 1 = right, 2 = down, 3 = left
 */

void getNextPosition(int r, int c, int direction, int* nr, int* nc)
{
	*nr = r;
	*nc = c;

	if(direction == 0)
	{
		*nr = r -1;
	}
	else if(direction == 1)
	{
		*nc = c + 1;
	}
	else if(direction == 2)
	{
		*nr = r + 1;
	}
	else if(direction == 3)
	{
		*nc = c - 1;
	}
}



/* moveEnemy
 * Moves the enemy based on movement rules
 * The enemy checks forward, left and right directions
 */

void moveEnemy(int** map, int rows, int cols,
               int* enemyDirection,
               int* gameOver)
{
    int er, ec;

    /* direction variables */
    int forwardDir;
    int leftDir;
    int rightDir;
    int backDir;

    /* positions for each direction */
    int fr, fc;
    int lr, lc;
    int rr, rc;
    int br, bc;

    /* final movement position */
    int newr, newc;

    /* find Enemy position */
    findEnemy(map, rows, cols, &er, &ec);

    /* determine relative directions */
    forwardDir = *enemyDirection;

    /* rotate 90 anti-clockwise */
    leftDir = (*enemyDirection + 3) % 4;

    /* rotate 90 clockwise */
    rightDir = (*enemyDirection + 1) % 4;

    /* rotate 180 */
    backDir = (*enemyDirection + 2) % 4;

    /* calculate next positions */
    getNextPosition(er, ec, forwardDir, &fr, &fc);
    getNextPosition(er, ec, leftDir, &lr, &lc);
    getNextPosition(er, ec, rightDir, &rr, &rc);
    getNextPosition(er, ec, backDir, &br, &bc);

    /* start with current position */
    newr = er;
    newc = ec;

    /*
     * CASE 1:
     * If forward is free, keep moving forward
     */

    if(isBlocked(map, rows, cols, fr, fc) == 0 &&
       isBlocked(map, rows, cols, lr, lc) == 1 &&
       isBlocked(map, rows, cols, rr, rc) == 1)
    {
        newr = fr;
        newc = fc;
    }


    /*
     * CASE 2:
     * Forward blocked and both left/right free
     * Use RNG
     */

    else if(isBlocked(map, rows, cols, fr, fc) == 1 &&
            isBlocked(map, rows, cols, lr, lc) == 0 &&
            isBlocked(map, rows, cols, rr, rc) == 0)
    {
        if(randomUCP(0, 1) == 0)
        {
            *enemyDirection = leftDir;

            newr = lr;
            newc = lc;
        }
        else
        {
            *enemyDirection = rightDir;

            newr = rr;
            newc = rc;
        }
    }


    /*
     * CASE 3:
     * Only left free
     */
	
    else if(isBlocked(map, rows, cols, lr, lc) == 0)
    {
        *enemyDirection = leftDir;

        newr = lr;
        newc = lc;
    }


     /* CASE 4:
      * Only right free
      */

    else if(isBlocked(map, rows, cols, rr, rc) == 0)
    {
        *enemyDirection = rightDir;

        newr = rr;
        newc = rc;
    }


     /* CASE 5:
     * Dead end
     */
    else
    {
        *enemyDirection = backDir;

        newr = br;
        newc = bc;
    }

    /* check if Enemy catches Player */
    if(map[newr][newc] == 4)
    {
        *gameOver = 1;
    }
    else
    {
        /* move Enemy */
        map[er][ec] = 0;
        map[newr][newc] = 5;
    }
}

/* insertFirst
 * Insert a new GameState at the front of the list
 */

void insertFirst(Node** head, GameState state)
{
	Node* newNode;

	/* allocate memory for new node */
	newNode = (Node* )malloc(sizeof(Node));

	/* copy game state into node */
	newNode -> state = state;

	/* link new node to current head */
	newNode -> next = *head;

	/* update head */
	*head = newNode;
}


/* remove First
 * Remove the first node from linked list and return the stored GameState */

int removeFirst(Node** head, GameState* state)
{
	Node* temp;

	/* check if list is empty */
	if(*head == NULL)
	{
		return 0;
	}

	/*copy state from first node */
	*state = (*head) -> state;

	/* temporary pointer */
	temp = *head;

	/* move head to next node */
	*head = (*head) -> next;

	/* free removed node */
	free(temp);

	/* undo success */
	return 1; 
}

/* freeList
 * Free all remaining nodes in the linked list
 */

void freeList(Node* head)
{
	Node* temp;

	while(head != NULL)
	{
		temp = head;
		head = head -> next;
		free(temp);
	}
}
