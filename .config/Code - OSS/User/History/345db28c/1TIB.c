#include "tileblaster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * readFile ()
 *
 * Arguments: FILE *file and int *error
 * Returns: Board *board
 * Side-Effects: changes the value of the second argument (error) if the problem is invalid
 *
 * Description: creates a Board and sets it up with the current problem information
 *****************************************************************************/

Board *getBoard(FILE *file, int *error){

    Board *board = (Board *) malloc (sizeof(Board));

    // getting the header of the problem
    if (fscanf(file, "%i %i %i",
        &board->lines, &board->columns, &board->variant) != 3) {
            free(board);
            return NULL;    
    } 
    board->score = 0;
    
    // initializing the board matrix
    board->tiles = (Vector2 **) malloc (board->lines * sizeof(Vector2 *));

    for (uint k = 0; k < board->lines; k++) {
        board->tiles[k] = (Vector2 *) malloc (board->columns * sizeof(Vector2));
    }

    // getting every element off of the file
    for (int line = board->lines - 1, id = 0; line >= 0; line--){
        for (int column = 0; column < board->columns; column++){
            fscanf(file, "%i", &board->tiles[line][column].x);
            board->tiles[line][column].y = id;
            id++;
        }
    }
    /* Checking if the problem is invalid or not */
    if (board->variant != -1 && board->variant != -3 && board->variant < 0) {
        *error = 1;
    }
    /* Returns the board created */
    printf("got a new board!\n");
    return board;
}

char *outputName(char *inputName) {

    char *name;
    char extension[] = ".toleblists";
    uint len, i;

    len = strlen(inputName);

    name = (char *) malloc((len + 2) * sizeof(char));
    for (i = 0, i < len - 10, i++) {
        name[i] = inputName[i];
    }
    for (i = len - 10, i < len + 2; i++) {
        name[i] = extension[i - len -10];
    }

    return name;
}

void printMoveList(FILE *file, MoveList *moves) {

    printMoveList(file, moves->previous);
    fprintf(file, "%i %i\n", moves->lastPlay.y, moves->lastPlay.x);
}

/******************************************************************************
 * writeFile ()
 *
 * Arguments: FILE *file, Board *board and int score
 * Returns: nothing
 * Side-Effects: changes the second argument (Board *) if it's the second variant
 *
 * Description: writes to the output file the answer to the problem according to its variant
 *****************************************************************************/

void writeFile(FILE *file, Board *board, MoveList *allMoves) {

    uint moves;
    MoveList *move;

    /* Writing the problem header */
    fprintf(file, "%i %i %i\n",
                board->lines, board->columns, board->variant);
    if (allMoves == NULL) {
        fprintf(file, "0 -1\n\n");
        return;
    }
    for (moves = 0, move = allMoves; move; move = move->previous, moves++);
    fprintf(file, "%i %i\n", moves, allMoves->score);
    printMoveList(file, allMoves);
    fprintf(file, "\n");

    return;
}
