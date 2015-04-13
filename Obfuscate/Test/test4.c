#include <stdio.h>

int main() {
    int a = 42;
    int b = 0;
    a = 1 - a;
    b = 0 + a;
    printf("a = %i\n", a);
    printf("b = %i\n", b);
    return 0;
}
