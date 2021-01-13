/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:55:49 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/13 17:04:42 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "../utils/bidirect_iter.hpp"
# include "../utils/reverse_bidirect_iter.hpp"

namespace ft
{			
	template <class T, class Alloc = std::allocator<T> >
	class list
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
			typedef typename ft::list_bidirect_iter<T, true, Alloc>		iterator;
			typedef typename ft::list_bidirect_iter<T, false, Alloc>	const_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, true, Alloc>	reverse_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, false, Alloc>	const_reverse_iterator;

			// =================== Member Functions ===================
			// Default constructor
			explicit list (const allocator_type& alloc = allocator_type())
				: _endList(nullptr), _size(0)
			{
				(void)alloc;
				_endList = new Node;
				_endList->next = nullptr;
				_endList->prev = nullptr;
			}

			// Fill constructor
			// remind : value_type() appelle le constructeur par defaut de T
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _endList(nullptr), _size(0)
			{
				(void)alloc;
				_endList = new Node;
				_endList->next = nullptr;
				_endList->prev = nullptr;
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// Range constructor 
			// template <class InputIterator>
			// list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

			// copy (4)
			list (const list& x);

			~list(){}

			list& operator= (const list& x);

			// ====================== Iterators =======================
			iterator begin() { return iterator(_endList->next);}
			iterator end() { return iterator(_endList);}
			const_iterator begin() const;
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			// ======================= Capacity =======================
			bool empty() const;
			size_type size() const { return _size; }
			size_type max_size() const;

			// ===================== Element access ===================
			reference front();
			reference back();
			const_reference front() const;
			const_reference back() const;

			// ======================= Modifiers ======================
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
			// fill (2)
			void assign (size_type n, const value_type& val);
			
			void push_front (const value_type& val)
			{
				Node *node = new Node;
				node->data = val;
				node->prev = _endList;
				node->next = (!_size) ? _endList : _endList->next;
				_endList->next = node;
				_size++;
			}
			
			void push_back (const value_type& val)
			{
				Node *node = new Node;
				node->data = val;
				node->next = _endList;
				node->prev = _endList->prev;
				_endList->prev = node;
				_size++;
			}
			
			void pop_front();
			void pop_back();
			// single element (1)
			iterator insert (iterator position, const value_type& val);
			// fill (2)
			void insert (iterator position, size_type n, const value_type& val);
			// range (3)
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);
			void swap (list& x);
			void resize (size_type n, value_type val = value_type());
			void clear();

			// ======================= Operations =====================
			// entire list (1)
			void splice (iterator position, list& x);
			// single element (2)
			void splice (iterator position, list& x, iterator i);
			// element range (3)
			void splice (iterator position, list& x, iterator first, iterator last);
			void remove (const value_type& val);
			template <class Predicate>
			void remove_if (Predicate pred);
			void unique();
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred);
			void merge (list& x);
			template <class Compare>
			void merge (list& x, Compare comp);
			void sort();
			template <class Compare>
			void sort (Compare comp);
			void reverse();

			private :
			struct Node 
			{
				T data;
				Node *next;
				Node *prev;
			};
				// allocator_type		_myAlloc;
				Node			*_endList;
				size_type		_size;
	};
}

#endif