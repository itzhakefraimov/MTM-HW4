#ifndef _HEADER_FILE_
#define _HEADER_FILE_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/* Error messages text */
#define ERROR_LOCATE_FILE_MSG "Could not locate file. Exiting..."
#define ERROR_MEM_ALLOCATION_MSG "Failed to allocate memory. Exiting..."

/* Text files names used by the program */
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

/**
 * Adds a Node to the Binary Tree according to the given key
 *
 * @param tree Points to the pointer of the tree
 * @param k Data of the added node
 * @param out Output file
 * @param print ADT print function structure
 * @param cmp ADT compare keys function structure
 * @param cmp ADT free_data function structure
 */
void AddTreeNode(PTree* tree, void* k, FILE* output, void(print)(void*, FILE*), dim(*cmp)(void*, void*), void(free_data)(void*));

/**
 * Prints the Binary Tree using inorder format recursively
 *
 * @param tree Points to tree
 * @param out Output file
 * @param print ADT print function structure
 */
void PrintInorder(PTree tree, FILE* output, void(print)(void*, FILE*));

/**
 * Prints the Binary Tree Height
 *
 * @param tree Points to tree
 * @param out Output file
 */
void PrintTreeHeight(PTree tree, FILE* output);

/**
 * Prints the Maximum Key found in the Binary Tree
 *
 * @param tree Points to tree
 * @param out Output file
 * @param print ADT print function structure
 */
void PrintMaxKey(PTree tree, FILE* output, void(print)(void*, FILE*));

/**
 * Prints the minimum kth elements of the Binary Tree
 *
 * @param tree Points to the tree
 * @param k Amount of min elements to print
 * @param count Count of printed elements
 * @param cound_nodes Count of the tree nodes
 * @param out Output file
 * @param print ADT print function structure
 */
void PrintKMin(PTree tree, int k, int* count, int count_nodes, FILE* output, void(print)(void*, FILE*));

/**
 * Frees the Binary Tree recursively
 *
 * @param tree Points to tree
 * @param cmp ADT free_data function structure
 */
void FreeTree(PTree tree, void(free_data)(void*));

/**
 * Checks if a given key already exists in the Binary Tree
 *
 * @param tree Points to tree
 * @param k Key to check
 * @param cmp ADT compare keys function structure
 * @returns true if exists; false otherwise
 */
bool IsKeyExistsInTree(PTree tree, void* k, dim(*cmp)(void*, void*));

/**
 * Gets the position of the to be added node's parent according to his key
 *
 * @param tree Points to tree
 * @param k Key of the new node
 * @param cmp ADT compare keys function structure
 * @returns Parent's address; NULL otherwise
 */
PTree GetCorrectPos(PTree tree, void* k, dim(*cmp)(void*, void*));

/**
 * Calculates the Binary Tree's Height recursively
 *
 * @param tree Points to tree
 * @returns Height of the tree; -1 if empty
 */
int GetTreeHeight(PTree tree);

/**
 * Calculates the Binary Tree's amount of Nodes recursively
 *
 * @param tree Points to tree
 * @returns Nodes count of the tree; 0 if empty
 */
int CountTreeNodes(PTree tree);

#endif