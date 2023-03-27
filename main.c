#include <stdio.h>
#include "vector.h"

int main() {
    vector v = vector_init();
    vector_pushback(v,3);
    vector_pushback(v,5);
    vector_pushback(v,7);

    printf("\n%u\n",vector_size(v));
    for(int i=0;i<vector_size(v);++i) {
        printf("%u ",vector_i(v,i));
    }
    printf("\n");

    vector_destroy(v);

    return 0;
}