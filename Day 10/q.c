#include <stdio.h>
#define STRING_BUFFER_SIZE 40

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    int val = 0;
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        
    }

    printf("%d\n", val);
    fclose(file);
    return 0;
}
