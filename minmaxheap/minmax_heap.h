/**
 * \file minmax_heap.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Tue Nov 8 07:28:39 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __MINMAX_HEAP_H
#define __MINMAX_HEAP_H

struct heap_node;
typedef struct heap_node *mmheap;

mmheap initialize(int capacity);
void insert(mmheap mh, int x);
int deletemin(mmheap mh);
int deletemax(mmheap mh);

#endif //__MINMAX_HEAP_H

