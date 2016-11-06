/**
 * \file btree.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Sun Nov 6 12:27:07 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

#define T (3)
#define TRUE	(1)
#define FALSE	(0)

struct btnode{
	int t;	//[t-1, 2t-1]
	int n;
	int *element;
	struct btnode **child;
	int leaf;
};

btree split_child(btree parent, int p, btree childy);

static btree newnode(int t, int leaf)
{
	btree bnode;

	bnode = (btree)malloc(sizeof(*bnode));
	bnode->t = t;
	bnode->leaf = leaf;
	bnode->n = 0;
	bnode->element = (int *)malloc(sizeof(int) * (2*t-1));
	bnode->child = (struct btnode **)malloc(sizeof(btree)*(2*t));

	return bnode;
}

static void insert_nonfull(btree node, int x)
{
	int i = node->n - 1;

	if (node->leaf) {
		while(i >= 0 && node->element[i] > x) {
			node->element[i+1] = node->element[i];
			i--;
		}

		node->element[i+1] = x;
		node->n ++;
	} else {
		while(i>=0 && node->element[i] > x)
			i--;

		if(node->child[i+1]->n == 2 * node->t - 1) {
			node = split_child(node, i+1, node->child[i+1]);

			if(node->element[i+1] < x) 
				i++;
		}

		insert_nonfull(node->child[i+1], x);
	}
}

btree split_child(btree parent, int p, btree childy)
{
	int i;
	btree childx;

	childx = newnode(childy->t, childy->leaf);
	childx->n = childx->t - 1;

	//split elements
	for (i = 0; i < childx->t-1; i++)
		childx->element[i] = childy->element[i + childy->t];

	//split child
	if (childy->leaf == FALSE) {
		for(i = 0; i < childx->t; i++)
			childx->child[i] = childy->child[i + childy->t];
	}

	//reduce the number of keys in y
	childy->n = childy->t - 1;

	/* modify parent */
	//add new child into parent
	for (i = parent->n; i >= p+1 ; i--)
		parent->child[i+1] = parent->child[i];
	parent->child[p+1] = childx;

	//add new key
	for (i = parent->n; i >= p; i--)
		parent->element[i+1] = parent->element[i];
	parent->element[p] = childy->element[childy->t - 1];

	parent->n++;

	return parent;
}

position search(btree node, int x)
{
	int i = 0;

	while(i < node->n && x > node->element[i])
		i++;

	if (i < node->n && node->element[i] == x)
		return node;

	if (node->leaf)
		return NULL;

	return search(node->child[i], x);
}

btree insert(btree node, int x)
{
	int i = 0;
	btree tmpcell;

	if (node == NULL) {
		node = newnode(T, TRUE);
		node->element[0] = x;
		node->n = 1;
	} else {
		//full
		if (node->n == 2*T-1) {
			tmpcell = newnode(T, FALSE);
			tmpcell->child[0] = node;
			node = split_child(tmpcell, 0, node);

			//choose a child, and insert the new element
			if (node->element[0] < x) {
				i++;
			}

			insert_nonfull(node->child[i], x);
		} else { //not full
			insert_nonfull(node, x);
		}
	}

	return node;
}

void traverse(btree node)
{
	int i;
	for (i = 0; i < node->n; i++) {
		if (node->leaf == FALSE)
			traverse(node->child[i]);
		printf("%d ", node->element[i]);
	}

	if(node->leaf == FALSE) {
		traverse(node->child[i]);
	}
}

int main()
{
	btree bt = NULL;

	bt = insert(bt, 10);
	bt = insert(bt, 20);
	bt = insert(bt, 5);
	bt = insert(bt, 6);
	bt = insert(bt, 12);
	bt = insert(bt, 30);
	bt = insert(bt, 7);
	bt = insert(bt, 17);

	traverse(bt);
	printf("\n");

	if (search(bt, 6))
		printf("Present\n");
	if (search(bt, 15) == NULL)
		printf("not present\n");

	return 0;
}

