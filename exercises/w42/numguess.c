#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    while (1) {

        time_t seed = time(NULL);
        srand(seed);
        int secret = rand() % 100;

        for (int attempts = 1; attempts <= 10; attempts++) {
            int guess;
            printf("attempt: %d\n", attempts);
            printf("guess number [0,99]: ");

            while (scanf("%d", &guess) != 1 || (guess < 0 || guess > 99)) {
                getchar();
                printf("invalid!!! try again: ");
            }
            getchar();

            if (guess == secret) {
                printf("correct guess!\nsecret: %d\nguess: %d\nattempts: %d\n\n",
                                                secret, guess, attempts);
                break;
            }
            if (attempts < 10) {
                printf("sorry! too %s, try again\n\n", (guess < secret)? "small" : "big");
            } else {
                printf("LOOOSER\n");
            }
        }
        char yn = '\0';
        printf("keep playing? y/n: ");
        scanf("%c", &yn);
        getchar();
        if (yn != 'y' && yn != 'Y') break;
    }
}