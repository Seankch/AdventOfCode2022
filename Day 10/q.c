#include <stdio.h>
#define STRING_BUFFER_SIZE 40
#define LIST_SIZE 100

int Part_1(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    int cycle = 1, value = 0;
    int sixSignalStrengthSum = 0, registerValue = 1;
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (sscanf(buffer, "%*s %d", &value) == 1){
            // addx, 2 cycles
            for (int i = 0; i < 2; ++i){
                // If cycle is at 20th, 60th, 100th, 140th, 180th, and 220th, increment sum
                if ((cycle % 40) == 20){
                    sixSignalStrengthSum += (cycle * registerValue);
                }

                // Increment register value at the second cycle
                registerValue += ((i == 1)? value : 0);
                ++cycle;
            }
        }
        else{
            // If cycle is at 20th, 60th, 100th, 140th, 180th, and 220th, increment sum
            if ((cycle % 40) == 20){
                sixSignalStrengthSum += (cycle * registerValue);
            }
            ++cycle;
        }
    }

    fclose(file);
    return sixSignalStrengthSum;
}

void Part_2(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return;
    }

    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    int cycle = 1, value = 0, registerValue = 1;
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (sscanf(buffer, "%*s %d", &value) == 1){
            // addx, 2 cycles
            for (int i = 0; i < 2; ++i){
                // Check if current printed pixel position is within sprite
                // Print '#' if within, else print '.'
                int isWithinSpriteLeftLimit = ((cycle - 1) % 40) >= registerValue - 1;
                int isWithinSpriteRightLimit = ((cycle - 1) % 40) <= registerValue + 1;
                printf("%c", (isWithinSpriteLeftLimit && isWithinSpriteRightLimit)? '#' : '.');

                // Increment signal strength at the second cycle
                registerValue += (i == 1)? value : 0;

                // If printed pixel position is at the end of row, print a newline
                if ((cycle % 40) == 0){
                    printf("\n");
                }
                ++cycle;
            }
        }
        else{
            // Check if current printed pixel position is within sprite
            // Print '#' if within, else print '.'
            int isWithinSpriteLeftLimit = ((cycle - 1) % 40) >= registerValue - 1;
            int isWithinSpriteRightLimit = ((cycle - 1) % 40) <= registerValue + 1;
            printf("%c", (isWithinSpriteLeftLimit && isWithinSpriteRightLimit)? '#' : '.');

            // If printed pixel position is at the end of row, print a newline
            if ((cycle % 40) == 0){
                printf("\n");
            }
            ++cycle;
        }
    }

    fclose(file);
}

int main(void){
    printf("Total strength of six signals: %d\n", Part_1());
    Part_2();
    return 0;
}
