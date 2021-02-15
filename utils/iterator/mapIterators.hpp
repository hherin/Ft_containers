/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:35 by hherin            #+#    #+#             */
/*   Updated: 2021/02/15 15:19:22 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP


namespace ft
{
	template <typename T, bool B, typename D> class map_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef D* 												mapelem_pointer;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			map_bidirect_iter(mapelem_pointer val = 0) : _current(val){}
			map_bidirect_iter(map_bidirect_iter<T, true, D> const &cp) { _current = cp.getCurrent(); }
			map_bidirect_iter(map_bidirect_iter<T, false, D> const &cp) { _current = cp.getCurrent(); }
			map_bidirect_iter operator=(map_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~map_bidirect_iter(){}

			map_bidirect_iter	operator++() 
            { //_current = _current->next; return *this; 
                if (_current->right)
                    _current = _current->right;
                else
                    _current = _current->parent;
                return *this;
            }
			map_bidirect_iter	operator++(int) { map_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			
            map_bidirect_iter	operator--()
            { //_current = _current->prev; return *this; 
                if (_current->left)
                    _current = _current->left;
                else
                    current
            }
			map_bidirect_iter	operator--(int) { map_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return _current->data; }
			mapelem_pointer	operator->() { return _current; }
			bool				operator==(const map_bidirect_iter& b) { return this->_current == b._current; }
			bool				operator!=(const map_bidirect_iter& b) { return this->_current != b._current; }
			mapelem_pointer	getCurrent() const { return _current; }					// two types of iterators (const and non const)

		protected:
			mapelem_pointer _current;
	};
}


#endif