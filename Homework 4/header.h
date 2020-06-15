#ifndef _HEADER_FILE_
#define _HEADER_FILE_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define ERROR_LOCATE_FILE_MSG "Could not locate file. Exiting..."
#define ERROR_MEM_ALLOCATION_MSG "Failed to allocate memory. Exiting..."

#define INSTRUCTIONS_FILE "Instructions.txt"
#define OUTPUT_FILE "Output.txt"

typedef enum { false, true }bool;
typedef enum { lower = -1, equal = 0, bigger = 1 }dim;

typedef struct Tree* PTree;

/**
 * Outputs a meesage to the console and exits the program afterwards
 *
 * @param msg Error to output
 * @note exits The program with errorcode EXIT_FAILURE
 */
void ConsoleErrorMsg(const char* msg);

bool AddTreeNode(PTree* tree, void* k, FILE* output, dim(*cmp)(void*, void*));
void PrintInorder(PTree tree, FILE* output, void(print)(void*, FILE*));
void PrintTreeHeight(PTree tree, FILE* output);
void PrintMaxKey(PTree tree, FILE* output, void(print)(void*, FILE*));
void PrintKMin(PTree tree, int k, FILE* output, void(print)(void*, FILE*));

bool IsKeyExistsInTree(PTree tree, void* k, dim(*cmp)(void*, void*));
PTree GetCorrectPos(PTree tree, void* k, dim(*cmp)(void*, void*));
int GetTreeHeight(PTree tree);
int CountTreeNodes(PTree tree);

#endif