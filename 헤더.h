#pragma once
#include <stdio.h>
#include <stdlib.h>

#define numRow 5
#define numCol 10
int matrix[numRow][numCol] = {
	{5,90,5,9,80,80,7,90,7,90},
	{100,30,30,51,160,160,160,51,160,59},
	{500,100,7000,100,900,600,100,100,650,100},
	{1000,300,41,300,41,41,41,900,900,950},
	{90,81,81,95,81,83,81,90,81,90}
};

#define MALLOC(p,s) if(!((p) = malloc(s))) {fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

typedef struct element{
	int row, key, count;
}Element;

typedef struct node* treePointer;
typedef struct node {
	Element data;
	treePointer leftChild, rightChild;
}Node;

void BSTInsert(treePointer* node, int key, int row);
treePointer modifiedSearch(treePointer tree, int key);
treePointer make_BST(int row);
void loser_tree();
treePointer* search_big_count(treePointer tree);
treePointer* compare(treePointer* tree1, treePointer* tree2);
void BSTMakeAndInit(treePointer* pRoot);
void Restructuring(treePointer*** loserTree, treePointer*** winner_of_losertree);