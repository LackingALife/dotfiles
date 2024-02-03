#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    FILE* words = fopen("lusiadas-words.txt", "r");
    if (!words) {
        fprintf(stderr, "There is no file named lusiadas-words.txt!\n");
        exit(EXIT_FAILURE);
    }

    char **word_array;

}