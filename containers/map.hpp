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
// # include "../utils/ABR/AVLtree.hpp"
# include "../utils/ABR/utilsTree.hpp"

template <class T, class M>
struct s_abr
{
	ft::pair<T, M> p;
	
	s_abr *parent;
	s_abr *neutral;
	s_abr *left;
	s_abr *right;
};

namespace ft
{
	template < class Key,												// map::key_type
			class T,													// map::mapped_type
			class Compare = ft::less<Key>,								// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >			// map::allocator_type
			> 
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef s_abr<const Key, T>									Node;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef const Node*										const_pointer;
			typedef typename ft::map_bidirect_iter<true, Node, value_type>	iterator;
			typedef typename ft::map_bidirect_iter<false, Node, value_type>	const_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, true, Node>	reverse_iterator;
			// typedef typename ft::map_reverse_bidirect_iter<T, false, Node>	const_reverse_iterator;

		private :
			Node *_root;
			Node *neutral;
			size_type _size;
			key_compare _comp;
			allocator_type _alloc;
			std::allocator<Node> _nodAlloc;
		
		public:
		/*
		** =========================== Member functions ==========================
		*/
		// empty constr
		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _root(0), _size(0), _comp(comp), _alloc(alloc)
		{
			neutral = new Node;
			neutral->left = neutral;
			neutral->right = neutral;
		}

		// range (2)	
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0) :
			_size(0), _comp(comp), _alloc(alloc)
		{
			neutral = new Node;
			neutral->left = neutral;
			neutral->right = neutral;
			while (first != last){
				insert(*first);
				first++;
			}
		}
		// copy (3)	
		map (const map& x)
		: _size(0), _comp(x._comp), _alloc(x._alloc)
		{
			neutral = new Node;
			neutral->left = neutral;
			neutral->right = neutral;
		}

		~map()
		{

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
		iterator begin() {return iterator(neutral->left, neutral); }
		const_iterator begin() const {return iterator(neutral->left, neutral); }
		iterator end() { return iterator(neutral, neutral); }
		const_iterator end() const { return iterator(neutral, neutral); }
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
			return ft::pair<iterator, bool>(insert(iterator(_root), val), isKeyInBinTree(val.first, _root) ? 0 : 1);
		}

		// with hint (2)	
		iterator insert (iterator position, const value_type& val)
		{
			Node *pos = position.getCurrent();
			Node *ret = (pos != neutral) ? insertNewNode(&pos, val) : insertNewNode(&_root, val);
			if (ret){
				ret->neutral = neutral;
				_size++;
				if (_size == 1){
					neutral->left = ret; neutral->right = ret;
				}
				else if (neutral->left && ret->p.first < neutral->left->p.first)
					neutral->left = ret;
				else if (neutral->right && ret->p.second > neutral->right->p.second)
					neutral->right = ret;
			}
			return ret ? iterator(ret) : iterator(isKeyInBinTree(val.first, pos));
		}

		// range (3)	
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator >::type* = 0)
		{
			while (first != last){
				insert(*first);
				first++;
			}
		}

		void erase (iterator position)
		{
			deleteNode(position.getCurrent(), (*position).first);
		}

		size_type erase (const key_type& k)
		{
			return reinterpret_cast<size_type>(deleteNode(&_root, k));
		}

    	void erase (iterator first, iterator last)
		{
			while (first != last){
				deleteNode(&_root, (*first).first);
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
		Node *createNewTree(Node *ls, Node *rs, Node *parent, value_type const &content)
		{
			Node *newNode = _nodAlloc.allocate(1); //new Node;
			if (!newNode){
				std::cout << "Malloc failed\n";
				return NULL;
			}

			_alloc.construct(&newNode->p, content);
			newNode->parent = parent;
			newNode->left = ls;
			newNode->right = rs;
			return newNode;
		}

		/*
		** Recursive insert function that returns the new created node
		*/
		Node *recInsertNode(Node **bst, Node *parent, value_type const &content)
		{
			if (isKeyInBinTree(content.first, *bst))						// IS the key already present
				return NULL;
			else if (!*bst){
				if (!(*bst = createNewTree(NULL, NULL, parent, content)))	// case empty tree
					return *bst;
			}
			else{										// check which side the leave should be added
				parent = *bst;
				if (content.first > (*bst)->p.first)
					return recInsertNode(&(*bst)->right, parent, content);
				else if (content.first < (*bst)->p.first)
					return recInsertNode(&(*bst)->left, parent, content);
			}
			return *bst;
		}
		
		// returns 1 if element has been inserted are 0 if already in tree
		Node *insertNewNode(Node **bst, value_type const &content)
		{
			Node *newNode = NULL;
			newNode = (*bst) ? recInsertNode(bst, newNode, content) : recInsertNode(&_root, newNode, content);
			return newNode;
		}


		Node *isKeyInBinTree(key_type const &key, Node *bst)
		{	
			if (!bst)
				return NULL;
			else
			{
				if (key == bst->p.first)
					return bst;
				else
				{
					if (key < bst->p.first)
						return isKeyInBinTree(key, bst->left);
					else
						return isKeyInBinTree(key, bst->right);
				}
			}
		}

		Node	*recDeleteNode(Node **bst, Node **root, key_type const& key)
		{
			if (!*bst)
				return *bst;
			if ((*bst)->p.first > key){										// the deletenode is in left side
				(*bst)->left = recDeleteNode(&((*bst)->left), root, key);
				((*bst)->left) ?  (*bst)->left->parent = *bst : 0;
			}
			else if ((*bst)->p.first < key)	{									// ... right side
				(*bst)->right = recDeleteNode(&((*bst)->right), root, key);
				((*bst)->right) ? (*bst)->right->parent = *bst : 0;
			}
			else if (key == (*root)->p.first){
				Node *tmp2 = ((*root)->right) ? ::Min<key_type, T>((*root)->right) : Max<key_type, T>((*root)->left);
				(*bst)->p.first = tmp2->p.first;
				(*bst)->right = recDeleteNode(&((*bst)->right), root, tmp2->p.first);
				return *bst;
			}
			else {
				Node *tmp = NULL;
				if (!(*bst)->left && !(*bst)->right)
					;
				else if ((*bst)->right && !(*bst)->left)
					tmp = (*bst)->right;
				else if ((*bst)->left && !(*bst)->right)
					tmp = (*bst)->left;
				else{
					Node *tmp2 = ::Min<key_type, T>((*bst)->right);
					(*bst)->p.first = tmp2->p.first;
					(*bst)->right = recDeleteNode(&((*bst)->right), root, tmp2->p.first);
					return *bst;
				}
				delete *bst;
				*bst = NULL;
				return tmp;
			}
			return *bst;
		}

		int	deleteNode(Node **node, key_type const &content)
		{
			bool ret = isKeyInBinTree(content, _root);
			recDeleteNode(node, &_root, content);
			return ret;
		}
	};
}

#endif