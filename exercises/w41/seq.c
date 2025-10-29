#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define pint(x) printf(#x" == %d\n", x)

typedef struct {
    int len;
    int seq[100];
} seq_t;

int main() {
    seq_t seq[100];
    int n_seq = 0;
    int end_of_seq = 1;
    int i = 0;
    int j = 0;
    int n;
    int num;
    while ((n = fscanf(stdin, "%d", &num))) {
        if (n == EOF) break;
        if (n_seq == 0) {
            n_seq = num;
            continue;
        }
        if (end_of_seq == 1) {
            seq[i].len = num;
            end_of_seq = 0;
            j = 0;
            continue;
        }
        seq[i].seq[j++] = num;
        if (j == seq[i].len) {
            end_of_seq = 1;
            i++;
        }
    }

    for (int k = 0; k < n_seq; k++) {
        printf("seq[%d] = [", k);
        for (int l = 0; l < seq[k].len; l++) {
            if (l > 0) printf(",");
            printf("%d", seq[k].seq[l]);
        }
        printf("] ");

        int is_arithmetic = 1;
        int diff = seq[k].seq[0] - seq[k].seq[1];
        for (int l = 1; l < seq[k].len-1; l++) {
            if (seq[k].seq[l] - seq[k].seq[l+1] != diff) {
                is_arithmetic = 0;
                break;
            }
        }
        printf("%s arithmetic\n", (is_arithmetic)? "is" : "is not");
    }

}