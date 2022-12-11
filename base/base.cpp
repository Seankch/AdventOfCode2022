#include <iostream>
#include <fstream>
#include <string>

void ParseInput(void);
int Part_1(void);
int Part_2(void);

int main(void){
    ParseInput();
    std::cout << "Part 1: " << Part_1() << std::endl;
    std::cout << "Part 2: " << Part_2() << std::endl;
    return 0;
}

void ParseInput(void){
    std::fstream file;
    file.open("input.txt");
    if (!file.is_open()){
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

int Part_1(void){
    int val = 0;
    return val;
}

int Part_2(void){
    int val = 0;
    return val;
}
