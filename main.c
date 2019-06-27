#include "���.h"
int main()
{
	loser_tree();
	return 0;
}

void BSTInsert(treePointer* node, int key, int row)
{
	//Ʈ�� �� ��� �� ���� �������� ������ ��尡 ������ �ش� ����� count���� 1 ������Ų��.
	//�׷��� ���� ���� data = (row, key, 0)�� �� ��带 ÷��

	treePointer ptr = NULL, temp;
	temp = modifiedSearch((*node), key);
	
	//Ʈ���� key���� ���� ��尡 ���ų� ����ִ� Ʈ���� ���
	if (temp || !(*node))
	{
		//ptr�̶�� ��带 ����� (key, count, row)��� data field�� �������� �Ѵ�.
		MALLOC(ptr, sizeof(*ptr));

		ptr->data.key = key;
		ptr->data.count = 0;
		ptr->data.row = row;
		ptr->leftChild = ptr->rightChild = NULL;

		//Ʈ���� ������ �ƴϸ� ���� ���� ptr��带 �˸��� �ڸ��� ��ġ��Ų��.
		if (*node)
		{
			if (key < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		}
		//Ʈ���� �����̸� ptr��� �׳� �߰�
		else *node = ptr;
	}
	//Ʈ���� key���� ���� ��尡 �ִ� ��쿡 �ش� ����� count���� 1������Ų��.
	else
	{
		while (*node) {
			if ((*node)->data.key == key) {
				(*node)->data.count++;
				break;
			}
			else if ((*node)->data.key > key)
				(*node) = (*node)->rightChild;
			else
				(*node) = (*node)->leftChild;
		}
	}

	//return node;
}

treePointer modifiedSearch(treePointer tree, int key)
{
	/*
	Ʈ���� �����̰ų� key�� �����ϸ� NULL���� ��ȯ�ϰ�
	�׷��� ������ Ž�� ���߿� ���������� �˻��� ��忡 ���� �����͸� ��ȯ�Ѵ�.*/
	while (tree)
	{
		//key���� �����ϸ� null ��ȯ
		if (key == tree->data.key) return NULL;

		//key�� tree�� ����Ű�� ����� key������ ���� ���
		if (key < tree->data.key) {

			//tree�� ����Ű�� ��尡 ���� �ڽ� ������ ���
			if (tree->leftChild)
				tree = tree->leftChild;
			//��尡 ���� �ڽ� ������ �ʴ� ���
			else
				break;
		}
		//key�� ����� key������ ū ���
		else {
			//��尡 ������ �ڽ� ������ ���
			if (tree->rightChild)
				tree = tree->rightChild;
			else
				break;
		}
		//���������� �˻��� ��� ��ȯ
		return tree;
	}
}
void BSTMakeAndInit(treePointer* pRoot)
{
	*pRoot = NULL;
}

treePointer make_BST(int row)
{
	/*matrix�� row�� ���� binary search tree�� ����� ��带 ����Ű�� �����͸� ��ȯ�Ѵ�.
	*/
	treePointer bstRoot;
	BSTMakeAndInit(&bstRoot);
	for (int i = 0; i < numCol; i++) {	
	BSTInsert(&bstRoot, matrix[row][i], row);
	}
	return bstRoot;
}
void loser_tree()
{
	//leaf node�� numRow���̹Ƿ� ��� ���� 2*numRow�� losertree �����
	treePointer* loserTree[2 * numRow];
	treePointer* winner_of_losertree[numRow];
	
	//loser tree�� leaf node �ʱ�ȭ
	for (int i = 0; i < numRow; i++) { 
		treePointer bstRoot = make_BST(i);
		treePointer* bigCount = search_big_count(bstRoot);
		loserTree[numRow + i] = bigCount;
	}
	for (int i = numRow * 2 - 1; i > 1; i = i - 2) {
		//�ڽ��� �ִ� ���� ���� ��带 ���� ��
		if(((*(loserTree[i-1]))->leftChild != NULL) && ((*(loserTree[i]))->leftChild == NULL)){		
			winner_of_losertree[i / 2] = compare(loserTree[i], winner_of_losertree[i - 1]);
			if (winner_of_losertree[i / 2] == loserTree[i])
				loserTree[i / 2] = winner_of_losertree[i - 1];
			else
				loserTree[i / 2] = loserTree[i];
		}

		//�Ѵ� �ڽ��� ���� ��(�Ѵ� leaf node�� ��)
		else if ((*(loserTree[i - 1]))->leftChild == NULL && ((*(loserTree[i]))->leftChild == NULL)) {
			winner_of_losertree[i / 2] = compare((*(loserTree[i])), (*(loserTree[i - 1])));
			if (winner_of_losertree[i / 2] == loserTree[i])
				loserTree[i / 2] = loserTree[i-1];
			else
				loserTree[i / 2] = loserTree[i];
		}
		//�Ѵ� �ڽ��� ������
		else {
				winner_of_losertree[i / 2] = compare((*(winner_of_losertree[i])), (*(winner_of_losertree[i - 1])));
				if (winner_of_losertree[i / 2] == winner_of_losertree[i])
					loserTree[i / 2] = winner_of_losertree[i - 1];
				else
					loserTree[i / 2] = winner_of_losertree[i];
		}
	}
	
	//���� ���� ����
	loserTree[0] = winner_of_losertree[1];
	
	//���� ���� ���
	printf("(%d, %d, %d)\n", (*(loserTree[0]))->data.row, (*(loserTree[0]))->data.key, (*(loserTree[0]))->data.count);

	//���� ���ڰ� �ִ� ��� -1�� ����
	(*(loserTree[0]))->data.key = -1;
	(*(loserTree[0]))->data.count = -1;
	
	//�θ���� ��
	while((*(loserTree[0]))->data.key != -1)
		Restructuring(&loserTree, &winner_of_losertree);
}

void Restructuring(treePointer*** loserTree, treePointer*** winner_of_losertree)
{
	int i = numRow + (**loserTree[0])->data.row;
	while (i) {
		//�θ���� �ڽĳ�� ��
		winner_of_losertree[i/2] = compare(*loserTree[i], *loserTree[i / 2]);
		if (winner_of_losertree[i / 2] == loserTree[i])
			loserTree[i / 2] = loserTree[i / 2];
		//�θ���� �̵�
		i = i / 2;
	}
	//��Ʈ��忡 ���� ���� ����
	loserTree[0]= winner_of_losertree[1];

	//���� ���� ���
	printf("(%d, %d, %d)\n", (**loserTree[0])->data.row, (**loserTree[0])->data.key, (**loserTree[0])->data.count);

	//���� ���ڰ� �ִ� ��� -1�� ����
	(**loserTree[0])->data.key = -1;
	(**loserTree[0])->data.count = -1;
}
treePointer* search_big_count(treePointer tree)
{
	/*tree�� ��� �� count�� ���� ū ����� ������ ��ȯ
	*/
	if (tree) return NULL;
	//root����� count�� ���� ũ�ٰ� ����
	treePointer* big_count = &tree;

	/*tree�� null�̸� null ��ȯ, null�� �ƴϸ� count�� ū ��� ã��*/
	if (big_count) {
		big_count = compare(search_big_count(tree->leftChild), tree);
		big_count = compare(search_big_count(tree->rightChild), big_count);
	}
	return big_count;
}

// winner return
treePointer* compare(treePointer* tree1, treePointer* tree2)
{
	
	if (tree1 == NULL)
		return tree2;
	if (tree2 == NULL)
		return tree1;
		
	/*count -> ������ -> row�� ������ ũ�⸦ ���Ͽ� �� ū ��� ��ȯ*/
	if ((*tree1)->data.count > (*tree2)->data.count)
		return tree1;
	else if ((*tree1)->data.count < (*tree2)->data.count)
		return tree2;
	else
		if ((*tree1)->data.key > (*tree2)->data.key)
			return tree1;
		else if ((*tree1)->data.key < (*tree2)->data.key)
			return tree2;
		else
			if ((*tree1)->data.row > (*tree2)->data.row)
				return tree1;
			else if ((*tree1)->data.row < (*tree2)->data.row)
				return tree2;
			else
				return tree2;
}
