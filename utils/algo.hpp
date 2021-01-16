/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:49:30 by hherin            #+#    #+#             */
/*   Updated: 2021/01/12 13:37:47 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_HPP
# define ALGO_HPP

#include "../containers/vector.hpp"

namespace ft
{
	template <typename T>
	bool is_max(T obj1, T obj2)
	{
		return obj1.size() > obj2.size();
	}

	template <typename T>
	T& max(T& obj1, T& obj2)
	{
		if (obj1.size() > obj2.size())
			return obj1;
		return obj2;
	}

	template <typename T>
	T& min(T& obj1, T& obj2)
	{
		if (obj1.size() < obj2.size())
			return obj1;
		return obj2;
	}

	template<class T>
	bool is_less(const T& a, const T& b)
	{
		return a < b;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) 
				return false;
			else if (*first1 < *first2) 
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}
}
#endif