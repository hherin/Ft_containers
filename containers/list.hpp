/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:55:49 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/22 14:35:45 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "../utils/iterator/bidirect_iter.hpp"
# include "../utils/iterator/reverse_bidirect_iter.hpp"
# include "../utils/algo.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef T					value_type;
			typedef Alloc				allocator_type;
			typedef T&					reference;
			typedef const T&			const_reference;
			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef T*					pointer;
			typedef const T*			const_pointer;

		private :
			struct Node
			{
				T data;
				Node *next;
				Node *prev;
			};
			Node			*_endList;
			size_type		_size;
			allocator_type	_alloc;

		public:
			typedef typename ft::list_bidirect_iter<T, true, Node>			iterator;
			typedef typename ft::list_bidirect_iter<T, false, Node>			const_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, true, Node>	reverse_iterator;
			typedef typename ft::list_reverse_bidirect_iter<T, false, Node>	const_reverse_iterator;

			// =================== Member Functions ===================
			// Default constructor
			explicit list (const allocator_type& alloc = allocator_type())
				: _endList(nullptr), _size(0), _alloc(alloc) { createNewList(); }

			// Fill constructor
			// remind : value_type() appelle le constructeur par defaut de T
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				: _endList(nullptr), _size(0), _alloc(alloc)
			{
				createNewList();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// Range constructor
			template <class InputIterator>
			list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename std::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
			{
				_alloc = alloc;
				createNewList();
				_size = 0;
				while (first != last)
					push_back(*first++);
			}

			// Copy constructor
			list (const list& x) 
			{
				createNewList();
				*this = x;
			}

			~list() { clear(); }

			list& operator= (const list& x)
			{
				if (this == &x)
					return *this;
				clear();
				for (iterator it(x.begin()); it != iterator(x.end()); it++)
					push_back(*it);
				return *this;
			}

			// ====================== Iterators =======================

			// begin() Returns an iterator pointing to the first element in the list container.
			// end() Returns an iterator pointing to the last element in the list container.
			iterator begin() { return (!_size ? iterator(_endList) : iterator(_endList->next));}
			iterator end() { return iterator(_endList); }
			const_iterator begin() const { return (!_size ? iterator(_endList) : iterator(_endList->next));}
			const_iterator end() const { return iterator(_endList);}
			
			// rbegin() Returns a reverse iterator pointing to the last element in the container
			// rend() Returns a reverse iterator pointing to the theoretical element preceding the first element in the list container 
			reverse_iterator rbegin() { return reverse_iterator(_endList->prev); }
			const_reverse_iterator rbegin() const { return reverse_iterator(_endList->prev); }
			reverse_iterator rend() { return reverse_iterator(_endList); }
			const_reverse_iterator rend() const { return reverse_iterator(_endList); }

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
			reference front() { return _endList->next->data; }
			reference back() { return _endList->prev->data; }
			const_reference front() const { return _endList->next->data; }
			const_reference back() const { return _endList->prev->data; }

			// ======================= Modifiers ======================

			/*
			** Assigns new contents to the list container, replacing its current contents, and modifying its size accordingly.
			**
			** @param first, last Input iterators to the initial and final positions in a sequence. last exclueded.
			** @param n New size of the container
			** @param val Value to fill the container with
			*/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename std::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
			{
				clear();
				createNewList();
				while (first != last)
					push_back(*first++);
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				createNewList();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// Inserts a new element at the beginning of the list with the copy of val
			void push_front (const value_type& val)
			{
				Node *node = new Node;
				node->data = val;
				if (!_size){
					node->next = _endList;
					_endList->prev = node;
				}
				else{
					node->next = _endList->next;
					_endList->next->prev = node;
				}
				node->prev = _endList;
				_endList->next = node;
				_size++;
			}

			// nserts a new element at the end of the list with the copy of val
			void push_back (const value_type& val)
			{
				Node *node = new Node;
				node->data = val;
				if (!_size){
					node->prev = _endList;
					_endList->next = node;
				}
				else{
					node->prev = _endList->prev;
					_endList->prev->next = node;
				}
				node->next = _endList;
				_endList->prev = node;
				_size++;
			}

			// Removes the first element in the list container, effectively reducing its size by one.
			void pop_front()
			{
				Node *destr = _endList->next;		// save elem to be destroyed
				_endList->next = destr->next;		// _endlist point to second elem => becomes first of the list
				destr->next->prev = _endList;		// first elem point to _endList
				_alloc.destroy(&destr->data);
				delete destr;
				_size--;
			}

			// Removes the last element in the list container, effectively reducing the container size by one.
			void pop_back()
			{
				Node *destr = _endList->prev;		// save elem to be destroyed
				_endList->prev = destr->prev;		// end of the list changed
				destr->prev->next = _endList;		// new last elem point to _endList
				_alloc.destroy(&destr->data);
				delete destr;
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
				iterator *Cpos = pos;
				insert(pos, 1, val);
				return Cpos++;
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
			void insert (iterator pos, InputIterator first, InputIterator last, typename std::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
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
				_alloc.destroy(&pos->data);
				delete pos.getCurrent();
				_size--;
				return ret;
			}

			iterator erase (iterator first, iterator last)
			{
				iterator ret;
				while (first != last)
					ret = erase(first++);
				return ret;
			}

			// Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
			void swap (list& x)
			{
				ft::mySwap(_size, x._size);
				ft::mySwap(_endList, x._endList);
			}

			/*
			** Resizes the container so that it contains n elements.
			** reduce or expand the size of the list
			*/
			void resize (size_type n, value_type val = value_type())
			{
				while (n > _size)
					pop_back();
				while (n < _size)
					push_back(val);
			}

			// Removes all elements from the list container, and leaving the container with a size of 0.
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					pop_back();
				_size = 0;
			}

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
						_alloc.destroy(&it->data);
						delete it.getCurrent();
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
						_alloc.destroy(&it->data);
						delete it.getCurrent();
					}
					it = next;
				}
			}

			// Removes all but the first element from every consecutive group of equal elements in the container.
			void unique()
			{
				for (iterator it(begin()); it != end(); it++){
					iterator next = it->next;
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
				for (iterator it(begin()); it != end(); it++){
					iterator next = it;
					next++;
					if (binary_pred(*next,*it))
						erase(next);
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
				iterator ourIter(begin());
				iterator mergeIter(x.begin());  //iterator on x list
				
				while (1){
					iterator ourNext(ourIter->next);
					iterator mergeNext(mergeIter->next);
					
					if (x.empty())
						break;
					if (ourIter == end()){
						splice(end(), x, mergeIter, x.end());
						break;
					}
					if (*ourIter >= *mergeIter){
						transfertLink(ourIter, mergeIter);
						_size++;
						x._size--;
						mergeIter = mergeNext;
					}
					else
						ourIter = ourNext;
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
				iterator ourIter(begin());
				iterator mergeIter(x.begin());  //iterator on x list
				
				while (1){
					iterator ourNext(ourIter->next);
					iterator mergeNext(mergeIter->next);
					
					if (x.empty())
						break;
					if (ourIter == end()){
						splice(end(), x, mergeIter, x.end());
						break;
					}
					if (comp(*mergeIter, *ourIter)){
						transfertLink(ourIter, mergeIter);
						_size++;
						x._size--;
						mergeIter = mergeNext;
					}
					else
						ourIter = ourNext;
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
				tmp = _endList->next;
				_endList->next = _endList->prev;
				_endList->prev = tmp;
			}

		protected:
			// create the neutral elem for the linked list
			void createNewList()
			{
				_endList = new Node;
				_endList->data = value_type();
				_endList->next = _endList;
				_endList->prev = _endList;
			}

			// create new link before pos with a copy of val
			void addLink(iterator pos, const value_type &val)
			{
				Node *Cpos = pos.getCurrent();	// get pointer of pos
				Node *nod = new Node();
				// insert nod in the list
				nod->next = Cpos;
				nod->prev = pos->prev;

				// change list pointer to close the list
				pos->prev->next = nod;
				pos->prev = nod;

				nod->data = val;
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
			friend bool operator<(const list& lhs, const list& rhs)
			{
				if (lhs._size > rhs._size)
					return false;
				iterator right(rhs.begin());
				for (iterator left(lhs.begin()); left != iterator(lhs.end()); left++)
					if (*right++ < *left)
						return false;
				return true;
			}
			friend bool operator!= (const list& lhs, const list& rhs) { return !(operator==(lhs, rhs)); }
			friend bool operator<= (const list& lhs, const list& rhs) { return operator==(lhs, rhs) || operator<(lhs, rhs); }
			friend bool operator>  (const list& lhs, const list& rhs) { return !operator<=(lhs, rhs); }
			friend bool operator>= (const list& lhs, const list& rhs) { return operator==(lhs, rhs) || operator>(lhs, rhs); }
	};
}

#endif