/**
 * \file bin_heap.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 08:49:53 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __BIN_HEAP_H
#define __BIN_HEAP_H

struct heap_st;
typedef struct heap_st *priority_queue;

priority_queue initialize(int max_element);
void destroy(priority_queue h);
void insert(priority_queue h, int x);
int delete_min(priority_queue h);
int find_min(priority_queue h);
int is_empty(priority_queue h);
int is_full(priority_queue h);

#endif //__BIN_HEAP_H

