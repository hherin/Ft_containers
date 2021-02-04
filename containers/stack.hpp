/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:31:43 by hherin            #+#    #+#             */
/*   Updated: 2021/02/03 11:02:01 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	
	template <class T, class Container = ft::vector<T> > class stack
	{
		public: 
			typedef T						value_type;
			typedef size_t					size_type;
			typedef Container				container_type;
		
		protected:
			container_type _ctnr;
			
		public:
			// =================== Member Functions ===================
			explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {}
			stack(const stack& other) : _ctnr(other._ctnr) {}
			stack& operator=(const stack& other) 
			{ 
				if (this != &other)
					_ctnr = other._ctnr; 
				return *this;
			}
			
			// Returns whether the stack is empty: i.e. whether its size is zero.
			bool empty() const { return !_ctnr.size(); }
			
			// Returns the number of elements in the stack.
			size_type size() const { return _ctnr.size(); }

			// Returns a reference to the top element in the stack. 
			value_type& top() { return _ctnr.back(); }
			const value_type& top() const { return _ctnr.back(); }

			// Inserts a new element at the top of the stack, above its current top element. 
			// The content of this new element is initialized to a copy of val.
			void push (const value_type& val) { _ctnr.push_back(val); }

			// Removes the element on top of the stack, effectively reducing its size by one.
			void pop() { _ctnr.pop_back(); }
		
			friend bool operator== (const stack& lhs, const stack& rhs) { return lhs._ctnr == rhs._ctnr; }
			friend bool operator!= (const stack& lhs, const stack& rhs) { return lhs._ctnr != rhs._ctnr; }
			friend bool operator<  (const stack& lhs, const stack& rhs) { return lhs._ctnr < rhs._ctnr; }
			friend bool operator<= (const stack& lhs, const stack& rhs) { return lhs._ctnr <= rhs._ctnr; }
			friend bool operator>  (const stack& lhs, const stack& rhs) { return lhs._ctnr > rhs._ctnr; }
			friend bool operator>= (const stack& lhs, const stack& rhs) { return lhs._ctnr >= rhs._ctnr; }
		
	};
}

#endif