/**
 * \file leftist_heap.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 16:05:29 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "leftist_heap.h"

struct tree_node{
	struct tree_node *left;
	struct tree_node *right;
	int element;
	int npl;
};

static priority_queue newnode(int x)
{
	priority_queue lh;

	lh = (priority_queue)malloc(sizeof(*lh));
	if (lh == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}

	lh->left = lh->right = NULL;
	lh->npl = 0;
	lh->element = x;

	return lh;
}

void swap_child(priority_queue lh)
{
	priority_queue tmp;

	tmp = lh->left;
	lh->left = lh->right;
	lh->right = tmp;
}

priority_queue mergel(priority_queue lhx, priority_queue lhy)
{
	if (lhx->left == NULL) {
		lhx->left = lhy;
	} else {
		lhx->right = merge(lhx->right, lhy);
		if (lhx->left->npl < lhx->right->npl)
			swap_child(lhx);
		lhx->npl = lhx->right->npl + 1;
	}

	return lhx;
}


priority_queue merge(priority_queue lhx, priority_queue lhy)
{
	priority_queue rel;

	if (lhx == NULL) 
		return lhy;
	if (lhy == NULL)
		return lhx;
	if (lhx->element > lhy->element) {
		rel = mergel(lhy, lhx);
	} else {
		rel = mergel(lhx, lhy);
	}

	return rel;
}

int find_min(priority_queue lh)
{
	if (lh == NULL)
		return -1;
	return lh->element;
}

priority_queue insert(priority_queue lh, int x)
{
	priority_queue nlh;

	nlh = newnode(x);
	if (lh == NULL) {
		return nlh;
	} else {
		lh = merge(lh, nlh);
	}

	return lh;
}

priority_queue delete_min(priority_queue lh)
{
	priority_queue nlh;

	if(lh == NULL)
		return NULL;

	nlh = merge(lh->left, lh->right);
	free(lh);
	return nlh;
}

int main()
{
	int i, a;
	priority_queue lh;

	for (i = 0; i < 10; i++) {
		a = random()%100;
		lh = insert(lh, a);
	}

	for (i = 0; i < 10;i++) {
		printf("%d ", find_min(lh));
		lh = delete_min(lh);
	}

	return 0;
}



