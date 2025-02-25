#include <stdio.h>

int main() {
    float celsius, fahrenheit;
    int choice;

    printf("\n=== Temperature Converter ===\n");
    printf("1. Convert Celsius to Fahrenheit\n");
    printf("2. Convert Fahrenheit to Celsius\n");
    printf("Enter your choice (1 or 2): ");
    
    if (scanf("%d", &choice) != 1) {
        printf("\nError: Invalid input! Please enter a number.\n");
        return 1;
    }

    if (choice == 1) {
        printf("\nEnter temperature in Celsius: ");
        scanf("%f", &celsius);
        fahrenheit = (celsius * 9 / 5) + 32;
        printf("Result: %.2f°C = %.2f°F\n", celsius, fahrenheit);
    } 
    else if (choice == 2) {
        printf("\nEnter temperature in Fahrenheit: ");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - 32) * 5 / 9;
        printf("Result: %.2f°F = %.2f°C\n", fahrenheit, celsius);
    } 
    else {
        printf("\nError: Invalid choice! Please enter 1 or 2.\n");
    }

    return 0;
}

