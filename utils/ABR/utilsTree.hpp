/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsTree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:00:14 by hherin            #+#    #+#             */
/*   Updated: 2021/02/15 15:37:09 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILSTREE_HPP
# define UTILSTREE_HPP

#include "../../containers/vector.hpp"
# include <iomanip>

template <class T, class M> struct s_abr;
template <class T, class M> int getHeightTree(s_abr<T, M> const *a);

template <class T, class M>
ft::vector<s_abr<T, M>*> save_key(s_abr<T, M> *bst)
{
	ft::vector<s_abr<T, M>*> TreeArray;
	if (!bst)
		return TreeArray;
		
	s_abr<T, M> *current = bst;
	TreeArray.push_back(current);
	
	int i = 1;
	while (i <= pow(2, (getHeightTree(bst) - 1)) - 1)
	{
		(TreeArray[i - 1]) ? TreeArray.push_back(current->left) : TreeArray.push_back(0);
		(TreeArray[i - 1]) ? TreeArray.push_back(current->right) : TreeArray.push_back(0);

		current = TreeArray[i];
		i++;
	}
	return TreeArray;
}

template <class T, class M>
void printTree(s_abr<T, M> *bst)
{
	ft::vector<s_abr<T, M> *> treeArray = save_key(bst);
	int level = 1;
	size_t i = 1;
	int index = 1;
	int width =  pow(2, getHeightTree(bst)) * 3;  // =>   * spaces
	
	std::cout.width((width - 3) / 2);
	std::cout << "[ " << treeArray[0]->p.first << " ]" << "\n";
	
	while (i < treeArray.size()){
		std::cout.width( (width - 3) / (pow(2, level) + 1) );
		(treeArray[i]) ? 
			std::cout << "[ " << treeArray[i]->p.first << " ]" : std::cout << "[NIL]";
		
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

template <class T, class M>
void	iterTree(s_abr<T, M> const *bst)
{
	if (!bst)
		return ;
	else{
		iterTree(bst->left);
		std::cout << bst->p.first << " ";
		iterTree(bst->right);
	}
}

template <class T, class M>
T	Max(s_abr<T, M> *bst)
{
	if (!bst->right)
		return bst->p.first;
	else
		return Max<T>(bst->right);
}

template <class T, class M>
s_abr<T, M> *isKeyInBinTree(T const &key, s_abr<T, M> *bst)
{	
	if (!bst)
		return NULL;
	else
	{
		if (key == bst->p.first)
			return bst;
		else
		{
			if (key < bst->p.first)
				return isKeyInBinTree(key, bst->left);
			else
				return isKeyInBinTree(key, bst->right);
		}
	}
}

#endif