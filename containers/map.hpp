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

template <class K, class M>
struct node
{
	ft::pair<K, M> data;

	node *neutral;
	node *parent;
	node *left;
	node *right;
};

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
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef node<const key_type, mapped_type>				Node;
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
			ft::myAlloc<Node> _nodAlloc;
		
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
			Node *rootSave = _root;
			(pos != neutral) ? _root = pos : 0;
			Node *ret = (pos != neutral) ? insertNewNode(val) : insertNewNode(val);
			_root = rootSave;
			if (ret){
				ret->neutral = neutral;
				_size++;
				if (_size == 1){
					neutral->left = ret; neutral->right = ret;
				}
				else if (neutral->left && ret->data.first < neutral->left->data.first)
					neutral->left = ret;
				else if (neutral->right && ret->data.second > neutral->right->data.second)
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

		// void printMap()
		// {
		// 	printTree<const Key, T>(_root);
		// }

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

		Node *createNode(value_type const &data, Node *p)
		{
			Node *newNode = _nodAlloc.allocate(1);
			if (!newNode){
				std::cout << "Allocation failed\n";
				return NULL;
			}

			_alloc.construct(&newNode->data, data);
			newNode->parent = p;
			newNode->right = NULL;
			newNode->left = NULL;

			return newNode;
		}

		int getHeightTree(Node const *a)
		{
			if (!a)
				return 0;
			
			int left = 0;
			int right = 0;

			left = getHeightTree(a->left);
			right = getHeightTree(a->right);
			return (left > right) ? left + 1 : right + 1;
		} 

		void	right_right_Rotation(Node *insertNode)
		{
			if (!insertNode)
				return ;
			
			Node *pivot = insertNode->left;

			insertNode->left = pivot->right;
			(pivot->right) ? pivot->right->parent = insertNode : 0;
			
			pivot->right = insertNode;
			pivot->parent = insertNode->parent;

			if (insertNode->parent){
				Node *parent = insertNode->parent;
				
				(parent->left == insertNode) ? parent->left = pivot : parent->right = pivot; 
			}
			insertNode->parent = pivot;
			if (!pivot->parent)
				_root = pivot;
		}

		void	left_left_Rotation(Node *insertNode)
		{
			if (!insertNode || !insertNode->right)
				return ;
			
			Node *pivot = insertNode->right;	

			insertNode->right = pivot->left;
			(pivot->left) ? pivot->left->parent = insertNode : 0;
				
			pivot->left = insertNode;
			pivot->parent = insertNode->parent;
			
			if (insertNode->parent){
				Node *parent = insertNode->parent;
				(parent->left == insertNode) ? parent->left = pivot : parent->right = pivot;
			}
				
			insertNode->parent = pivot;
			if (!pivot->parent)
				_root = pivot;
		}

		void left_right_Rotation(Node *insertNode)
		{
			//left rotation 
			Node *left = insertNode->left;
			insertNode->left = left->right;
			insertNode->left->parent = insertNode;
			insertNode->left->left = left;
			insertNode->left->left->parent = insertNode->left;

			//right rotation
			Node *tmp = insertNode;
			insertNode = insertNode->left;
			insertNode->parent = tmp->parent;
			insertNode->right = tmp;
			tmp->parent = insertNode;
			if (!tmp->parent)
				_root = insertNode;
		}

		void right_left_Rotation(Node *insertNode)
		{
			//right rotation
			Node *right = insertNode->right;
			insertNode->right = right->left;
			insertNode->right->parent = insertNode;
			insertNode->right->right = right;
			insertNode->right->right->parent = insertNode->right;

			//left rotation
			Node *tmp = insertNode;
			insertNode = insertNode->right;
			insertNode->parent = tmp->parent;
			insertNode->left = tmp;
			tmp->parent = insertNode;
			if (!tmp->parent)
				_root = insertNode;
		}

		
		void	BalancedTree(Node *insertNode)
		{
			if (!insertNode)
				return ;
			while (insertNode){
				int bl = getHeightTree(insertNode->left);
				int br = getHeightTree(insertNode->right);
				if (bl - br > 1){
					Node *tmp = insertNode->left;
					if (getHeightTree(tmp->left) - getHeightTree(tmp->right) < -1)
					right_left_Rotation(insertNode);
					else
						right_right_Rotation(insertNode);
				}
				else if (bl - br < -1){
					Node *tmp = insertNode->right;
					if (getHeightTree(tmp->left) - getHeightTree(tmp->right) > 1)
						left_right_Rotation(insertNode);
					else
						left_left_Rotation(insertNode);
				}
				insertNode = insertNode->parent;
			}
		}

		/*
		** Recursive insert function that returns the new created node
		*/

		Node *recInsertNode(Node **bst, Node *parent, value_type const &content)
		{
			if (isKeyInBinTree(content.first, *bst))						// IS the key already present
				return NULL;
			else if (!*bst){
				if (!(*bst = createNode(content, parent)))	// case empty tree
					return *bst;
			}
			else{										// check which side the leave should be added
				parent = *bst;
				if (content.first > (*bst)->data.first)
					return recInsertNode(&(*bst)->right, parent, content);
				else if (content.first < (*bst)->data.first)
					return recInsertNode(&(*bst)->left, parent, content);
			}
			return *bst;
		}

		// returns 1 if element has been inserted are 0 if already in tree
		Node *insertNewNode(value_type const &content)
		{
			Node *newNode = NULL;
			Node *recRoot = _root;
			newNode = recInsertNode(&recRoot, newNode, content);
			BalancedTree(newNode);
			return newNode;
		}

		Node *isKeyInBinTree(key_type const &key, Node *bst)
		{	
			if (!bst)
				return NULL;
			else
			{
				if (key == bst->data.first)
					return bst;
				else
				{
					if (key < bst->data.first)
						return isKeyInBinTree(key, bst->left);
					else
						return isKeyInBinTree(key, bst->right);
				}
			}
		}

		void deleteNode(Node **root, key_type const data)
		{
			if (!*root)
				return;
			Node *del = isKeyInBinTree(data, *root);
			
			if (!del)
				return;
			if (del->right && !del->left){
				Node *right = del->right;
				right->parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = right : del->parent->left = right;
				else
					*root = del->right;
				delete del;
				BalancedTree(right, root);
			}
			else if (del->left && !del->right){
				Node *left = del->left;
				left->parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = left : del->parent->left = left;
				else
					*root = del->left;
				delete del;
				BalancedTree(left, root);
			}
			else if (!del->left && !del->right){
				Node *parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = NULL : del->parent->left = NULL;
				else
					*root = NULL;
				delete del;
				if (parent)
					BalancedTree(parent, root);
			}
			else{
				Node *right = del->right;
				while (right->left)
					right = right->left;
				del->data.first = right->data.first;
				deleteNode(&right, right->data.first);
			}
		}
	};
}

#endif