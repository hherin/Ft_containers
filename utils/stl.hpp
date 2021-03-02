/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:49:30 by hherin            #+#    #+#             */
/*   Updated: 2021/01/12 13:37:47 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_HPP
# define STL_HPP

namespace ft
{

	// =============================================== ft::pair ===========================================
	// std::pair is a class template that provides a way to store two heterogeneous objects as a single unit.
	// A pair is a specific case of a std::tuple with two elements.
	template <class T1, class T2>
	class pair
	{	
		public:
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		// default (1)	
		pair() : first(), second() {}

		// initialization (3)	
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
		
		// copy (2)	
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		
		pair& operator= (const pair& pr)
		{
			if (this == &pr)
				return *this;
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}

		friend bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
		friend bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); }
		friend bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }
		friend bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }
		friend bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }
		friend bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

	};

	// ============================================================ ft::less =========================================
	// Binary function object class whose call returns whether the its first argument compares less than the second (as returned by operator <).
	template <class T> 
	struct less
	{
		bool operator() (const T& x, const T& y) const { return x < y; }
	};


	// ============================================================ ft::mySwap ==========================================
	// SWap the content of two objects
	template <class H>
	void	mySwap(H& a, H&b)
	{
		H tmp = a;
		a = b;
		b = tmp;
	}

	// =============================================== ft::lexicographical_compare =========================================
	// Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) 
				return false;
			else if (*first1 < *first2) 
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}
}
#endif