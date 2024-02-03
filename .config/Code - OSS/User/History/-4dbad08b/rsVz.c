#include <stdio.h>
#include <string.h>

int sum_first_even_terms(int k) {
    if (k == 2) return k;
    if (k == 1 || k == 3) return 0;
    return sum_first_even_terms(k-1) + sum_first_even_terms(k-3);
}

int main(int argc, char **argv) {
    
}