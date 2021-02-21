/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:35 by hherin            #+#    #+#             */
/*   Updated: 2021/02/19 16:10:54 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <iostream>
# include <memory>
# include "../traits.hpp"
# include "../../containers/stack.hpp"
# include <stack>
	
namespace ft
{
	template <class T1, class T2> class pair;

	template < bool B, typename D, class valueT> class map_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef D* 												map_pointer;
			typedef valueT											value_type;
			typedef typename ft::chooseIf<B, const valueT&, valueT&>::type	reference;
			typedef typename ft::chooseIf<B, const valueT*, valueT*>::type	pointer;

			map_bidirect_iter(map_pointer val = 0, map_pointer neutral = 0) : _current(val), _neutral(neutral)
			{
			}
			map_bidirect_iter(map_bidirect_iter<true, D, value_type> const &cp) { _current = cp.getCurrent(); _neutral = cp._neutral; }
			// map_bidirect_iter(map_bidirect_iter<false, D, value_type> const &cp) { _current = cp.getCurrent(); }
			map_bidirect_iter operator=(map_bidirect_iter const &cp)
			{
				if (this != &cp){
					_current = cp._current;
					_neutral = cp._neutral;
				}
				return *this;
			}
			~map_bidirect_iter(){}

			map_bidirect_iter&	operator++() 
			{
				if (_current == _neutral->right)
					_current = _neutral;
				else if (_current == _neutral)
					_current = _current->left;
				else{
					if (_current->right){
						_current = _current->right;
						while (_current->left)
							_current = _current->left;
					}
					else{
						if (_current->parent)
							_current = _current->parent;
					}
				}
				return *this;
			}
			map_bidirect_iter	operator++(int) { map_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			
            map_bidirect_iter	operator--() 
			{ 
				if (_current == _neutral->left)
					_current = _neutral;
				else if (_current == _neutral)
					_current = _current->right;
				else{
					if (_current->left){
						_current = _current->left;
						while (_current->right)
							_current = _current->right;
					}
					else{
						if (_current->parent)
							_current = _current->parent;
					}
				}
				return *this; }
			map_bidirect_iter	operator--(int) { map_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return _current->p; }
			pointer				operator->() { return &_current->p; }
			bool				operator==(const map_bidirect_iter& b) { return (this->_current->p.first == b._current->p.first && this->_current->p.second == b._current->p.second); }
			bool				operator!=(const map_bidirect_iter& b) { return this->_current != b._current; }
			map_pointer	getCurrent() const { return _current; }					// two types of iterators (const and non const)

		private:
			map_pointer _current;
			map_pointer _neutral;
			
			
	};
}


#endif