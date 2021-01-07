/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:14 by hherin            #+#    #+#             */
/*   Updated: 2021/01/07 10:30:02 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <exception>
# include "traits.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			class iterator
			{
				public:
					typedef typename Alloc::difference_type difference_type;
					typedef typename Alloc::value_type value_type;
					typedef typename Alloc::reference reference;
					typedef typename Alloc::pointer pointer;
					typedef std::random_access_iterator_tag iterator_category;

					iterator(pointer val) : _current(val){}
					iterator(iterator const &cp) : _current(cp._current){}
					iterator operator=(iterator const &cp)
					{
						if (this != &cp)
							_current = cp._current;
						return *this;
					}
					~iterator(){}
					//pre incrementation
					iterator operator++(){ _current++; return *this; }
					//post incrementation
					iterator operator++(value_type){ iterator tmp = *this; ++(*this); return tmp; }
					reference operator*() { return *_current; }
					pointer operator->() { return _current; }
					friend bool operator==(const iterator& a, const iterator& b) { return a._current == b._current; };
					friend bool operator!=(const iterator& a, const iterator& b) { return a._current != b._current; };

				private:
					pointer _current;
			};


			//=======================================Coplien Class=======================================
			//allocatorawarecontainer copy cpp reference
			//Default constructor
			explicit vector (const allocator_type& alloc = allocator_type())
				: _vecSize(0), _vecCapacity(_vecSize + 10), _myAlloc(alloc)
			{
				_vector = _myAlloc.allocate(_vecCapacity);
			}

			//Fill constructor with n elements
			explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
				: _vecSize(0), _vecCapacity(_vecSize + 10), _myAlloc(alloc)
			{
				_vector = _myAlloc.allocate(_vecCapacity);
				for (size_type i = 0; i < n; i++)
					push_back(value);
			}

																											// if inputs are pointer segfault, std::vector throw an exception
			// Fill constructor with a range between the first to the last elements of an other vector
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator >::type* = 0)
				: _vecSize(0), _vecCapacity(_vecSize + 10), _myAlloc(alloc)
			{
				_vector = _myAlloc.allocate(_vecCapacity);
				while (first != last){
					push_back(*first);
					first++;
				}
			}

			// Copy constructor
			vector(const vector &x)
			{
				_vecSize = x._vecSize;
				_vecCapacity = x._vecCapacity;
				_myAlloc = x._myAlloc;
				_vector = _myAlloc.allocate(_vecCapacity);
				for (size_type i = 0; i < _vecSize; i++)
					std::swap(_vector[i], x._vector[i]);
			}

			vector& operator=(const vector& x)
			{
				if (this == &x)
					return *this;
				_myAlloc.deallocate(_vector);
				swap(x);
				return *this;
			}

			~vector()
			{
				std::cout << "deallocate\n";
				_myAlloc.deallocate(_vector, _vecCapacity);
			}

			//=======================================Iterators=======================================
			iterator				begin(){ return iterator(_vector); }
			// const_iterator			begin() const { return Iterator(_vector[0]); }
			iterator				end() { return iterator(_vector + _vecSize); }
			// const_iterator			end() const { return Iterator(_vector[_vecSize]); }
			// reverse_iterator		rbegin();
			// const_reverse_iterator	rbegin() const;
			// reverse_iterator		rend();
			// const_reverse_iterator	rend() const;


			//=======================================Capacity=======================================
			// Returns the number of elements in vector (unsigned int)
			size_type	size() const { return _vecSize; }

			// // Returns the maximum number of elements the vector can hold (depend of OS or library implementation limitations)
			// size_type	max_size() const;

			// /*
			// ** Resize a container with n elements
			// **
			// ** if sz < size() : reduction to its first n elements (the rest is removed and destroyed)
			// ** if sz > size() : expand container size (automatic reallocation) +
			// ** complete elements with copy of c or default value until reach a size of sz
			// **
			// ** @param sz: new container size (unsigned int)
			// ** @param c: object copy in the added element
			// */
			void		resize(size_type sz, const value_type &c = value_type());

			// // Returns the size of the storage space currrently allocated for the vector (in terme of elements)
			size_type	capacity() const { return _vecCapacity; }

			// // Returns whether the vector is empty
			bool		empty() const { return _vecSize == 0; }

			/*
			** Reverve at least n unitialized elements in vector
			** if n > current capacity: rallocation storage to size n or more
			** no effect on vector size
			**
			** @param n minimum capacity for the vector
			*/
			// void reserve(size_type n);

			//====================================Element access====================================
			// Returns a reference to the element at position n in container
			reference			operator[](size_type n) { return (_vector[n]); }
			const_reference		operator[](size_type n) const { return (_vector[n]); }

			// // Same as operator[] but check if n is within the bounds of valid element or throw an exception
			// reference			at(size_type n);
			// const_reference		at(size_type n) const;

			// // Returns a ref to the first element in the vector
			// reference			front();
			// const_reference		front() const;

			// // Returns a ref to the last element in the vector
			// reference			back();
			// const_reference		back() const;

			// // Returns a direct pointer to the memory array used by vector to store its elements
			// value_type*			data();
			// const value_type*	data() const;

			//=======================================Modifiers=======================================
			//If a reallocation happens,the storage needed is allocated using the internal allocator.

			// Range version. new elements constructed in the range between first and last
			// template <class InputIterator>
			// void	assign(InputIterator first, InputIterator last);

			// /*
			// ** New container with n element initialized to a copy of val
			// **
			// ** @param n: new size of container
			// ** @param val: value to fill the container with
			// */
			// void	assign(size_type n, const value_type& val);

			/*
			** Add a new element at the end of the vector
			** increase the container size by one - realloc if new vector size surpasses the current vector capacity
			** @param val Value to be copied
			*/
			void	push_back(const value_type& x) 																			// check leaks if pointer array
			{
				resizeIfNeeded();
				_vector[_vecSize] = x;
				_vecSize++;
			}

			// // Removes the last element in the vector + reduce container size
			// void	pop_back();

			/*
			** Insert the new element before the element at the specified position
			** increase the container size (may realloc the vector capacity)
			**
			** @param pos: position where the new element shoud be insert
			** @param x: value to be copied
			** @param first/last: Copies of elements in this range are inserted at pos
			*/
			// iterator	insert(const_iterator pos, const value_type& x);
			// iterator	insert(const_iterator pos, size_type n, const value_type& x);
			// template <class InputIterator>
			// iterator	insert(const_iterator pos, InputIterator first, InputIterator last);

			/*
			** Removes one or a range of elements. Reduce the size of container
			** Returns a iterator pointing to the new location of the element that followed the last
			** element erased by the function call
			** Container end if it's empty
			*/
			// iterator	erase(const_iterator position);
			// iterator	erase(const_iterator first, const_iterator last);

			// // Removed all element from the vector. new size container = 0
			void	clear()
			{
				_myAlloc.deallocate(_vector, _vecCapacity);
				_vector = _myAlloc.allocate(10);
				_vecCapacity = 10;
				_vecSize = 0;
			}

			// exchange the content of the vector with the content of sVec
			void	swap(vector &sVec)
			{
				std::swap(this->_vecSize, sVec._vecSize);
				std::swap(this->_vecCapacity, sVec._vecCapacity);
				std::swap(this->_myAlloc, sVec._myAlloc);
				std::swap(this->_vector, sVec._vector);
			}

		private:
			unsigned int	_vecSize;
			unsigned int	_vecCapacity;
			allocator_type	_myAlloc;
			pointer			_vector;

			void resizeIfNeeded()
			{
				if (_vecSize >= _vecCapacity){
					pointer newVec = _myAlloc.allocate(_vecCapacity);
					for (unsigned int i = 0; i < _vecSize; i++)
						newVec[i] = _vector[i];
					_myAlloc.deallocate(_vector, _vecCapacity);
					_vector = newVec;
					_vecCapacity += 10;
				}
			}
	};
}
#endif