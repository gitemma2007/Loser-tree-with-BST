#include "헤더.h"
int main()
{
	loser_tree();
	return 0;
}

void BSTInsert(treePointer* node, int key, int row)
{
	//트리 내 노드 중 같은 정수값을 가지는 노드가 있으면 해당 노드의 count값을 1 증가시킨다.
	//그렇지 않은 경우는 data = (row, key, 0)인 새 노드를 첨가

	treePointer ptr = NULL, temp;
	temp = modifiedSearch((*node), key);
	
	//트리에 key값이 같은 노드가 없거나 비어있는 트리인 경우
	if (temp || !(*node))
	{
		//ptr이라는 노드를 만들어 (key, count, row)라는 data field를 가지도록 한다.
		MALLOC(ptr, sizeof(*ptr));

		ptr->data.key = key;
		ptr->data.count = 0;
		ptr->data.row = row;
		ptr->leftChild = ptr->rightChild = NULL;

		//트리가 공백이 아니면 새로 만든 ptr노드를 알맞은 자리에 위치시킨다.
		if (*node)
		{
			if (key < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		}
		//트리가 공백이면 ptr노드 그냥 추가
		else *node = ptr;
	}
	//트리에 key값이 같은 노드가 있는 경우에 해당 노드의 count값을 1증가시킨다.
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
	트리가 공백이거나 key가 존재하면 NULL값을 반환하고
	그렇지 않으면 탐색 도중에 마지막으로 검사한 노드에 대한 포인터를 반환한다.*/
	while (tree)
	{
		//key값이 존재하면 null 반환
		if (key == tree->data.key) return NULL;

		//key가 tree가 가리키는 노드의 key값보다 작은 경우
		if (key < tree->data.key) {

			//tree가 가리키는 노드가 왼쪽 자식 가지는 경우
			if (tree->leftChild)
				tree = tree->leftChild;
			//노드가 왼쪽 자식 가지지 않는 경우
			else
				break;
		}
		//key가 노드의 key값보다 큰 경우
		else {
			//노드가 오른쪽 자식 가지는 경우
			if (tree->rightChild)
				tree = tree->rightChild;
			else
				break;
		}
		//마지막으로 검사한 노드 반환
		return tree;
	}
}
void BSTMakeAndInit(treePointer* pRoot)
{
	*pRoot = NULL;
}

treePointer make_BST(int row)
{
	/*matrix의 row에 대한 binary search tree를 만들어 노드를 가리키는 포인터를 반환한다.
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
	//leaf node가 numRow개이므로 노드 수는 2*numRow인 losertree 만들기
	treePointer* loserTree[2 * numRow];
	treePointer* winner_of_losertree[numRow];
	
	//loser tree의 leaf node 초기화
	for (int i = 0; i < numRow; i++) { 
		treePointer bstRoot = make_BST(i);
		treePointer* bigCount = search_big_count(bstRoot);
		loserTree[numRow + i] = bigCount;
	}
	for (int i = numRow * 2 - 1; i > 1; i = i - 2) {
		//자식이 있는 노드와 없는 노드를 비교할 때
		if(((*(loserTree[i-1]))->leftChild != NULL) && ((*(loserTree[i]))->leftChild == NULL)){		
			winner_of_losertree[i / 2] = compare(loserTree[i], winner_of_losertree[i - 1]);
			if (winner_of_losertree[i / 2] == loserTree[i])
				loserTree[i / 2] = winner_of_losertree[i - 1];
			else
				loserTree[i / 2] = loserTree[i];
		}

		//둘다 자식이 없을 때(둘다 leaf node일 때)
		else if ((*(loserTree[i - 1]))->leftChild == NULL && ((*(loserTree[i]))->leftChild == NULL)) {
			winner_of_losertree[i / 2] = compare((*(loserTree[i])), (*(loserTree[i - 1])));
			if (winner_of_losertree[i / 2] == loserTree[i])
				loserTree[i / 2] = loserTree[i-1];
			else
				loserTree[i / 2] = loserTree[i];
		}
		//둘다 자식이 있을때
		else {
				winner_of_losertree[i / 2] = compare((*(winner_of_losertree[i])), (*(winner_of_losertree[i - 1])));
				if (winner_of_losertree[i / 2] == winner_of_losertree[i])
					loserTree[i / 2] = winner_of_losertree[i - 1];
				else
					loserTree[i / 2] = winner_of_losertree[i];
		}
	}
	
	//최종 승자 저장
	loserTree[0] = winner_of_losertree[1];
	
	//최종 승자 출력
	printf("(%d, %d, %d)\n", (*(loserTree[0]))->data.row, (*(loserTree[0]))->data.key, (*(loserTree[0]))->data.count);

	//최종 승자가 있던 노드 -1로 저장
	(*(loserTree[0]))->data.key = -1;
	(*(loserTree[0]))->data.count = -1;
	
	//부모노드와 비교
	while((*(loserTree[0]))->data.key != -1)
		Restructuring(&loserTree, &winner_of_losertree);
}

void Restructuring(treePointer*** loserTree, treePointer*** winner_of_losertree)
{
	int i = numRow + (**loserTree[0])->data.row;
	while (i) {
		//부모노드와 자식노드 비교
		winner_of_losertree[i/2] = compare(*loserTree[i], *loserTree[i / 2]);
		if (winner_of_losertree[i / 2] == loserTree[i])
			loserTree[i / 2] = loserTree[i / 2];
		//부모노드로 이동
		i = i / 2;
	}
	//루트노드에 최종 승자 저장
	loserTree[0]= winner_of_losertree[1];

	//최종 승자 출력
	printf("(%d, %d, %d)\n", (**loserTree[0])->data.row, (**loserTree[0])->data.key, (**loserTree[0])->data.count);

	//최종 승자가 있던 노드 -1로 저장
	(**loserTree[0])->data.key = -1;
	(**loserTree[0])->data.count = -1;
}
treePointer* search_big_count(treePointer tree)
{
	/*tree의 노드 중 count가 가장 큰 노드의 포인터 반환
	*/
	if (tree) return NULL;
	//root노드의 count가 가장 크다고 가정
	treePointer* big_count = &tree;

	/*tree가 null이면 null 반환, null이 아니면 count가 큰 노드 찾기*/
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
		
	/*count -> 정수값 -> row값 순서로 크기를 비교하여 더 큰 노드 반환*/
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
