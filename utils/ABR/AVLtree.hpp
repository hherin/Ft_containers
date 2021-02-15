/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLtree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:17 by hherin            #+#    #+#             */
/*   Updated: 2021/02/15 16:43:28 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOEUDBINAIRE_HPP
# define NOEUDBINAIRE_HPP

# include <cmath>
# include "utilsTree.hpp"

template <class T, class M>
struct s_abr
{
	ft::pair<T, M> p;
	
	s_abr *parent;
	s_abr *left;
	s_abr *right;
};

template <class T, class M>
s_abr<T, M> *createNewTree(T const &key, M const &map, s_abr<T, M> *ls, s_abr<T, M> *rs, s_abr<T, M> *p)
{
	s_abr<T, M> *root = new s_abr<T, M>;
	if (!root){
		std::cout << "Malloc failed\n";
		return NULL;
	}
	root->p.first = key;
	root->p.second = map;
	root->left = ls;
	root->right = rs;
	root->parent = p;
	return root;
}


/*
** Recursive insert function that returns the new created node
*/
template <class T, class M>
s_abr<T, M> *recInsertNode(s_abr<T, M> **bst, T const &key, M const &map, s_abr<T, M> *parent)
{
	if (isKeyInBinTree(key, *bst))						// IS the key already present
		return NULL;
	else if (!*bst){
		if (!(*bst = createNewTree<T, M>(key, map, NULL, NULL, parent)))	// case empty tree
			return NULL;
	}
	else{												// check which side the leave should be added
		parent = *bst;
		if (key > (*bst)->p.first)
			return recInsertNode(&(*bst)->right, key, map, parent);
		else if (key < (*bst)->p.first)
			return recInsertNode(&(*bst)->left, key, map, parent);
	}
	return *bst;
}

template <class T, class M>
void	rightRotation(s_abr<T, M> *node, s_abr<T, M> **root)
{
	if (!node)
		return ;
	
	s_abr<T, M> *pivot = node->left;

	node->left = pivot->right;
	(pivot->right) ? pivot->right->parent = node : 0;
	
	pivot->right = node;
	pivot->parent = node->parent;

	if (node->parent){
		s_abr<T, M> *parent = node->parent;
		
		(parent->left == node) ? parent->left = pivot : parent->right = pivot; 
	}
	node->parent = pivot;
	if (!pivot->parent)
		*root = pivot;
}

template <class T, class M>
void	leftRotation(s_abr<T, M> *node, s_abr<T, M> **root)
{
	if (!node || !node->right)
		return ;
	
	s_abr<T, M> *pivot = node->right;	

	node->right = pivot->left;
	(pivot->left) ? pivot->left->parent = node : 0;
		
	pivot->left = node;
	pivot->parent = node->parent;
	
	if (node->parent){
		s_abr<T, M> *parent = node->parent;

		(parent->left == node) ? parent->left = pivot : parent->right = pivot;
	}
		
	node->parent = pivot;
	if (!pivot->parent)
		*root = pivot;
}

template <class T, class M>
void	BalancedTree(s_abr<T, M> *node, s_abr<T, M> **root)
{
	if (!node)
		return ;
	while (node){
		int bl = getHeightTree(node->left);
		int br = getHeightTree(node->right);
		if (bl - br > 1)
			rightRotation(node, root);
		else if (bl - br < -1)
			leftRotation(node, root);
		node = node->parent;
	}
}

template <class T, class M>
void insertNewNode(s_abr<T, M> **bst, T const &key, M const &map)
{
	s_abr<T, M> *newNode = NULL;
	newNode = recInsertNode(bst, key, map, newNode);
	// BalancedTree<T>(newNode, bst);
}

template <class T, class M>
int getHeightTree(s_abr<T, M> const *a)
{
	if (!a)
		return 0;
	
	int left = 0;
	int right = 0;

	left = getHeightTree(a->left);
	right = getHeightTree(a->right);
	return (left > right) ? left + 1 : right + 1;
} 

template <class T, class M>
s_abr<T, M>	*recDeleteNode(s_abr<T, M> **bst, s_abr<T, M> **root, T const& key)
{
	if (!*bst)
		return *bst;
	std::cout << "add bst " << *bst << "KEY: " << (*bst)->p.first << "\n";
	if ((*bst)->p.first > key){										// the deletenode is in left side
		(*bst)->left = recDeleteNode(&((*bst)->left), root, key);
		((*bst)->left) ?  (*bst)->left->parent = *bst : 0;
		BalancedTree((*bst)->left, root);
	}
	else if ((*bst)->p.first < key)	{									// ... right side
		(*bst)->right = recDeleteNode(&((*bst)->right), root, key);
		((*bst)->right) ? (*bst)->right->parent = *bst : 0;
		BalancedTree((*bst)->right, root);
	}
	else if (key == (*root)->p.first){
		s_abr<T, M> *tmp2 = ((*root)->right) ? ::Min<T, M>((*root)->right) : Max<T, M>((*root)->left);
		(*bst)->p.first = tmp2->p.first;
		(*bst)->right = recDeleteNode(&((*bst)->right), root, tmp2->p.first);
		return *bst;
	}
	else {
		s_abr<T, M> *tmp = NULL;
		if (!(*bst)->left && !(*bst)->right)
			;
		else if ((*bst)->right && !(*bst)->left)
			tmp = (*bst)->right;
		else if ((*bst)->left && !(*bst)->right)
			tmp = (*bst)->left;
		else{
			s_abr<T, M> *tmp2 = ::Min<T, M>((*bst)->right);
			(*bst)->p.first = tmp2->p.first;
			// std::cout << "MIN " << (*bst)->p.first >> "\n";
			(*bst)->right = recDeleteNode(&((*bst)->right), root, tmp2->p.first);
			return *bst;
		}
		delete *bst;
		*bst = NULL;
		return tmp;
	}
	return *bst;
}

template <class T, class M>
void	deleteNode(s_abr<T, M> **root, T const &key)
{
	recDeleteNode(root, root, key);
	std::cout << "\n============================\n";
	// std::cout << "avant:\n";
	// printTree(*root);
	// BalancedTree(isKeyInBinTree(key, *root), root);
	// std::cout << "\napres:\n";
	// printTree(*root);
	// std::cout << "ret del " << del->p.first  << "\n";
}


#endif