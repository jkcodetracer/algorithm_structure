/**
 * \file list.h
 * \author  wzj
 * \brief adt list
 * \version
 * \note
 * \date: Fri Nov 4 14:06:27 AEST 2016
 *
 * discript your detail info.
 */
#ifndef _CT_LIST_H_
#define _CT_LIST_H_

struct node;
typedef struct node *ptr_to_node;
typedef ptr_to_node ctlist;
typedef ptr_to_node ctposition;

ctlist make_empty(ctlist l);
int is_empty(ctlist l);
int is_last(ctposition p, ctlist l);
ctposition find(int x, ctlist l);
void delete(int x, ctlist l);
ctposition find_previous(int x, ctlist l);
void insert(int x, ctlist l, ctposition p);
void delete_list(ctlist l);
ctposition header(ctlist l);
ctposition first(ctlist l);
ctposition advance(ctposition p);
int retrieve(ctposition p);

#endif //_CT_LIST_H_

