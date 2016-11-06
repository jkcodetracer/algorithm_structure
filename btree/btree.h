/**
 * \file btree.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Sun Nov 6 12:27:03 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __BTREE_H_
#define __BTREE_H_

struct btnode;
typedef struct btnode *btree;
typedef struct btnode *position;

position search(btree root, int x);
btree insert(btree bt, int x);
btree btremove(btree bt, int x);

#endif //__BTREE_H_

