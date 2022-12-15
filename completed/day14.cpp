#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <queue>
#include <vector>

#define NUM_OF_ROWS 170
#define NUM_OF_COLS 1000
#define MAX_NUM_OF_SAND 27000

typedef struct SandInfo{
    int x, y;
    bool isAtRest, active;

    SandInfo(int _x, int _y, bool _isAtRest, bool _active):x(_x), y(_y), isAtRest(_isAtRest), active(_active){}
}SandInfo;

void ParseInput(char _grid[][NUM_OF_COLS]);
int Part_1(char _grid[][NUM_OF_COLS], std::vector<SandInfo> _sandPool);
int Part_2(char _grid[][NUM_OF_COLS], std::vector<SandInfo> _sandPool);

int main(void){
    char grid[NUM_OF_ROWS][NUM_OF_COLS] = {0};
    std::vector<SandInfo> sandPool;
    for (int i = 0; i < MAX_NUM_OF_SAND; ++i){
        sandPool.emplace_back(500, 0, false, false);
    }

    ParseInput(grid);
    std::cout << "Part 1: " << Part_1(grid, sandPool) << std::endl;
    
    // Reset grid for part 2
    for (int i = 0; i < NUM_OF_ROWS; ++i){
        for (int j = 0; j < NUM_OF_COLS; ++j){
            grid[i][j] = 0;
        }
    }

    ParseInput(grid);
    std::cout << "Part 2: " << Part_2(grid, sandPool) << std::endl;
    return 0;
}

void DrawLine(char _grid[][NUM_OF_COLS], std::pair<int, int>* _start, std::pair<int, int>* _end){
    int height = _end->second - _start->second;
    int width = _end->first - _start->first;

    if (height != 0){
        int count = abs(height);
        for (int i = 0; i <= count; ++i){
            _grid[_start->second + ((height > 0)? i : -i)][_start->first] = '#';
        }
    }
    else if (width != 0){
        int count = abs(width);
        for (int i = 0; i <= count; ++i){
            _grid[_start->second][_start->first + ((width > 0)? i : -i)] = '#';
        }
    }
}

void ParseInput(char _grid[][NUM_OF_COLS]){
    std::fstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    std::string line, token;
    while (getline(file, line)) {
        std::queue<std::pair<int, int>> drawpaths;
        std::stringstream ss(line);
        while(ss >> token){
            if (token.find("->") != std::string::npos)
                continue;
            
            size_t commaIndex = token.find(",");
            int x = std::stoi(token.substr(0, commaIndex));
            int y = std::stoi(token.substr(commaIndex + 1, token.size() - 1));
            drawpaths.emplace(x, y);
        }

        while(drawpaths.size() > 1){
            // Get start and end of path
            std::pair<int, int> start(drawpaths.front());
            drawpaths.pop(); 
            std::pair<int, int> end(drawpaths.front());

            // Draw on grid
            DrawLine(_grid, &start, &end);
        }
    }

    file.close();
}

int Part_1(char _grid[][NUM_OF_COLS], std::vector<SandInfo> _sandPool){
    int restingSandCount = 0, activeSandCount = 0;
    while(activeSandCount < MAX_NUM_OF_SAND){
        // Spawn sand
        _sandPool[activeSandCount++].active = true;

        // Move sand
        for (int i = 0; i < _sandPool.size(); ++i){
            if (!_sandPool[i].active)
                break;

            if (_sandPool[i].isAtRest)
                continue;

            // Check downwards first
            if (_grid[_sandPool[i].y + 1][_sandPool[i].x] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x] != 'o'){
                _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                ++(_sandPool[i].y);
                _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
            }
            else{
                // Then check bottom left
                if (_grid[_sandPool[i].y + 1][_sandPool[i].x - 1] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x - 1] != 'o'){
                    _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                    ++(_sandPool[i].y);
                    --(_sandPool[i].x);
                    _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
                }
                // Then check bottom right
                else if (_grid[_sandPool[i].y + 1][_sandPool[i].x + 1] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x + 1] != 'o'){
                    _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                    ++(_sandPool[i].y);
                    ++(_sandPool[i].x);
                    _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
                }
                // If all paths below are blocked
                else{
                    ++restingSandCount;
                    _sandPool[i].isAtRest = true;
                }
            }

            // If sand reached the bottom, exit
            if (_sandPool[i].x < 0 || _sandPool[i].x >= NUM_OF_COLS || _sandPool[i].y < 0 || _sandPool[i].y >= NUM_OF_ROWS)
                return restingSandCount;
        }
    }

    return restingSandCount;
}

int Part_2(char _grid[][NUM_OF_COLS], std::vector<SandInfo> _sandPool){
    // Create a floor at the bottom
    for (int i = 0; i < NUM_OF_COLS; ++i){
        _grid[167][i] = '#';
    }

    bool isReachedTop = false;
    int restingSandCount = 0, activeSandCount = 0;
    while((activeSandCount < MAX_NUM_OF_SAND) && !isReachedTop){
        // Spawn sand
        _sandPool[activeSandCount++].active = true;

        // Move sand
        for (int i = 0; i < _sandPool.size(); ++i){
            if (!_sandPool[i].active)
                break;

            if (_sandPool[i].isAtRest)
                continue;

            // Check downwards first
            if (_grid[_sandPool[i].y + 1][_sandPool[i].x] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x] != 'o'){
                _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                ++(_sandPool[i].y);
                _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
            }
            else{
                // Then check bottom left
                if (_grid[_sandPool[i].y + 1][_sandPool[i].x - 1] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x - 1] != 'o'){
                    _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                    ++(_sandPool[i].y);
                    --(_sandPool[i].x);
                    _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
                }
                // Then check bottom right
                else if (_grid[_sandPool[i].y + 1][_sandPool[i].x + 1] != '#' && _grid[_sandPool[i].y + 1][_sandPool[i].x + 1] != 'o'){
                    _grid[_sandPool[i].y][_sandPool[i].x] = ' ';
                    ++(_sandPool[i].y);
                    ++(_sandPool[i].x);
                    _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
                }
                // If all paths below are blocked
                else{
                    ++restingSandCount;
                    _sandPool[i].isAtRest = true;

                    // When sand reaches the top, exit
                    if (_sandPool[i].x == 500 && _sandPool[i].y == 0){
                        _grid[_sandPool[i].y][_sandPool[i].x] = 'o';
                        isReachedTop = true;
                        break;
                    }
                }
            }
        }
    }

    return restingSandCount;
}
