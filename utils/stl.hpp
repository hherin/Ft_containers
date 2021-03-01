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

	template <class T> 
	struct less
	{
		bool operator() (const T& x, const T& y) const { return x < y; }
	};

	// template <typename T>
	// bool is_max(T obj1, T obj2)
	// {
	// 	return obj1.size() > obj2.size();
	// }

	// template <typename T>
	// T& max(T& obj1, T& obj2)
	// {
	// 	if (obj1.size() > obj2.size())
	// 		return obj1;
	// 	return obj2;
	// }

	// template <typename T>
	// T& min(T& obj1, T& obj2)
	// {
	// 	if (obj1.size() < obj2.size())
	// 		return obj1;
	// 	return obj2;
	// }

	// template<class T>
	// bool is_less(const T& a, const T& b)
	// {
	// 	return a < b;
	// }

	template <class H>
	void	mySwap(H& a, H&b)
	{
		H tmp = a;
		a = b;
		b = tmp;
	}

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