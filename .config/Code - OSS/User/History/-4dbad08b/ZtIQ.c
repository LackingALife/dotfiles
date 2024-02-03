#include <stdio.h>
#include <string.h>

int sum_first_even_terms(int k) {
    if (k <= 3) return k;
    int first = sum_first_even_terms(k-1);
    int second = sum_first_even_terms(k-3);
    printf("%i %i\n", first, second);
    if (first % 2 == 1) first = 0;
    if (second % 2 == 1) second = 0;
    return first + second;
}

int main(int argc, char **argv) {
    printf("%i\n", sum_first_even_terms(10));
}