/**
 * \file splay_tree.h
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Sat Nov 5 09:04:09 AEST 2016
 *
 * discript your detail info.
 */
#ifndef __SPLAY_TREE_H
#define __SPLAY_TREE_H

struct spl_node;
typedef struct spl_node *position;
typedef struct spl_node *spltree;

position find(spltree sp, int x);
spltree insert(spltree sp, int x);
spltree ctremove(spltree sp, int x);

#endif //__SPLAY_TREE_H
