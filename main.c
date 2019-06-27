#include "Çì´õ.h"

int main()
{
	//make BST and initialize
	treePointer* BST[numRow];
	for (int i = 0; i < numRow; i++) {
		BST[i] = NULL;
		for(int j=0; j<numCol; j++)
			BSTInsert(*BST+i, matrix[i][j],i);
	}

	//make loser tree
	treePointer* loserTree[numRow * 2];// = (treePointer*)malloc(sizeof(treePointer) * numRow * 2);

	//make space for winner
	treePointer* winner[numRow];// = (treePointer*)malloc(sizeof(treePointer) * numRow);

	SetLeafNodes(loserTree, BST);

	//set nonleaf nodes of loser tree and print first winner
	SetNonleafNodes(loserTree, winner);
	PrintWinner(loserTree);
	BSTRemove(BST[(*loserTree[0])->data.row], *loserTree[0]);

	//restructure loser tree and print winners
	while (isEmpty(BST)) {
		Restructure(loserTree, winner);
		PrintWinner(loserTree);
		BSTRemove(BST[(*loserTree[0])->data.row], *loserTree[0]);
	}
	return 0;
}


void BSTInsert(treePointer* pRoot, int k, int row)
{
	/*if tree has a node whose key is same as k, count + 1
	  if tree doesn't have a node with k, make a new node and place it on right place
	*/

	treePointer ptr, temp = modifiedSearch(*pRoot, k);
	if (temp || !(*pRoot)) {
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.row = row;
		ptr->data.count = 0;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*pRoot)
			if (k < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		else *pRoot = ptr;
	}
}

treePointer modifiedSearch(treePointer tree, int k)
{
	/* return pointer of node whose key is k
	   if tree is not empty and doesn't have that kind of node, return latest visited node
	   if tree is empty, return NULL
	*/
	treePointer cNode = tree;

	while (cNode) {
		if (k == cNode->data.key) return cNode;
		if (k < cNode->data.key)
			if (cNode->leftChild)
				cNode = cNode->leftChild;
			else
				return cNode;
		else
			if (cNode->rightChild)
				cNode = cNode->rightChild;
			else
				return cNode;
	}
	return NULL;
}

/*
void BSTMakeAndInit(treePointer* pRoot)
{
	*pRoot = NULL;
}
*/
Element BSTGetNodeData(treePointer bst)
{
	return GetData(bst);
}

void RemoveLeftSubTree(treePointer bt)
{
	treePointer delNode;

	if (bt != NULL) {
		delNode = bt->leftChild;
		bt->leftChild = NULL;
	}
}

void RemoveRightSubTree(treePointer bt)
{
	treePointer delNode;

	if (bt != NULL) {
		delNode = bt->rightChild;
		bt->rightChild = NULL;
	}
}

void ChangeLeftSubTree(treePointer main, treePointer sub)
{
	main->leftChild = sub;
}

void ChangeRightSubTree(treePointer main, treePointer sub)
{
	main->rightChild = sub;
}

treePointer BSTRemove(treePointer* pRoot, treePointer delNode)
{
	Element target = GetData(delNode);
	treePointer pVRoot = MakeBTreeNode();
	treePointer pNode = pVRoot;
	treePointer cNode = *pRoot;
	treePointer dNode;

	ChangeRightSubTree(pVRoot, *pRoot);

	while ((cNode != NULL) && (GetData(cNode).key != target.key))
	{
		pNode = cNode;
		if (target.key < GetData(cNode).key)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if (cNode == NULL)
		return NULL;

	dNode = cNode;

	if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if (GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}
	else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		treePointer dcNode;

		if (GetLeftSubTree(dNode) != NULL)
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);

		if (GetLeftSubTree(pNode) == dNode)
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}
	else
	{
		treePointer mNode = GetRightSubTree(dNode);
		treePointer mpNode = dNode;
		Element delData;

		while (GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}

		delData = GetData(dNode);
		SetData(dNode, GetData(mNode));

		if (GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode;
		SetData(dNode, delData);
	}

	if (GetRightSubTree(pVRoot) != *pRoot)
		* pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);
	return dNode;
}

int isEmpty(treePointer** BST)
{
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numCol; j++)
			if (BST[i][j] != NULL)
				return 0;
	return 1;
}


treePointer MakeBTreeNode(void)
{
	treePointer nd;
	MALLOC(nd, sizeof(Node));
	nd->leftChild = NULL;
	nd->rightChild = NULL;
	return nd;
}

Element GetData(treePointer bt)
{
	return bt->data;
}

void SetData(treePointer bt, Element data)
{
	bt->data = data;
}

treePointer GetLeftSubTree(treePointer bt)
{
	return bt->leftChild;
}
treePointer GetRightSubTree(treePointer bt)
{
	return bt->rightChild;
}

void MakeLeftSubTree(treePointer main, treePointer sub)
{
	if (main->leftChild)
		free(main->leftChild);

	main->leftChild = sub;
}

void MakeRightSubTree(treePointer main, treePointer sub)
{
	if (main->rightChild)
		free(main->rightChild);

	main->rightChild = sub;
}


treePointer* Compare(treePointer* tree1, treePointer* tree2)
{
	/*compare two nodes
	priority: 1. count 2. key 3.row
	*/
	if (*tree1 == NULL) return tree2;
	if (*tree2 == NULL) return tree1;

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
			else
				return tree2;
}

void SetLeafNodes(treePointer** loserTree, treePointer** BST)
{
	for (int i = 0; i < numRow; i++)
		loserTree[numRow * 2 - (i + 1)] = BST[i];
}

void SetNonleafNodes(treePointer** loserTree, treePointer** winner)
{
	for (int i = numRow - 1; i > 0; i--) {
		if ((*(loserTree[i]))->leftChild->leftChild == NULL && ((*(loserTree[i]))->rightChild->leftChild != NULL)) {
			winner[i] = Compare(loserTree[i * 2 + 1], winner[i * 2]);
			if (winner[i] == loserTree[i * 2 + 1])
				loserTree[i] = winner[i * 2];
			else
				loserTree[i / 2] = loserTree[i * 2 + 1];
		}

		else if ((*(loserTree[i]))->leftChild->leftChild == NULL && ((*(loserTree[i]))->rightChild->leftChild == NULL)) {
			winner[i] = Compare(loserTree[i * 2], loserTree[i * 2 + 1]);
			if (winner[i] == loserTree[i * 2])
				loserTree[i] = loserTree[i * 2 + 1];
			else
				loserTree[i] = loserTree[i * 2];
		}

		else {
			winner[i] = Compare(winner[i * 2], winner[i * 2 + 1]);
			if (winner[i] == winner[i * 2])
				loserTree[i] = winner[i * 2 + 1];
			else
				loserTree[i] = winner[i * 2];
		}
	}

	loserTree[0] = winner[1];
}

void PrintWinner(treePointer** loserTree)
{
	printf("(%d, %d, %d)\n", (*loserTree[0])->data.row, (*loserTree[0])->data.key, (*loserTree[0])->data.count);
}

void Restructure(treePointer** loserTree, treePointer** winner)
{
	int i = numRow * 2 - 1 - (*loserTree[0])->data.row;
	while (i) {
		winner[i / 2] = Compare(loserTree[i], loserTree[i / 2]);
		if (winner[i / 2] == loserTree[i / 2])
			loserTree[i / 2] = loserTree[i];

		i = i / 2;
	}

	loserTree[0] = winner[1];
}