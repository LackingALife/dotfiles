#include <stdio.h>

int sum_first_even_terms(int k) {
    if (k <= 3) return k;
    int old = sum_first_even_terms(k-1);
    int sum;
    sum = sum_first_even_terms(k-1) + sum_first_even_terms(k-3);
    printf("%i-%i\n", k, sum);
    if (sum % 2 == 1) return 0;
    return sum;
}

int sum_even_terms_under(int p) {




}

int main(int argc, char **argv) {
    printf("%i\n", sum_first_even_terms(10));
}