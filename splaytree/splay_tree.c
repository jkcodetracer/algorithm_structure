/**
 * \file splay_tree.c
 * \author  wzj
 * \brief
 * \version
 * \note
 * \date: Sat Nov 5 09:04:18 AEST 2016
 *
 * discript your detail info.
 */
#include <stdio.h>
#include <stdlib.h>
#include "splay_tree.h"

struct spl_node{
	int element;
	struct spl_node *left;
	struct spl_node *right;
}spl_node;

static spltree newnode(int x)
{
	spltree p;
	p = (spltree)malloc(sizeof(*p));
	p->left = NULL;
	p->right = NULL;
	p->element = x;

	return p;
}

static spltree rotate_right(spltree st)
{
	position p;

	if (st == NULL || st->left == NULL)
		return st;

	p = st->left;
	st->left = p->right;
	p->right = st;

	return p;
}

static spltree rotate_left(spltree st)
{
	position p;

	if (st == NULL || st->right == NULL)
		return st;
	p = st->right;
	st->right = p->left;
	p->left = st;

	return p;
}

static spltree splay(spltree st, int x)
{
	if (st == NULL || st->element == x) 
		return st;

	if (st->element > x) {
		if (st->left == NULL)
			return st;
		//zig zig
		if (st->left->element > x) {
			st->left->left = splay(st->left->left, x);
			st = rotate_right(st);
		} else if (st->left->element < x){ //zig zag
			st->left->right = splay(st->left->right, x);
			if (st->left->right)
				st->left = rotate_left(st->left);
		}
		return (st->left == NULL)? st:rotate_right(st);
	} else {
		if (st->right == NULL)
			return st;
		//zag zag
		if (st->right->element < x) {
			st->right->right = splay(st->right->right, x);
			st = rotate_left(st);
		} else if(st->right->element > x) {//zag zig
			st->right->left = splay(st->right->left, x);
			if (st->right->left) 
				st->right = rotate_right(st->right);
		}

		return (st->right == NULL)? st:rotate_left(st);
	}
}

spltree find(spltree st, int x)
{
	return splay(st, x);
}

spltree insert(spltree st, int x)
{
	position p;

	if (st == NULL)
		return newnode(x);

	st = splay(st, x);
	p = newnode(x);
	if (st->element > x) {
		p->left = st->left;
		p->right = st;
		st->left = NULL;
	} else {
		p->right = st->right;
		p->left = st;
		st->right = NULL;
	}

	return p;
}

spltree findmin(spltree st)
{
	position p;
	if (st == NULL)
		return NULL;

	p = st;
	while(p->left)
		p = p->left;

	return p;
}

spltree ctremove(spltree st, int x)
{
	position p, tmpcell;
	if (st == NULL)
		return NULL;

	p = find(st, x);
	if (p == NULL) 
		return st;
	if (p->left && p->right) {
		tmpcell = findmin(p->right);
		p->element = tmpcell->element;
		p->right = ctremove(p->right, p->element);
	} else {
		tmpcell = p;
		if (p->left == NULL) {
			p = p->right;
		} else if (p->right == NULL) {
			p = p->left;
		}

		free(tmpcell);
	}

	return p;
}

void preorder(spltree st)
{
	if (st) {
		printf("%d ", st->element);
		preorder(st->left);
		preorder(st->right);
	}
}

int main()
{
	spltree st;

	st = newnode(100);
	st->left = newnode(50);
	st->right = newnode(200);
	st->left->left = newnode(40);
	st->left->left->left = newnode(30);
	st->left->left->left->left = newnode(20);
	st = insert(st, 25);

	preorder(st);

	return 0;
}

