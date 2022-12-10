#include <stdio.h>
#define STRING_BUFFER_SIZE 40

// Function declarations
int Part_1(void);
int Part_2(void);

int main(void) {
    printf("Part 1 value: %d\n", Part_1());
    printf("Part 2 value: %d\n", Part_2());
    return 0;
}

int Part_1(void){
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        // If file cannot be opened, return NULL
        return 0;
    }

    int val = 0;
    char buffer[STRING_BUFFER_SIZE] = { '\0' };
    while (fgets(buffer, STRING_BUFFER_SIZE, file)) {

    }

    fclose(file);
    return val;
}

int Part_2(void) {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        // If file cannot be opened, return NULL
        return 0;
    }

    int val = 0;
    char buffer[STRING_BUFFER_SIZE] = { '\0' };
    while (fgets(buffer, STRING_BUFFER_SIZE, file)) {

    }

    fclose(file);
    return val;
}
