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
// # include "../utils/ABR/AVLtree.hpp"
# include "../utils/algo.hpp"
# include "../utils/iterator/mapIterators.hpp"

namespace ft
{
	template < class Key,												// map::key_type
			class T,													// map::mapped_type
			class Compare = ft::less<Key>,								// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >		// map::allocator_type
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
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef size_t											size_type;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef typename ft::map_bidirect_iter<T, true, Node, key_type, mapped_type>	iterator;
			typedef typename ft::map_bidirect_iter<T, false, Node, key_type, mapped_type>	const_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, true, Node>	reverse_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, false, Node>	const_reverse_iterator;

		private :
			Node *_root;
			size_type _size;
			key_compare _comp;
			allocator_type _alloc;
		
		public:
		/*
		** =========================== Member functions ==========================
		*/
		// empty constr
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _root(0), _size(0), _comp(comp), _alloc(alloc)
		{}

		// range (2)	
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			createRoot();
			_comp = comp;
			_alloc(alloc);
			InputIterator tmp(first);
			while (first != last){
				iterator beg = begin();
				while (beg != end()){
					if (_comp((*first).first, (*beg).first))
						addLink(beg, *first);
					beg++;
				}
				first++;
			}
		}
		// copy (3)	
		map (const map& x)
		{
			createRoot();
			_comp = x._comp;
			_alloc(x._alloc);
			iterator xit = x.begin();
			while (xit != x.end()){
				iterator it = begin();
				while (it != end()){
					if (_comp((*xit).first, (*it).first))
						addLink(it, *xit);
					it++;
				}
				xit++;
			}
		}

		~map()
		{
			while (_size){
				Node *destr = _root->prev;				// save elem to be destroyed
				_root->prev = destr->prev;				// end of the list changed
				destr->prev->next = _root;		// new last elem point to _root
				delete destr;
				_size--;
			}
			delete _root;
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
					break;
				}
				it++;
			}
					return ft::pair<iterator, bool>(it, true);
		}
		// // with hint (2)	
		iterator insert (iterator position, const value_type& val)
		{
			while (position != end()){
				if ((*position).first == val.first)
					return position;
				if (_comp(val.first, (*position).first)){
					addLink(position, val);
					break;
					// return ft::pair<iterator, bool>(position, true);
				}
				position++;
			}
			return position;
		}
		// // range (3)	
		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);

		// void erase (iterator position);
		// size_type erase (const key_type& k);
    	// void erase (iterator first, iterator last);

		// void swap (map& x);
		// void clear();

		// /*
		// ** ======================================== Observers ==============================
		// */

		// key_compare key_comp() const;
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
				_root = new Node;
				_root->data = value_type();
				_root->next = _root;
				_root->prev = _root;
			}

			// create new link before pos with a copy of val
			void addLink(iterator pos, const value_type &val)
			{
				Node *Cpos = pos.getCurrent();	// get pointer of pos
				Node *nod = new Node();
				// insert nod in the list
				nod->next = Cpos;
				nod->prev = Cpos->prev;

				// change list pointer to close the list
				Cpos->prev->next = nod;
				Cpos->prev = nod;

				nod->content = val;
				_size++;
			}
	};
}

#endif