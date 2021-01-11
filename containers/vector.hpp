/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:14 by hherin            #+#    #+#             */
/*   Updated: 2021/01/11 18:33:05 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <exception>
# include <cmath>
# include "../utils/traits.hpp"
# include "../utils/random_iter.hpp"
# include "../utils/algo.hpp"
# include "../utils/reverse_random_iter.hpp"

# define EXTRA_MEM 10

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
			typedef typename ft::random_iter<T, true, Alloc>	iterator;
			typedef typename ft::random_iter<T, false, Alloc>	const_iterator;
			typedef typename ft::reverse_random_iter<T, true, Alloc>	reverse_iterator;
			typedef typename ft::reverse_random_iter<T, false, Alloc>	const_reverse_iterator;
			class exceptionOutOfRange;

			//=======================================Coplien Class=======================================
			//allocatorawarecontainer copy cpp reference
			//Default constructor
			explicit vector (const allocator_type& alloc = allocator_type())
				: _size(0), _capacity(_size + EXTRA_MEM), _myAlloc(alloc)
			{
				_vector = _myAlloc.allocate(_capacity);
			}

			//Fill constructor with n elements
			explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
				: _size(0), _capacity(_size + EXTRA_MEM), _myAlloc(alloc)
			{
				_vector = _myAlloc.allocate(_capacity);
				for (size_type i = 0; i < n; i++)
					push_back(value);
			}

																											// if inputs are pointer segfault, std::vector throw an exception
			// Fill constructor with a range between the first to the last elements of an other vector
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator >::type* = 0)
				: _myAlloc(alloc)
			{
				_size = last - first;
				_capacity = _size + EXTRA_MEM;
				_vector = _myAlloc.allocate(_capacity);
				while (first != last){
					push_back(*first);
					first++;
				}
			}

			// Copy constructor
			vector(const vector &x)
				:_size(x._size), _capacity(x._capacity), _myAlloc(x._myAlloc)
			{
				_vector = _myAlloc.allocate(_capacity);
				for (std::pair<iterator, const_iterator> it(begin(), x.begin()); it.first != end(); it.first++, it.second++)
					*it.first = *it.second;
			}

			vector& operator=(const vector& x)
			{
				if (this == &x)
					return *this;
				_myAlloc.deallocate(_vector, _capacity);
				_size = x._size;
				_capacity = x._capacity;
				_myAlloc = std::allocator_traits<allocator_type>::select_on_container_copy_construction(x._myAlloc);
				_vector = _myAlloc.allocate(_capacity);
				for (std::pair<iterator, const_iterator> it(begin(), x.begin()); it.first != end(); it.first++, it.second++)
					*it.first = *it.second;
				return *this;
			}

			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					pop_back();
				_myAlloc.deallocate(_vector, _capacity);
			}

			//=======================================Iterators=======================================
			const_iterator			begin() const { return const_iterator(_vector); }
			iterator				begin() { return iterator(_vector); }
			iterator				end() { return iterator(_vector + _size); }
			const_iterator			end() const { return const_iterator(_vector + _size); }
			reverse_iterator		rbegin() { return reverse_iterator(_vector + _size - 1); }
			const_reverse_iterator	rbegin() const { return reverse_iterator(_vector + _size - 1); }
			reverse_iterator		rend() { return reverse_iterator(_vector - 1); }
			const_reverse_iterator	rend() const { return reverse_iterator(_vector - 1); }


			//=======================================Capacity=======================================
			// Returns the number of elements in vector (unsigned int)
			size_type	size() const { return _size; }

			// // Returns the maximum number of elements the vector can hold (depend of OS or library implementation limitations)
			size_type	max_size() const { return _myAlloc.max_size(); }

			// /*
			// ** Resize a container with n elements
			// **
			// ** if sz < size() : reduction to its first n elements (the rest is removed and destroyed)
			// ** if sz > size() : expand container size (automatic reallocation) +
			// ** complete elements with copy of c or default value until reach a size of sz
			// **
			// ** @param sz New container size (unsigned int)
			// ** @param c Object copied in the added element
			// */
			void		resize(size_type sz, const value_type &c = value_type())
			{
				if (sz < _size){
					for (size_type i = 0; i < _size - sz; i++)
						pop_back();
				}
				else{
					for (size_t i = _size; i < sz; i++)
						push_back(c);
				}
			}

			// // Returns the size of the storage space currrently allocated for the vector (in terme of elements)
			size_type	capacity() const { return _capacity; }

			// // Returns whether the vector is empty
			bool		empty() const { return _size == 0; }

			/*
			** Reverve at least n unitialized elements in vector
			** if n > current capacity: rallocation storage to size n or more
			** no effect on vector size
			** @param n Minimum capacity for the vector
			*/
			void reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				pointer tmp = _myAlloc.allocate(n);
				for (std::pair<iterator, int> it (begin(), 0); it.first != end(); it.first++, it.second++)
					tmp[it.second] = *it.first;
				_myAlloc.deallocate(_vector, _capacity);
				_capacity = n;
				_vector = tmp;
			}

			//====================================Element access====================================
			// Returns a reference to the element at position n in container
			reference			operator[](size_type n) { return (_vector[n]); }
			const_reference		operator[](size_type n) const { return (_vector[n]); }

			// // Same as operator[] but check if n is within the bounds of valid element or throw an exception
			reference			at(size_type n)
			{
				if (n >= _size)
					throw exceptionOutOfRange();
				return (_vector[n]);
			}

			const_reference		at(size_type n) const
			{
				if (n >= _size)
					throw exceptionOutOfRange();
				return (_vector[n]);
			}

			// Returns a ref to the first element in the vector
			reference			front() { return _vector[0]; }
			const_reference		front() const { return _vector[0]; }

			// Returns a ref to the last element in the vector
			reference			back() { return _vector[_size - 1] ; }
			const_reference		back() const { return _vector[_size - 1] ; }

			// // Returns a direct pointer to the memory array used by vector to store its elements
			value_type*			data() { return _vector; }

			const value_type*	data() const { return _vector; }

			//=======================================Modifiers=======================================
			//If a reallocation happens,the storage needed is allocated using the internal allocator.

			// Range version. new elements constructed in the range between first and last
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				clear();
				while (first != last)
					push_back(*first++);
			}

			// /*
			// ** New container with n element initialized to a copy of val
			// **
			// ** @param n: new size of container
			// ** @param val: value to fill the container with
			// */
			void	assign(size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			/*
			** Add a new element at the end of the vector
			** increase the container size by one - realloc if new vector size surpasses the current vector capacity
			** @param val Value to be copied
			*/
			void	push_back(const value_type& x) 																			// check leaks if pointer array
			{
				resizeIfNeeded();
				_vector[_size] = x;
				_size++;
			}

			// // Removes the last element in the vector + reduce container size
			void	pop_back()
			{
				_myAlloc.destroy(&_vector[_size - 1]);
				_size--;
			}

			/*
			** Insert the new element before the element at the specified position
			** increase the container size (may realloc the vector capacity)
			**
			** @param pos Position where the new element shoud be insert
			** @param x Value to be copied
			** @param first/last Copies of elements in this range are inserted at pos
			*/
			iterator	insert(const_iterator pos, const value_type& x) { return insert(pos, (size_type)1, x); }

			iterator	insert(const_iterator pos, size_type n, const value_type& x)
			{
				difference_type addX = iterator(pos) - begin() + 1; // position for added value x
				difference_type tmp = end() - 1 - iterator(pos) + n; // how many time we have to swap the vector

				iterator it;
				if (_size + n > _capacity) // check if there is enought place in vector
					reserve(_size + n + EXTRA_MEM);
				for (size_type i = n; i > 0; i--){ // how many times the vector is swap
					it = end() - 1 + n;
					for (difference_type j = 0; j < tmp; j++){ // loop for how many time it will be swapped
						std::swap(*(it), *(it + 1));
						it--;
					}
					tmp --;
				}
				it = begin() + addX;
				_size += n;
				while (n--){
					*it = x;
					it++;
				}
				return iterator(pos);
			}

			template <class InputIterator>
			iterator	insert(const_iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator >::type* = 0)
			{
				size_type index = iterator(pos) - begin() + 1;
				insert(pos, last - first, 0);
				iterator it = begin() + index;
				while (first != last)
					*(it++) = *(first++);
				return iterator(pos);
			}

			/*
			** Removes one or a range of elements. Reduce the size of container
			** Returns a iterator pointing to the new location of the element that followed the last
			** element erased by the function call
			** Container end if it's empty
			*/
			iterator	erase(const_iterator position) { return erase(position, position); }

			iterator	erase(const_iterator first, const_iterator last)
			{
				pointer tmp;
				size_type era = last - first + 1; // number of element to be destroyed
				tmp = _myAlloc.allocate(_capacity - era);
				for (std::pair<size_type, size_type> i(0, 0); i.first < _size; i.first++){
					if (i.first < static_cast<size_type>(iterator(first) - begin()) ||
					 i.first >= static_cast<size_type>(iterator(first) - begin()) + era)
						tmp[i.second++] = _vector[i.first];
					_myAlloc.destroy(&_vector[i.first]);
				}
				_size -= era;
				_capacity -= era;
				_vector = tmp;
				return iterator(last + 1);
			}

			// Removed all element from the vector. new size container = 0
			void	clear()
			{
				_myAlloc.deallocate(_vector, _capacity);
				for (size_type i = 0; i < _size; i++)
					_myAlloc.destroy(_vector[i]);
				_vector = _myAlloc.allocate(EXTRA_MEM);
				_capacity = EXTRA_MEM;
				_size = 0;
			}

			// exchange the content of the vector with the content of sVec
			void	swap(vector &sVec)
			{
				swapVector(ft::max<vector>(*this, sVec), ft::min<vector>(*this, sVec));
				std::swap(this->_size, sVec._size);
				std::swap(this->_myAlloc, sVec._myAlloc);
			}

		private:
			unsigned int	_size;
			unsigned int	_capacity;
			allocator_type	_myAlloc;
			pointer			_vector;

			void resizeIfNeeded()
			{
				if (_size >= _capacity){
					pointer newVec = _myAlloc.allocate(_capacity);
					for (unsigned int i = 0; i < _size; i++)
						newVec[i] = _vector[i];
					_myAlloc.deallocate(_vector, _capacity);
					for (unsigned int i = 0; i < _size; i++)
						_myAlloc.destroy(&_vector[i]);
					_vector = newVec;
					_capacity += EXTRA_MEM;
				}
			}

			void swapVector(vector& min, vector& max)
			{
				vector tmp = max;
				for (std::pair< vector::iterator, vector::iterator > it(max.begin(), min.begin()); it.second != min.end(); it.first++, it.second++)
					*it.first = *it.second;
				min._myAlloc.deallocate(min._vector, min._capacity);
				min._vector = min._myAlloc.allocate(max._capacity);
				for (std::pair< vector::iterator, vector::iterator > it(min.begin(), tmp.begin()); it.second != tmp.end(); it.first++, it.second++)
					*it.first = *it.second;
				min._capacity = max._capacity;
			}
	};

	template <class T, class Alloc >
	class vector<T, Alloc>::exceptionOutOfRange
	{
		public:
			exceptionOutOfRange(){}
			const char* what() const throw() { return "Input out of range.\n";}
	};
}
#endif