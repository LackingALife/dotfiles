#include "tileblaster.h"
#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * addToVectorList()
 *
 * Arguments: head - the head of a list of tiles
 *            tile - the tile being added to the list of tiles
 * Returns: the new head of a stack VectorList
 * Side-Effects: none
 * Description: adds a vector to the vector list
 *****************************************************************************/

VectorList *addToVectorList(VectorList *head, Vector2 tile) {

    VectorList *vector = (VectorList *) malloc(sizeof(VectorList));

    vector->tile = tile;
    vector->next = head;

    return vector;
}

// returns the new head of a stack VectorList
/******************************************************************************
 *removeVector()
 *
 * Arguments: head - the head of a list of vectors 
 * Returns: the new head of a stack VectorList
 * Side-Effects: free's the member wanting to be removed from the list
 *
 * Description: removes a vector from the vector list
 *****************************************************************************/

VectorList *removeVector(VectorList *head) {

    VectorList *ret = head->next;
    free(head);
    return ret;

}

/******************************************************************************
 * createSolution()
 *
 * Arguments: moves - a list of moves made throughout the program's execution
 * Returns: a list of vectors with an associated score
 * Side-Effects: none
 *
 * Description: creates a list of all the moves made in correct order and
 *              a score
 *****************************************************************************/


Solution createSolution(MoveList *moves) {
    Solution answer;

    answer.score = 0;
    answer.moves = NULL;

    if (!moves) return answer;

    VectorList *head = NULL;
    MoveList *aux;

    for (aux = moves; aux->next; aux = aux->next) {
        head = addToVectorList(head, aux->tile);
    } 
    answer.score = moves->score;
    answer.moves = head;
    return answer;
}

Solution solve(Board *board) {

    MoveList *origin, *current;
    int target = board->variant;

    Solution solution;
    
    solution.score = 0;
    solution.moves = NULL;

    origin = (MoveList *) malloc(sizeof(*origin));

    origin->tile.x = -1;
    origin->tile.y = -1;
    origin->score = 0;
    origin->id = -1;
    origin->color = -1;
    origin->clusters = NULL;
    origin->next = NULL;
    origin->previous = NULL;
    origin->board = board;

    resetClusterSets(origin->board);
    origin->clusters = findAllClusters(origin->board);

    current = origin;

    while (1) {

        //showVectorList(current->clusters);
        if (!current->clusters || hopeless(current->board, target, current)) {
            //printf("no clusters found!\n");
            if (origin == current) {
                //printf("leaving..\n");
                break;
            } 
            //printf("%i ", head->score);
            if (current->board->variant >= -1 && current->score > current->board->variant) {
                solution = createSolution(current);
                freeMoveList(origin);
                return solution;
            }
            if (current->board->variant == -3 && current->score > target) {
                target = current->score;
                //printf("New Target: %i\n", target);
                if (solution.moves) freeVectorList(solution.moves);
                solution = createSolution(current);
            }
            //printf("Next Play: %i %i\n\n", play.y, play.x);
            //showBoard(board);
            //printf("--reverting--\n\n");
            //showMoveList(head);

            current = current->next;

            //showBoard(board);
            //showMoveList(current);
            continue;
        }

        //showBoard(board);
        //printf("--removing--\n\n");
        //printf("%i\n", id);
    
        current = removeCluster(current,  current->clusters->tile);

        //printf("%i %printf("empty tile! moving on..\n");i\n", head->tile.y, head->tile.x);
        //showBoard(board);
        //printf("--falling--\n\n");

        //showBoard(board);
        if (current->next) {
            current->score += current->next->score;
            current->next->clusters = removeVector(current->next->clusters);
        }

        //showBoard(board);
        //showMoveList(current);
        //showVectorList(current->clusters);
        //showTileList(head->tileHead);
    }
    //showBoard(board);
    freeMoveList(origin);
    //printf("%p\n", solution);
    return solution;
}

void freeMoveList(MoveList *head) {

    MoveList *moveTmp;

    while (head) {
        freeVectorList(head->clusters);
        freeBoard(head->board);
        moveTmp = head;
        head = head->previous;
        free(moveTmp);
    }
    return;
}

void freeVectorList(VectorList *head) {

    VectorList *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void showMoveList(MoveList *move) {
    printf("--------\n");
    for (MoveList *aux = move; aux; aux=aux->previous) {
        printf("%i %i\n", aux->tile.y, aux->tile.x);
        showBoard(aux->board);
    }
    printf("color: %i id: %i score: %i\n",
            move->color, move->id, move->score);
    printf("--------\n\n");
}