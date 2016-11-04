/**
 * \file avl_tree.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Fri Nov 4 21:04:53 AEST 2016
 *
 * discript your detail info.
 */

#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct avl_node{
	int element;
	avltree left;
	avltree right;
	int height;
};

static int max(int x, int y)
{
	if (x > y)
		return x;
	else 
		return y;
}

static int height(position p)
{
	if (p == NULL)
		return -1;
	else
		return p->height;
}

/**
 * \brief rotate to right, move the left child to upper
 * */
static position single_rotate_left(avltree t)
{
	position p;

	p = t->left;
	t->left = p->right;
	p->right = t;

	//fix the height
	p->height = max(height(p->left), height(p->right)) + 1;
	t->height = max(height(t->left), height(t->right)) + 1;
	return p;
}

static position single_rotate_right(avltree t)
{
	position p;

	p = t->right;
	t->right = p->left;
	p->left = t;
	//fix the height
	p->height = max(height(p->left), height(p->right)) + 1;
	t->height = max(height(t->left), height(t->right)) + 1;

	return p;
}

static position double_rotate_left(avltree t)
{
	position p;

	t->left = single_rotate_right(t->left);
	p = single_rotate_left(t);

	return p;
}

static position double_rotate_right(avltree t)
{
	position p;

	t->right = single_rotate_left(t->right);
	p = single_rotate_right(t);

	return p;
}

avltree insert(int x, avltree t)
{
	if(t == NULL) {
		t = (avltree)malloc(sizeof(*t));
		if (t == NULL) {
			printf("Out of space!\n");
			return NULL;
		} else {
			t->element = x;
			t->left = t->right = NULL;
		}
	}

	if(x < t->element) {
		t->left = insert(x, t->left);
		if (height(t->left) - height(t->right) == 2) {
			if (x < t->left->element) {
				t = single_rotate_left(t);
			} else {
				t = double_rotate_left(t);
			}
		}
	} else if (x > t->element){
		t->right = insert(x, t->right);
		if (height(t->right) - height(t->left) == 2) {
			if (x > t->right->element) {
				t = single_rotate_right(t);
			} else {
				t = double_rotate_right(t);
			}
		}
	}

	t->height = max(height(t->left), height(t->right)) + 1;
	return t;
}

position ctremove(int x, avltree t)
{
	position tmpcell;

	if (t == NULL) {
		return NULL;
	}

	if (x < t->element) {
		t->left = ctremove(x, t->left);
		t->height = max(height(t->right), height(t->left))+1;
		if (height(t->right) - height(t->left) == 2) {
			if (height(t->right->right) - 
			height(t->right->left) <= 0) {
				t = single_rotate_right(t);
			} else {
				t = double_rotate_right(t);
			}
		}
	} else if (x > t->element){
		t->right = ctremove(x, t->right);
		t->height = max(height(t->right), height(t->left))+1;
		if (height(t->left) - height(t->right) == 2) {
			if (height(t->left->left) - 
			height(t->left->right) <= 0) {
				t = single_rotate_left(t);
			} else {
				t = double_rotate_left(t);
			}
		}
	} else if (x == t->element) {
		if (t->right && t->left) {
			tmpcell = find_min(t->right);
			t->element = tmpcell->element;
			t->right = ctremove(t->element, t->right);
		} else {
			tmpcell = t;
			if (t->right == NULL) {
				t = t->left;
			} else if (t->left == NULL) {
				t = t->right;
			}
			free(tmpcell);
		}
	}

	return t;
}

position find_min(avltree t)
{
	if(t == NULL)
		return NULL;

	if(t->left == NULL) {
		return t;
	} else {
		return find_min(t->left);
	}
}

position find_max(avltree t)
{
	if (t == NULL)
		return NULL;

	if (t->right == NULL) {
		return t;
	} else {
		return find_max(t->right);
	}
}

void pre_order(avltree t)
{
	if (t != NULL) {
		printf("%d ", t->element);
		pre_order(t->left);
		pre_order(t->right);
	}
}

int main()
{
	avltree t = NULL;

	t = insert(9, t);
	t = insert(5, t);
	t = insert(10, t);
	t = insert(0, t);
	t = insert(6, t);
	t = insert(11, t);
	t = insert(-1, t);
	t = insert(1, t);
	t = insert(2, t);
	pre_order(t);
	
	printf("\n");
	t = ctremove(10, t);
	pre_order(t);
	return 0;
}
