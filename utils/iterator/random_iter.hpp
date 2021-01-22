/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_iter.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:30:56 by hherin            #+#    #+#             */
/*   Updated: 2021/01/22 12:11:50 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ITER_HPP
# define RANDOM_ITER_HPP

# include <iostream>
# include <memory>
# include "bidirect_iter.hpp"
# include "reverse_bidirect_iter.hpp"
#include "../../containers/vector.hpp"

namespace ft
{
	template <class T, class Alloc> class vector;
	
    template <class T, bool B> class random_iter
			: public virtual ft::vect_bidirect_iter<T, B>
	{
		public:
			typedef T												value_type;
			typedef T*												nonConst_pointer;
			typedef std::ptrdiff_t									difference_type;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			random_iter(nonConst_pointer val = 0) : ft::vect_bidirect_iter<T, B>(val){}
			random_iter(random_iter<T, true> const &cp) : ft::vect_bidirect_iter<T, B>(cp) {}
			random_iter(random_iter<T, false> const &cp) : ft::vect_bidirect_iter<T, B>(cp) {}


			random_iter operator=(random_iter const &cp)
			{
				if (this != &cp)
					this->_current = cp._current;
				return *this;
			}

			~random_iter(){}

			// ---------------------------------- Operators overload ------------------------------------
			difference_type	operator-(random_iter const &lhs) { return (this->_current - lhs._current); }

			random_iter operator+(int n)
			{
				random_iter ret(*this);
				return ret += n;
			}
			
			random_iter operator-(int n)
			{
				random_iter ret(*this);
				return ret -= n;
			}

			// ------------------------------------ Compoud assignment ------------------------------------
			random_iter operator+=(int n)
			{
				for (int i = 0; i < n; i++)
					(n > 0) ? this->_current++ : this->_current--;
				return *this;
			}
			
			random_iter operator-=(int n)
			{
				for (int i = 0; i < n; i++)
					(n > 0) ? this->_current-- : this->_current++;
				return *this;
			}
			
			value_type operator[](int n) { return *(*this + n); }

			// ------------------------------------ Inequality comparisons ------------------------------------
			friend bool operator>(const random_iter &x, const random_iter &y) { return (*x > *y); }
			friend bool operator>=(const random_iter &x, const random_iter &y) { return (*x >= *y); }
			friend bool operator<(const random_iter &x, const random_iter &y) { return (*x < *y); }
			friend bool operator<=(const random_iter &x, const random_iter &y) { return (*x <= *y); }
	};

	//============================================== Reverse ===============================================

	 template <class T, bool B> class reverse_random_iter
			: public virtual ft::vect_reverse_bidirect_iter<T, B>
	{
		public:
			typedef T												value_type;
			typedef T*												nonConst_pointer;
			typedef std::ptrdiff_t									difference_type;
			typedef typename ft::chooseIf<B, const T&, T&>::type	reference;
			typedef typename ft::chooseIf<B, const T*, T*>::type	pointer;

			reverse_random_iter(nonConst_pointer val = 0) : ft::vect_reverse_bidirect_iter<T, B>(val){}
			reverse_random_iter(reverse_random_iter<T, true> const &cp) : ft::vect_reverse_bidirect_iter<T, B>(cp) {}
			reverse_random_iter(reverse_random_iter<T, false> const &cp) : ft::vect_reverse_bidirect_iter<T, B>(cp) {}
			explicit reverse_random_iter(random_iter<T, false> const &cp) : ft::vect_reverse_bidirect_iter<T, B>(cp.getCurrent() - 1) {}

			reverse_random_iter operator=(reverse_random_iter const &cp)
			{
				if (this != &cp)
					this->_current = cp._current;
				return *this;
			}

			~reverse_random_iter(){}

			// ---------------------------------- Operators overload ------------------------------------
			difference_type	operator-(reverse_random_iter const &lhs) { return (lhs._current - this->getCurrent()); }

			reverse_random_iter operator+(int n)
			{
				reverse_random_iter ret(*this);
				return ret += n;
			}
			
			reverse_random_iter operator-(int n)
			{
				reverse_random_iter ret(*this);
				return ret -= n;
			}

			// ------------------------------------ Compoud assignment ------------------------------------
			reverse_random_iter operator+=(int n)
			{
				for (int i = 0; i < n; i++)
					(n > 0) ? this->_current-- : this->_current++;
				return *this;
			}
			
			reverse_random_iter operator-=(int n)
			{
				for (int i = 0; i < n; i++)
					(n > 0) ? this->_current++ : this->_current--;
				return *this;
			}
			
			value_type operator[](int n) { return *(*this + n); }
			
			// ------------------------------------ Inequality comparisons ------------------------------------
			friend bool operator>(const reverse_random_iter &x, const reverse_random_iter &y) { return (*x > *y); }
			friend bool operator>=(const reverse_random_iter &x, const reverse_random_iter &y) { return (*x >= *y); }
			friend bool operator<(const reverse_random_iter &x, const reverse_random_iter &y) { return (*x < *y); }
			friend bool operator<=(const reverse_random_iter &x, const reverse_random_iter &y) { return (*x <= *y); }
	};
}

#endif