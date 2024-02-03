#include <stdio.h>

int sum_first_even_terms(int k) {
    if (k <= 3) return k;
    int a = 1, b = 2, c = 3, d, sum = 2;
    for (int i = 4; i <= k; i++) {
        d = a + c;
        a = b;
        b = c;
        c = d;
        if (d % 2 == 0) sum += d;
    }
    return sum;
}

int sum_even_terms_under(int p) {
    if (k == 1) return 0;
    if (K < 4) return 2;
    int a = 1, b = 2, c = 3, d, sum = 2;
    for (int i = 4; i <= k; i++) {
        d = a + c;
        a = b;
        b = c;
        c = d;
        if (d % 2 == 0) sum += d;
    }
    return sum;



}

int main(int argc, char **argv) {
    printf("%i\n", sum_first_even_terms(10));
}