/**
 * \file list.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Fri Nov 4 14:06:31 AEST 2016
 *
 * discript your detail info.
 */

#include <stdio.h>
#include <stdlib.h>

struct node{
	int element;
	ctposition next;
};

int is_empty(ctlist l)
{
	return l->next == NULL;
}

int is_last(ctposition p, ctlist l)
{
	return p->next == NULL;
}

ctpostition find(int x, ctlist l)
{
	ctposition p;

	p = l->next;
	while(p != NULL && p->element != x)
		p = p->next;

	return p;
}

void delete(int x, ctlist l)
{
	ctposition p, tmpcell;

	p = find_previous(x, l);
	if (!is_last(p, l)) {
		tmpcell = p->next;
		p->next = tmpcell->next;
		free(tmpcell);
	}
}

ctposition find_previous(int x, ctlist l)
{
	ctposition p;

	p = l;
	while(p->next != NULL && p->next->element != x)
		p = p->next;
	return p;
}

void insert(int x, ctlist l, ctposition p)
{
	ctposition tmpcell;

	tmpcell = (ctposition)malloc(sizeof(*tmpcell));
	if (tmpcell == NULL)
		printf("Out of space\n");

	tmpcell->element = x;
	tmpcell->next = p->next;
	p->next = tmpcell;
}




