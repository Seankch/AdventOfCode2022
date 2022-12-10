#include <stdio.h>
#include <string.h>
#define MAX_NUM_OF_CRATES_INPUT 8
#define MAX_NUM_OF_STACKS 9
#define STRING_BUFFER_SIZE 40

typedef struct StackInfo{
    char crates[100];
    int numOfCrates;
} StackInfo;

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    // 2D array for the whole stack of crates
    StackInfo stackOfCrates[MAX_NUM_OF_STACKS] = {{0}, 0};

    int rowCounter = 0;
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (rowCounter < MAX_NUM_OF_CRATES_INPUT){
            // Parse the input for crates
            for (int i = 0; i < MAX_NUM_OF_STACKS; ++i){
                char crateID = buffer[1+i*4]; // Start from 1, increment by 4 each iteration
                if (crateID >= 'A' && crateID <= 'Z'){
                    // Add crate to array (top crate is at back of array)
                    stackOfCrates[i].crates[MAX_NUM_OF_CRATES_INPUT - rowCounter - 1] = crateID;
                    ++stackOfCrates[i].numOfCrates;
                }
            }
        }
        else if (rowCounter >= 10){
            // Move crates
            int numOfMovedCrates, fromStackID, toStackID;
            sscanf(buffer, "move %d from %d to %d", &numOfMovedCrates, &fromStackID, &toStackID);
            
            /*
            // Part 1
            for(int i = 0; i < numOfMovedCrates; ++i){
                stackOfCrates[toStackID - 1].crates[stackOfCrates[toStackID - 1].numOfCrates] = stackOfCrates[fromStackID - 1].crates[stackOfCrates[fromStackID - 1].numOfCrates - 1];
                --stackOfCrates[fromStackID - 1].numOfCrates;
                ++stackOfCrates[toStackID - 1].numOfCrates;
            }
            */

            // Part 2
            for(int i = numOfMovedCrates - 1; i >= 0; --i){
                stackOfCrates[toStackID - 1].crates[stackOfCrates[toStackID - 1].numOfCrates] = stackOfCrates[fromStackID - 1].crates[stackOfCrates[fromStackID - 1].numOfCrates - i - 1];
                ++stackOfCrates[toStackID - 1].numOfCrates;
            }
            stackOfCrates[fromStackID - 1].numOfCrates -= numOfMovedCrates;
        }

        ++rowCounter;
    }

    // Print top of all stacks
    for (int i = 0; i < MAX_NUM_OF_STACKS; ++i){
        printf("%c", stackOfCrates[i].crates[stackOfCrates[i].numOfCrates - 1]);
    }
    printf("\n");

    fclose(file);
    return 0;
}
