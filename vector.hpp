/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:14 by hherin            #+#    #+#             */
/*   Updated: 2021/01/04 16:59:22 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>


namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class Vector
	{
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef implementation-defined						iterator;
			typedef implementation-defined						const_iterator;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			
			//=======================================Coplien Class=======================================
			// Default constructor
			explicit Vector (const allocator_type& alloc = allocator_type());
			
			// Fill constructor with n elements
			explicit Vector(size_type n, const value_type& value = value_type(), const allocator_type& = allocator_type());
			
			// Fill constructor with a range between the first to the last elements of an other vector
			template <class InputIterator>
				Vector(InputIterator first, InputIterator last, const allocator_type& alloc= allocator_type());
			
			// Copy constructor
			Vector(const Vector& x);
			
			~Vector();
			Vector& operator=(const Vector& x);

			//=======================================Iterators=======================================
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;


			//=======================================Capacity=======================================
			// Returns the number of elements in vector (unsigned int)
			size_type	size() const;

			// Returns the maximum number of elements the vector can hold (depend of OS or library implementation limitations)
			size_type	max_size() const;

			/*
			** Resize a container with n elements
			**
			** if sz < size() : reduction to its first n elements (the rest is removed and destroyed)
			** if sz > size() : expand container size (automatic reallocation) + 
			** complete elements with copy of c or default value until reach a size of sz
			**
			** @param sz: new container size (unsigned int)
			** @param c: object copy in the added element
			*/
			void		resize(size_type sz, const value_type& c = value_type());
			
			// Returns the size of the storage space currrently allocated for the vector (in terme of elements)
			size_type	capacity() const;
			
			// Returns whether the vector is empty
			bool		empty() const;
			
			/*
			** Reverve at least n unitialized elements in vector
			** if n > current capacity: rallocation storage to size n or more
			** no effect on vector size
			**
			** @param n minimum capacity for the vector
			*/
			void reserve(size_type n);

			//====================================Element access====================================
			// Returns a reference to the element at posiion n in container
			reference			operator[](size_type n);
			const_reference		operator[](size_type n) const;

			// Same as operator[] but check if n is within the bounds of valid element or throw an exception
			reference			at(size_type n);
			const_reference		at(size_type n) const;
			
			// Returns a ref to the first element in the vector
			reference			front();
			const_reference		front() const;
			
			// Returns a ref to the last element in the vector
			reference			back();
			const_reference		back() const;

			// Returns a direct pointer to the memory array used by vector to store its elements
			value_type*			data();
			const value_type*	data() const;
			
			//=======================================Modifiers=======================================
			//If a reallocation happens,the storage needed is allocated using the internal allocator.

			// Range version. new elements constructed in the range between first and last 
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last);

			/*
			** New container with n element initialized to a copy of val
			**
			** @param n: new size of container
			** @param val: value to fill the container with
			*/
			void	assign(size_type n, const value_type& val);

			/*
			** Add a new element at the end of the vector
			** increase the container size by one - realloc if new vector size surpasses the current vector capacity
			**
			** @param val: value to be copied
			*/
			void	push_back(const value_type& x);
			
			// Removes the last element in the vector + reduce container size
			void	pop_back();
			
			/*
			** Insert the new element before the element at the specified position 
			** increase the container size (may realloc the vector capacity)
			**
			** @param pos: position where the new element shoud be insert
			** @param x: value to be copied
			** @param first/last: Copies of elements in this range are inserted at pos
			*/
			iterator	insert(const_iterator pos, const value_type& x);
			iterator	insert(const_iterator pos, size_type n, const value_type& x);
			template <class InputIterator>
			iterator	insert(const_iterator pos, InputIterator first, InputIterator last);
			
			/*
			** Removes one or a range of elements. Reduce the size of container
			** Returns a iterator pointing to the new location of the element that followed the last
			** element erased by the function call
			** Container end if it's empty
			*/
			iterator	erase(const_iterator position);
			iterator	erase(const_iterator first, const_iterator last);

			// Removed all element from the vector. new size container = 0
			void	clear();
			
			// exchange the content of the vector with the content of an other object
			void	swap(Vector&);
			
			//====================================Template Spec====================================
		// 	template < class T, class Alloc = allocator<T> > class vector; // generic template
		// template <class Alloc> class vector<bool,Alloc>;               // bool specialization
		
		private:
			unsigned int	_vecSize;
			unsigned int	_vecCapacity;
			allocator_type	_myAllocator;
			pointer			_vector;
			
	};

	template <class T, class allocator_type>
	Vector<T, allocator_type>::Vector(const allocator_type& alloc)
		: _vecSize(0), _vecCapacity(_vecSize + 10), _myAllocator(alloc)
	{
		_vector = _myAllocator(_vecSize);
	}

	template <class T, class allocator_type>
	Vector<T, allocator_type>::Vector(size_type n, const value_type& value, const allocator_type &alloc)
		: _vecSize(n), _vecCapacity(_vecSize + 10), _myAllocator(alloc)
	{
		for 
	}
}
#endif