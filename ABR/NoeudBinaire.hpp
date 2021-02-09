/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoeudBinaire.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:17 by hherin            #+#    #+#             */
/*   Updated: 2021/02/09 16:12:32 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOEUDBINAIRE_HPP
# define NOEUDBINAIRE_HPP

# include "../utils/traits.hpp"
# include <cmath>
# include "../containers/vector.hpp"
# include <iomanip>

template <class T>
struct s_abr
{
	T key;
	
	s_abr *left;
	s_abr *right;
};

template <class T>
T& nodValue(s_abr<T> *a) { return a->key; } // lancer exception si vide ?

template <class T>
s_abr<T> *createNewTree(T &key, s_abr<T> *ls, s_abr<T> *rs)
{
	s_abr<T> *root = new s_abr<T>;
	if (!root){
		std::cout << "Malloc failed\n";
		return NULL;
	}
	root->key = key;
	root->left = ls;
	root->right = rs;
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
void insertNewNode(s_abr<T> **bst, T &key)
{
	if (isKeyInBinTree(key, *bst))						// IS the key already present
		return ;
	else if (!*bst){
		if (!(*bst = createNewTree<T>(key, NULL, NULL)))	// case empty tree
			return ;
	}
	else{												// check which side the leave should be added
		if (key > (*bst)->key)
			insertNewNode(&(*bst)->right, key);
		else if (key < (*bst)->key)
			insertNewNode(&(*bst)->left, key);
	}
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
ft::vector<s_abr<T>*> save_key(s_abr<T> *bst)
{
	ft::vector<s_abr<T>*> TreeArray;
	if (!bst)
		return TreeArray;
		
	s_abr<T> *current = bst;
	TreeArray.push_back(current);
	
	int i = 1;
	// std::cout << "SIZE NODE " << 2 * (getHeightTree(bst) - 1)<< "\n";
	while (i <= 2 * (getHeightTree(bst) - 1) + 1)
	{
		// std::cout << i - 1 << "= ";
		// (TreeArray[i - 1]) ? std::cout << current->key : std::cout << "nil";
		// std::cout << "\n";
		(TreeArray[i - 1]) ? TreeArray.push_back(current->left) : TreeArray.push_back(0);
		(TreeArray[i - 1]) ? TreeArray.push_back(current->right) : TreeArray.push_back(0);

		current = TreeArray[i];
		i++;
	}
	return TreeArray;
}

template <class T>
void printTree(s_abr<T> *bst)
{
	ft::vector<s_abr<T> *> treeArray = save_key(bst);
	int level = 1;
	size_t i = 1;
	int index = 1;
	// int width =  (2 * getHeightTree(bst) + 1) * 3 * 3;
	
	// std::cout.width((width - 3) / 2);
	std::cout << "[ " << treeArray[0]->key << " ]" << "\n";
	
	while (i < treeArray.size()){
		// std::cout.width( (width - pow(2, level) * 3) / (pow(2, level) + 1) );
		(treeArray[i]) ? 
			std::cout << "[ " << treeArray[i]->key << " ]" : std::cout << "[NIL]";
		
		if (index == pow(2, level)) {
			std::cout << "\n";
			level++;
			index = 1;
		}
		else{
			std::cout << " ";
			index++;
		}
		i++;
	}
	treeArray.clear();
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

// template <class T>
// void	print_MTF_Tree(s_abr<T> const *bst)
// {
// 	int height = getHeightTree(bst);
// 	std::string buf;
// 	s_abr<T> *tmp = bst;
	
// 	buf += tmp->data;
// 	while (height){
// 		buf += tmp->left->data;
// 		buf += tmp->right-data;
// 	}
// }



#endif