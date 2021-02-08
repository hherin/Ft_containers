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

namespace ft
{
	template < class Key,												// map::key_type
			class T,													// map::mapped_type
			class Compare = std::less<Key>,								// map::key_compare
			class Alloc = std::allocator<std::pair<const Key,T> >		// map::allocator_type
			> 
	class map
	{
		typedef typename Key									key_type;
		typedef typename T										mapped_type;
		typedef typename ft::pair<const key_type, mapped_type>	value_type;
		typedef typename Compare								value_compare;
		// ADD typedef



		/*
		** =========================== Member functions ==========================
		*/
		// empty constr
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		// range (2)	
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		// copy (3)	
		map (const map& x);
		~map();
		map& operator= (const map& x);

		/*
		** ================================== Iterators ==============================
		*/
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/*
		** ================================== Capacity =================================
		*/ 
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		/*
		** ================================== Element Access ============================
		*/
		mapped_type& operator[] (const key_type& k);

		/*
		** ================================== Modifiers ==================================
		*/
		// single element (1)	
		pair<iterator,bool> insert (const value_type& val);
		// with hint (2)	
		iterator insert (iterator position, const value_type& val);
		// range (3)	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);

		void erase (iterator position);
		size_type erase (const key_type& k);
    	void erase (iterator first, iterator last);

		void swap (map& x);
		void clear();

		/*
		** ======================================== Observers ==============================
		*/

		key_compare key_comp() const;
		value_compare value_comp() const;

		/*
		** ===================================== Operations =================================
		*/
		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;
		size_type count (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

	};
}

#endif