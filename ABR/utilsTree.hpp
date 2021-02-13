/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsTree.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:00:14 by hherin            #+#    #+#             */
/*   Updated: 2021/02/13 16:04:53 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILSTREE_HPP
# define UTILSTREE_HPP

#include "../containers/vector.hpp"
# include <iomanip>

template <class T> struct s_abr;
template <class T> int getHeightTree(s_abr<T> const *a);

template <class T>
ft::vector<s_abr<T>*> save_key(s_abr<T> *bst)
{
	ft::vector<s_abr<T>*> TreeArray;
	if (!bst)
		return TreeArray;
		
	s_abr<T> *current = bst;
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

template <class T>
void printTree(s_abr<T> *bst)
{
	ft::vector<s_abr<T> *> treeArray = save_key(bst);
	int level = 1;
	size_t i = 1;
	int index = 1;
	int width =  pow(2, getHeightTree(bst)) * 3;  // =>   * spaces
	
	std::cout.width((width - 3) / 2);
	std::cout << "[ " << treeArray[0]->key << " ]" << "\n";
	
	while (i < treeArray.size()){
		std::cout.width( (width - 3) / (pow(2, level) + 1) );
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



#endif