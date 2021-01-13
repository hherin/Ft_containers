/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bidirect_iter.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:18:40 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/13 16:35:48 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECT_ITER_HPP
# define REVERSE_BIDIRECT_ITER_HPP

# include <iostream>
# include <memory>
# include "../utils/traits.hpp"

namespace ft
{
    template <class T, bool B, class Alloc = std::allocator<T> > class vect_reverse_bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;

			typedef typename ft::chooseIf<B,  typename Alloc::const_reference, typename Alloc::reference>::type reference;
			typedef typename ft::chooseIf<B,  typename Alloc::const_pointer, typename Alloc::pointer>::type pointer;

			typedef typename Alloc::pointer nonConst_pointer;
			typedef std::bidirectional_iterator_tag iterator_category;

			vect_reverse_bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			vect_reverse_bidirect_iter(vect_reverse_bidirect_iter<T, true, Alloc> const &cp) {_current = cp.getCurrent();}
			vect_reverse_bidirect_iter(vect_reverse_bidirect_iter<T, false, Alloc> const &cp) {_current = cp.getCurrent();}
			vect_reverse_bidirect_iter operator=(vect_reverse_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~vect_reverse_bidirect_iter(){}


			vect_reverse_bidirect_iter		operator++() { _current--; return *this; }
			vect_reverse_bidirect_iter		operator++(int) { vect_reverse_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			vect_reverse_bidirect_iter		operator--() { _current++; return *this; }
			vect_reverse_bidirect_iter		operator--(int) { vect_reverse_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return *_current; }
			pointer				operator->() { return _current; }
			friend bool			operator==(const vect_reverse_bidirect_iter& a, const vect_reverse_bidirect_iter& b) { return a._current == b._current; }
			friend bool			operator!=(const vect_reverse_bidirect_iter& a, const vect_reverse_bidirect_iter& b) { return a._current != b._current; }
			nonConst_pointer	getCurrent() const {return _current;}

		protected:
			nonConst_pointer _current;
	};

	template <class T, bool B, class Alloc = std::allocator<T> > class list_reverse_bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;

			typedef typename ft::chooseIf<B,  typename Alloc::const_reference, typename Alloc::reference>::type reference;
			typedef typename ft::chooseIf<B,  typename Alloc::const_pointer, typename Alloc::pointer>::type pointer;

			typedef typename Alloc::pointer nonConst_pointer;
			typedef std::bidirectional_iterator_tag iterator_category;

			list_reverse_bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			list_reverse_bidirect_iter(list_reverse_bidirect_iter<T, true, Alloc> const &cp) {_current = cp.getCurrent();}
			list_reverse_bidirect_iter(list_reverse_bidirect_iter<T, false, Alloc> const &cp) {_current = cp.getCurrent();}
			list_reverse_bidirect_iter operator=(list_reverse_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~list_reverse_bidirect_iter(){}


			list_reverse_bidirect_iter		operator++() { _current--; return *this; }
			list_reverse_bidirect_iter		operator++(int) { list_reverse_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			list_reverse_bidirect_iter		operator--() { _current++; return *this; }
			list_reverse_bidirect_iter		operator--(int) { list_reverse_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return *_current; }
			pointer				operator->() { return _current; }
			friend bool			operator==(const list_reverse_bidirect_iter& a, const list_reverse_bidirect_iter& b) { return a._current == b._current; }
			friend bool			operator!=(const list_reverse_bidirect_iter& a, const list_reverse_bidirect_iter& b) { return a._current != b._current; }
			nonConst_pointer	getCurrent() const {return _current;}

		protected:
			nonConst_pointer _current;
	};
}

#endif