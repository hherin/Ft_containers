/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bidirect_iter.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:18:40 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/11 18:27:07 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECT_ITER_HPP
# define REVERSE_BIDIRECT_ITER_HPP

# include <iostream>
# include <memory>

namespace ft
{
    template <class T, bool B, class Alloc = std::allocator<T> > class reverse_bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;

			typedef typename ft::chooseIf<B,  typename Alloc::const_reference, typename Alloc::reference>::type reference;
			typedef typename ft::chooseIf<B,  typename Alloc::const_pointer, typename Alloc::pointer>::type pointer;

			typedef typename Alloc::pointer nonConst_pointer;
			typedef std::bidirectional_iterator_tag iterator_category;

			reverse_bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			reverse_bidirect_iter(reverse_bidirect_iter<T, true, Alloc> const &cp) {_current = cp.getCurrent();}
			reverse_bidirect_iter(reverse_bidirect_iter<T, false, Alloc> const &cp) {_current = cp.getCurrent();}
			reverse_bidirect_iter operator=(reverse_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~reverse_bidirect_iter(){}


			reverse_bidirect_iter		operator++() { _current--; return *this; }
			reverse_bidirect_iter		operator++(int) { reverse_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			reverse_bidirect_iter		operator--() { _current++; return *this; }
			reverse_bidirect_iter		operator--(int) { reverse_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return *_current; }
			pointer				operator->() { return _current; }
			friend bool			operator==(const reverse_bidirect_iter& a, const reverse_bidirect_iter& b) { return a._current == b._current; }
			friend bool			operator!=(const reverse_bidirect_iter& a, const reverse_bidirect_iter& b) { return a._current != b._current; }
			nonConst_pointer	getCurrent() const {return _current;}

		protected:
			nonConst_pointer _current;
	};
}

#endif