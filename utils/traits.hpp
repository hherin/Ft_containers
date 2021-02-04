/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:35:44 by hherin            #+#    #+#             */
/*   Updated: 2021/02/04 12:33:53 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <iostream>
#include "iterator/bidirect_iter.hpp"

namespace ft
{
	template <typename T, bool B, typename D> class list_bidirect_iter;
	
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


	// ========================= isABR ========================
	// template <class, class = void>
	// struct isABR { static const bool value = false; };
	
	// template<>
	// struct isABR<s_abr> { static const bool value = true; };
	
	// ================== IsInterger type =====================
	template <class, class = void>
	struct is_integral { static const bool value = false; };

	template <>
	struct is_integral<bool> { static const bool value = true; };
	
	template <>
	struct is_integral<wchar_t> { static const bool value = true; };

	template <>
	struct is_integral<short> { static const bool value = true; };
	
	template <>
	struct is_integral<int> { static const bool value = true; };

	template <>
	struct is_integral<long> { static const bool value = true; };

	template <>
	struct is_integral<long long> { static const bool value = true; };

	//==================== choose const iterator====================
	/*
	** Set the appropriate type for iterators 
	** => true is for non const type, false for const type
	*/
	template <bool B, typename isConst, typename notConst>
	struct chooseIf {};

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

} // namespace ft
#endif