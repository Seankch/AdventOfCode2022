#include <stdio.h>

#define BUFFER_SIZE 7

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    int highestSum[3] = { 0, 0, 0 };
    int calories = 0, currentSum = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, BUFFER_SIZE, file)){
        if (sscanf(buffer, "%d", &calories) != EOF){
            currentSum += calories;
        }
        else{
            for (int i = 0; i < 3; ++i){
                if (currentSum > highestSum[i]){
                    highestSum[i] = currentSum;
                    break;
                }
            }
            currentSum = 0;
        }
    }

    currentSum = 0;
    for (int i = 0; i < 3; ++i){
        currentSum += highestSum[i];
    }
    printf("Total Calories: %d\n", currentSum);

    fclose(file);
    return 0;
}
