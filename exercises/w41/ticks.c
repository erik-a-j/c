#include <stdio.h>
#include <math.h>

int main() {
    int ticks = 0;
    float revs = 0;
    
    printf("Enter song length in ticks: ");
    scanf("%d", &ticks);

    if (ticks >= 1 && ticks <= pow(10, 5)) {
        printf("revolutions needed: %.2f\n", (float)ticks / 4);
    } else {
        printf("invalid number\n");
    }

}