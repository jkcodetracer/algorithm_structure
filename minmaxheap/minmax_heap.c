/**
 * \file minmax_heap.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Tue Nov 8 07:28:44 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "minmax_heap.h"

struct heap_node{
	int capacity;
	int size;
	int *elements;
};

mmheap initialize(int capacity)
{
	mmheap mh;

	mh = (mmheap)calloc(1, sizeof(*mh));
	mh->capacity = capacity;
	mh->elements = (int*)calloc(capacity, sizeof(int));
	mh->size = 0;

	return mh;
}

static int get_fa(int idx)
{
	return (idx-1)/2;
}

static int get_gfa(int idx)
{
	if(idx <= 2) {
		return -1;
	}

	return ((idx-1)/2 - 1)/2;
}

int is_empty(mmheap mh)
{
	if(mh->size == 0)
		return 1;
	else 
		return 0;
}

int is_full(mmheap mh)
{
	if (mh->capacity == mh->size)
		return 1;
	else
		return 0;
}

int get_depth(int idx)
{
	int depth = 0;

	while(idx > 0) {
		idx = (idx-1)/2;
		depth++;
	}

	return depth;
}

int is_odd_level(int idx)
{
	int level = 0;
	level = get_depth(idx);

	return (level%2);
}
/* 
 * 1 偶数层节点，关键字小于父亲但是大于祖父
 * 2 奇数层节点，关键字大于父亲但是小于祖父
 * 使用 percolate up策略，调整一个节点后，继续调整被修改的节点，
 * 保证树的属性
 * */
void insert(mmheap mh, int x)
{
	int idx;
	int fa, gfa;

	if(is_full(mh))
		return ;

	fa = gfa = 0;
	for (idx = mh->size++; idx > 0; ) {
		fa = get_fa(idx);
		gfa = get_gfa(idx);

		if (gfa == -1) {
			if (x < mh->elements[fa]){
				idx = fa;
			}

			break;
		}

		if (is_odd_level(idx)) {
			if (x >= mh->elements[fa] && 
			    x <= mh->elements[gfa]) {
				break;
			}

			if (x > mh->elements[gfa]) {
				mh->elements[idx] = mh->elements[gfa];
				idx = gfa;
				continue;
			}

			if (x < mh->elements[fa]) {
				mh->elements[idx] = mh->elements[fa];
				idx = fa;
				continue;
			}
		} else {
			if(x <= mh->elements[fa] &&
			   x >= mh->elements[gfa]){
				break;
			}

			if(x > mh->elements[fa]){
				mh->elements[idx] = mh->elements[fa];
				idx = fa;
				continue;
			}

			if(x < mh->elements[gfa]) {
				mh->elements[idx] = mh->elements[gfa];
				idx = gfa;
				continue;
			}
		}
	}

	mh->elements[idx] = x;
}
/**
 * 使用percolate down 策略，将孩子和孙子节点中最小的值向上调整就可以了
 * 1 先检查是否有孩子节点
 * 2 在检查是否有孙子节点
 * 3 有孙子节点，选择最小的孙子，继续调整。
 * */
int deletemin(mmheap mh)
{
	int i = 0,j;
	int min_element;
	int last_element;
	int tmp_min, gchild;
	int tmp_idx;

	if (is_empty(mh))
		return -1;

	min_element = mh->elements[0];
	last_element = mh->elements[--mh->size];
	for(i = 0; (2*i+1) < mh->size; i = gchild) {
		tmp_min = 100000;
		gchild = (4*i+2)+1;
		if (gchild >= mh->size) {
			gchild = 2*i+1;
			if (gchild+1 < mh->size && 
			mh->elements[gchild+1] < mh->elements[gchild]) {
				gchild++;
			}
		} else {
			for (j = 1; j <= 4; j++) {
				tmp_idx = (4*i+2)+j;
				if (tmp_idx >= mh->size)
					break;
				if (mh->elements[tmp_idx] < tmp_min) {
					tmp_min = mh->elements[tmp_idx];
					gchild = tmp_idx;
				}
			}
		}

		if (last_element > mh->elements[gchild]) {
			mh->elements[i] = mh->elements[gchild];
		} else {
			break;
		}
	}
	mh->elements[i] = last_element;
	return min_element;
}
/**
 * 1基本思想同deletemin.这里每次调整最大值就可以
* */
int deletemax(mmheap mh)
{
	int i,j;
	int max_element;
	int last_element;
	int tmp_max, gchild;
	int tmp_idx = 0;

	if (is_empty(mh))
		return -1;
	max_element = -1;
	for (i = 0; i < mh->size && i < 3; i++) {
		if (mh->elements[i] > max_element) {
			max_element = mh->elements[i];
			tmp_idx = i;
		}
	}
	
	last_element = mh->elements[--mh->size];
	for (i = tmp_idx; (2*i+1) < mh->size; i = gchild) {
		tmp_max = -1;
		tmp_idx = -1;
		gchild = (4*i+2)+1;
		if (gchild >= mh->size) {
			gchild = 2*i+1;
			if (gchild+1 < mh->size &&
			mh->elements[gchild+1] > mh->elements[gchild]) {
				gchild++;
			}
		} else {
			for (j = 1; j<=4; j++) {
				tmp_idx = (4*i+2)+j;
				if (tmp_idx >=mh->size)
					break;
				if (mh->elements[tmp_idx] < tmp_max) {
					tmp_max = mh->elements[tmp_idx];
					gchild = tmp_idx;
				}
			}
		}

		if (last_element < mh->elements[gchild]) {
			mh->elements[i] = mh->elements[gchild];
		} else {
			break;
		}
	}

	mh->elements[i] = last_element;
	return max_element;
}

#if 0
int main()
{
	int i;
	mmheap mh;

	mh = initialize(1000);
	for (i = 0; i < 100; i++) {
		printf("%d ", i);
		insert(mh, i);
	}

	printf("\n");

	for (i = 0; i < 100; i++) {
		printf("%d ", deletemin(mh));
	}

	printf("\n");
	return 0;
}

#endif

#if 1
int main()
{
	int i;
	mmheap mh;

	mh = initialize(100);
	insert(mh, 13);
	insert(mh, 14);
	insert(mh, 16);
	insert(mh, 19);
	insert(mh, 21);
	insert(mh, 19);
	insert(mh, 68);
	insert(mh, 65);
	insert(mh, 26);
	insert(mh, 32);
	insert(mh, 31);
	for (i = 0; i < 5; i++) {
		printf("%d %d\n", deletemin(mh), deletemax(mh));
	}

	printf("\n");
	return 0;
}

#endif
