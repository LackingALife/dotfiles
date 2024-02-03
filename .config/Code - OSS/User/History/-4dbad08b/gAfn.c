#include <stdio.h>

int max_blank_sequence(char *s1) {
    if (!s1) return 0;
    int counter = 0, max = 0;
    int len = strlen(s1);




}

int main(int argc, char **argv) {
    char *string = "Às vezes    existem  epaços em        branco nas sequências de caracteres";
    printf("%i\n", max_blank_sequence(string));
    return 0;
}