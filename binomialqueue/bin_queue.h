/**
 * \file bin_queue.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Mon Nov 7 20:41:45 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __BINOMIAL_QUEUE_H
#define __BINOMIAL_QUEUE_H

struct bin_node;
struct collection;
typedef struct bin_node *position;
typedef struct bin_node *bin_tree;
typedef struct collection *bin_queue;

bin_queue initialize();
bin_queue insert(bin_queue bq, int x);
int is_empty(bin_queue bq);
int deletemin(bin_queue bq);
void destruction(bin_queue bq);


#endif //__BINOMIAL_QUEUE_H
