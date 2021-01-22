/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bidirect_iter.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:18:40 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/22 11:58:23 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_BIDIRECT_ITER_HPP
# define REVERSE_BIDIRECT_ITER_HPP

# include <iostream>
# include <memory>
# include "../traits.hpp"

namespace ft
{
    template <class T, bool B> class vect_reverse_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef  T*												nonConst_pointer;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			vect_reverse_bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			vect_reverse_bidirect_iter(vect_reverse_bidirect_iter<T, true> const &cp) { _current = cp.getCurrent(); }
			vect_reverse_bidirect_iter(vect_reverse_bidirect_iter<T, false> const &cp) { _current = cp.getCurrent(); }
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
			reference						operator*() const { return *_current; }
			pointer							operator->() { return _current; }
			bool							operator==(const vect_reverse_bidirect_iter& b) { return this->_current == b._current; }
			bool							operator!=(const vect_reverse_bidirect_iter& b) { return this->_current != b._current; }
			nonConst_pointer				getCurrent() const { return _current; }

		protected:
			nonConst_pointer _current;
	};

	template <class T, bool B, class D> class list_reverse_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef  D*												listelem_pointer;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			list_reverse_bidirect_iter(listelem_pointer val = 0) : _current(val){}
			list_reverse_bidirect_iter(list_reverse_bidirect_iter<T, true, D> const &cp) { _current = cp.getCurrent(); }
			list_reverse_bidirect_iter(list_reverse_bidirect_iter<T, false, D> const &cp) { _current = cp.getCurrent(); }
			list_reverse_bidirect_iter(list_bidirect_iter<T, false, D> const &cp) { _current = cp.getCurrent()->prev; }
			list_reverse_bidirect_iter operator=(list_reverse_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~list_reverse_bidirect_iter(){}

			list_reverse_bidirect_iter		operator++() { _current = _current->prev; return *this; }
			list_reverse_bidirect_iter		operator++(int) { list_reverse_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			list_reverse_bidirect_iter		operator--() { _current = _current->next; return *this; }
			list_reverse_bidirect_iter		operator--(int) { list_reverse_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference						operator*() const { return _current->data; }
			pointer							operator->() { return _current; }
			bool							operator==(const list_reverse_bidirect_iter& b) { return this->_current == b._current; }
			bool							operator!=(const list_reverse_bidirect_iter& b) { return this->_current != b._current; }
			listelem_pointer				getCurrent() const { return _current; }

		protected:
			listelem_pointer _current;
	};
}

#endif