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
#if 0
int  main()
{
	int i, a;
	priority_queue h;

	h = initialize(1000);
	for (i = 0; i < 100; i++) {
		a = random()%100;
		insert(h, a);
		printf("%d ", a);
	}
	printf("\n");

	for (i = 0; i < 100; i++) {
		printf("%d ", delete_min(h));
	}
	printf("\n");

	return 0;
}
#endif
int main()
{
	int i;
	priority_queue h;

	h = initialize(1000);
	insert(h, 13);
	insert(h, 14);
	insert(h, 16);
	insert(h, 19);
	insert(h, 21);
	insert(h, 19);
	insert(h, 68);
	insert(h, 65);
	insert(h, 26);
	insert(h, 32);
	insert(h, 31);
	for (i = 0; i < 11;i++) {
		printf("%d ", delete_min(h));
	}

	printf("\n");
	return 0;
}
