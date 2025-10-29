#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int aa = *(int*)a;
    int bb = *(int*)b;
    return aa - bb;
}

int main() {
    int rnums[10] = {0};

    FILE *urand = fopen("/dev/urandom", "rb");
    if (!urand) return 1;

    for (int i = 0; i < 10; i++) {
        fread(&rnums[i], sizeof(int), 1, urand);
        rnums[i] %= 1000;
        printf("rnums[%d]: %d\n", i, rnums[i]);
    }
    printf("\n");

    qsort(rnums, 10, sizeof(int), compare);
    for (int i = 0; i < 10; i++) {
        printf("sorted[%d]: %d\n", i, rnums[i]);
    }

    fclose(urand);
}