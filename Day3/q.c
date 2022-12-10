#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 60

void FindSameItemType(char const _buffer[][BUFFER_SIZE], int* _totalScore) {
    for (int i = 0; _buffer[0][i] != '\0'; ++i) {
        for (int j = 0; _buffer[1][j] != '\0'; ++j) {
            for (int k = 0; _buffer[2][k] != '\0'; ++k) {
                if (_buffer[0][i] == _buffer[1][j] && _buffer[0][i] == _buffer[2][k]) {
                    if (_buffer[0][i] >= 'A' && _buffer[0][i] <= 'Z') {
                        *_totalScore += ((int)(_buffer[0][i] - 'A') + 1);
                    }
                    else if (_buffer[0][i] >= 'a' && _buffer[0][i] <= 'z') {
                        *_totalScore += ((int)(_buffer[0][i] - 'a') + 27);
                    }
                    return;
                }
            }
        }
    }
}

int Part_2(void) {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        // If file cannot be opened, return NULL
        return 0;
    }

    int totalScore = 0, currIter = 0;
    char buffer[3][BUFFER_SIZE] = { {'\0'}, {'\0'}, {'\0'} };
    while (fgets(buffer[currIter], BUFFER_SIZE, file)) {
        if (currIter == 2) {
            // Search for similar character
            FindSameItemType(buffer, &totalScore);

            // Reset string buffers
            for (int i = 0; i < 3; ++i) {
                memset(buffer[i], 0, sizeof(buffer[i]));
            }
        }

        // Move to next elf group
        currIter = (currIter + 1) % 3;
    }

    fclose(file);
    return totalScore;
}

int Part_1(void) {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        // If file cannot be opened, return NULL
        return 0;
    }

    int totalScore = 0, length = 0;
    int map[52] = { 0 };
    char buffer[BUFFER_SIZE] = { '\0' };
    char str1[BUFFER_SIZE] = { '\0' };
    char str2[BUFFER_SIZE] = { '\0' };
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // Get length of whole string
        length = strlen(buffer);

        // Split strings
        strncpy(str1, &(buffer[0]), length / 2);
        strncpy(str2, &(buffer[length / 2]), length / 2);

        // Find similar characters
        for (int i = 0; i < (length / 2); ++i) {
            for (int j = 0; j < (length / 2); ++j) {
                if (str1[i] == str2[j]) {
                    if (str1[i] >= 'A' && str1[i] <= 'Z') {
                        if (map[((int)(str1[i]) - 'A') + 1] == 0)
                        {
                            map[((int)(str1[i]) - 'A') + 1] = 1;
                            totalScore += ((int)(str1[i] - 'A') + 27);
                        }
                    }
                    else if (str1[i] >= 'a' && str1[i] <= 'z') {
                        if (map[((int)(str1[i]) - 'a') + 1] == 0)
                        {
                            map[((int)(str1[i]) - 'a') + 1] = 1;
                            totalScore += ((int)(str1[i] - 'a') + 1);
                        }
                    }
                }
            }
        }

        // Reset temp string buffers and dict
        memset(str1, 0, sizeof(str1));
        memset(str2, 0, sizeof(str2));
        memset(map, 0, sizeof(map));
    }

    fclose(file);
    return totalScore;
}

int main(void) {
    printf("Part 1: TotalScore: %d\n", Part_1());
    printf("Part 2: TotalScore: %d\n", Part_2());
    return 0;
}
