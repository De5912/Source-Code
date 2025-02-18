#include <stdio.h>

int main() {
    int num1, num2, div;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    div = num1 / num2;

    printf("div: %d\n", div);

    return 0;
}
