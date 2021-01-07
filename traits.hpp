/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:35:44 by hherin            #+#    #+#             */
/*   Updated: 2021/01/06 16:14:32 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
# define TRAITS_HPP

#include <iostream>

namespace ft
{
	template< bool B, class T = void >
	struct enable_if {};
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class, class =void>
	struct is_integer
	{
		static const bool value = false;
	};
	template <>
	struct is_integer<int>
	{
		static const bool value = true;
	};
}
#endif