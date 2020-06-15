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

bool AddTreeNode(PTree* tree, void* k, FILE* output, dim(*cmp)(void*, void*))
{
	PTree NewNode, Parent;

	if (IsKeyExistsInTree(*tree, k, cmp))
	{
		fputs("Cannot add the same key twice\n", output);
		return false;
	}

	if ((NewNode = (PTree)malloc(sizeof(TreeNode))) == NULL)
	{
		// TODO: Free all program memory
		ConsoleErrorMsg(ERROR_MEM_ALLOCATION_MSG);
	}

	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Key = k;

	/* if tree is empty, sets as first node */
	if (*tree == NULL)
	{
		*tree = NewNode;
		return true;
	}

	Parent = GetCorrectPos(*tree, NewNode->Key, cmp);
	if (cmp(NewNode->Key, Parent->Key) == bigger)
		Parent->Right = NewNode;
	else
		Parent->Left = NewNode;
	return true;
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
	fprintf(output, "the height of your tree is %d\n", GetTreeHeight(tree));
}

void PrintMaxKey(PTree tree, FILE* output, void(print)(void*, FILE*))
{
	if (tree == NULL)
	{
		fputs("No max key in your tree since its empty", output);
		return;
	}

	while (tree->Right != NULL)
		tree = tree->Right;
	fputs("The maximum is ", output);
	print(tree->Key, output);
	fputs("\n", output);
}

void PrintKMin(PTree tree, int k, FILE* output, void(print)(void*, FILE*))
{
	int count = CountTreeNodes(tree);
	if (k < 1)
		return;

	if (k > count)
	{
		fprintf(output, "There are no %d elements in this tree", k);
		return;
	}

	if (tree->Left != NULL)
	{
		tree = tree->Left;
		PrintKMin(tree, k - 1, output, print);
	}
	if (tree->Right != NULL)
	{
		tree = tree->Right;
		PrintKMin(tree, k - 1, output, print);
	}
	print(tree->Key, output);
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
	if (tree->Left == NULL && cmp(k, tree->Key) == lower)
		return tree;
	if (tree->Right == NULL && cmp(k, tree->Key) == bigger)
		return tree;
	return GetCorrectPos(cmp(tree->Key, k) == bigger ? tree->Right : tree->Left, k, cmp);
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
	if (tree->Left == NULL && tree->Right == NULL)
		return 1;
	return CountTreeNodes(tree->Left) + CountTreeNodes(tree->Right);
}