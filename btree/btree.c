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

int find_key(btree node, int x)
{
	int i = 0;
	while(i < node->n && node->element[i] < x)
		i++;

	return i;
}

static void remove_from_leaf(btree node, int idx)
{
	int i;
	for(i = idx + 1; i < node->n; i++)
		node->element[i-1] = node->element[i];

	node->n--;
}

static int get_pred(btree node, int idx)
{
	btree tmp;
	tmp = node->child[idx];
	while(tmp->leaf == FALSE)
		tmp = tmp->child[tmp->n];
	return tmp->element[tmp->n-1];
}

static int get_succ(btree node, int idx)
{
	btree tmp;
	tmp = node->child[idx+1];
	while(tmp->leaf == FALSE)
		tmp = tmp->child[0];
	return tmp->element[0];
}

void merge_tree(btree node, int idx)
{
	int i;
	btree child, sibling;

	child = node->child[idx];
	sibling = node->child[idx+1];

	child->element[child->t - 1] = node->element[idx];

	//merge key
	for (i = 0; i < sibling->n; i++) {
		child->element[child->t+i] = sibling->element[i];
	}
	//merge subtree
	if (child->leaf == FALSE) {
		for (i = 0; i <= sibling->n; i++) {
			child->child[child->t+i] = sibling->child[i];
		}
	}
	//regulate current node
	for (i = idx+1; i < node->n; i++) {
		node->element[i-1] = node->element[i];
	}

	for (i = idx+2; i <= node->n; i++) {
		node->child[i-1] = node->child[i];
	}

	child->n += sibling->n + 1;
	node->n--;

	free(sibling);
}

static void remove_from_nonleaf(btree node, int idx)
{
	int x = node->element[idx];

	if (node->child[idx]->n >= node->t) {
		//2a
		int pred = get_pred(node, idx);
		node->element[idx] = pred;
		btremove(node->child[idx], pred);
	} else if (node->child[idx + 1]->n >= node->t) {
		//2b
		int succ = get_succ(node, idx);
		node->element[idx] = succ;
		btremove(node->child[idx + 1], succ);
	} else {//2c
		merge_tree(node, idx);
		btremove(node->child[idx], x);
	}
}

static void borrow_from_prev(btree node, int idx)
{
	int i;
	btree child, sibling;

	child = node->child[idx];
	sibling = node->child[idx-1];

	//regulate main child
	for (i = child->n-1; i >= 0; i--) 
		child->element[i+1] = child->element[i];

	if (child->leaf == FALSE) {
		for (i = child->n; i >= 0; i--) {
			child->child[i+1] = child->child[i];
		}
	}
	//borrow node from parent
	child->element[0] = node->element[idx-1];
	//borrow node from sibling
	if (child->leaf == FALSE) {
		child->child[0] = sibling->child[sibling->n];
	}

	node->element[idx-1] = sibling->element[sibling->n-1];

	child->n++;
	sibling->n--;
}

static void borrow_from_next(btree node, int idx)
{
	int i;
	btree child, sibling;

	child = node->child[idx];
	sibling = node->child[idx+1];
	//borrow node from parent
	child->element[child->n] = node->element[idx];
	//borrow from sibling;
	if (child->leaf == FALSE) {
		child->child[child->n+1] = sibling->child[0];
	}

	node->element[idx] = sibling->element[0];

	//regulate sibling
	for(i = 1; i < sibling->n; i++)
		sibling->element[i-1] = sibling->element[i];
	if (sibling->leaf != FALSE) {
		for (i = 1; i <= sibling->n; i++)
			sibling->child[i-1] = sibling->child[i];
	}

	child->n++;
	sibling->n--;
}

static void fill_subtree(btree node, int idx)
{
	//case:3a
	if (idx != 0 && node->child[idx-1]->n >= node->t)
		borrow_from_prev(node, idx);
	else if (idx != node->n && node->child[idx+1]->n >= node->t)
		borrow_from_next(node, idx);
	else {
	//case 3b  merge left+right
		if (idx != node->n)
			merge_tree(node, idx);
		else 
			merge_tree(node, idx-1);
	}
}

btree btremove(btree node, int x)
{
	int idx, flag;

	idx = find_key(node, x);
	//the key in current node
	if(idx < node->n && node->element[idx] == x) {
		if (node->leaf == TRUE) {
			//case 1
			remove_from_leaf(node,idx);
		} else {
			//case 2
			remove_from_nonleaf(node, idx);
		}
	} else {
	//the key in the subtree
		if (node->leaf == TRUE)
			return NULL;
		//remember whether it is the last child
		flag = ((idx == node->n)?TRUE:FALSE);
		if (node->child[idx]->n < node->t)
			// case 3
			fill_subtree(node, idx);

		//subtree merged and it was the last child
		if ((flag == TRUE) && idx > node->n)
			btremove(node->child[idx-1],x); 
		else
			btremove(node->child[idx], x);

	}

	return node;
}

int main()
{
	btree bt = NULL;

	bt = insert(bt, 1);
	bt = insert(bt, 3);
	bt = insert(bt, 7);
	bt = insert(bt, 10);
	bt = insert(bt, 11);
	bt = insert(bt, 13);
	bt = insert(bt, 14);
	bt = insert(bt, 15);
	bt = insert(bt, 18);
	bt = insert(bt, 16);
	bt = insert(bt, 19);
	bt = insert(bt, 24);
	bt = insert(bt, 25);
	bt = insert(bt, 26);
	bt = insert(bt, 21);
	bt = insert(bt, 4);
	bt = insert(bt, 5);
	bt = insert(bt, 20);
	bt = insert(bt, 22);
	bt = insert(bt, 2);
	bt = insert(bt, 17);
	bt = insert(bt, 12);
	bt = insert(bt, 6);

	traverse(bt);
	printf("\n");

	if (search(bt, 6))
		printf("Present\n");
	if (search(bt, 15))
		printf("present\n");

	btremove(bt, 6);
	traverse(bt);
	printf("\n");

	btremove(bt, 13);
	traverse(bt);
	printf("\n");

	btremove(bt, 7);
	traverse(bt);
	printf("\n");

	btremove(bt, 4);
	traverse(bt);
	printf("\n");

	btremove(bt, 2);
	traverse(bt);
	printf("\n");

	btremove(bt, 16);
	traverse(bt);
	printf("\n");

	return 0;
}

