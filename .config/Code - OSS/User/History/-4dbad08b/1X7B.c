#include <stdio.h>
#include <string.h>

int sum_first_even_terms(int k) {
    if (k <= 3) return k;
    return sum_first_even_terms(k-1) + sum_first_even_terms(k-3);
}

int main(int argc, char **argv) {
    
}