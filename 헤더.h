#pragma once
#include <stdio.h>
#include <stdlib.h>

//lists that have to be sorted in increasing order
#define numRow 5
#define numCol 10
int matrix[numRow][numCol] = {
	{5,90,5,9,80,80,7,90,7,90},
	{100,30,30,51,160,160,160,51,160,59},
	{500,100,7000,100,900,600,100,100,650,100},
	{1000,300,41,300,41,41,41,900,900,950},
	{90,81,81,95,81,83,81,90,81,90}
};

//allocating memory
#define MALLOC(p,s) if(!((p) = malloc(s))) {fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

//structure of data part of a node
typedef struct element {
	int row, key, count;
}Element;

//structure of a node
typedef struct node* treePointer;
typedef struct node {
	Element data;
	treePointer leftChild;
	treePointer rightChild;
}Node;

//void BSTMakeAndInit(treePointer* pRoot);
Element BSTGetNodeData(treePointer bst);
void BSTInsert(treePointer* pRoot, int, int);
//treePointer BSTSearch(treePointer bst, Element target);
treePointer modifiedSearch(treePointer, int);
void RemoveLeftSubTree(treePointer bt);
void RemoveRightSubTree(treePointer bt);
void ChangeLeftSubTree(treePointer main, treePointer sub);
void ChangeRightSubTree(treePointer main, treePointer sub);
treePointer BSTRemove(treePointer* pRoot, treePointer delNode);
int isEmpty(treePointer** BST);

treePointer MakeBTreeNode(void);
Element GetData(treePointer bt);
void SetData(treePointer bt, Element data);
treePointer GetLeftSubTree(treePointer bt);
treePointer GetRightSubTree(treePointer bt);
void MakeLeftSubTree(treePointer main, treePointer sub);
void MakeRightSubTree(treePointer main, treePointer sub);

treePointer* Compare(treePointer* tree1, treePointer* tree2);
void SetLeafNodes(treePointer** loserTree, treePointer** BST);
void SetNonleafNodes(treePointer** loserTree, treePointer** winner);
void PrintWinner(treePointer** loserTree);
void Restructure(treePointer** loserTree, treePointer** winner);
