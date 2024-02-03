#include "tileblaster.h"
#include <stdio.h>
#include <string.h>

#define ERROR_ARGUMENTS 1
#define ERROR_FILE 2


int main(int argc, char **argv){

    /* Making sure the input filename has been supplied and nothing more */
    if (argc != 2) return ERROR_ARGUMENTS;

    /* Allocating memory to know if there are any problems with the problem format */
    int error, color, id;
    uint total, score, line, column, tiles;
    /* Creating the name for the output file */
    char *filenameIn = argv[1];
    char *filenameOut;
    
    /* Get the output file name */
    filenameOut = outputName(filenameIn); 
    if (!filenameOut) return ERROR_FILE;

    /* Opening the input and output files */
    FILE *fileIn = fopen(filenameIn, "r");
    FILE *fileOut = fopen(filenameOut, "w");

    /* Making sure the files were opened correctly */
    if (!fileIn || !fileOut) return ERROR_FILE;
    
    Board *board;
    MoveList *moveHead;
    
    error = 0;
    while ((board = getBoard(fileIn, &error))){
        /* Reseting error */
        total = 0;

        /* Reading a single problem and creating a board for it */

        /* Checking if the problem is invalid or not */
        if (error == 1) {
            error = 0;
            /* Writing the problem header and moving on to the next problem after freeing the board */
            fprintf(fileOut, "%i %i %i\n\n", 
                    board->lines, board->columns, board->variant);

            freeBoard(board);
            continue;
        }
        error = 0;
        moveHead = NULL;
        while ((id = findAllClusters(board)) != -1){
            //showboard(board);
            //showID(board);

            line = id / board->columns + 1;
            column = id % board->columns + 1;
            //printf("%i %i %i\n", id, line, column);
            tiles = removeCluster(board, line, column);
            moveHead = moveListAdd(moveHead, line, column);
            score += tiles * (tiles - 1);
            //showBoard(board);
            //showID(board);
        } 
        /* Writing to the output file */
        writeFile(fileOut, board, moveHead, score);
        freeMoveList(moveHead);
        freeBoard(board);
    }
    /* Freeing the variable error and closing the files before closing the programm */
    free(filenameOut);

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}