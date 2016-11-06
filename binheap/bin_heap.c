/**
 * \file bin_heap.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 08:50:01 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bin_heap.h"

#define MIN_ELEMENT	(-100)

struct heap_st{
	int capacity;
	int size;
	int *elements;
};

int is_full(priority_queue h)
{
	if(h->size == h->capacity)
		return 1;
	else 
		return 0;
}

int is_empty(priority_queue h)
{
	if (h->size == 0)
		return 1;
	else
		return 0;
}

priority_queue initialize(int max_element)
{
	priority_queue h;

	h = (priority_queue)malloc(sizeof(*h) + sizeof(int)*max_element);
	if (h == NULL) {
		printf("malloc failed\n");
		return NULL;
	}
	h->elements = (int*)(h+1);
	h->capacity = max_element;
	h->size = 0;
	h->elements[0] = MIN_ELEMENT;

	return h;
}

//h->elements[0] is a sentinel
void insert(priority_queue h, int x)
{
	int i;

	if (is_full(h)) {
		printf("binary heap is full\n");
		return;
	}

	for (i = ++h->size;h->elements[i/2] > x; i/=2) {
		h->elements[i] = h->elements[i/2];
	}

	h->elements[i] = x;
}

int delete_min(priority_queue h)
{
	int i, child;
	int last_element, min_element;

	if (is_empty(h)) {
		printf("queue is empty!\n");
		return 0;
	}
	
	min_element = h->elements[1];
	last_element = h->elements[h->size--];

	for(i = 1; i*2 <= h->size; i = child) {
		child = 2*i;
		if (child != h->size &&
		h->elements[child+1] < h->elements[child]) {
			child++;
		}

		if (last_element > h->elements[child]) {
			h->elements[i] = h->elements[child];
		} else {
			break;
		}
	}

	h->elements[i] = last_element;
	return min_element;
}

int  main()
{
	int i, a;
	priority_queue h;

	h = initialize(100);
	for (i = 0; i < 10; i++) {
		a = random()%100;
		insert(h, a);
	}

	for (i = 0; i < 10; i++) {
		printf("%d ", delete_min(h));
	}

	return 0;
}

