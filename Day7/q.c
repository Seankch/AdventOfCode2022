#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STRING_BUFFER_SIZE 40

typedef enum TYPE{
    TYPE_DIRECTORY,
    TYPE_FILE
}TYPE;

typedef struct TreeNode{
    char nodeName[STRING_BUFFER_SIZE];
    struct TreeNode* prev;
    struct TreeNode* childNodes[50];
    int childNodeSize;
    int nodeSize;
    TYPE nodeType;
}TreeNode;

void InitNode(TreeNode* _node){
    _node->prev = NULL;
    _node->childNodeSize = 0;
    _node->nodeSize = 0;
    _node->nodeType = TYPE_DIRECTORY;
    memset(_node->childNodes, 0, sizeof(_node->childNodes));
}

int IsDirectoryOrFile(char const* _buffer, char _nodeName[], int* _fileSize, TYPE* _type){
    memset(_nodeName, 0, STRING_BUFFER_SIZE);
    if (*_buffer == 'd' && *(_buffer + 1) == 'i' && *(_buffer + 2) == 'r'){
        *_type = TYPE_DIRECTORY;
        *_fileSize = 0;
        int iter = 4;
        while (*(_buffer + iter) != '\n'){
            _nodeName[iter - 4] = *(_buffer + iter);
            ++iter;
        }
        _nodeName[iter - 4] = '\0';

        return 1;
    }
    else if (*_buffer != '$' && sscanf(_buffer, "%d", _fileSize) != EOF){
        *_type = TYPE_FILE;
        int iter = 0, offset, startCopying = 0;
        while (*(_buffer + iter) != '\n'){
            if (!startCopying){
                if (*(_buffer + iter) == ' '){
                    startCopying = 1;
                    offset = iter + 1; // + 1 to skip the space
                }
            }
            else{
                _nodeName[iter - offset] = *(_buffer + iter);
            }

            ++iter;
        }

        _nodeName[iter - offset] = '\0';
        return 1;
    }

    return 0;
}

void InsertTreeNode(TreeNode* _prev, char const* _nodeName, int _size, TYPE _type){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    InitNode(newNode);

    _prev->childNodes[_prev->childNodeSize++] = newNode;
    newNode->prev = _prev;
    strcpy(newNode->nodeName, _nodeName);
    newNode->nodeSize = _size;
    newNode->nodeType = _type;

    // Increment size of previous directories
    if (newNode->nodeType == TYPE_FILE){
        TreeNode* mover = newNode->prev;
        while (mover){
            mover->nodeSize += newNode->nodeSize;
            mover = mover->prev;
        }
    }
}

void CreateTree(TreeNode* _root){
    FILE *file = fopen("input.txt", "r");
    if (!file){
        // If file cannot be opened, return NULL
        return;
    }

    int fileSize = 0;
    TYPE currNodeType;
    TreeNode* mover = _root;
    char nodeName[STRING_BUFFER_SIZE] = {'\0'};
    char buffer[STRING_BUFFER_SIZE] = {'\0'};
    while (fgets(buffer, STRING_BUFFER_SIZE, file)){
        if (IsDirectoryOrFile(buffer, nodeName, &fileSize, &currNodeType)){
            InsertTreeNode(mover, nodeName, fileSize, currNodeType);
        }
        else if (*buffer == '$'){
            if (*(buffer + 2) == 'c' && *(buffer + 3) == 'd'){
                if (*(buffer + 5) == '.' && *(buffer + 6) == '.'){
                    mover = mover->prev;
                }
                else{
                    // Reset nodeName string buffer
                    memset(nodeName, 0, sizeof(nodeName));
                    
                    // Copy name from buffer to nodeName string buffer
                    int iter = 5;
                    while (*(buffer + iter) != '\n'){
                        nodeName[iter - 5] = *(buffer + iter);
                        ++iter;
                    }
                    nodeName[iter - 5] = '\0';

                    // Search for nodeName among childNodes
                    for (int i = 0; i < mover->childNodeSize; ++i){
                        if (mover->childNodes[i]->nodeType == TYPE_DIRECTORY && !strcmp(mover->childNodes[i]->nodeName, nodeName)){
                            // If childNode is found, move into childNode
                            mover = mover->childNodes[i];
                            break;
                        }
                    }
                }
            }
        }   
    }

    fclose(file);
}

void DeleteTree(TreeNode** _nextNode){
    for (int i = 0; i < (*_nextNode)->childNodeSize; ++i){
        DeleteTree(&((*_nextNode)->childNodes[i]));
    }

    free(*_nextNode);
    *_nextNode = NULL;
}

void Traverse_Part1(TreeNode* _nextNode, int* _totalSum){
    if (_nextNode->nodeType == TYPE_DIRECTORY && _nextNode->nodeSize <= 100000){
        *_totalSum += _nextNode->nodeSize;
    }

    for (int i = 0; i < _nextNode->childNodeSize; ++i){
        if (_nextNode->childNodes[i]->nodeType == TYPE_DIRECTORY)
            Traverse_Part1(_nextNode->childNodes[i], _totalSum);
    }
}

int Part_1(TreeNode* _root){
    int totalSum = 0;

    // Traverse through the tree and compute totalSum
    Traverse_Part1(_root, &totalSum);

    return totalSum;
}

void Traverse_Part2(TreeNode* _nextNode, const int _neededAmt, int* _currSmallestAmt){
    if (_nextNode->nodeSize >= _neededAmt && _nextNode->nodeSize <= (*_currSmallestAmt)){
        *_currSmallestAmt = _nextNode->nodeSize;
    }

    for (int i = 0; i < _nextNode->childNodeSize; ++i){
        if (_nextNode->childNodes[i]->nodeType == TYPE_DIRECTORY)
            Traverse_Part2(_nextNode->childNodes[i], _neededAmt, _currSmallestAmt);
    }
}

int Part_2(TreeNode* _root){
    // Needed amount to delete = updateSize - (currently unused space)
    int neededAmount = 30000000 - (70000000 - _root->nodeSize);
    int currSmallestAmt = _root->nodeSize;
    Traverse_Part2(_root, neededAmount, &currSmallestAmt);

    return currSmallestAmt;
}

int main(void){
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    InitNode(root);
    strcpy(root->nodeName, "/");
    CreateTree(root);

    printf("Part 1: Size of all directories with size at most 100000: %d\n", Part_1(root));
    printf("Part 2: Size of smallest directory needed to be deleted: %d\n", Part_2(root));

    DeleteTree(&root);
    return 0;
}
