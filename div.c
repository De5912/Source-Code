#include <stdio.h>

int main() {
    int num1, num2, div;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    if (num2 == 0) {
        printf("Error: Division by zero is not allowed.\n");
    } else {
        div = num1 / num2;  
        printf("div: %d\n", div);
    }

    return 0;
}
