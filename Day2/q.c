#include <stdio.h>
#define BUFFER_SIZE 7

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    // Part 2
    int scores[3][3] = {{3, 1, 2},  // Lose + base score
                        {4, 5, 6},  // Draw + base score
                        {8, 9, 7}}; // Win + base score
    int totalScore = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, BUFFER_SIZE, file)){
        int playerMove = (int)(buffer[2] - 'X');
        int opponentMove = (int)(buffer[0] - 'A');
        totalScore += scores[playerMove][opponentMove];
    }

    printf("TotalScore: %d\n", totalScore);
    fclose(file);
    return 0;
}
