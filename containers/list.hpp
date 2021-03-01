/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:55:49 by heleneherin       #+#    #+#             */
/*   Updated: 2021/03/01 21:47:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "../utils/iterator/bidirect_iter.hpp"
# include "../utils/iterator/reverse_bidirect_iter.hpp"
# include "../utils/stl.hpp"
# include "../utils/allocator.hpp"

namespace ft
{
	template <class T, class Alloc = ft::myAlloc<T> >
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

		private :
			struct Node
			{
				T data;
				Node *next;
				Node *prev;
			};
			Node				*_head;
			size_type			_size;
			allocator_type		_alloc;
			ft::myAlloc<Node>	_nodeAlloc;

		public:
			typedef typename ft::list_bidirect_iter<T, true, Node>			iterator;
			typedef typename ft::list_bidirect_iter<T, false, Node>			const_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, true, Node>	reverse_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, false, Node>	const_reverse_iterator;

			// =================== Member Functions ===================
			// Default constructor
			explicit list (const allocator_type& alloc = allocator_type())
				: _size(0), _alloc(alloc) { _head = createNewNode(); }

			// Fill constructor
			// remind : value_type() appelle le constructeur par defaut de T
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _size(0), _alloc(alloc)
			{
				_head = createNewNode();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// Range constructor
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
				: _size(0), _alloc(alloc)
			{
				_head = createNewNode();
				while (first != last)
					push_back(*first++);
			}

			// Copy constructor
			list (const list& x)
				: _size(0), _alloc(x._alloc)
			{
				_head = createNewNode();
				for (iterator it(x.begin()); it != iterator(x.end()); it++)
					push_back(*it);
			}

			~list() 
			{ 
				while (_size)
					pop_back();
				_alloc.destroy(&_head->data);
				_nodeAlloc.deallocate(_head, 1);
			}

			list& operator= (const list& x)
			{
				list tmp(x);
				swap(tmp);
				return *this;
			}

			// ====================== Iterators =======================

			// begin() Returns an iterator pointing to the first element in the list container.
			// end() Returns an iterator pointing to the last element in the list container.
			iterator begin() { return (!_size ? iterator(_head) : iterator(_head->next));}
			iterator end() { return iterator(_head); }
			const_iterator begin() const { return (!_size ? iterator(_head) : iterator(_head->next));}
			const_iterator end() const { return iterator(_head);}
			
			// rbegin() Returns a reverse iterator pointing to the last element in the container
			// rend() Returns a reverse iterator pointing to the theoretical element preceding the first element in the list container 
			reverse_iterator rbegin() { return reverse_iterator(_head->prev); }
			const_reverse_iterator rbegin() const { return reverse_iterator(_head->prev); }
			reverse_iterator rend() { return reverse_iterator(_head); }
			const_reverse_iterator rend() const { return reverse_iterator(_head); }

			// ======================= Capacity =======================

			// Returns whether the list container is empty
			bool empty() const { return (_size == 0); }

			// Returns the size of the list container
			size_type size() const { return _size; }

			// Returns the maximum number of elements that the list container can hold
			size_type max_size() const;

			// ===================== Element access ===================
			// front() Returns a reference to the first data element in the list container.
			// back() Returns a reference to the last data element in the list container.
			reference front() { return _head->next->data; }
			reference back() { return _head->prev->data; }
			const_reference front() const { return _head->next->data; }
			const_reference back() const { return _head->prev->data; }

			// ======================= Modifiers ======================

			/*
			** Assigns new contents to the list container, replacing its current contents, and modifying its size accordingly.
			**
			** @param first, last Input iterators to the initial and final positions in a sequence. last exclueded.
			** @param n New size of the container
			** @param val Value to fill the container with
			*/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
			{
				clear();
				while (first != last)
					push_back(*first++);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// Inserts a new element at the beginning of the list with the copy of val
			void push_front (const value_type& val)
			{
				Node *node = createNewNode(val);

				node->next = _head->next;
				node->prev = _head;
				
				_head->next->prev = node;
				_head->next = node;
				_size++;
			}

			// nserts a new element at the end of the list with the copy of val
			void push_back (const value_type& val)
			{
				Node *node = createNewNode(val);

				node->next = _head;
				node->prev = _head->prev;

				_head->prev->next = node;
				_head->prev = node;
				_size++;
			}

			// Removes the first element in the list container, effectively reducing its size by one.
			void pop_front()
			{
				if (!_size)
					return ;
				Node *destr = _head->next;				// save elem to be destroyed
				_head->next = destr->next;				// _head point to second elem => becomes first of the list
				destr->next->prev = _head;		// first elem point to _head
				_alloc.destroy(&destr->data);
				_nodeAlloc.deallocate(destr, 1);

				_size--;
			}

			// Removes the last element in the list container, effectively reducing the container size by one.
			void pop_back()
			{
				if (!_size)
					return ;
				Node *destr = _head->prev;				// save elem to be destroyed
				_head->prev = destr->prev;				// end of the list changed
				destr->prev->next = _head;		// new last elem point to _head
				_alloc.destroy(&destr->data);
				_nodeAlloc.deallocate(destr, 1);

				_size--;
			}

			/*
			** Insert new elements before the element at the specified position
			**
			** @param pos Position in the container where the new elements are inserted
			** @param n Number of elements to insert (initialize with a copy of val)
			** @param val Value to be copied (or moved)
			** @param first,last Iterators specifying a range of elements, last excluded
			*/
			// single element (1)
			iterator insert (iterator pos, const value_type& val)
			{
				insert(pos, 1, val);
				return iterator(pos->prev);
			}

			// fill (2)
			void insert (iterator pos, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++){
					addLink(pos, val);
					pos = pos->prev;
				}
			}

			// range (3)
			template <class InputIterator>
			void insert (iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
			{
				while (first != last)
					addLink(pos, *first++);
			}

			/*
			** Removes from the vector either a single element (position) or a range of elements ([first,last))
			** Return : An iterator pointing to the new location of the element that followed the last element
			** 			erased by the function call
			*/
			iterator erase (iterator pos)
			{
				iterator ret;
				pos->prev->next = pos->next;
				pos->next->prev = pos->prev;
				ret = iterator(pos->next);

				Node *destr = pos.getCurrent();
				_alloc.destroy(&destr->data);
				_nodeAlloc.deallocate(destr, 1);
				_size--;
				return ret;
			}

			iterator erase (iterator first, iterator last)
			{
				iterator ret(first);
				while (first != last)
					ret = erase(first++);
				return ret;
			}

			// Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
			void swap (list& x)
			{
				ft::mySwap(_size, x._size);
				ft::mySwap(_head, x._head);
			}

			/*
			** Resizes the container so that it contains n elements.
			** reduce or expand the size of the list
			*/
			void resize (size_type n, value_type val = value_type())
			{
				while (n > _size)
					push_back(val);
				while (n < _size)
					pop_back();
			}

			// Removes all elements from the list container, and leaving the container with a size of 0.
			void clear() { erase(begin(), end()); }

			// ======================= Operations =====================
			/*
			** Transfers elements from x into the container, inserting them at position.
			** The first version (1) transfers all the elements of x into the container.
			** The second version (2) transfers only the element pointed by i from x into the container.
			** The third version (3) transfers the range [first,last) from x into the container.
			*/
			// entire list (1)
			void splice (iterator pos, list& x)
			{
				for (iterator it = x.begin(); it != x.end();){
					iterator next = it->next;
					splice(pos, x, it);
					it = next;
				}
			}

			// single element (2)
			void splice (iterator pos, list& x, iterator i)
			{
				transfertLink(pos, i);
				_size++;
				x._size--;
			}
			
			// element range (3)
			void splice (iterator pos, list& x, iterator first, iterator last)
			{
				while (first != last){
					iterator next = first->next;
					splice(pos, x, first);
					first = next;
				}
			}

			
			/*
			** Removes from the container all the elements that compare equal to val. 
			** This calls the destructor of these objects and reduces the container size by the number of elements removed.
			*/
			void remove (const value_type& val)
			{
				for (iterator it = begin(); it != end(); ){
					iterator next = it->next;
					if (*it == val){
						it->prev->next = it->next;
						it->next->prev = it->prev;
						Node *destr = it.getCurrent();
						_alloc.destroy(&destr->data);
						_nodeAlloc.deallocate(destr, 1);
						_size--;
					}
					it = next;
				}
			}
			
			/*
			** Removes from the container all the elements for which Predicate pred returns true. 
			** This calls the destructor of these objects and reduces the container size by the number of elements removed.
			** The function calls pred(*i) for each element (where i is an iterator to that element). 
			** Any of the elements in the list for which this returns true, are removed from the container.
			*/
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				for (iterator it = begin(); it != end(); ){
					iterator next = it->next;
					if (pred(*it)){
						it->prev->next = it->next;
						it->next->prev = it->prev;
						Node *destr = it.getCurrent();
						_alloc.destroy(&destr->data);
						_nodeAlloc.deallocate(destr, 1);
						_size--;
					}
					it = next;
				}
			}

			// Removes all but the first element from every consecutive group of equal elements in the container.
			void unique()
			{
				for (iterator it(begin()); it->next != end().getCurrent(); ){
					iterator next(it);
					next++;
					if (*it == *next)
						erase(it);
					it = next;
				}
			}
			
			/*
			** Takes as argument a specific comparison function that determine the "uniqueness" of an element. 
			** In fact, any behavior can be implemented (and not only an equality comparison), but notice that the 
			** function will call binary_pred(*i,*(i-1)) for all pairs of elements (where i is an iterator to an element, 
			** starting from the second) and remove i from the list if the predicate returns true.
			**
			** @param binary_pred Predicate that, taking two values of the same type than those contained in the list, 
			** returns true to remove the element passed as first argument from the container, and false otherwise.
			** This shall be a function pointer or a function object.
			*/
			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred)
			{
				for (iterator it(begin()->next); it != end(); ){
					iterator next(it);
					next++;
					if (binary_pred(it->prev->data , *it))
						erase(it);
					it = next;
				}
			}

			/*
			** Merges x into the list by transferring all of its elements at their respective ordered positions into the container 
			** (both containers shall already be ordered). his effectively removes all the elements in x (which becomes empty), 
			** and inserts them into their ordered position within container
			*/
			void merge (list& x)
			{
				if (this == &x)
					return ;
				iterator ourIter(end());
				
				while (!x.empty()){
					iterator mergeIter = x.begin();
					
					if (ourIter->next == end().getCurrent()){
						splice(end(), x, mergeIter, x.end());
						break;
					}
					if (ourIter->next->data > *mergeIter){
						iterator pos(ourIter->next);
						transfertLink(pos, mergeIter);
						_size++;
						x._size--;
						ourIter++;
					}
					else
						ourIter++;
				}
			}
			
			/* 
			** @param comp Binary predicate that, taking two values of the same type than those contained in the list, 
			** returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
			** This shall be a function pointer or a function object.
			*/ 
			template <class Compare>
			void merge (list& x, Compare comp)
			{
				if (this == &x)
					return ;
				iterator ourIter(end());
				
				while (!x.empty()){
					iterator mergeIter = x.begin();
					
					if (ourIter->next == end().getCurrent()){
						splice(end(), x, mergeIter, x.end());
						break;
					}
					if (comp(*mergeIter, ourIter->next->data)){
						iterator pos(ourIter->next);
						transfertLink(pos, mergeIter);
						_size++;
						x._size--;
						ourIter++;
					}
					else
						ourIter++;
				}
			}
			
			void sort()
			{
				for (size_type i = 0; i < _size; i++){
					
					for (iterator current(begin()->next); current != end(); ){
						iterator next(current->next);
						iterator previous(current->prev);
						if (*current < *previous){
							current->next->prev = previous.getCurrent();
							
							Node* tmp= current->next;
							current->next = previous.getCurrent();
							current->prev = previous->prev;
							
							previous->prev->next = current.getCurrent();
							previous->prev = current.getCurrent();
							previous->next = tmp;
						}
						current = next;
					}
				}
			}
			
			template <class Compare>
			void sort (Compare comp)
			{
				for (size_type i = 0; i < _size; i++){
					
					for (iterator current(begin()->next); current != end(); ){
						iterator next(current->next);
						iterator previous(current->prev);
						if (comp(*current, *previous)){
							current->next->prev = previous.getCurrent();
							
							Node* tmp= current->next;
							current->next = previous.getCurrent();
							current->prev = previous->prev;
							
							previous->prev->next = current.getCurrent();
							previous->prev = current.getCurrent();
							previous->next = tmp;
						}
						current = next;
					}
				}
			}
			
			// Reverses the order of the elements in the list container.
			void reverse()
			{
				Node *tmp;
				iterator rest(begin());
				
				for (size_type i = 0; i < _size; i++){ // changer order inside the list
					iterator next(rest->next);
					tmp = rest->prev;
					rest->prev = rest->next;
					rest->next = tmp;
					rest = next;
				}

				//change order of the neutral side node
				tmp = _head->next;
				_head->next = _head->prev;
				_head->prev = tmp;
			}

		protected:
			// create the neutral elem for the linked list
			Node *createNewNode(value_type val = value_type())
			{
				Node *node = _nodeAlloc.allocate(1);
				_alloc.construct(&node->data, val);
				node->next = node;
				node->prev = node;
				return node;
			}

			// create new link before pos with a copy of val
			void addLink(iterator pos, const value_type &val)
			{
				Node *Cpos = pos.getCurrent();	// get pointer of pos
				Node *nod = createNewNode(val);
				
				// insert nod in the list
				nod->next = Cpos;
				nod->prev = pos->prev;

				// change list pointer to close the list
				pos->prev->next = nod;
				pos->prev = nod;

				// nod->data = val;
				_size++;
			}

				// transfert newLink before pos
			void transfertLink(iterator pos, iterator newLink)
			{
				if (pos == newLink)
					return ;
				// change pointer of newLink old list
				newLink->prev->next = newLink->next;
				newLink->next->prev = newLink->prev;
					
				// change pointer for new position of newLink
				newLink->next = pos.getCurrent();
				newLink->prev = pos->prev;

				// this list point to newLink
				pos->prev->next = newLink.getCurrent();
				pos->prev = newLink.getCurrent();
			}
			

			void printlist()
			{
				for (iterator it = begin(); it != end(); it++)
					std::cout << *it << "| ";
				std::cout << std::endl << std::endl;
			}

		// =====================Non Member method ==========================	
		public:
			friend void swap (list& x, list& y) { x.swap(y); }
			friend bool operator==(const list& lhs, const list& rhs)
			{
				if (lhs._size != rhs._size)
					return false;
				iterator left(lhs.begin());
				iterator right(rhs.begin());
				for (size_type i = 0; i < lhs._size; i++)
					if (*left++ != *right++)
						return false;
				return true;
			}
			friend bool operator<(const list& lhs, const list& rhs){ return ft::lexicographical_compare<typename ft::list<T, Alloc>::iterator, typename ft::list<T, Alloc>::iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
			friend bool operator!= (const list& lhs, const list& rhs) { return !(operator==(lhs, rhs)); }
			friend bool operator<= (const list& lhs, const list& rhs) { return operator==(lhs, rhs) || operator<(lhs, rhs); }
			friend bool operator>  (const list& lhs, const list& rhs) { return !operator<=(lhs, rhs); }
			friend bool operator>= (const list& lhs, const list& rhs) { return operator==(lhs, rhs) || operator>(lhs, rhs); }
	};
}

#endif