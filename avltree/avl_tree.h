/**
 * \file avl_tree.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Fri Nov 4 21:04:46 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __AVLTREE_H
#define __AVLTREE_H

struct avl_node;
typedef struct avl_node *position;
typedef struct avl_node *avltree;

avltree make_empty(avltree t);
position find(int x, avltree t);
position find_min(avltree t);
position find_max(avltree t);
avltree insert(int x, avltree t);
avltree ctremove(int x, avltree t);
int retrieve(position p);

#endif //__AVLTREE_H

