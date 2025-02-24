#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_array(int *p, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);
    printf("\n");
}

int main() {
    // Exercise 1
    printf("Exercise 1:\n");
    int n = 5;
    int *p = &n;
    printf("n=%d\n", n); // %d - format to a decimal
    printf("*p=%d\n", *p);
    printf("p=%u\n", (unsigned int)p);
    printf("\n");

    // Exercise 2
    printf("Exercise 2:\n");
    int **pp = &p;
    printf("p=%u\n", (unsigned int)p);
    printf("*pp=%u\n", (unsigned int)*pp);
    printf("\n");

    // Exercise 3
    printf("Exercise 3:\n");
    int s[100] = { 0 }; // all zeroes by the compiler
    int *d = malloc(100 * sizeof(int)); // new int[100] in C++
    memset(d, 0, 100); // all zeroes in run time
    printf("\n");

    // Exercise 4
    printf("Exercise 4:\n");
    s[1] = 1;
    printf("s[0]=%d\n", s[0]);
    printf("*s=%d\n", *s);
    printf("s[1]=%d\n", s[1]);
    printf("*(s+1)=%d\n", *(s+1));
    printf("*p=%d\n", *p);
    printf("p[0]=%d\n", p[0]);
    printf("\n");

    // Exercise 5
    printf("Exercise 5:\n");
    printf("sizeof(s)=%u\n", sizeof(s));
    printf("sizeof(d)=%u\n", sizeof(d));
    printf("\n");

    // Exercise 6
    printf("Exercise 6:\n");
    *p = 0;
    char *cp = (char *)p;
    cp[0] = 'A';
    printf("*cp=%c\n", *cp); // %c - format for a character
    printf("*p=%d\n", *p);
    free(d); // del[] d in C++
    printf("\n");

}