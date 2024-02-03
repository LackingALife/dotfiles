#include <stdio.h>
#include <string.h>

int max_blank_sequence(char *s1) {
    if (!s1) return 0;
    int counter = 0, max = 0, where = 0, full = 0;
    int len = strlen(s1);

    while(*s1 != '\0') {
        if (*s1 == ' ') {
            if (full == 0) {
                s1 += max;
                full = 1;
            }
            else s1++;
        } else {
            if (max < counter) max = counter;
            if (max >= len - where) break;
            full = 0;
        }
        
        where++;
    }

    return max;
}

int main(int argc, char **argv) {
    char *string = "Às vezes    existem  epaços em        branco nas sequências de caracteres";
    printf("%i\n", max_blank_sequence(string));
    return 0;
}