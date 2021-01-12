/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirect_iter.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:31:57 by hherin            #+#    #+#             */
/*   Updated: 2021/01/12 13:16:12 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECT_ITER_HPP
# define BIDIRECT_ITER_HPP

# include <iostream>
# include <memory>

namespace ft
{
    template <class T, bool B, class Alloc = std::allocator<T> > class bidirect_iter
	{
		public:
			typedef typename Alloc::difference_type difference_type;
			typedef typename Alloc::value_type value_type;
			
			typedef typename ft::chooseIf<B,  typename Alloc::const_reference, typename Alloc::reference>::type reference;
			typedef typename ft::chooseIf<B,  typename Alloc::const_pointer, typename Alloc::pointer>::type pointer;
			
			typedef typename Alloc::pointer nonConst_pointer;
			typedef std::bidirectional_iterator_tag iterator_category;
			
			bidirect_iter(nonConst_pointer val = 0) : _current(val){}
			bidirect_iter(bidirect_iter<T, true, Alloc> const &cp) {_current = cp.getCurrent();}
			bidirect_iter(bidirect_iter<T, false, Alloc> const &cp) {_current = cp.getCurrent();}
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
			reference			operator*() const { return *_current; }
			pointer				operator->() { return _current; }
			friend bool			operator==(const bidirect_iter& a, const bidirect_iter& b) { return a._current == b._current; }
			friend bool			operator!=(const bidirect_iter& a, const bidirect_iter& b) { return a._current != b._current; }
			nonConst_pointer	getCurrent() const {return _current;}
			
		protected:
			nonConst_pointer _current;
	};
}


#endif