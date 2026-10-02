#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "game.h"
#include "terminal.h"
#include "random.h"
#include "newSleep.h"

/* 
 * main
 * Entry point of the program
 * Handles command line arguments and tests map loading
 */

int main(int argc, char* argv[])
{
	int** map;
	int rows, cols;
	char input;
	
	int treasureCollected;
	int gameWon;
	int gameOver;
	int enemyDirection;
	int furiousMode;
	
        /* store previous game state */
        GameState state;

        /* linked list head for undo */
        Node* head;

	/* check number of arguments */
	if(argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
	}
	else
	{
		/* load map from file */
		map = loadMap(argv[1], &rows, &cols);
		
		treasureCollected = 0; /* initialize because haven' collect treasure */
		gameWon = 0; /* initialize because haven't win the game */
		gameOver = 0; /* initialize because haven't lose the game */
		enemyDirection = 3; /* enemy starts facing left */
		furiousMode = 0; /* initialize because haven't get treasure */
		head = NULL; /* linked list initially empty, no undo history */

		/* disable terminal buffering */
                disableBuffer();
		
		/* initialize random number generator */
		initRandom();
		{
			while(gameWon == 0 && gameOver ==0) /* continue running before win or lose */
			{
				/* clear the screen */
                                system("clear");

				/* print map */
				printMap(map, rows, cols, enemyDirection, furiousMode);
				
				/* prompt user for movement input */
				printf("Press 'w' to move UP\n");
				printf("Press 's' to move DOWN\n");
				printf("Press 'a' to move LEFT\n");
				printf("Press 'd' to move RIGHT\n");
				printf("Press 'u' to UNDO\n");
				printf("Move (w/s/a/d): ");

				/* press w/s/a/d can immediately move */
				input = getchar();
			
				if(input == 'w' || input == 's' || input == 'a' || input == 'd')
				{
    					/* save current game state */
				        findPlayer(map, rows, cols, &state.playerRow, &state.playerCol);
                                        findEnemy(map, rows, cols, &state.enemyRow, &state.enemyCol);
                                        findTreasure(map, rows, cols, &state.treasureRow, &state.treasureCol);

                                        state.enemyDirection = enemyDirection;
                                        state.treasureCollected = treasureCollected;

                                        insertFirst(&head, state);

                                        movePlayer(map, rows, cols, input, &treasureCollected, &gameWon, &gameOver);

				        if(treasureCollected == 1)
    					{
        					furiousMode = 1;
    					}

    					if(gameWon == 0 && gameOver == 0)
    					{
        					if(furiousMode == 1)
        					{
            						moveEnemy(map, rows, cols, &enemyDirection, &gameOver);
							newSleep(0.1);
            						moveEnemy(map, rows, cols, &enemyDirection, &gameOver);
							newSleep(0.1);
            						moveEnemy(map, rows, cols, &enemyDirection, &gameOver);
							newSleep(0.1);
        					}
        					else
        					{
            						moveEnemy(map, rows, cols, &enemyDirection, &gameOver);
							newSleep(0.1);
							moveEnemy(map, rows, cols, &enemyDirection, &gameOver);
                                                        newSleep(0.1);

        					}
    					}
				}

				/* check undo input */
				if(input == 'u')
				{
					/* retrieve previous game state */
					if(removeFirst(&head, &state) == 1)
					{
						int pr, pc;
						int er, ec;

						/* remove current player and enemy */
						findPlayer(map, rows, cols, &pr, &pc);
						findEnemy(map, rows, cols, &er, &ec);

						map[pr][pc] = 0;
						map[er][ec] = 0;

						/* restore treasure if not collected */
						if(state.treasureCollected == 0 &&
						   state.treasureRow != -1 &&
						   state.treasureCol != -1)
						{
							map[state.treasureRow][state.treasureCol] = 3;
						}

						/*restore player position */
						map[state.playerRow][state.playerCol] = 4;

						/* restore enemy position */
						map[state.enemyRow][state.enemyCol] = 5;

						/* restore game variables */
						enemyDirection = state.enemyDirection;
						treasureCollected = state.treasureCollected;
					}
				}

			}

		/* display winning message */
		if(gameWon == 1)
		{
			printf("Congratulations!!! You won the game!\n");
		}

		/* display losing message */
		if(gameOver == 1)
		{
			printf("Game Over! Enemy caught you!\n");
		}

		/* restore terminal settings */
		enableBuffer();

		/* free all remaining nodes in the linked list */
		freeList(head);

		/* free allocated memory */
		freeMap(map, rows);
		
		}
	}

	return 0;
}	


