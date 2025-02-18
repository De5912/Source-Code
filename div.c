#include <stdio.h>

int main() {
    float num1, num2, div;  
    int check; 

    printf("Enter two numbers: ");
    check = scanf("%f %f", &num1, &num2); 

    if (check != 2) {
        printf("Error: Invalid input! Please enter numeric values.\n");
        return 1;
    }

    if (num2 == 0) {
        printf("Error: Division by zero is not allowed.\n");
    } else {
        div = num1 / num2;  
        printf("div: %.2f\n", div);  
    }

    return 0;
}

