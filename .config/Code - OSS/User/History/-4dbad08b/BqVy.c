#include <stdio.h>

int max_blank_sequence(char *s1) {
    if (!s1) return 0;
    int counter = 0, max = 0, where = 0;
    int len = strlen(s1);

    while(s1 != '\0') {
        if (s1 == ' ') {
            s1 += max;
            max = 0;
        }
        if (max >= len - where) break;

        where++;
    }

    return max;
}

int main(int argc, char **argv) {
    char *string = "Às vezes    existem  epaços em        branco nas sequências de caracteres";
    printf("%i\n", max_blank_sequence(string));
    return 0;
}