/**
 * \file leftist_heap.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 16:05:23 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __LEFTIST_HEAP_H_
#define __LEFTIST_HEAP_H_

struct tree_node;
typedef struct tree_node *priority_queue;

priority_queue initialize(void);
int find_min(priority_queue lh);
int is_empty(priority_queue lh);
priority_queue merge(priority_queue lhx, priority_queue lhy);
priority_queue insert(priority_queue lh, int x);
priority_queue delete_min(priority_queue lh);


#endif //__LEFTIST_HEAP_H_
