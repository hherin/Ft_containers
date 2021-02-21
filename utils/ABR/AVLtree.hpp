/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLtree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:17 by hherin            #+#    #+#             */
/*   Updated: 2021/02/19 15:01:31 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOEUDBINAIRE_HPP
# define NOEUDBINAIRE_HPP

# include <cmath>
# include "utilsTree.hpp"
# include "../algo.hpp"

template <class T, class M>
struct s_abr;

// template <class T, class M>
// s_abr<T, M> *createNewTree(s_abr<T, M> *ls, s_abr<T, M> *rs, s_abr<T , M> *parent, ft::pair<T, M> const &content)
// {
// 	s_abr<T, M> *root = new s_abr<T, M>;
// 	if (!root){
// 		std::cout << "Malloc failed\n";
// 		return NULL;
// 	}
// 	root->p.first = content.first;
// 	root->p.second = content.second;
// 	root->parent = parent;
// 	root->left = ls;
// 	root->right = rs;
// 	return root;
// }

// /*
// ** Recursive insert function that returns the new created node
// */
// template <class T, class M>
// s_abr<T, M> *recInsertNode(s_abr<T, M> **bst, s_abr<T, M> *parent, ft::pair<T, M> const &content)
// {
// 	if (isKeyInBinTree(content.first, *bst))						// IS the key already present
// 		return NULL;
// 	else if (!*bst){
// 		if (!(*bst = createNewTree<T, M>(NULL, NULL, parent, content)))	// case empty tree
// 			return *bst;
// 	}
// 	else{										// check which side the leave should be added
// 		parent = *bst;
// 		if (content.first > (*bst)->p.first)
// 			return recInsertNode(&(*bst)->right, parent, content);
// 		else if (content.first < (*bst)->p.first)
// 			return recInsertNode(&(*bst)->left, parent, content);
// 	}
// 	return *bst;
// }


// // returns 1 if element has been inserted are 0 if already in tree
// template <class T, class M>
// s_abr<T, M> *insertNewNode(s_abr<T, M> **bst, ft::pair<T, M> const &content)
// {
// 	s_abr<T, M> *newNode = NULL;
// 	newNode = recInsertNode(bst, newNode, content);
// 	return newNode;
// }

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
	if ((*bst)->p.first > key){										// the deletenode is in left side
		(*bst)->left = recDeleteNode(&((*bst)->left), root, key);
		((*bst)->left) ?  (*bst)->left->parent = *bst : 0;
	}
	else if ((*bst)->p.first < key)	{									// ... right side
		(*bst)->right = recDeleteNode(&((*bst)->right), root, key);
		((*bst)->right) ? (*bst)->right->parent = *bst : 0;
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
void	deleteNode(s_abr<T, M> **root, ft::pair<T, M> content)
{
	recDeleteNode(root, root, content.first);
}


#endif