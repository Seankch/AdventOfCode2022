#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// For part 2
#define TOTAL_NUM_OF_PACKETS 302

enum{
    LEFT_BRACKET = -2,
    RIGHT_BRACKET = -3,
    EMPTY_BRACKET = -1,
    OUT_OF_RANGE = -4
};

bool IsInRightOrder(std::vector<int> _packetData1, std::vector<int> _packetData2);
int Part_1(void);
int Part_2(void);

int main(void){
    std::cout << "Part 1: " << Part_1() << std::endl;
    std::cout << "Part 2: " << Part_2() << std::endl;
    return 0;
}

bool IsValidNumber(int _val){
    return _val >= -1 && _val <= 10;
}

int GetNextNum(const std::vector<int>* _list, int _index, int _maxIndex){
    int iter = _index;
    while(!IsValidNumber((*_list)[iter++]));

    if (iter > _maxIndex){
        return OUT_OF_RANGE;
    }

    return (*_list)[iter - 1];
}

bool IsInRightOrder(const std::vector<int>* _left, const std::vector<int>* _right){
    int minSize = (_left->size() < _right->size())? _left->size() : _right->size();
    for (int i = 0; i < minSize; ++i){
        if ((*_left)[i] == LEFT_BRACKET && IsValidNumber((*_right)[i])){
            int leftNextNum = GetNextNum(_left, i, _left->size());
            if (leftNextNum == OUT_OF_RANGE)
                break;

            if (leftNextNum < (*_right)[i]){
                return true;
            }
            else if (leftNextNum >= (*_right)[i]){
                return false;
            }
        }
        else if ((*_right)[i] == LEFT_BRACKET && IsValidNumber((*_left)[i])){
            int rightNextNum = GetNextNum(_right, i, _right->size());
            if (rightNextNum == OUT_OF_RANGE)
                break;

            if ((*_left)[i] <= rightNextNum){
                return true;
            }
            else if ((*_left)[i] > rightNextNum){
                return false;
            }
        }
        else if (IsValidNumber((*_left)[i]) || IsValidNumber((*_right)[i])){
            int leftNextNum = GetNextNum(_left, i, _left->size());
            int rightNextNum = GetNextNum(_right, i, _right->size());
            if (leftNextNum == OUT_OF_RANGE || rightNextNum == OUT_OF_RANGE)
                break;

            if (leftNextNum < rightNextNum){
                return true;
            }
            else if (leftNextNum > rightNextNum){
                return false;
            }
        }
    }
    
    return (minSize == _left->size());
}

int Part_1(void){
    std::fstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Unable to open file." << std::endl;
        return -1;
    }

    char ch, prevch;
    int sum = 0, pairIndex = 1, packetIndex = 0;
    std::vector<int> packetData[2];
    while (file.get(ch)) {
        // Handle empty lists
        if (ch == ']' && prevch == '['){
            packetData[packetIndex].push_back(EMPTY_BRACKET);
        }

        // Parse input
        if (ch == '['){
            // Append -2 for opening bracket
            packetData[packetIndex].push_back(LEFT_BRACKET);
        }
        else if (ch == ']'){
            // Append -3 for closing bracket
            packetData[packetIndex].push_back(RIGHT_BRACKET);
        }
        else if (ch == '\n' && packetIndex == 2){
            // Skip newline seperator
            packetIndex = 0;
            continue;
        }
        else if (ch >= '0' && ch <= '9'){
            if (prevch >= '0' && prevch <= '9'){
                // Handle double digits
                packetData[packetIndex].pop_back();
                std::string s = std::to_string(prevch - '0') + std::to_string(ch - '0');
                packetData[packetIndex].push_back(std::stoi(s));
            }
            else{
                // Handle single digits
                packetData[packetIndex].push_back((int)(ch - '0'));
            }
        }
        else if (ch == '\n'){
            // Increment to parse the second packet
            ++packetIndex;

            // Both packets have been parsed, do comparison
            if (packetIndex == 2){
                if (IsInRightOrder(&packetData[0], &packetData[1])){
                    sum += pairIndex;
                }

                ++pairIndex;
                for(int i = 0; i < 2; ++i){
                    packetData[i].clear();
                }
            }
        }

        prevch = ch;
    }

    file.close();
    return sum;
}

int Part_2(void){
    std::fstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Unable to open file." << std::endl;
        return -1;
    }

    int packetIndex = 0;
    std::vector<int> packetData[TOTAL_NUM_OF_PACKETS];
    // Add [[2]] and [[6]]
    for (; packetIndex < 2; ++packetIndex){
        packetData[packetIndex].push_back(LEFT_BRACKET);
        packetData[packetIndex].push_back(LEFT_BRACKET);
        packetData[packetIndex].push_back(((packetIndex == 0)? 2 : 6));
        packetData[packetIndex].push_back(RIGHT_BRACKET);
        packetData[packetIndex].push_back(RIGHT_BRACKET);
    }
    
    char ch, prevch;
    while (file.get(ch)) {
        // Handle empty lists
        if (ch == ']' && prevch == '['){
            packetData[packetIndex].push_back(EMPTY_BRACKET);
        }

        // Parse input
        if (ch == '['){
            // Append -2 for opening bracket
            packetData[packetIndex].push_back(LEFT_BRACKET);
        }
        else if (ch == ']'){
            // Append -3 for closing bracket
            packetData[packetIndex].push_back(RIGHT_BRACKET);
        }
        else if (ch >= '0' && ch <= '9'){
            if (prevch >= '0' && prevch <= '9'){
                // Handle double digits
                packetData[packetIndex].pop_back();
                std::string s = std::to_string(prevch - '0') + std::to_string(ch - '0');
                packetData[packetIndex].push_back(std::stoi(s));
            }
            else{
                // Handle single digits
                packetData[packetIndex].push_back((int)(ch - '0'));
            }
        }
        else if (ch == '\n'){
            if (prevch == '\n'){
                // skip newline
                continue;
            }
            else{
                // Increment to parse the next packet
                ++packetIndex;
            }
        }

        prevch = ch;
    }

    // Save [[2]] and [[6]] before sorting
    std::vector<int> temp2 = packetData[0];
    std::vector<int> temp6 = packetData[1];

    // Packets have been parsed, now to sort them (bubble sort)
    for (int i = 0; i < TOTAL_NUM_OF_PACKETS - 1; ++i){
        for (int j = 0; j < TOTAL_NUM_OF_PACKETS - i - 1; ++j){
            if (!IsInRightOrder(&packetData[j], &packetData[j + 1])){
                std::vector<int> swapper = packetData[j];
                packetData[j] = packetData[j + 1];
                packetData[j + 1] = swapper;
            }
        }
    }

    // Search for [[2]] and [[6]] and compute result
    int result = 1;
    for (int i = 0; i < TOTAL_NUM_OF_PACKETS; ++i){
        if (packetData[i] == temp2 || packetData[i] == temp6){
            result *= (i + 1);
        }
    }

    file.close();
    return result;
}
