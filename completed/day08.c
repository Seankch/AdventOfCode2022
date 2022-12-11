#include <stdio.h>
#include <string.h>
#define STRING_BUFFER_SIZE 40

int IsTreeVisible(int _treeMap[][99], int _currRow, int _currCol){
    if (_currRow == 0 || _currRow == 98 || _currCol == 0 || _currCol == 98)
        return 1;

    int isTopBlocked, isBottomBlocked, isLeftBlocked, isRightBlocked;
    isTopBlocked = isBottomBlocked = isLeftBlocked = isRightBlocked = 0;

    // Check left - right
    for (int i = 0; i < 99; ++i){
        if (i == _currCol)
            continue;

        if (_treeMap[_currRow][_currCol] <= _treeMap[_currRow][i]){
            if (i < _currCol)  
                isLeftBlocked = 1;
            else if (i > _currCol)
                isRightBlocked = 1;
        }
    }

    // Check top - bottom
    for (int i = 0; i < 99; ++i){
        if (i == _currRow)
            continue;

        if (_treeMap[_currRow][_currCol] <= _treeMap[i][_currCol]){
            if (i < _currRow)  
                isTopBlocked = 1;
            else if (i > _currRow)
                isBottomBlocked = 1;
        }
    }

    return !(isTopBlocked && isBottomBlocked && isLeftBlocked && isRightBlocked);
}

int Part_1(int _treeMap[][99]){
    int visibleTreeCount = 0;
    for (int i = 0; i < 99; ++i){
        for (int j = 0; j < 99; ++j){
            if (IsTreeVisible(_treeMap, i, j)){
                ++visibleTreeCount;
            }
        }
    }

    return visibleTreeCount;
}

int ComputeScenicScore(int _treeMap[][99], int _currRow, int _currCol){
    int numOfVisibleTreesTop, numOfVisibleTreesBottom, numOfVisibleTreesLeft, numOfVisibleTreesRight;
    numOfVisibleTreesTop = numOfVisibleTreesBottom = numOfVisibleTreesLeft = numOfVisibleTreesRight = 0;

    // Check left
    for (int i = _currCol - 1; i >= 0; --i){
        ++numOfVisibleTreesLeft;
        if (_treeMap[_currRow][_currCol] <= _treeMap[_currRow][i]){
            break;
        }
    }

    // Check right
    for (int i = _currCol + 1; i < 99; ++i){
        ++numOfVisibleTreesRight;
        if (_treeMap[_currRow][_currCol] <= _treeMap[_currRow][i]){
            break;
        }
    }

    // Check top
    for (int i = _currRow - 1; i >= 0; --i){
        ++numOfVisibleTreesTop;
        if (_treeMap[_currRow][_currCol] <= _treeMap[i][_currCol]){
            break;
        }
    }

    // Check Bottom
    for (int i = _currRow + 1; i < 99; ++i){
        ++numOfVisibleTreesBottom;
        if (_treeMap[_currRow][_currCol] <= _treeMap[i][_currCol]){
            break;
        }
    }

    return numOfVisibleTreesTop * numOfVisibleTreesBottom * numOfVisibleTreesLeft * numOfVisibleTreesRight;
}

int Part_2(int _treeMap[][99]){
    int highestScenicScore = 0;
    for (int i = 0; i < 99; ++i){
        for (int j = 0; j < 99; ++j){
            int scenicScore = ComputeScenicScore(_treeMap, i, j);
            if (scenicScore >= highestScenicScore)
                highestScenicScore = scenicScore;
        }
    }

    return highestScenicScore;
}

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    // Parse tree heights into tree map
    int treeMap[99][99];
    int ch, row = 0, col = 0;
    while ((ch = fgetc(file)) != EOF){
        if ((char)ch == '\n'){
            col = 0;
            ++row;
        }
        else{
            treeMap[row][col] = ch - '0';
            ++col;
        }
    }

    printf("Visible trees: %d\n", Part_1(treeMap));
    printf("Highest scenic score: %d\n", Part_2(treeMap));

    fclose(file);
    return 0;
}
