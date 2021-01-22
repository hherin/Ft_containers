/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:34:24 by hherin            #+#    #+#             */
/*   Updated: 2021/01/22 15:03:45 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

#include "list.hpp"

namespace ft
{
	template <class T, class Container = ft::list<T> > class queue
	{
		
		public:
			typedef T						value_type;
			typedef size_t					size_type;
			typedef Container				container_type;
		
		private:
			container_type _ctnr;

		public:
			// Constructs a queue container adaptor object.
			explicit queue (const container_type& ctnr = container_type())
				: _ctnr(ctnr) {}
			
			// Returns whether the queue is empty: i.e. whether its size is zero.
			bool empty() const { return _ctnr.empty(); }

			// Returns the number of elements in the queue.
			size_type size() const { return _ctnr.size(); }

			// Returns a reference to the next element in the queue. This member function effectively calls member front of the underlying container object.
			value_type& front() { return _ctnr.front(); }
			const value_type& front() const { return _ctnr.front(); }

			// Returns a reference to the last element in the queue. This is the "newest" element in the queue
			value_type& back() { return _ctnr.back(); }
			const value_type& back() const { return _ctnr.back(); }

			// Inserts a new element at the end of the queue, after its current last element. The content of this new element is initialized to val.
			void push (const value_type& val) { _ctnr.push_back(); }
			
			// Removes the next element in the queue, effectively reducing its size by one.
			void pop() { return _ctnr.pop_front(); }


			friend bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr = rhs._ctnr; }
			friend bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr != rhs._ctnr; }
			friend bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr < rhs._ctnr; }
			friend bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr <= rhs._ctnr; }
			friend bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr > rhs._ctnr; }
			friend bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs._ctnr >= rhs._ctnr; }
	};
}

#endif