/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:35 by hherin            #+#    #+#             */
/*   Updated: 2021/02/16 15:47:56 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <iostream>
# include <memory>
# include "../traits.hpp"
	
namespace ft
{
	template <class T1, class T2> class pair;

	template <typename T, bool B, typename D, class Key, class Type> class map_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef D* 												mapelem_pointer;
			typedef ft::pair<const Key, Type>						value_type;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			map_bidirect_iter(mapelem_pointer val = 0) : _current(val){}
			map_bidirect_iter(map_bidirect_iter<T, true, D, Key, Type> const &cp) { _current = cp.getCurrent(); }
			map_bidirect_iter(map_bidirect_iter<T, false, D, Key, Type> const &cp) { _current = cp.getCurrent(); }
			map_bidirect_iter operator=(map_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~map_bidirect_iter(){}

			map_bidirect_iter	operator++() { _current = _current->next; return *this; }
			map_bidirect_iter	operator++(int) { map_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			
            map_bidirect_iter	operator--() { _current = _current->prev; return *this; }
			map_bidirect_iter	operator--(int) { map_bidirect_iter tmp = *this; --(*this); return tmp; }
			value_type&			operator*() const { return _current->content; }
			value_type*			operator->() { return &_current->content; }
			bool				operator==(const map_bidirect_iter& b) { return (this->_current->first == b._current->first && this->_current->second == b._current->second); }
			bool				operator!=(const map_bidirect_iter& b) { return this->_current != b._current; }
			mapelem_pointer	getCurrent() const { return _current; }					// two types of iterators (const and non const)

		protected:
			mapelem_pointer _current;
	};
}


#endif