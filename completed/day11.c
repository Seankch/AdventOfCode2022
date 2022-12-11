#include <stdio.h>
#include <assert.h>
#include <string.h>
#define STRING_BUFFER_SIZE 50
#define NUM_OF_MONKEYS 8

enum {
    FRONT_OF_QUEUE
};

typedef struct MonkeyInfo{
    // Store items
    long itemList[36];
    int itemListSize;
    // Record count of monkey business
    long monkeyBusinessCount;
    // Variables for test
    int testValue;
    int nextMonkeyIndex[2]; // index 0 = false, index 1 = true
    // Variables for operation
    int operationValue;
    char operationOperator;
}MonkeyInfo;

// Function declarations
void ParseInput(MonkeyInfo _monkeys[]);
long DoMonkeyBusiness(MonkeyInfo _monkeys[], int _maxRoundCount, int _isPart1);
void ThrowItem(MonkeyInfo* _from, MonkeyInfo* _to);

int main(void) {
    // Part 1
    MonkeyInfo monkeys_part1[NUM_OF_MONKEYS] = {0};
    ParseInput(monkeys_part1);
    printf("Part 1 value: %ld\n", DoMonkeyBusiness(monkeys_part1, 20, 1));

    // Part 2
    MonkeyInfo monkeys_part2[NUM_OF_MONKEYS] = {0};
    ParseInput(monkeys_part2);
    printf("Part 2 value: %ld\n", DoMonkeyBusiness(monkeys_part2, 10000, 0));
    return 0;
}

void ParseInput(MonkeyInfo _monkeys[]){
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        // If file cannot be opened, return NULL
        return;
    }

    char* token, *delimiter = ":,";
    int monkeyCounter = 0, itemValue = 0;
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    // Parse input file
    while (fgets(buffer, STRING_BUFFER_SIZE, file)) {
        if(strstr(buffer, "Starting items: ")){
            // Parse item list
            token = strtok(buffer, delimiter);
            while(token != NULL){
                if (sscanf(token, " %d", &itemValue) == 1){
                    _monkeys[monkeyCounter].itemList[_monkeys[monkeyCounter].itemListSize] = itemValue;
                    ++(_monkeys[monkeyCounter].itemListSize);
                }
                token = strtok(NULL, delimiter);
            }
        }
        else if (strstr(buffer, "Operation: ")){
            // Parse operation operator
            char* temp;
            assert((temp = strchr(buffer, '+')) || (temp = strchr(buffer, '*')));
            _monkeys[monkeyCounter].operationOperator = *temp;

            // Parse operation value
            if(sscanf(temp, "%*c %d", &_monkeys[monkeyCounter].operationValue) != 1){
                _monkeys[monkeyCounter].operationValue = -1;
            }
        }
        else if (strstr(buffer, "Test: ")){
            // Parse test value
            char* temp = strstr(buffer, "by");
            sscanf(temp, "%*s %d", &_monkeys[monkeyCounter].testValue);            
        }
        else if (strstr(buffer, "If true: ")){
            // Parse next monkey index for true cases
            char* temp = strstr(buffer, "monkey");
            sscanf(temp, "%*s %d", &_monkeys[monkeyCounter].nextMonkeyIndex[1]);     
        }
        else if (strstr(buffer, "If false: ")){
            // Parse next monkey index for false cases
            char* temp = strstr(buffer, "monkey");
            sscanf(temp, "%*s %d", &_monkeys[monkeyCounter].nextMonkeyIndex[0]);     
        }
        else if (!strstr(buffer, "Monkey ")){
            // Increment counter after parsing current monkey
            ++monkeyCounter;
        }

        memset(buffer, 0, sizeof(buffer));
    }

    fclose(file);
}

long DoMonkeyBusiness(MonkeyInfo _monkeys[], int _maxRoundCount, int _isPart1){
    int product = 1;
    for (int i = 0; i < NUM_OF_MONKEYS; ++i){
        product *= _monkeys[i].testValue;
    }
    
    for (int roundCount = 0; roundCount < _maxRoundCount; ++roundCount){
        for (int i = 0; i < NUM_OF_MONKEYS; ++i){
            while(_monkeys[i].itemListSize > 0){
                ++_monkeys[i].monkeyBusinessCount;

                // Perform operation. if operationValue is -1, then multiply/add by its old value
                if (_monkeys[i].operationOperator == '*'){
                    _monkeys[i].itemList[FRONT_OF_QUEUE] *= (_monkeys[i].operationValue == -1)? _monkeys[i].itemList[FRONT_OF_QUEUE] : _monkeys[i].operationValue;
                }
                else{
                    _monkeys[i].itemList[FRONT_OF_QUEUE] += (_monkeys[i].operationValue == -1)? _monkeys[i].itemList[FRONT_OF_QUEUE] : _monkeys[i].operationValue;
                }

                if (_isPart1){
                    // Monkey gets bored, divide worry by 3
                    _monkeys[i].itemList[FRONT_OF_QUEUE] /= 3;
                }
                else{
                    // Modulo by product of all test values to reduce worry
                    _monkeys[i].itemList[FRONT_OF_QUEUE] %= product;
                }

                // Perform division test and throw item
                int isDivisible = !(_monkeys[i].itemList[FRONT_OF_QUEUE] % _monkeys[i].testValue);
                int nextMonkeyIndex = _monkeys[i].nextMonkeyIndex[isDivisible];
                ThrowItem(&_monkeys[i], &_monkeys[nextMonkeyIndex]);
            }
        }
    }

    // Compute top 2 monkey business count
    long topTwoCount[2] = {0, 0};
    for (int i = 0; i < NUM_OF_MONKEYS; ++i){
        for (int j = 0; j < 2; ++j){
            if (_monkeys[i].monkeyBusinessCount > topTwoCount[j]){
                if (j == 0){
                    topTwoCount[1] = topTwoCount[0];
                }
                topTwoCount[j] = _monkeys[i].monkeyBusinessCount;
                break;
            }
        }
    }

    return topTwoCount[0] * topTwoCount[1];
}

void ThrowItem(MonkeyInfo* _from, MonkeyInfo* _to){
    // Move item from source monkey to destination monkey
    _to->itemList[_to->itemListSize] = _from->itemList[FRONT_OF_QUEUE];

    if (_from->itemListSize > 1){
        // Move all items forward
        for (int i = 1; i < _from->itemListSize; ++i){
            _from->itemList[i - 1] = _from->itemList[i];
            _from->itemList[i] = 0;
        }
    }
    else{
        _from->itemList[FRONT_OF_QUEUE] = 0;
    }

    ++(_to->itemListSize);
    --(_from->itemListSize);
}
