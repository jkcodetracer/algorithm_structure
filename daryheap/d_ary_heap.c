/**
 * \file d_ary_heap.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 14:34:54 AEST 2016
 *
 * discript your detail info.
 */

#include <stdio.h>
#include <stdlib.h>
#include "d_ary_heap.h"

#define MIN_D	(2)
#define MIN_DATA    (-1000)
#define MAX_DATA    (10000)


struct dary_heap_st{
	int capacity;
	int size;
	int d;
	int *elements;
};

dary_heap initialize(int max_element, int d)
{
	dary_heap dh;

	if (d < MIN_D) {
		printf("d(%d) is less than 2\n", d);
		return NULL;
	}

	dh = (dary_heap) malloc(sizeof(*dh)+sizeof(int)*max_element);
	if(dh == NULL) {
		printf("malloc failed!\n");
		return NULL;
	}
	dh->d = d;
	dh->capacity = max_element;
	dh->elements =(int*)(dh+1);
	dh->size = 0;

	return dh;
}

int is_full(dary_heap dh)
{
	if (dh->capacity == dh->size)
		return 1;
	else 
		return 0;
}

int is_empty(dary_heap dh)
{
	if (dh->size == 0) 
		return 1;
	else 
		return 0;
}

int get_parent(dary_heap dh, int idx)
{
	return (idx-1)/dh->d;
}

void insert(dary_heap dh, int x)
{
	int i, parent;

	if (is_full(dh)) {
		printf("dh is full, %d\n", dh->size);
		return;
	}

	i = dh->size++;
	parent = get_parent(dh, i);
	while(i > 0 && dh->elements[parent] > x) {
		dh->elements[i] = dh->elements[parent];
		i = parent;
		parent = get_parent(dh, i);
	}

	dh->elements[i] = x;
}

int find_successor(dary_heap dh, int idx)
{
	int i, tmp_idx, min_value, min_idx;

	min_idx = idx;
	min_value = MAX_DATA;
	for (i = 1; i <= dh->d; i++) {
		tmp_idx = idx * dh->d + i;
		if (tmp_idx >= dh->size) {
			break;
		}
		if (dh->elements[tmp_idx] < min_value) {
			min_value = dh->elements[tmp_idx];
			min_idx = tmp_idx;
		}
	}

	return min_idx;
}

int delete_min(dary_heap dh)
{
	int i = 0, child;
	int min_element, last_element;

	if (is_empty(dh)) {
		printf("dh is empty!\n");
		return -1;
	}
	min_element = dh->elements[0];
	last_element = dh->elements[--dh->size];

	while(i < dh->size) {
		child = find_successor(dh, i);
		if (child == i)
			break;

		if (last_element > dh->elements[child]) {
			dh->elements[i] = dh->elements[child];
			i = child;
		} else {
			break;
		}
	}

	dh->elements[i] = last_element;
	return min_element;
}

int main()
{
	int i, a;
	dary_heap dh;

	dh = initialize(100, 4);
	for (i = 0; i < 100; i++) {
		a = random()%100;
		insert(dh, a);
	}

	for (i = 0; i < 10; i++) {
		printf("%d ", delete_min(dh));
	}

	return 0;
}

