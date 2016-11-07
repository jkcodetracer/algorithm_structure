/**
 * \file bin_queue.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 20:41:57 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bin_queue.h"

#define MAX_TREES	(128)
#define MAX_VALUE	(100000)

enum merge_status{
	NO_TREES = 0,
	ONLY_BT1,
	ONLY_BT2,
	BT1_AND_BT2,
	ONLY_CARRY,
	BT1_AND_CARRY,
	BT2_AND_CARRY,
	ALL_TREE
};

struct bin_node{
	int element;
	position left_child;
	position next_sibling;
};

struct collection{
	int current_size;
	bin_tree trees[MAX_TREES];
};

static bin_queue s_initialize(int x)
{
	bin_tree bt;
	bin_queue bq;

	bt = (bin_tree)calloc(1, sizeof(*bt));
	//check
	bq = (bin_queue)calloc(1, sizeof(*bq));
	//check
	bq->current_size = 1;
	bq->trees[0] = bt;
	bt->element = x;
	bt->left_child = bt->next_sibling = NULL;

	return bq;
}

bin_queue initialize()
{
	bin_queue bq;

	bq = (bin_queue)calloc(1, sizeof(*bq));
	if(bq == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}
	bq->current_size = 0;

	return bq;
}

void free_tree(bin_tree bt)
{
	if (bt != NULL) {
		free_tree(bt->left_child);
		free_tree(bt->next_sibling);
		free(bt);
	}
}

void destruction(bin_queue bq)
{
	int i, j;

	i = 0;
	j = 1;

	while(bq->current_size > 0) {
		if (bq->trees[i]) {
			free_tree(bq->trees[i]);
			bq->trees[i] = NULL;
			bq->current_size -= j;
		}
		j = j*2;
		i++;
	}

	free(bq);
}

int is_empty(bin_queue bq)
{
	if(bq && bq->current_size > 0) {
		return 0;
	} else {
		return 1;
	}
}

//big one become a child of the small one
bin_tree combine(bin_tree tx, bin_tree ty)
{
	if (tx->element > ty->element)
		return combine(ty, tx);
	ty->next_sibling = tx->left_child;
	tx->left_child = ty;

	return tx;
}

bin_queue merge(bin_queue bq1, bin_queue bq2)
{
	int i,j;
	int status;
	bin_tree btx, bty, carry;

	bq1->current_size += bq2->current_size;
	carry = NULL;
	//the merge can be stopped earlier.
	//for (i = 0, j = 1; j <= bq1->current_size; i++, j*=2) {
	for (i = 0, j = 1; bq2->current_size != 0 || carry; i++, j*=2) {
		btx = bq1->trees[i];
		bty = bq2->trees[i];
		status = !!btx + 2 * !!bty + 4 * !!carry;
		if (bty) {
			bq2->current_size -= j;
		}

		switch(status){
			case NO_TREES:
			case ONLY_BT1:
				break;
			case ONLY_BT2:
				bq1->trees[i] = bty;
				bq2->trees[i] = NULL;
				break;
			case BT1_AND_BT2:
				carry = combine(btx, bty);
				bq1->trees[i] = NULL;
				bq2->trees[i] = NULL;
				break;
			case ONLY_CARRY:
				bq1->trees[i] = carry;
				carry = NULL;
				break;
			case BT1_AND_CARRY:
				carry = combine(btx, carry);
				bq1->trees[i] = NULL;
				break;
			case BT2_AND_CARRY:
				carry = combine(carry, bty);
				bq2->trees[i] = NULL;
				break;
			case ALL_TREE:
				bq1->trees[i] = carry;
				carry = combine(btx, bty);
				bq2->trees[i] = NULL;
				break;
		}
	}

	return bq1;
}

bin_queue insert(bin_queue bq, int x)
{
	bin_queue tmp;

	tmp = s_initialize(x);
	if (tmp == NULL) {
		printf("init tmp bin queue failed!\n");
		return NULL;
	}

	bq = merge(bq, tmp);

	return bq;
}

int deletemin(bin_queue bq)
{
	int i;
	int min_element, min_idx;
	bin_queue deleted_que;
	bin_tree deleted_tree;

	if (is_empty(bq))
		return -1;

	min_idx = 0;
	min_element = MAX_VALUE;
	for (i = 0; i < MAX_TREES; i++) {
		if (bq->trees[i] &&
		    bq->trees[i]->element < min_element) {
			min_idx = i;
			min_element = bq->trees[i]->element;
		}
	}

	deleted_tree = bq->trees[min_idx]->left_child;
	free(bq->trees[min_idx]);
	bq->trees[min_idx] = NULL;
	bq->current_size -= (1<<min_idx);

	deleted_que = initialize();
	deleted_que->current_size = (1<<min_idx) - 1;
	for(i = min_idx - 1; i >= 0; i--) {
		deleted_que->trees[i] = deleted_tree;
		deleted_tree = deleted_tree->next_sibling;
		deleted_que->trees[i]->next_sibling = NULL;
	}

	bq = merge(bq, deleted_que);
	destruction(deleted_que);

	return min_element;
}

int main()
{
	int i, a;
	bin_queue bq;

	bq = initialize();
	for (i = 0; i < 100; i++) {
		a = random()%100;
		bq = insert(bq, a);
	}

	for (i = 0; i < 100; i++) {
		printf("%d ", deletemin(bq));
	}
	printf("\n");

	destruction(bq);

	return 0;
}



