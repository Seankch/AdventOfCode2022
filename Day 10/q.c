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
    int sixSignalStrengthSum = 0, signalStrengthSum = 1;
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (sscanf(buffer, "%*s %d", &value) == 1){
            // addx, increment signal strength at the second cycle
            for (int i = 0; i < 2; ++i){
                if ((cycle % 40) == 20){
                    sixSignalStrengthSum += (cycle * signalStrengthSum);
                }

                signalStrengthSum += ((i == 1)? value : 0);
                ++cycle;
            }
        }
        else{
            if ((cycle % 40) == 20){
                sixSignalStrengthSum += (cycle * signalStrengthSum);
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
    int cycle = 1, value = 0, signalStrengthSum = 1;
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (sscanf(buffer, "%*s %d", &value) == 1){
            // addx, increment signal strength at the second cycle
            for (int i = 0; i < 2; ++i){
                // Check if current printed pixel position is within sprite
                int isWithinSpriteLeftLimit = ((cycle - 1) % 40) >= signalStrengthSum - 1;
                int isWithinSpriteRightLimit = ((cycle - 1) % 40) <= signalStrengthSum + 1;
                printf("%c", (isWithinSpriteLeftLimit && isWithinSpriteRightLimit)? '#' : '.');
                signalStrengthSum += (i == 1)? value : 0;
                if ((cycle % 40) == 0){
                    printf("\n");
                }

                ++cycle;
            }
        }
        else{
            // Check if current printed pixel position is within sprite
            int isWithinSpriteLeftLimit = ((cycle - 1) % 40) >= signalStrengthSum - 1;
            int isWithinSpriteRightLimit = ((cycle - 1) % 40) <= signalStrengthSum + 1;
            printf("%c", (isWithinSpriteLeftLimit && isWithinSpriteRightLimit)? '#' : '.');
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
