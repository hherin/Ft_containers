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
# include <cmath>
# include "../utils/stl.hpp"
# include "../utils/iterator/mapIterators.hpp"
# include "../utils/allocator.hpp"
# include "list.hpp"

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
			typedef typename ft::map_rev_bidirect_iter<true, Node, value_type>	reverse_iterator;
			typedef typename ft::map_rev_bidirect_iter<false, Node, value_type>	const_reverse_iterator;

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
			_root(0), _size(0), _comp(comp), _alloc(alloc)
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
		: _root(0), _size(0), _comp(x._comp), _alloc(x._alloc)
		{
			neutral = new Node;
			neutral->left = neutral;
			neutral->right = neutral;

			if (x.size())
				for (const_iterator it = x.begin(); it != x.end(); it++)
					insert((*it));
		}

		~map()
		{
			clear();
			delete neutral;
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
		const_iterator begin() const {return const_iterator(neutral->left, neutral); }
		iterator end() { return iterator(neutral, neutral); }
		const_iterator end() const { return const_iterator(neutral, neutral); }
		reverse_iterator rbegin() { return reverse_iterator(neutral->right, neutral); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(neutral->right, neutral); }
		reverse_iterator rend() { return reverse_iterator(neutral, neutral); }
		const_reverse_iterator rend() const  { return const_reverse_iterator(neutral, neutral); }

		// /*
		// ** ================================== Capacity =================================
		// */ 
		bool empty() const { return !_size; }
		size_type size() const { return _size; }
		// size_type max_size() const;

		// /*
		// ** ================================== Element Access ============================
		// */
		mapped_type& operator[] (const key_type& k)
		{
			value_type val(k, mapped_type());
			ft::pair<iterator,bool> ret = insert(val);
			return ret.first->second;

		}

		// /*
		// ** ================================== Modifiers ==================================
		// */
		// single element (1)	
		ft::pair<iterator,bool> insert (const value_type& val)
		{
			bool ishere = (_root) ? !isKeyInBinTree(val.first, _root) : 1;
			return ft::pair<iterator, bool>(insert(iterator(_root, neutral), val), ishere);
		}

		// with hint (2)	
		iterator insert (iterator position, const value_type& val)
		{
			Node *pos = position.getCurrent();
			Node *ret = insertNewNode(&_root, val);
			if (ret){
				ret->neutral = neutral;
				_size++;
				if (_size == 1){
					neutral->left = ret; neutral->right = ret;
				}
				else{
					neutral->left = getMin();
					neutral->right = getMax();
				}
			}
			return ret ? iterator(ret, neutral) : iterator(isKeyInBinTree(val.first, pos), neutral);
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

		void printMap() { printTree(_root); }

		void erase (iterator position)
		{
			_size -= deleteNode(&_root, position->first);

			neutral->right = (!_size) ? neutral : getMax();
			neutral->left = (!_size) ? neutral : getMin();
		}

		size_type erase (const key_type& k)
		{
			Node *del = isKeyInBinTree(k, _root);
			if (del){
				erase(iterator(del, neutral));
				return 1;
			}
			return 0;
		}

    	void erase (iterator first, iterator last)
		{
			ft::list<Key> delKey;

			while (first != last){
				delKey.push_back(first->first);
				first++;
			}

			while (delKey.size()){
				_size -= deleteNode(&_root, delKey.front());
				delKey.pop_front();
				neutral->right = (!_size) ? neutral : getMax();
				neutral->left = (!_size) ? neutral : getMin();
			}
		}

		void swap (map& x)
		{
			ft::mySwap(_size, x._size);
			ft::mySwap(_root, x._root);
			ft::mySwap(neutral, x.neutral);
			ft::mySwap(_comp, x._comp);
			ft::mySwap(_alloc, x._alloc);
			ft::mySwap(_nodAlloc, x._nodAlloc);
		}

		void clear() { erase(begin(), end()); }

		// /*
		// ** ======================================== Observers ==============================
		// */

		key_compare key_comp() const { return _comp; }
		value_type value_comp() const { return value_type(_comp); }

		// /*
		// ** ===================================== Operations =================================
		// */

		iterator find (const key_type& k)
		{
			Node *ret = isKeyInBinTree(k, _root);
			return (ret) ? iterator(ret, neutral) : end();
		}

		const_iterator find (const key_type& k) const
		{
			Node *ret = isKeyInBinTree(k, _root);
			return (ret) ? const_iterator(ret, neutral) : end();
		}

		size_type count (const key_type& k) const
		{
			return isKeyInBinTree(k, _root) ? 1 : 0;
		}

		iterator lower_bound (const key_type& k)
		{
			for (iterator it = begin(); it != end(); it++){
				if (_comp(k, it->first) || (!_comp(it->first, k) && !_comp(k, it->first)))
					return it;
			}
			return end();
		}

		const_iterator lower_bound (const key_type& k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				if (_comp(k, it->first) || (!_comp(it->first, k) && !_comp(k, it->first)))
					return it;
			return end();
		}

		iterator upper_bound (const key_type& k)
		{
			for (iterator it = begin(); it != end(); it++)
				if (it->first > k)
					return it;
			return end();
		}


		const_iterator upper_bound (const key_type& k) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				// if (it->first > k)
				if (_comp(k, it->first))
					return it;
			return end();
		}

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			for (const_iterator it = begin(); it != end(); it++){
				if (!_comp(it->first, k) && !_comp(k, it->first)){
					const_iterator next(it);
					next++;
					return ft::pair<const_iterator,const_iterator>(it, next);
				}
				else if (_comp(k, it->first))
					return ft::pair<const_iterator,const_iterator>(it, it);
			}
			return ft::pair<const_iterator,const_iterator>(end(), end());
		}		

		ft::pair<iterator,iterator>    equal_range (const key_type& k)
		{
			for (iterator it = begin(); it != end(); it++){
				if (!_comp(it->first, k) && !_comp(k, it->first)){
					iterator next(it);
					next++;
					return ft::pair<iterator,iterator>(it, next);
				}
				else if (_comp(k, it->first))
					return ft::pair<iterator,iterator>(it, it);
			}
			return ft::pair<iterator,iterator>(end(), end());
		}
		
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

		void destroyNode(Node **del)
		{
			_alloc.destroy(&(*del)->data);
			_nodAlloc.deallocate(*del, 1);
			*del = NULL;
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

		void	right_Rotation(Node *insertNode)
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

		void	left_Rotation(Node *insertNode)
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
		
		void	BalancedTree(Node *insertNode)
		{
			while (insertNode){
				int bl = getHeightTree(insertNode->left);
				int br = getHeightTree(insertNode->right);
				if (bl - br >= 2){
					Node *tmp = insertNode->left;
					if (getHeightTree(tmp->left) - getHeightTree(tmp->right) <= 0)
					{
						left_Rotation(insertNode->left);
						right_Rotation(insertNode);
					}
					else
						right_Rotation(insertNode);
				}
				else if (bl - br <= -2){
					Node *tmp = insertNode->right;
					if (getHeightTree(tmp->left) - getHeightTree(tmp->right) >= 0)
					{
						right_Rotation(insertNode->right);
						left_Rotation(insertNode);
					}
					else
						left_Rotation(insertNode);
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
				*bst = createNode(content, parent);	// case empty tree
				return *bst;
			}
			else{										// check which side the leave should be added
				parent = *bst;
				if (!_comp(content.first, (*bst)->data.first))
					return recInsertNode(&(*bst)->right, parent, content);
				else if (_comp(content.first, (*bst)->data.first))
					return recInsertNode(&(*bst)->left, parent, content);
			}
			return *bst;
		}

		// returns 1 if element has been inserted are 0 if already in tree
		Node *insertNewNode(Node **bst, value_type const &content)
		{
			Node *newNode = NULL;
			newNode = (*bst) ? recInsertNode(bst, newNode, content) : recInsertNode(&_root, newNode, content);
			BalancedTree(newNode);
			return newNode;
		}

		Node *isKeyInBinTree(key_type const &key, Node *bst) const
		{	
			if (!bst)
				return NULL;
			else
			{
				if (key == bst->data.first)
					return bst;
				else
				{
					if (_comp(key, bst->data.first))
						return isKeyInBinTree(key, bst->left);
					else
						return isKeyInBinTree(key, bst->right);
				}
			}
		}

		int deleteNode(Node **root, key_type const data)
		{
			if (!*root)
				return false;
			Node *del = isKeyInBinTree(data, *root);
			
			if (!del)
				return false;
			else if (del->right && !del->left){
				Node *right = del->right;
				right->parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = right : del->parent->left = right;
				else
					*root = del->right;
				destroyNode(&del);
				BalancedTree(right);
			}
			else if (del->left && !del->right){
				Node *left = del->left;
				left->parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = left : del->parent->left = left;
				else
					*root = del->left;
				destroyNode(&del);
				BalancedTree(left);
			}
			else if (!del->left && !del->right){
				Node *parent = del->parent;
				if (del->parent)
					(del->parent->right == del) ? del->parent->right = NULL : del->parent->left = NULL;
				else
					*root = NULL;
				destroyNode(&del);
				if (parent)
					BalancedTree(parent);
			}
			else{
				Node *right = del->right;
				while (right->left)
					right = right->left;
				_alloc.destroy(&del->data);
				_alloc.construct(&del->data, right->data);
				deleteNode(&right, right->data.first);
			}
			return true;
		}

		Node *getMax()
		{
			Node *ret = _root;
			while (ret && ret->right)
				ret = ret->right;
			return ret;
		}

		Node *getMin() 
		{
			Node *ret = _root;
			while (ret && ret->left)
				ret = ret->left;
			return ret;
		}

		ft::vector<Node*> save_key(Node *bst)
		{
			ft::vector<Node*> TreeArray;
			if (!bst)
				return TreeArray;
				
			Node *current = bst;
			TreeArray.push_back(current);
			
			int i = 1;
			while (i <= pow(2, (getHeightTree(bst) - 1)) - 1)
			{
				(TreeArray[i - 1]) ? TreeArray.push_back(current->left) : TreeArray.push_back(0);
				(TreeArray[i - 1]) ? TreeArray.push_back(current->right) : TreeArray.push_back(0);

				current = TreeArray[i];
				i++;
			}
			return TreeArray;
		}

		void printTree(Node *bst)
		{
			if (!bst)
				return;
			ft::vector<Node *> treeArray = save_key(bst);
			int level = 1;
			size_t i = 1;
			int index = 1;
			int width =  pow(2, getHeightTree(bst)) * 3;  // =>   * spaces
			
			std::cout.width((width - 3) / 2);
			std::cout << "[ " << treeArray[0]->data.first << " ]" << "\n";
			
			while (i < treeArray.size()){
				std::cout.width( (width - 3) / (pow(2, level) + 1) );
				(treeArray[i]) ? 
					std::cout << "[ " << treeArray[i]->data.first << " ]" : std::cout << "[NIL]";
				
				if (index == pow(2, level)) {
					std::cout << "\n";
					level++;
					index = 1;
				}
				else{
					std::cout << " ";
					index++;
				}
				i++;
			}
			treeArray.clear();
		}
	};
}

#endif