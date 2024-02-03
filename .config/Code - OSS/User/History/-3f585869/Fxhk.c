#include "tileblaster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rearrangeColors(Board* board, int maxColor) {

    int max = 0;
    int min = maxColor;
    int color = 1;
    while (1) {
        for (int line = 1; line <= board->lines; line++) {
            for (int column = 1; column <= board->columns; column++) {
                if (board->tiles[line-1][column-1].x < min && board->tiles[line-1][column-1].x >= color)
                    min = board->tiles[line-1][column-1].x;
                if (board->tiles[line-1][column-1].x > max) max = board->tiles[line-1][column-1].x;
            }
        }
        printf("%i\n", min);
        for (int line = 1; line <= board->lines; line++) {
            for (int column = 1; column <= board->columns; column++) {
                if (board->tiles[line-1][column-1].x == min) board->tiles[line-1][column-1].x = color;
            }
        }
        if (min == max) break;
        color++;
        min = max;
    }
    return color;
}

/******************************************************************************
 * getBoard()
 *
 * Arguments: file - the file being opened for reading
 *            error - error code address for error handling
 * Returns: the board read from the file
 * Side-Effects: changes the value of the second argument (error) if the problem is invalid
 *
 * Description: creates a Board and sets it up with the current problem information
 *****************************************************************************/

Board *getBoard(FILE *file, int *error){

    Board *board = (Board *) malloc (sizeof(Board));
    if (!board) {
        fprintf(stderr, "Error allocating memory for variable \"board\", in function getBoard()!\n");
        exit(1);
    }
    uint numColor = 0;

    // getting the header of the problem
    if (fscanf(file, "%i %i %i",
        &board->lines, &board->columns, &board->variant) != 3) {
            free(board);
            return NULL;    
    } 
    
    // initializing the board matrix
    board->tiles = (Vector2 **) malloc (board->lines * sizeof(Vector2 *));

    if (!board->tiles) {
        fprintf(stderr, "Error allocating memory for variable \"board->tiles\", in function getBoard()!\n");
        exit(1);
    }

    for (int k = 0; k < board->lines; k++) {
        board->tiles[k] = (Vector2 *) malloc (board->columns * sizeof(Vector2));
        if (!board->tiles[k]) {
            fprintf(stderr, "Error allocating memory for variable \"board->tiles[%i]\", in function getBoard()!\n", k);
            exit(1);
        }
    }

    // getting every element off of the file
    for (int line = board->lines - 1; line >= 0; line--){
        for (int column = 0; column < board->columns; column++){
            if (fscanf(file, "%i", &board->tiles[line][column].x) != 1) *error = 1;
            if (board->tiles[line][column].x > numColor) numColor = board->tiles[line][column].x;
        }
    }
    resetClusterSets(board);
    showBoard(board);
    numColor = rearrangeColors(board, numColor);
    board->colors = (uint *)calloc(numColor, sizeof(uint));
    if (!board->colors) {
        fprintf(stderr, "Error allocating memory for variable \"board->colors\", in function getBoard()!\n");
        exit(1);
    }
    board->numColors = numColor;

    /* Checking if the problem is invalid or not */
    if (board->variant != -1 && board->variant != -3 && board->variant < 0) {
        *error = 1;
    }
    /* Returns the board created */
    showBoard(board);
    exit(0);
    return board;
}

/******************************************************************************
 * outputName()
 *
 * Arguments: inputName - input file name
 *
 * Returns: the output name of the file created by the program
 * Side-Effects: none
 *
 * Description: creates the name for the output file with the .tileblasts extension. Returns NULL if the input name is invalid
 *****************************************************************************/

char *outputName(char *inputName) {

    char *outputName, *checkName;
    char inputExtension[] = ".tilewalls";
    char outputExtension[] = ".tileblasts";
    uint len, i, j;
  
    len = strlen(inputName);

    checkName = inputName + len - strlen(inputExtension);
    if (strcmp(checkName, inputExtension) != 0) return NULL;

    outputName = (char *) malloc((len + 2) * sizeof(char));
    if (!outputName) {
        fprintf(stderr, "Error allocating memory for varaible \"outputName\", in function outputName()!\n");
        exit(1);
    }

    for (i = 0; i < len - 10; i++) {
        outputName[i] = inputName[i];
    }
    for (j = 0; i < len + 2; i++, j++) {
        outputName[i] = outputExtension[j];
    }

    return outputName;
}

/******************************************************************************
 * writeFile()
 *
 * Arguments: file - file to write out to
 *            boardSize - the number of lines and the number of columns of the 
 *            board
 * Returns: nothing
 * Side-Effects: none
 *
 * Description: writes to the output file the answer to the problem
 *****************************************************************************/

void writeFile(FILE *file, Vector2 boardSize, int variant, Solution answer) {

    uint moves;
    VectorList *move;

    /* Writing the problem header */
    fprintf(file, "%i %i %i\n",
                boardSize.y, boardSize.x, variant);
    if (!answer.moves) {
        if (variant > 0) {
            fprintf(file, "0 -1\n\n");
        } else {
            fprintf(file, "0 0\n\n");
        }
        return;
    } 
    for (moves = 0, move = answer.moves; move; move = move->next, moves++);
    fprintf(file, "%i %i\n", moves, answer.score);
    for (move = answer.moves; move; move = move->next) fprintf(file, "%i %i\n", move->tile.y, move->tile.x);
    fprintf(file, "\n");

    return;
}
