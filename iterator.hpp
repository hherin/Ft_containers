/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 14:20:10 by hherin            #+#    #+#             */
/*   Updated: 2021/01/07 17:50:32 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			
			bidirect_iter(pointer val = 0) : _current(val){}
			bidirect_iter(bidirect_iter const &cp) : _current(cp._current){}
			bidirect_iter operator=(bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~bidirect_iter(){}
			

			bidirect_iter		operator++(){ _current++; return *this; }
			bidirect_iter		operator++(int){ bidirect_iter tmp = *this; ++(*this); return tmp; } //post incrementation
			bidirect_iter		operator--(){ _current--; return *this; }
			bidirect_iter		operator--(int){ bidirect_iter tmp = *this; --(*this); return tmp; }
			reference			operator*() { return *_current; }
			pointer				operator->() { return _current; }
			friend bool			operator==(const bidirect_iter& a, const bidirect_iter& b) { return a._current == b._current; }
			friend bool			operator!=(const bidirect_iter& a, const bidirect_iter& b) { return a._current != b._current; }
			
		protected:
			pointer _current;
	};

	template <class T, class Alloc = std::allocator<T> >
	class random_iter : public virtual ft::bidirect_iter<T, Alloc>
	{
		public:
			typedef typename Alloc::difference_type			difference_type;
			typedef typename Alloc::value_type				value_type;
			typedef typename Alloc::reference				reference;
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::size_type				size_type;
			typedef std::random_access_iterator_tag			iterator_category;
			
			random_iter(pointer val = 0) : ft::bidirect_iter<T, Alloc>(val){}
			random_iter(random_iter const &cp) : ft::bidirect_iter<T, Alloc>(cp){}
			random_iter operator=(random_iter const &cp)
			{
				if (this != &cp)
					this->_current = cp._current;
				return *this;
			}
			~random_iter(){}
			
			difference_type	operator-(random_iter const &it) { return (this->_current - it._current); }
			
			// it + n  	| n + it
			random_iter operator+(size_type &n) { return random_iter(*this->_current + n); }
			friend random_iter operator+(size_type &n, random_iter &rhs) { return random_iter(rhs + n); }

			// it - n  	| n - it
			random_iter operator-(size_type &n) { return random_iter(*this->_current - n); }
			friend random_iter operator-(size_type &n, random_iter &rhs) { return random_iter(rhs - n); }
			
			// Inequality comparisons
			friend bool operator>(random_iter &x, random_iter &y) { return (*x > *y); }
			
	};


// Supports inequality comparisons (<, >, <= and >=) between iterators	a < b
// a > b
// a <= b
// a >= b
// Supports compound assignment operations += and -=	a += n
// a -= n
// Supports offset dereference operator ([])	a[n]
	
	template <class T, class Alloc = std::allocator<T> >
	class const_bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			
			const_bidirect_iter(pointer val = 0) : _current(val){}
			const_bidirect_iter(const_bidirect_iter const &cp) : _current(cp._current){}
			const_bidirect_iter operator=(const_bidirect_iter const &cp)
			{
				if (this != &cp)
					_current = cp._current;
				return *this;
			}
			~const_bidirect_iter(){}
			
//post incrementation
			const_bidirect_iter		operator++(int) { const_bidirect_iter tmp = *this; ++(*this); return tmp; }
			const_bidirect_iter		operator++() { _current++; return *this; }
			const reference				operator*() { return *_current; }
			const pointer					operator->() { return _current; }
			friend bool				operator==(const const_bidirect_iter& a, const const_bidirect_iter& b) { return a._current == b._current; }
			friend bool				operator!=(const const_bidirect_iter& a, const const_bidirect_iter& b) { return a._current != b._current; }
			
		protected:
			pointer _current;
	};

	template <class T, class Alloc = std::allocator<T> >
	class const_random_iter : public virtual ft::const_bidirect_iter<T, Alloc>
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::pointer pointer;
			typedef std::random_access_iterator_tag iterator_category;
			
			const_random_iter(pointer val = 0) : ft::const_bidirect_iter<T, Alloc>(val){}
			const_random_iter(const_random_iter const &cp) : ft::const_bidirect_iter<T, Alloc>(cp){}
			const_random_iter operator=(const_random_iter const &cp)
			{
				if (this != &cp)
					this->_current = cp._current;
				return *this;
			}
			virtual ~const_random_iter(){}
			
			difference_type	operator-(const_random_iter const &it) { return (this->_current - it._current); }
	};
}

#endif