/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:31:43 by hherin            #+#    #+#             */
/*   Updated: 2021/01/19 17:22:58 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft{
	template <class T, class Container = ft::vector<T> > class stack
	{
		public: 
			typedef T						value_type;
			typedef size_t					size_type;
			typedef Container				container_type;
		
		protected:
			Container _ctnr;
			size_type _size;
			
		public:
			// =================== Member Functions ===================
			explicit stack (const container_type& ctnr = container_type())
				: _ctnr(ctnr), _size(ctnr.size()) {}
			
			// Returns whether the stack is empty: i.e. whether its size is zero.
			bool empty() const { return (_size == 0); }
			
			// Returns the number of elements in the stack.
			size_type size() const { return _size; }

			// Returns a reference to the top element in the stack. 
			value_type& top() { return _ctnr.front(); }
			const value_type& top() const { return _ctnr.front(); }

			// Inserts a new element at the top of the stack, above its current top element. 
			// The content of this new element is initialized to a copy of val.
			void push (const value_type& val)
			{
				_size++;
				_ctnr.insert(_ctnr.begin(), val); 
			}

			// Removes the element on top of the stack, effectively reducing its size by one.
			void pop()
			{
				_size--;
				_ctnr.erase(_ctnr.begin());
			}
		
			friend bool operator== (const stack& lhs, const stack& rhs) { return lhs.operator==(lhs, rhs); }
			friend bool operator!= (const stack& lhs, const stack& rhs) { return lhs.operator!=(lhs, rhs); }
			friend bool operator<  (const stack& lhs, const stack& rhs) { return lhs.operator<(lhs, rhs); }
			friend bool operator<= (const stack& lhs, const stack& rhs) { return lhs.operator<=(lhs, rhs); }
			friend bool operator>  (const stack& lhs, const stack& rhs) { return lhs.operator>(lhs, rhs); }
			friend bool operator>= (const stack& lhs, const stack& rhs) { return lhs.operator>=(lhs, rhs); }
		
	};
}

#endif