/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoeudBinaire.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:46:17 by hherin            #+#    #+#             */
/*   Updated: 2021/02/04 15:51:12 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOEUDBINAIRE_HPP
# define NOEUDBINAIRE_HPP

# include "../utils/traits.hpp"

template <class T>
struct s_abr
{
	T key;
	
	s_abr *left;
	s_abr *right;
};

template<class T>
s_abr<T> *createNewEmptyTree() 
{ 
	return NULL;
}

template <class T>
s_abr<T> *createNewTree(T &key, s_abr<T> *ls, s_abr<T> *rs)
{
	s_abr<T> *root = new s_abr<T>;
	root->key = key;
	root->left = ls;
	root->right = rs;
	return root;
}

template <class T>
bool empty(s_abr<T> const *a) { return !a; }

template <class T>
T& nodValue(s_abr<T> *a) { return a->key; } // lancer exception si vide ?

template <class T>
bool isKeyInBinTree(T &key, s_abr<T> const *a)
{
	s_abr<T> *tmp = a;
	
	if (empty(tmp))
		return false;
	else
	{
		if (key == tmp->key)
			return true;
		else
		{
			if (key < tmp->key)
				return isKeyInBinTree(key, tmp->left);
			else
				return isKeyInBinTree(key, tmp->right);
		}
	}
}

template <class T>
void insertNewLeave(s_abr<T> **a, T &key)
{
	if (empty(*a))
		*a = createNewTree<T>(key, NULL, NULL);
	else
	{
		s_abr<T> *tmp = *a;
		if (key > tmp->key)
			insertNewLeave(&tmp->right, key);
		else if (key < tmp->key)
			insertNewLeave(&tmp->left, key);
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

#endif