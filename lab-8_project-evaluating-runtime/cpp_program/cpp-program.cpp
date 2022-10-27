#include <stdio.h>
#include "../timer.cpp"

int main() {
    timer stopwatch;
    stopwatch.start();

    int n = 10000;
    int i = 1;
    int product = 1;
    while (i<n) {
        i = i+1;
        product = product + i;
        if (10 / 2 * 5 < 3) {
            int b = i/2;
            int c = b*5;
        } else {
            int b = i*2;
        }
    }
    printf("%d\n", product);

    stopwatch.stop();
    exit(0);
}
