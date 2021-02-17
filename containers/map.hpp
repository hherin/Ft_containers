/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:05:46 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 12:05:04 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include "../utils/algo.hpp"
# include "../utils/iterator/mapIterators.hpp"
# include "../utils/allocator.hpp"

namespace ft
{
	template < class Key,												// map::key_type
			class T,													// map::mapped_type
			class Compare = ft::less<Key>,								// map::key_compare
			class Alloc = ft::myAlloc<ft::pair<const Key,T> >			// map::allocator_type
			> 
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;

			struct Node
			{
				value_type content;

				Node *next;
				Node *prev;
			};

			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::map_bidirect_iter<T, true, Node, key_type, mapped_type>	iterator;
			typedef typename ft::map_bidirect_iter<T, false, Node, key_type, mapped_type>	const_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, true, Node>	reverse_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, false, Node>	const_reverse_iterator;

		private :
			Node *_root;
			size_type _size;
			key_compare _comp;
			allocator_type _alloc;
			ft::myAlloc<Node> _nodAlloc;
		
		public:
		/*
		** =========================== Member functions ==========================
		*/
		// empty constr
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _root(0), _size(0), _comp(comp), _alloc(alloc)
		{
			createRoot();
		}

		// range (2)	
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0) :
			_size(0), _comp(comp), _alloc(alloc)
		{
			createRoot();
			for ( ; first != last; first++)
				insert(*first);
		}
		// copy (3)	
		map (const map& x)
		: _size(0), _comp(x._comp), _alloc(x._alloc)
		{
			createRoot();
			for (iterator xit = x.begin(); xit != x.end(); xit++)
				insert(*xit);
			
		}

		~map()
		{
			while (_size){
				Node *destr = _root->prev;				// save elem to be destroyed
				_root->prev = destr->prev;				// end of the list changed
				destr->prev->next = _root;		// new last elem point to _root
				_alloc.destroy(&destr->content);
				_nodAlloc.deallocate(destr, 1);
				_size--;
			}
			// _nodAlloc.deallocate(_root, 1);
		}

		map& operator= (const map& x)
		{
			map tmp(x);
			swap(tmp);
			return *this;
		}

		// /*
		// ** ================================== Iterators ==============================
		// */
		iterator begin() {return iterator(_root->next); }
		const_iterator begin() const {return iterator(_root->next); }
		iterator end() { return iterator(_root); }
		const_iterator end() const { return iterator(_root); }
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

		// /*
		// ** ================================== Capacity =================================
		// */ 
		bool empty() const { return !_size; }
		size_type size() const { return _size; }
		// size_type max_size() const;

		// /*
		// ** ================================== Element Access ============================
		// */
		// mapped_type& operator[] (const key_type& k);

		// /*
		// ** ================================== Modifiers ==================================
		// */
		// single element (1)	
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			iterator it = begin();
			while (it != end()){
				if ((*it).first == val.first)
					return ft::pair<iterator,bool>(it, false);
				if (_comp(val.first, (*it).first)){
					addLink(it, val);
					return ft::pair<iterator, bool>(it++, true);
				}
				it++;
			}
			if (it == end()){
				addLink(it, val);
				it++;
			}
			return ft::pair<iterator, bool>(it, true);
		}

		// with hint (2)	
		iterator insert (iterator position, const value_type& val)
		{
			while (position != end()){
				if ((*position).first == val.first)
					return position;
				if (_comp(val.first, (*position).first)){
					addLink(position, val);
					return position++;
				}
				position++;
			}
			if (position == end()){
				addLink(end(), val);
				position++;
			}
			return position;
		}
		// // range (3)	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			while (first != last){
				insert(begin(), *first);
				first++;
			}
		}

		void erase (iterator position)
		{
			Node *pos = position.getCurrent();
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			_alloc.destroy(&pos->content);
			_nodAlloc.deallocate(pos, 1);
			_size--;
		}

		size_type erase (const key_type& k)
		{
			size_type size = 0;
			iterator beg(_root->next);

			while (beg != end()){
				if ((*beg).first == k){
					erase(beg);
					size++;
				}
				beg++;
			}
			return size;
		}

    	void erase (iterator first, iterator last)
		{

			while (first != last){
				iterator next(first.getCurrent()->next);
				erase(first);
				first = next;
			}
		}

		void swap (map& x)
		{
			ft::mySwap(_size, x._size);
			ft::mySwap(_root, x._root);
			ft::mySwap(_comp, x._comp);
			ft::mySwap(_alloc, x._alloc);
			ft::mySwap(_nodAlloc, x._nodAlloc);
		}

		void clear() { erase(begin(), end()); }

		// /*
		// ** ======================================== Observers ==============================
		// */

		key_compare key_comp() const { return _comp; }
		// value_compare value_comp() const;

		// /*
		// ** ===================================== Operations =================================
		// */
		// iterator find (const key_type& k);
		// const_iterator find (const key_type& k) const;
		// size_type count (const key_type& k) const;
		// iterator lower_bound (const key_type& k);
		// const_iterator lower_bound (const key_type& k) const;
		// iterator upper_bound (const key_type& k);
		// const_iterator upper_bound (const key_type& k) const;
		// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		// pair<iterator,iterator>             equal_range (const key_type& k);
		
		private:
			void createRoot()
			{
				_root = _nodAlloc.allocate(1);
				_alloc.construct(&_root->content, value_type());
				_root->next = _root;
				_root->prev = _root;
			}

			// create new link before pos with a copy of val
			void addLink(iterator pos, const value_type &val)
			{
				Node *Cpos = pos.getCurrent();	// get pointer of pos
				Node *nod =  _nodAlloc.allocate(1);
				// insert nod in the list
				nod->next = Cpos;
				nod->prev = Cpos->prev;

				// change list pointer to close the list
				Cpos->prev->next = nod;
				Cpos->prev = nod;
				

				_alloc.construct(&nod->content, val);
				_size++;
			}
	};
}

#endif