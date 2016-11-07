/**
 * \file d_ary_heap.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 14:34:45 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __DARAY_HEAP_H
#define __DARAY_HEAP_H

struct dary_heap_st;
typedef struct dary_heap_st *dary_heap;

dary_heap initialize(int max_element, int d);
void insert(dary_heap dh, int x);
int delete_min(dary_heap dh);
int find_min(dary_heap dh);
int is_full(dary_heap dh);
int is_empty(dary_heap dh);

#endif //__DARAY_HEAP_H
