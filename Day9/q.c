#include <stdio.h>
#include <stdlib.h>

enum{
    HEAD = 0,
    TAIL = 9
};

typedef struct PositionInfo{
    int row;
    int col;
}PositionInfo;

int IsDetached(const PositionInfo _prev, const PositionInfo _curr){
    return (abs(_prev.row - _curr.row) > 1 || abs(_prev.col - _curr.col) > 1);
}

int Normalised(int _val){
    if (_val == 0)
        return _val;

    return (_val < 0)? -(_val / _val) : (_val / _val);
}

int main(void){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return 0;
    }

    // Init rope at 500, 500
    PositionInfo rope[10];
    PositionInfo initalPos = {500, 500};
    for (int i = 0; i < 10; ++i){
        rope[i].row = 500;
        rope[i].col = 500;
    }

    char moveDir;
    int moveCount = 0, tailVisitedCount = 1;
    int grid[1000][1000] = {[500][500] = 1};
    while (fscanf(file, "%c %d%*c", &moveDir, &moveCount) != EOF){
        // Handle Movement
        for (int i = 0; i < moveCount; ++i){
            // Handle head movement
            PositionInfo* head = &rope[HEAD];
            if (moveDir == 'U'){
                --(head->row);
            } 
            else if (moveDir == 'D'){
                ++(head->row);
            }
            else if (moveDir == 'L'){
                --(head->col);
            }
            else if (moveDir == 'R'){
                ++(head->col);
            }

            // Handle tail movement
            for (int ropeIndex = 1; ropeIndex < 10; ++ropeIndex){
                if (IsDetached(rope[ropeIndex - 1], rope[ropeIndex])){
                    rope[ropeIndex].row += Normalised(rope[ropeIndex - 1].row - rope[ropeIndex].row);
                    rope[ropeIndex].col += Normalised(rope[ropeIndex - 1].col - rope[ropeIndex].col);

                    if (ropeIndex == TAIL && (grid[rope[ropeIndex].row][rope[ropeIndex].col] == 0)){
                        grid[rope[ropeIndex].row][rope[ropeIndex].col] = 1;
                        ++tailVisitedCount;
                    }
                }
            }
        }
    }

    printf("Tail visited count: %d\n", tailVisitedCount);
    fclose(file);
    return 0;
}
