#include <stdio.h>
#include <string.h>

int sum_first_even_terms(int k) {
    if (k <= 3) return k;
    int sum;
    sum = sum_first_even_terms(k-1) + sum_first_even_terms(k-3);
    printf("%i\n", sum);
    //if (sum % 2 == 1) return 0;
    return sum;
}

int main(int argc, char **argv) {
    printf("%i\n", sum_first_even_terms(10));
}