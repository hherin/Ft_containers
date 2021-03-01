/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterators.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:51:35 by hherin            #+#    #+#             */
/*   Updated: 2021/03/01 20:23:51 by heleneherin      ###   ########.fr       */
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

			map_bidirect_iter(map_pointer val = 0, map_pointer neutral = 0) : _current(val), _neutral(neutral) { }
			map_bidirect_iter(map_bidirect_iter<true, D, value_type> const &cp) { _current = cp.getCurrent(); _neutral = cp.getNeutral(); }
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
				if (_current->data.first == _neutral->right->data.first)
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
						map_pointer currSave = _current;
						do 
							(_current->parent) ? _current = _current->parent : 0;
						while (_current->parent && _current->data.first < currSave->data.first);
						
					}
				}
				return *this;
			}
			map_bidirect_iter	operator++(int) { map_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			
            map_bidirect_iter	operator--() 
			{ 
				if (_current->data.first == _neutral->left->data.first)
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
						map_pointer currSave = _current;
						do 
							_current = _current->parent;
						while (_current->parent && _current->data.first > currSave->data.first);
					}
				}
				return *this; 
			}
			map_bidirect_iter	operator--(int) { map_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return _current->data; }
			pointer				operator->() { return &(_current->data); }
			bool				operator==(const map_bidirect_iter& b) { return (this->_current->data.first == b._current->data.first && this->_current->data.second == b._current->data.second); }
			bool				operator!=(const map_bidirect_iter& b) { return this->_current != b._current; }
			map_pointer	getCurrent() const { return _current; }		// two types of iterators (const and non const)
			map_pointer getNeutral() const { return _neutral; }

		private:
			map_pointer _current;
			map_pointer _neutral;
			
	};

	template < bool B, typename D, class valueT> class map_rev_bidirect_iter
	{
		public:
			typedef typename std::ptrdiff_t							difference_type;
			typedef D* 												map_pointer;
			typedef valueT											value_type;
			typedef typename ft::chooseIf<B, const valueT&, valueT&>::type	reference;
			typedef typename ft::chooseIf<B, const valueT*, valueT*>::type	pointer;

			map_rev_bidirect_iter(map_pointer val = 0, map_pointer neutral = 0) : _current(val), _neutral(neutral) { }
			map_rev_bidirect_iter(map_rev_bidirect_iter<true, D, value_type> const &cp) { _current = cp.getCurrent(); _neutral = cp.getNeutral(); }
			map_rev_bidirect_iter operator=(map_rev_bidirect_iter const &cp)
			{
				if (this != &cp){
					_current = cp._current;
					_neutral = cp._neutral;
				}
				return *this;
			}
			~map_rev_bidirect_iter(){}

			map_rev_bidirect_iter&	operator++() 
			{
				if (_current->data.first == _neutral->left->data.first)
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
						map_pointer currSave = _current;
						do 
							_current = _current->parent;
						while (_current->parent && _current->data.first > currSave->data.first);
					}
				}
				// std::cout << "neutral right " <<  _neutral->right->data.first << "\n";
				// std::cout << "current data " << _current->data.first << "\n";
				return *this;
			}
			map_rev_bidirect_iter	operator++(int) { map_rev_bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			
            map_rev_bidirect_iter	operator--() 
			{ 
				if (_current->data.first == _neutral->right->data.first)
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
						map_pointer currSave = _current;
						do 
							(_current->parent) ? _current = _current->parent : 0;
						while (_current->parent && _current->data.first < currSave->data.first);
						
					}
				}
				return *this; 
			}
			map_rev_bidirect_iter	operator--(int) { map_rev_bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() const { return _current->data; }
			pointer				operator->() { return &(_current->data); }
			bool				operator==(const map_rev_bidirect_iter& b) { return (this->_current->data.first == b._current->data.first && this->_current->data.second == b._current->data.second); }
			bool				operator!=(const map_rev_bidirect_iter& b) { return this->_current != b._current; }
			map_pointer	getCurrent() const { return _current; }		// two types of iterators (const and non const)
			map_pointer getNeutral() const { return _neutral; }

		private:
			map_pointer _current;
			map_pointer _neutral;
			
	};
}


#endif