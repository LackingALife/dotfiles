#include "tileblaster.h"
#include <stdio.h>
#include <stdlib.h>

MoveList *createMove(uint lines, uint columns) {

    uint i;

    MoveList *move = (MoveList *) malloc(sizeof(MoveList));
    move->tiles = (Vector2 **) malloc(lines * sizeof(Vector2 *));
    for (i = 0; i < lines; i++) {
        move->tiles[i] = (Vector2 *) malloc(columns * sizeof(Vector2));
    }

    move->originPlay.x = 0;
    move->originPlay.y = 0;
    move->lastPlay.x = 0;
    move->lastPlay.y = 0;
    move->score = 0;
    move->previous = NULL;

    return move;
}

void copyTiles(MoveList *move, Vector2 **tiles, uint lines, uint columns) {

    uint i, j;
    
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            move->tiles[i][j].x = tiles[i][j].x;
            move->tiles[i][j].y = tiles[i][j].y;
        }
    }

}

MoveList *copyMove(MoveList *move, uint lines, uint columns) {

    MoveList *copy = createMove(lines, columns);

    copyTiles(copy, move->tiles, lines, columns);

    copy->originPlay = move->originPlay;
    copy->lastPlay = move->lastPlay;
    copy->score = move->score;

    copy->previous = move;

    return copy;
}

void makeMove(MoveList *head, uint lines, uint columns, int line, int column) {
    MoveList *newMove = copyMove(head, lines, columns);
    int tilesInCluster, color, id;
    color = newMove->tiles[line][column].x;
    id = newMove->tiles[line][column].y;
    tilesInCluster = removeCluster(newMove->tiles, head->tiles, lines, columns, id);
    applyGravity(newMove->tiles, lines, columns);
    findAllClusters(newMove->tiles, lines, columns);
    newMove->originPlay.x = column;
    newMove->originPlay.y = line;
    head->lastPlay.x = column;
    head->lastPlay.y = line;
    newMove->score = head->score + tilesInCluster * (tilesInCluster - 1);
    head = newMove;
}

void *removeMove(MoveList *head, uint lines) {
    MoveList *tmp = head;
    uint i;
    head = head->previous;
    for (i = 0; i < lines; i++) free(tmp->tiles[i]);
    free(tmp->tiles);
    free(tmp);
}

Vector2 findMovetoMake(MoveList *move, uint lines, uint columns) {

    Vector2 ret;

    ret.x = -1;
    ret.y = -1;
    uint i, j;

    for (i = move->lastPlay.y; i < lines; i++) {
        for (j = move->lastPlay.x; j < columns; j++) {
            if (move->tiles[i][j].x == -1 || move->tiles[i][j].y == -1) continue;
            else if (invalidMove(move->tiles, lines, columns, i, j) == 0) {
                ret.x = j;
                ret.y = i;   
                return ret;
            }
        }
    }
    return ret;
}

MoveList *copyMoveList(MoveList *head, uint lines, uint columns) {

    MoveList *aux, *newHead = NULL, *lastCopied, *current;

    for (aux = head; aux; aux = aux->previous) {
        current = copyMove(aux, lines, columns);
        if (!newHead) {
            newHead = current;
            lastCopied = newHead;
            continue;
        }
        current->previous = NULL;
        lastCopied->previous = current;
        lastCopied = current;
    }
    return newHead;
}

MoveList *deepFind(Board *board) {

    MoveList *moveHistory, *solution = NULL;
    Vector2 move;
    int a;
    moveHistory = createMove(board->lines, board->columns);

    copyTiles(moveHistory, board->tiles, board->lines, board->columns);
    findAllClusters(moveHistory->tiles, board->lines, board->columns);

    while (moveHistory) {

        
        move = findMovetoMake(moveHistory, board->lines, board->columns);

        if (move.x == -1 || move.y == -1) {
            if (!solution) solution = copyMoveList(moveHistory, board->lines, board->columns);
            if (moveHistory->score > solution->score) {
                freeMoveList(solution, board->lines);
                solution = copyMoveList(moveHistory, board->lines, board->columns);
            } if (board->variant >= 0 && solution->score >= board->variant) return solution;
            removeMove(moveHistory, board->lines);
        }
        else makeMove(moveHistory, board->lines, board->columns, move.y, move.x);
    }

    if (board->variant > 0) return NULL;    

    return solution;
}

void freeMoveList(MoveList *head, uint lines) {
    while(head) removeMove(head, lines);
}