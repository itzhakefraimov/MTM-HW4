#include "header.h"

dim Int_Cmp(void* a, void* b)
{
	return *(int*)a > * (int*)b ?
		bigger : *(int*)a < *(int*)b ?
		lower : equal;
}

void Int_Print(void* a, FILE* out)
{
	fprintf(out, "%d ", *(int*)a);
}

void main()
{
	FILE* instructions = NULL, * output = NULL;
	PTree tree = NULL;
	int instruction, temp_key, * key;

	if (!(instructions = fopen(INSTRUCTIONS_FILE, "rt")))
		ConsoleErrorMsg(ERROR_LOCATE_FILE_MSG);
	if (!(output = fopen(OUTPUT_FILE, "wt")))
		ConsoleErrorMsg(ERROR_LOCATE_FILE_MSG);

	while (fscanf(instructions, "%d", &instruction) != EOF)
	{
		switch (instruction)
		{
		case 1:
			fscanf(instructions, "%d", &temp_key);
			if ((key = (int*)malloc(sizeof(int))) == NULL)
			{
				// TODO: Free all program memory
				ConsoleErrorMsg(ERROR_MEM_ALLOCATION_MSG);
			}
			*key = temp_key;
			if (AddTreeNode(&tree, key, output, Int_Cmp))
				fprintf(output, "%d was added to the tree\n", *(int*)key);
			break;
		case 2:
			PrintInorder(tree, output, Int_Print);
			break;
		case 3:
			PrintTreeHeight(tree, output);
			break;
		case 4:
			PrintMaxKey(tree, output, Int_Print);
			break;
		case 5:
			fscanf(instructions, "%d", &temp_key);
			PrintKMin(tree, temp_key, output, Int_Print);
			break;
		}
	}

	fclose(instructions);
	fclose(output);
}