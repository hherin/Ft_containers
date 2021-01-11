/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_random_iter.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:20:19 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/11 18:35:58 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef reverse_RANDOM_ITER_HPP
# define reverse_RANDOM_ITER_HPP

# include <iostream>
# include <memory>
# include "reverse_bidirect_iter.hpp"

namespace ft
{
    template <class T, bool B, class Alloc = std::allocator<T> > class reverse_random_iter
			: public virtual ft::reverse_bidirect_iter<T, B, Alloc>
	{
		public:
			typedef typename Alloc::difference_type			difference_type;
			typedef typename Alloc::value_type				value_type;
			typedef typename Alloc::size_type				size_type;
			typedef std::random_access_iterator_tag			iterator_category;

			typedef typename ft::chooseIf<B,  typename Alloc::const_reference, typename Alloc::reference>::type reference;
			typedef typename ft::chooseIf<B,  typename Alloc::const_pointer, typename Alloc::pointer>::type pointer;

			typedef typename Alloc::pointer nonConst_pointer;

			reverse_random_iter(nonConst_pointer val = 0) : ft::reverse_bidirect_iter<T, B, Alloc>(val){}
			reverse_random_iter(reverse_random_iter<T, true, Alloc> const &cp) : ft::reverse_bidirect_iter<T, B, Alloc>(cp) {}
			reverse_random_iter(reverse_random_iter<T, false, Alloc> const &cp) : ft::reverse_bidirect_iter<T, B, Alloc>(cp) {}


			reverse_random_iter operator=(reverse_random_iter const &cp)
			{
				if (this != &cp)
					this->_current = cp._current;
				return *this;
			}

			~reverse_random_iter(){}

			friend difference_type	operator-(reverse_random_iter const &it, reverse_random_iter const &rhs) { return (it._current - rhs._current); }

			reverse_random_iter operator+(int n) const
			{
				reverse_random_iter ret(*this);
				for (int i = 0; i < n; i++)
					ret--;
				return ret;
			}

			friend reverse_random_iter operator+(reverse_random_iter const &rhs, int n)
			{
				reverse_random_iter ret(rhs);
				return ret - n;
			}

			// it - n  	| n - it
			reverse_random_iter operator-(int n) const
			{
				reverse_random_iter ret(*this);
				for (int i = 0; i < n; i++)
					ret++;
				return ret;
			}

			friend reverse_random_iter operator-(int n, reverse_random_iter &rhs)
			{
				reverse_random_iter ret(rhs);
				return ret + n;
			}

			// Inequality comparisons
			friend bool operator>(reverse_random_iter &x, reverse_random_iter &y) { return (*x > *y); }
			friend bool operator>=(reverse_random_iter &x, reverse_random_iter &y) { return (*x >= *y); }
			friend bool operator<(reverse_random_iter &x, reverse_random_iter &y) { return (*x < *y); }
			friend bool operator<=(reverse_random_iter &x, reverse_random_iter &y) { return (*x <= *y); }

			//Compoud assignment
			reverse_random_iter operator+=(int n)
			{
				for (int i = 0; i < n; i++)
					this->_current--;
				return *this;
			}
			reverse_random_iter operator-=(int n)
			{
				for (int i = 0; i < n; i++)
					this->_current++;
				return *this;
			}
			value_type operator[](int n)
			{
				for (int i = 0; i < n; i++)
					this->_current--;
				return *(this->_current);
			}
	};
}

#endif