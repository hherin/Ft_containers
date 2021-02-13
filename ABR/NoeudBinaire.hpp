/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoeudBinaire.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:17 by hherin            #+#    #+#             */
/*   Updated: 2021/02/13 16:09:04 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOEUDBINAIRE_HPP
# define NOEUDBINAIRE_HPP

# include <cmath>
# include "utilsTree.hpp"

template <class T>
struct s_abr
{
	T key;
	
	s_abr *parent;
	s_abr *left;
	s_abr *right;
};

template <class T>
T& nodValue(s_abr<T> *a) { return a->key; } // lancer exception si vide ?

template <class T>
s_abr<T> *createNewTree(T &key, s_abr<T> *ls, s_abr<T> *rs, s_abr<T> *p)
{
	s_abr<T> *root = new s_abr<T>;
	if (!root){
		std::cout << "Malloc failed\n";
		return NULL;
	}
	root->key = key;
	root->left = ls;
	root->right = rs;
	root->parent = p;
	return root;
}


template <class T>
s_abr<T> *isKeyInBinTree(T &key, s_abr<T> *bst)
{	
	if (!bst)
		return NULL;
	else
	{
		if (key == bst->key)
			return bst;
		else
		{
			if (key < bst->key)
				return isKeyInBinTree(key, bst->left);
			else
				return isKeyInBinTree(key, bst->right);
		}
	}
}

template <class T>
void recInsertNode(s_abr<T> **bst, T &key, s_abr<T> *parent)
{
	if (isKeyInBinTree(key, *bst))						// IS the key already present
		return ;
	else if (!*bst){
		if (!(*bst = createNewTree<T>(key, NULL, NULL, parent)))	// case empty tree
			return ;
	}
	else{												// check which side the leave should be added
		parent = *bst;
		if (key > (*bst)->key)
			recInsertNode(&(*bst)->right, key, parent);
		else if (key < (*bst)->key)
			recInsertNode(&(*bst)->left, key, parent);
	}
}


template <class T>
void insertNewNode(s_abr<T> **bst, T &key)
{
	s_abr<T> *t = NULL;
	// int height
	recInsertNode(bst, key, t);
	
}

template <class T>
int getHeightTree(s_abr<T> const *a)
{
	if (!a)
		return 0;
	
	int left = 0;
	int right = 0;

	left = getHeightTree(a->left);
	right = getHeightTree(a->right);
	return (left > right) ? left + 1 : right + 1;
} 

template <class T>
void	iterTree(s_abr<T> const *bst)
{
	if (!bst)
		return ;
	else{
		iterTree(bst->left);
		std::cout << bst->key << " ";
		iterTree(bst->right);
	}
}

template <class T>
T	Max(s_abr<T> *bst)
{
	if (!bst->right)
		return bst->key;
	else
		return Max<T>(bst->right);
}

template <class T>
s_abr<T>	*deleteNode(s_abr<T> **bst, T& key)
{
	if (!*bst || !isKeyInBinTree(key, *bst))
		return NULL;
	if ((*bst)->key > key)										// the deletenode is in left side
		(*bst)->left = deleteNode(&((*bst)->left), key);
	else if ((*bst)->key < key)										// ... right side
		(*bst)->right = deleteNode(&((*bst)->right), key);
	else {
		s_abr<T> *tmp = NULL;
		if (!(*bst)->left && !(*bst)->right)
			;
		else if (!(*bst)->left)
			tmp = (*bst)->right;
		else if (!(*bst)->right)
			tmp = (*bst)->left;
		else{
			T tmp2 = Max<T>(*bst);
			(*bst)->key = tmp2;
			return deleteNode(&((*bst)->left), tmp2);
		}
		delete *bst;
		*bst = NULL;
		return tmp;
	}
	return *bst;
}

template <class T>
void	rightRotation(s_abr<T> **root)
{
	if (!*root)
		return ;
	
	s_abr<T> *pivot = (*root)->left;

	(*root)->left = pivot->right;
	pivot->right->parent = *root;
	
	pivot->right = (*root);
	pivot->right->parent = (*root)->parent;

	if ((*root)->parent){
		s_abr<T> *parent = (*root)->parent;
		
		(parent->left == *root) ? parent->left = pivot : parent->right = pivot; 
	}
	*root = pivot;
}



#endif