#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    int totalScore = 0;
    int min[2] = {0}, max[2] = {0};
    char buffer[BUFFER_SIZE] = {'\0'};
    while (fscanf(file, "%d-%d,%d-%d", &min[0], &max[0], &min[1], &max[1]) != EOF){
        // Check for overlap (Part 2)
        if (max[0] - min[1] >= 0 && max[1] - min[0] >= 0){
            ++totalScore;
        }
    }

    printf("TotalScore: %d\n", totalScore);
    fclose(file);
    return 0;
}
