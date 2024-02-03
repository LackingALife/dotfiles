#include <stdio.h>

int max_blank_sequence(char *s1) {
    int counter = 0, max = 0;
    while (*s1 != '\0') {
        if (*s1 == ' ') counter++;
        else {
            if (max < counter) max = counter;
            counter = 0;
        }
    }
    return max;
}

int main(int argc, char **argv) {
    char *string = "Às vezes    existem  epaços em        branco nas sequências de caracteres";
    printf("%i\n", max_blank_sequence(string));
    return 0;
}