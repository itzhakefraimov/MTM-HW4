#include "header.h"

typedef struct Tree
{
	void* Key;
	struct Tree* Left;
	struct Tree* Right;
}TreeNode;

void ConsoleErrorMsg(const char* msg)
{
	printf("\n%s", msg);
	exit(EXIT_FAILURE);
}

void AddTreeNode(PTree* tree, void* k, FILE* output, void(print)(void*, FILE*), dim(*cmp)(void*, void*), void(free_data)(void*))
{
	PTree NewNode, Parent;

	if (IsKeyExistsInTree(*tree, k, cmp))
	{
		fputs("\nCannot add the same key twice", output);
		return;
	}
	if ((NewNode = (PTree)malloc(sizeof(TreeNode))) == NULL)
	{
		free(k);
		FreeTree(*tree, free_data);
		ConsoleErrorMsg(ERROR_MEM_ALLOCATION_MSG);
	}
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Key = k;
	/* if tree is empty, sets as first node */
	if (*tree == NULL)
		*tree = NewNode;
	/* otherwise, gets the parent of the new node */
	else
	{
		Parent = GetCorrectPos(*tree, NewNode->Key, cmp);
		if (cmp(NewNode->Key, Parent->Key) == bigger)
			Parent->Right = NewNode;
		else
			Parent->Left = NewNode;
	}
	fputs("\n", output);
	print(NewNode->Key, output);
	fputs("was added to the tree", output);
}

void PrintInorder(PTree tree, FILE* output, void(print)(void*, FILE*))
{
	if (tree == NULL)
		return;
	PrintInorder(tree->Left, output, print);
	print(tree->Key, output);
	PrintInorder(tree->Right, output, print);
}

void PrintTreeHeight(PTree tree, FILE* output)
{
	fprintf(output, "\nthe height of your tree is %d", GetTreeHeight(tree));
}

void PrintMaxKey(PTree tree, FILE* output, void(print)(void*, FILE*))
{
	if (tree == NULL)
	{
		fputs("\nNo max key in your tree since its empty", output);
		return;
	}
	while (tree->Right != NULL)
		tree = tree->Right;
	fputs("\nThe maximum is ", output);
	print(tree->Key, output);
}

void PrintKMin(PTree tree, int k, int* count, int count_nodes, FILE* output, void(print)(void*, FILE*))
{
	if (tree == NULL || *count >= k)
		return;
	if (k > count_nodes)
	{
		fprintf(output, "\nThere are no %d elements in this tree", k);
		return;
	}
	/* prints leftside, starting from the lowest (recursive) */
	PrintKMin(tree->Left, k, count, count_nodes, output, print);
	/* prints as long as the count of printed elements is less than k */
	if (*count < k)
	{
		if (*count == 0)
			fprintf(output, "\nThere are %d small elements in this tree: ", k);
		(*count)++;
		print(tree->Key, output);
	}
	/* prints right side if there weren't enough smaller elements on the left branch */
	PrintKMin(tree->Right, k, count, count_nodes, output, print);
}

void FreeTree(PTree tree, void(free_data)(void*))
{
	if (tree == NULL)
		return;
	FreeTree(tree->Left, free_data);
	FreeTree(tree->Right, free_data);
	free_data(tree->Key);
	free(tree);
}

bool IsKeyExistsInTree(PTree tree, void* k, dim(*cmp)(void*, void*))
{
	if (tree == NULL)
		return false;
	if (cmp(tree->Key, k) == equal)
		return true;
	return IsKeyExistsInTree((k > tree->Key) ? tree->Left : tree->Right, k, cmp);
}

PTree GetCorrectPos(PTree tree, void* k, dim(*cmp)(void*, void*))
{
	if (tree->Left == NULL && cmp(k, tree->Key) == lower || tree->Right == NULL && cmp(k, tree->Key) == bigger)
		return tree;
	return GetCorrectPos(cmp(k, tree->Key) == bigger ? tree->Right : tree->Left, k, cmp);
}

int GetTreeHeight(PTree tree)
{
	int left, right;
	if (tree == NULL)
		return -1;
	left = GetTreeHeight(tree->Left);
	right = GetTreeHeight(tree->Right);
	return 1 + (left > right ? left : right);
}

int CountTreeNodes(PTree tree)
{
	if (tree == NULL)
		return 0;
	return 1 + CountTreeNodes(tree->Left) + CountTreeNodes(tree->Right);
}