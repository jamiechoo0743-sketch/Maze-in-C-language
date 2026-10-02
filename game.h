/* check GAME_H is not defined */
#ifndef GAME_H
/* If not defined, define this micro */
#define GAME_H

/* GameState
 * Store important game information for undo
 */

typedef struct
{
        int playerRow;
        int playerCol;

        int enemyRow;
        int enemyCol;

        int treasureRow;
        int treasureCol;

        int enemyDirection;
        int treasureCollected;
} GameState;

/* Node
 * Linked List node for storing GameState
 */

typedef struct Node
{
        GameState state;
        struct Node* next;
} Node;


void printMap(int** map, int rows, int cols, int enemyDirection, int furiousMode);
void findPlayer(int** map, int rows, int cols, int* pr, int* pc);
void movePlayer(int** map, int rows, int cols, char input, int* treasureCollected, int* gameWon, int* gameOver);
void findEnemy(int** map, int rows, int cols, int* er, int* ec);
void moveEnemy(int** map, int rows, int cols, int* enemyDirection, int* gameOver);
int isBlocked(int** map, int rows, int cols, int r, int c);
void getNextPosition(int r, int c, int direction, int* nr, int*nc);
void insertFirst(Node** head, GameState state); /* save state */
int removeFirst(Node** head, GameState* state); /* undo state */
void findTreasure(int** map, int rows, int cols, int* tr, int* tc);
void freeList(Node* head);
#endif
