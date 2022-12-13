#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

#define NUM_OF_ROWS 41
#define NUM_OF_COLS 161

typedef struct GridInfo GridInfo;
struct GridInfo{
    GridInfo* prev;
    int row, col;
    int gScore;
    int fScore;
    int height;
};

struct Comp{
    bool operator()(const GridInfo* _left, const GridInfo* _right){
        return (_left->fScore > _right->fScore);
    }
};

void ParseInput(GridInfo _grid[][NUM_OF_COLS], GridInfo* _src, GridInfo* _dst);
void FindPath(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst, std::vector<GridInfo*>* _foundPath, bool _isPart2);
int Part_1(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst);
int Part_2(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst);

int main(void){
    GridInfo grid[NUM_OF_ROWS][NUM_OF_COLS] = {NULL};
    GridInfo src = {NULL}, dst = {NULL};
    ParseInput(grid, &src, &dst);

    std::cout << "Part 1: " << Part_1(grid, src, dst) << std::endl;

    // Reset grid before moving to part 2
    for (int i = 0; i < NUM_OF_ROWS; ++i){
        for (int j = 0; j < NUM_OF_COLS; ++j){
            grid[i][j].gScore = 0;
            grid[i][j].fScore = 0;
            grid[i][j].prev = NULL;

            // Reverse height for part 2
            grid[i][j].height = 25 - grid[i][j].height;
        }
    }

    std::cout << "Part 2: " << Part_2(grid, src, dst) << std::endl;
    return 0;
}

void ParseInput(GridInfo _grid[][NUM_OF_COLS], GridInfo* _src, GridInfo* _dst){
    std::fstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    std::string line;
    int rowIter = 0, colIter = 0;
    char ch;
    while (file.get(ch)) {
        if (ch == '\n'){
            ++rowIter;
            colIter = 0;
            continue;
        }

        _grid[rowIter][colIter].row = rowIter;
        _grid[rowIter][colIter].col = colIter;
        _grid[rowIter][colIter].height = (int)(ch - 'a');

        if (ch == 'S'){
            _src->row = rowIter;
            _src->col = colIter;
            _grid[rowIter][colIter].height = 0;
        }
        else if (ch == 'E'){
            _dst->row = rowIter;
            _dst->col = colIter;
            _grid[rowIter][colIter].height = 25;
        }
        
        ++colIter;
    }

    file.close();
}

void FindPath(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst, std::vector<GridInfo*>* _foundPath, bool _isPart2){
    std::priority_queue <GridInfo*, std::vector<GridInfo*>, Comp> openSet;
    bool closedSet[NUM_OF_ROWS][NUM_OF_COLS] = {false};
    bool isAlreadyInOpenSet[NUM_OF_ROWS][NUM_OF_COLS] = {false};
    openSet.push(&_grid[_src.row][_src.col]);

    GridInfo* current = NULL;
    while(!openSet.empty()){
        // Remove lowest fscore from openset
        current = openSet.top();
        openSet.pop();
        isAlreadyInOpenSet[current->row][current->col] = false;
        
        // Get current node's neighbours while performing out-of-bounds check
        std::vector<GridInfo*> neighbours;
        if((current->row - 1) >= 0){
            neighbours.push_back(&_grid[current->row - 1][current->col]); // up
        }
        if ((current->row + 1 < NUM_OF_ROWS)){
            neighbours.push_back(&_grid[current->row + 1][current->col]); // down
        }
        if ((current->col - 1) >= 0){
            neighbours.push_back(&_grid[current->row][current->col - 1]); // left
        }
        if ((current->col + 1) < NUM_OF_COLS){
            neighbours.push_back(&_grid[current->row][current->col + 1]); // right
        }

        for (int i = 0; i < neighbours.size(); ++i){
            // If height is unreachable, skip
            if (neighbours[i]->height - current->height > 1){
                continue;
            }
            
            // If neighbour is in the closed set, skip
            if (closedSet[neighbours[i]->row][neighbours[i]->col]){
                continue;
            }

            // For Part 1: If neighbour is the goal, stop and return path
            if (!_isPart2 && (neighbours[i]->row == _dst.row) && (neighbours[i]->col == _dst.col)){
                //_foundPath->push_back(neighbours[i]);
                GridInfo* mover = current;
                while(mover){
                    _foundPath->insert(_foundPath->begin(), mover);
                    mover = mover->prev;
                }
                return;
            }

            // For part 2, stop when program has found a neighbour with the needed height
            if (_isPart2 && neighbours[i]->height == 25){
                GridInfo* mover = current;
                while(mover){
                    _foundPath->insert(_foundPath->begin(), mover);
                    mover = mover->prev;
                }
                return;
            }

            // Compute g, h and f score for neighbour
            int newGScore = current->gScore + 1; // 1 is the distance between current and neighbour
            int newHScore = abs(neighbours[i]->row - _dst.row) + abs(neighbours[i]->col - _dst.col);
            int newFScore = newGScore + newHScore;

            // If neighbour is already in openset and has a lower fscore than current, skip
            if (isAlreadyInOpenSet[neighbours[i]->row][neighbours[i]->col] && (newFScore > neighbours[i]->fScore))
                continue;

            // Update g and f score
            neighbours[i]->gScore = newGScore;
            neighbours[i]->fScore = newFScore;
            neighbours[i]->prev = current;

            // If not in openset, add into openset
            if (!isAlreadyInOpenSet[neighbours[i]->row][neighbours[i]->col]){
                isAlreadyInOpenSet[neighbours[i]->row][neighbours[i]->col] = true;
                openSet.push(neighbours[i]);
            }
        }

        closedSet[current->row][current->col] = true;

        // Visualization
        /*
        for (int i = 0; i < NUM_OF_ROWS; ++i){
            for (int j = 0; j < NUM_OF_COLS; ++j){
                if (i == _dst.row && j == _dst.col)
                    std::cout << "E";
                else
                    std::cout << closedSet[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        */
    }
}

int Part_1(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst){
    std::vector<GridInfo*> foundPath;
    FindPath(_grid, _src, _dst, &foundPath, false);
    return foundPath.size();
}

int Part_2(GridInfo _grid[][NUM_OF_COLS], GridInfo _src, GridInfo _dst){
    std::vector<GridInfo*> foundPath;
    FindPath(_grid, _dst, _src, &foundPath, true);
    return foundPath.size();
}
