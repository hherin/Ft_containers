/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirect_iter.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:31:57 by hherin            #+#    #+#             */
/*   Updated: 2021/01/19 19:05:54 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECT_ITER_HPP
# define BIDIRECT_ITER_HPP

# include <iostream>
# include <memory>
# include "../utils/traits.hpp"

namespace ft
{
	template <class T, bool B, class Alloc = std::allocator<T> > class vect_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef  T*												nonConst_pointer;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			vect_bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			vect_bidirect_iter(vect_bidirect_iter<T, true, Alloc> const &cp) {_current = cp.getCurrent();}
			vect_bidirect_iter(vect_bidirect_iter<T, false, Alloc> const &cp) {_current = cp.getCurrent();}
			vect_bidirect_iter operator=(vect_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~vect_bidirect_iter(){}

			vect_bidirect_iter	operator++(){ _current++; return *this; }
			vect_bidirect_iter	operator++(int){ vect_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			vect_bidirect_iter	operator--(){ _current--; return *this; }
			vect_bidirect_iter	operator--(int){ vect_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return *_current; }
			pointer				operator->() { return _current; }
			bool				operator==(const vect_bidirect_iter& b) { return this->_current == b._current; }
			bool				operator!=(const vect_bidirect_iter& b) { return this->_current != b._current; }
			nonConst_pointer	getCurrent() const {return _current;}

		protected:
			nonConst_pointer _current;
	};

	template <typename T, bool B, typename D, class Alloc = std::allocator<T> > class list_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef D* 												listelem_pointer;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			list_bidirect_iter(listelem_pointer val = 0) : _current(val){}
			list_bidirect_iter(list_bidirect_iter<T, true, D, Alloc> const &cp) {_current = cp.getCurrent();}
			list_bidirect_iter(list_bidirect_iter<T, false, D, Alloc> const &cp) {_current = cp.getCurrent();}
			list_bidirect_iter operator=(list_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~list_bidirect_iter(){}


			list_bidirect_iter	operator++(){ _current = _current->next; return *this; }
			list_bidirect_iter	operator++(int){ list_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			list_bidirect_iter	operator--(){ _current = _current->prev; return *this; }
			list_bidirect_iter	operator--(int){ list_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return _current->data; }
			listelem_pointer	operator->() { return _current; }
			bool				operator==(const list_bidirect_iter& b) { return this->_current == b._current; }
			bool				operator!=(const list_bidirect_iter& b) { return this->_current != b._current; }
			listelem_pointer	getCurrent() const {return _current;}					// two types of iterators (const and non const)

		protected:
			listelem_pointer _current;
	};
}


#endif