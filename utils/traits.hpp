/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:35:44 by hherin            #+#    #+#             */
/*   Updated: 2021/01/15 16:05:38 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <iostream>
#include "bidirect_iter.hpp"

namespace ft
{
	template <typename T, bool B, typename D, class Alloc > class list_bidirect_iter;
	
	// ================== Enableif =======================
	template <bool B, class T = void>
	struct enable_if
	{
	};
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// ================== IsInterger type =====================
	template <class, class = void>
	struct is_integer
	{
		static const bool value = false;
	};

	template <>
	struct is_integer<int>
	{
		static const bool value = true;
	};

	//==================== choose const iterator====================
	/*
	** Set the appropriate type for iterators 
	** => true is for non const type, false for const type
	*/
	template <bool B, typename isConst, typename notConst>
	struct chooseIf
	{
	};

	template <typename isConst, typename notConst>
	struct chooseIf<true, isConst, notConst>
	{
		typedef notConst type;
	};

	template <typename isConst, typename notConst>
	struct chooseIf<false, isConst, notConst>
	{
		typedef const isConst type;
	};

	// =================== isIterator traits ======================
	template <typename T, typename D, class Alloc>
	struct isIterator
	{};

	template <typename T, typename D, class Alloc>
	struct isIterator< list_bidirect_iter<T, true, D, Alloc>, D , Alloc>
	{ typedef T type; };

} // namespace ft
#endif