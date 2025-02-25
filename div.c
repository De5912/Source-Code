#include <stdio.h>

int main() {
    float num1, num2, div;  
    int check;
    char choice;

    do {
        printf("Enter two numbers: ");
        check = scanf("%f %f", &num1, &num2);

        if (check != 2) {
            printf("Error: Invalid input! Please enter numeric values.\n");
            while (getchar() != '\n'); 
            continue;  
        }

        if (num2 == 0) {
            printf("Error: Division by zero is not allowed.\n");
        } else {
            div = num1 / num2;
            printf("div: %.2f\n", div);
        }

        printf("Do you want to perform another calculation? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');

    printf("Goodbye!\n");
    return 0;

