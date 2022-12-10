#include <stdio.h>
#include <string.h>
#define STRING_BUFFER_SIZE 40

int FindMarker(int _numOfCharacters){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    int dataMap[26] = { 0 };
    int noRepeatCharCounter = 1, fileCharIndex = 0, ch = 0, backTrackIndex = 0;
    while ((ch = fgetc(file)) != EOF){
        if (noRepeatCharCounter == _numOfCharacters && dataMap[ch - 'a'] == 0) {
            // If there is no repeat characters after specified counts, break
            break;
        }
        else if (dataMap[ch - 'a'] != 0) {
            // If repeat character is found, reset map and counter
            memset(dataMap, 0, sizeof dataMap);
            noRepeatCharCounter = 1;

            // Backtrack iterator
            fileCharIndex = ++backTrackIndex;
            if (fseek(file, fileCharIndex, SEEK_SET) != 0)
                return -1;
        }

        ++dataMap[ch - 'a'];
        ++noRepeatCharCounter;
        ++fileCharIndex;
    }

    fclose(file);
    return fileCharIndex;
}

int main(void){
    // Print marker
    printf("Number of characters: %d, marker: %d\n", 4, FindMarker(4));
    printf("Number of characters: %d, marker: %d\n", 14, FindMarker(14));
    return 0;
}
