#include <stdio.h>

void priner(int count, int color_code) {
    for (int i = 0; i < count; i++) {
        // Print in the chosen color
        printf("\033[1;%dmHello World\033[0m\n", color_code);
    }
}
int main() {
    int count;
    int color_choice;
    int color_code;

    printf("Print how many times do you want to print Hello World: ");
    scanf("%d", &count);

    if (count < 0) {
        printf("Invalid input, try again\n");
        printf("Print how many times do you want to print Hello World: ");
        scanf("%d", &count);
    }
    printf("Choose a color:\n");
    printf("1. Red\n");
    printf("2. Green\n");
    printf("3. Yellow\n");
    printf("4. Blue\n");
    printf("5. Magenta\n");
    printf("6. Cyan\n");
    printf("7. White\n");
    scanf("%d", &color_choice);

    // Map the user's choice to the corresponding ANSI color code
    switch (color_choice) {
        case 1:
            color_code = 31; // Red
            break;
        case 2:
            color_code = 32; // Green
            break;
        case 3:
            color_code = 33; // Yellow
            break;
        case 4:
            color_code = 34; // Blue
            break;
        case 5:
            color_code = 35; // Magenta
            break;
        case 6:
            color_code = 36; // Cyan
            break;
        case 7:
            color_code = 37; // White
            break;
        default:
            color_code = 37; // Default to White if an invalid option is chosen
            printf("Invalid choice, defaulting to White.\n");
            break;
    }

    
    
    priner(count, color_code);

    return 0;
}
