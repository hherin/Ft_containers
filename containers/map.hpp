/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:05:46 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 12:05:04 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>

namespace ft
{
	template < class Key,												// map::key_type
			class T,													// map::mapped_type
			class Compare = std::less<Key>,								// map::key_compare
			class Alloc = std::allocator<std::pair<const Key,T> >		// map::allocator_type
			> class map
	{};
}

#endif