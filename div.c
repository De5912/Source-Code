#include <stdio.h>

int main() {
    float num1, num2, div;  // Change to float for decimal numbers

    printf("Enter two numbers: ");
    scanf("%f %f", &num1, &num2);  // %f for floating-point input

    // Check for division by zero
    if (num2 == 0) {
        printf("Error: Division by zero is not allowed.\n");
    } else {
        div = num1 / num2;  // Perform floating-point division
        printf("div: %.2f\n", div);  // Print result with 2 decimal places
    }

    return 0;
}

