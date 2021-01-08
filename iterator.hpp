/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:20:10 by hherin            #+#    #+#             */
/*   Updated: 2021/01/08 16:34:32 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace ft
{
// 	template <class T, class Alloc = std::allocator<T> > class bidirect_iter
// 	{
// 		public:
// 			typedef typename Alloc::difference_type difference_type;
// 			typedef typename Alloc::value_type value_type;
// 			typedef typename Alloc::reference reference;
// 			typedef typename Alloc::pointer pointer;
// 			typedef std::bidirectional_iterator_tag iterator_category;
			
// 			bidirect_iter(pointer val = 0) : _current(val){}
// 			bidirect_iter(bidirect_iter const &cp) : _current(cp._current){}
// 			bidirect_iter operator=(bidirect_iter const &cp)
// 			{
// 				if (this != &cp)
// 					_current = cp._current;
// 				return *this;
// 			}
// 			~bidirect_iter(){}
			

// 			bidirect_iter		operator++(){ _current++; return *this; }
// 			bidirect_iter		operator++(int){ bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
// 			bidirect_iter		operator--(){ _current--; return *this; }
// 			bidirect_iter		operator--(int){ bidirect_iter tmp = *this; --(*this); return tmp; }
// 			reference			operator*() { return *_current; }
// 			pointer				operator->() { return _current; }
// 			friend bool			operator==(const bidirect_iter& a, const bidirect_iter& b) { return a._current == b._current; }
// 			friend bool			operator!=(const bidirect_iter& a, const bidirect_iter& b) { return a._current != b._current; }
			
// 		protected:
// 			pointer _current;
// 	};

// 	template <class T, class Alloc = std::allocator<T> >
// 	class random_iter : public virtual ft::bidirect_iter<T, Alloc>
// 	{
// 		public:
// 			typedef typename Alloc::difference_type			difference_type;
// 			typedef typename Alloc::value_type				value_type;
// 			typedef typename Alloc::reference				reference;
// 			typedef typename Alloc::pointer					pointer;
// 			typedef typename Alloc::size_type				size_type;
// 			typedef std::random_access_iterator_tag			iterator_category;
			
// 			random_iter(pointer val = 0) : ft::bidirect_iter<T, Alloc>(val){}
// 			random_iter(random_iter const &cp) : ft::bidirect_iter<T, Alloc>(cp){}
// 			random_iter operator=(random_iter const &cp)
// 			{
// 				if (this != &cp)
// 					this->_current = cp._current;
// 				return *this;
// 			}
// 			~random_iter(){}
			
// 			difference_type	operator-(random_iter const &it) { return (this->_current - it._current); }
			
// 			random_iter operator+(int n) 
// 			{
// 				random_iter ret(*this);
// 				for (int i = 0; i < n; i++)
// 					ret++;
// 				return ret; 
// 			}
			
// 			friend random_iter operator+(random_iter const &rhs, int n) 
// 			{
// 				random_iter ret(rhs);
// 				return ret + n; 
// 			}

// 			// it - n  	| n - it
// 			random_iter operator-(int n) 
// 			{
// 				random_iter ret(*this);
// 				for (int i = 0; i < n; i++)
// 					ret--;
// 				return ret; 
// 			}
			
// 			friend random_iter operator-(int n, random_iter &rhs) 
// 			{ 
// 				random_iter ret(rhs);
// 				return ret - n; 
// 			}
			
// 			// Inequality comparisons
// 			friend bool operator>(random_iter &x, random_iter &y) { return (*x > *y); }
// 			friend bool operator>=(random_iter &x, random_iter &y) { return (*x >= *y); }
// 			friend bool operator<(random_iter &x, random_iter &y) { return (*x < *y); }
// 			friend bool operator<=(random_iter &x, random_iter &y) { return (*x <= *y); }

// 			//Compoud assignment
// 			random_iter operator+=(int n)
// 			{
// 				for (int i = 0; i < n; i++)
// 					this->_current++;
// 				return *this;
// 			}
// 			random_iter operator-=(int n)
// 			{
// 				for (int i = 0; i < n; i++)
// 					this->_current--;
// 				return *this;
// 			}
// 			value_type operator[](int n)
// 			{
// 				for (int i = 0; i < n; i++)
// 					this->_current++;
// 				return *(this->_current);
// 			}
// 	};
	
// 	template <class T, class Alloc = std::allocator<T> >
// 	class const_bidirect_iter
// 	{
// 		public:
// 			typedef typename Alloc::difference_type difference_type;
// 			typedef typename Alloc::value_type value_type;
// 			typedef typename Alloc::reference reference;
// 			typedef typename Alloc::pointer pointer;
// 			typedef std::bidirectional_iterator_tag iterator_category;
			
// 			const_bidirect_iter(pointer val = 0) : _current(val){}
// 			const_bidirect_iter(const_bidirect_iter const &cp) : _current(cp._current){}
// 			const_bidirect_iter operator=(const_bidirect_iter const &cp)
// 			{
// 				if (this != &cp)
// 					_current = cp._current;
// 				return *this;
// 			}
// 			~const_bidirect_iter(){}
			
// //post incrementation
// 			const_bidirect_iter		operator++(int) { const_bidirect_iter tmp = *this; ++(*this); return tmp; }
// 			const_bidirect_iter		operator++() { _current++; return *this; }
// 			reference				operator*() const {std::cout << "ICI\n"; return *_current; }
// 			const pointer					operator->() { return _current; }
// 			friend bool				operator==(const const_bidirect_iter& a, const const_bidirect_iter& b) { return a._current == b._current; }
// 			friend bool				operator!=(const const_bidirect_iter& a, const const_bidirect_iter& b) { return a._current != b._current; }
			
// 		protected:
// 			pointer _current;
// 	};



}

#endif