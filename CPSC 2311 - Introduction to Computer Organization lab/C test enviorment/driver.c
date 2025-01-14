#include <stdio.h>


int main() {
    int x;
    int k[3]= {15, 73, 155};

    printf("Enter input for x: ");
    scanf("%d", &x);
    printf("x = %d\n\n", x);
    int anwserOne = (x<<4) - x;
    int answerTwo = (x<<6) + (x<<3) + (x<<0);
    int anwserThree = (x<<7) + (x<<4) + (x<<2) + (x<<3) - x;
    printf("Correct answer for Q1: %d * %d = %d\n", x, k[0], x * k[0]);
    printf("k = %d with 1 shifts and 1 add/sub  equals: %d\n\n", k[0], anwserOne);
    printf("Correct answer for Q2: %d * %d = %d\n", x, k[1], x * k[1]);
    printf("k = %d with 3 shifts and 2 add/sub equals: %d\n\n", k[1], answerTwo);
    printf("Correct answer for Q2: %d * %d = %d\n", x, k[2], x * k[2]);
    printf("k = %d with 4 shifts and 4 add/sub equals: %d\n", k[2], anwserThree);
    return 0;
}
