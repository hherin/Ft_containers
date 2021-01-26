/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:58:14 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 11:55:46 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <algorithm>
# include <memory>
# include <exception>
# include "../utils/traits.hpp"
# include "../utils/iterator/random_iter.hpp"
# include "../utils/algo.hpp"


namespace ft
{
	template <class T, bool B> class random_iter;
	template <class T, bool B> class reverse_random_iter;
	template <bool B, class T> struct enable_if;
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2);
}

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
			typedef typename ft::random_iter<T, true>			iterator;
			typedef typename ft::random_iter<T, false>			const_iterator;
			typedef typename ft::reverse_random_iter<T, true>	reverse_iterator;
			typedef typename ft::reverse_random_iter<T, false>	const_reverse_iterator;
			class exceptionOutOfRange : public std::exception
			{
				public:
					exceptionOutOfRange(){}
					const char* what() const throw() { return "Input out of range.\n";}
			};
			
		private:
			size_type		_size;
			size_type		_capacity;
			pointer			_vector;
			allocator_type	_alloc;
		
		public:
			// =======================================Coplien Class=======================================
			//allocatorawarecontainer copy cpp reference
			//Default constructor
			explicit vector (const allocator_type& alloc = allocator_type())
				: _size(0), _capacity(0), _alloc(alloc)
			{
				_vector = _alloc.allocate(_capacity);
			}

			//Fill constructor with n elements
			explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
				: _size(0), _capacity(n), _alloc(alloc)
			{
				_vector = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					push_back(value);
			}

																											// if inputs are pointer segfault, std::vector throw an exception
			// Fill constructor with a range between the first to the last elements of an other vector
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
				: _size(0), _capacity(last - first), _alloc(alloc)
			{
				_vector = _alloc.allocate(_capacity);
				while (first != last){
					push_back(*first);
					first++;
				}
			}

			// Copy constructor
			vector(const vector &x)
				:_size(x._size), _capacity(x._size)
			{
				_alloc = x._alloc;
				_vector = _alloc.allocate(_capacity);
				iterator it = begin();
				for (iterator xIt(x.begin()); xIt != iterator(x.end()); xIt++)
					_alloc.construct(&(*it++), *xIt);
			}

			vector& operator=(const vector& x)
			{
				vector tmp(x);
				swap(tmp);
				return *this;
			}

			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					pop_back();
				_alloc.deallocate(_vector, _capacity);
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

			// Returns the maximum number of elements the vector can hold (depend of OS or library implementation limitations)
	// size_type	max_size() const { return _myAlloc.max_size(); }

			/*
			** Resize a container with n elements
			** if sz < size() : reduction to its first n elements (the rest is removed and destroyed)
			** if sz > size() : expand container size (automatic reallocation) +
			** complete elements with copy of c or default value until reach a size of sz
			**
			** @param sz New container size (unsigned int)
			** @param c Object copied in the added element
			*/
			void		resize(size_type sz, const value_type &c = value_type())
			{
				if (sz < _size){
					size_t rem = _size - sz;
					for (size_type i = 0; i < rem; i++)
						pop_back();
				}
				else
					for (size_t i = _size; i < sz; i++)
						push_back(c);
			}

			// Returns the size of the storage space currrently allocated for the vector (in terme of elements)
			size_type	capacity() const { return _capacity; }

			// Returns whether the vector is empty
			bool		empty() const { return _size == 0; }

			/*
			** Reverve at least n unitialized elements in vector
			** if n > current capacity: rallocation storage to size n or more
			** no effect on vector size
			** trow an exception if > max_size
			** @param n Minimum capacity for the vector
			*/
			void reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				pointer tmp = _alloc.allocate(n);
				int i = 0;
				for (iterator it = begin(); it != end(); it++){
					_alloc.construct(&tmp[i++], *it);
					_alloc.destroy(&(*it));
				}
				_alloc.deallocate(_vector, _capacity);
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
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
			{
				clear();
				while (first != last)
					push_back(*first++);
			}

			/*
			** New container with n element initialized to a copy of val
			**
			** @param n: new size of container
			** @param val: value to fill the container with
			*/
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
				_alloc.construct(&_vector[_size], x);
				_size++;
			}

			// Removes the last element in the vector + reduce container size
			void	pop_back() 
			{
				_alloc.destroy(&_vector[_size - 1]);
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
			iterator	insert(const_iterator pos, const value_type& x) 
			{
				difference_type posIdx = iterator(pos) - begin();			// save the index position in case reserve is called
				
				if (_size + 1 > _capacity)
					reserve(_size * 2);
				iterator it(begin() + posIdx);			
				value_type tmp = *it;										// save previous value of pos
				*it++ = x;													// insert the value 
				for ( ; it != end(); it++)									// loop for swap the rest of the vector
					ft::mySwap(tmp, *it);
				*it = tmp;													// last element of vector
				_size++;
				return begin() + posIdx;
			}

			void	insert(iterator pos, size_type n, const value_type& x)
			{
				difference_type posIdx = iterator(pos) - begin();
				for (size_type i = 0; i < n; i++){
					iterator it(begin() + posIdx++);
					insert(it, x);
				}
			}

			template <class InputIter>
			iterator	insert(const_iterator pos, InputIter first, InputIter last, typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter >::type* = 0)
			{
				int diff = -1;
				iterator retInsert(pos - 1);
				while (first != last){
					retInsert = insert(retInsert + 1, *first++);
					diff++;
				}
				return retInsert - diff;
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
				bool add = (first == last) ? 1 : 0; // booleen for erase with 1 element
				size_type era = last - first + 1; // number of element to be destroyed
				if (_size == era){
					clear();
					return NULL;
				}
				pointer tmp;
				size_t ret = iterator(last) - begin();
				tmp = _alloc.allocate(_capacity - era);
				size_type j = 0;
				for (size_type i = 0; i < _size; i++){
					if (i < (size_type)(iterator(first) - begin()) || i >= (size_type)(iterator(last) - begin()) + add)
						_alloc.construct(&tmp[j++], _vector[i]);
					_alloc.destroy(&_vector[i]);
				}
				_alloc.deallocate(_vector, _capacity);
				_size -= era - 1 + add;
				_capacity -= era;
				_vector = tmp;
				return iterator(begin() + ret);
			}

			// Removed all element from the vector. new size container = 0
			void	clear()
			{
				while (_size)
					pop_back();
			}

			// exchange the content of the vector with the content of sVec
			void	swap(vector &sVec)
			{				
				ft::mySwap(_vector, sVec._vector);
				ft::mySwap(_size, sVec._size);
				ft::mySwap(_capacity, sVec._capacity);
				ft::mySwap(_alloc, sVec._alloc);
			}


			void resizeIfNeeded()
			{
				if (_size >= _capacity){
					pointer newVec = _alloc.allocate((!_size) ? 1 : _size * 2);
					for (unsigned int i = 0; i < _size; i++){
						_alloc.construct(&newVec[i], _vector[i]);
						_alloc.destroy(&_vector[i]);
					}
					_alloc.deallocate(_vector, _capacity);
					_vector = newVec;
					_capacity = _size * 2;
				}
			}
			
		public:
			//================================= Non Members function ========================================
			friend bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs )
			{
				if (lhs._size != rhs._size)
					return false;
				for (size_t i = 0; i < lhs._size; i++){
					if (lhs[i] != rhs[i])
						return false;
				}
				return true;
			}
			friend bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs ) { return !(operator==(lhs, rhs)); }
			friend bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs ) { return ft::lexicographical_compare<typename ft::vector<T, Alloc>::iterator, typename ft::vector<T, Alloc>::iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
			friend bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs ) { if (lhs == rhs || lhs < rhs) return true; return false; }
			friend bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { if (!operator==(lhs, rhs) && !operator<(lhs, rhs)) return true; return false; }
			friend bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) { if (lhs == rhs || lhs > rhs) return true; return false;}
			friend void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
	};

}
#endif