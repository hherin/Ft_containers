/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:55:07 by hherin            #+#    #+#             */
/*   Updated: 2021/02/17 11:26:43 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

# include <exception>
# include <iostream>

namespace ft
{
	template <class T>
	class myAlloc
	{
		public:
		typedef T				value_type;
		typedef T*				pointer;
		typedef const T*		const_pointer;
		typedef T&				reference;
		typedef const T&		const_reference;
		typedef std::size_t		size_type;
		typedef std::ptrdiff_t	difference_type;
		
		// nothing in constructor because no state in allocator
		myAlloc() throw() {}
		myAlloc(const myAlloc&) throw() {}
		template <class U>
		myAlloc (const myAlloc<U>&) throw() {}
		~myAlloc() throw() {}
	   
		pointer allocate(int n)
		{
			pointer ret;
			int size = n * sizeof(value_type);
			
			try{
				ret = reinterpret_cast<pointer>(::operator new(size));
			}
			catch (std::exception &e){
				std::cout << e.what();
			}
			return ret;
		}
		
    	void deallocate(pointer p, int n)
		{
			(void)n;
			::operator delete(p);
		}

		void construct(pointer p, const T& v) { new((void*)p)T(v); }
		
    	void destroy(pointer p) { p->~T(); }
		
		template <class T1, class T2>
		friend bool operator== (const myAlloc<T1>&, const myAlloc<T2>&) throw()  { return true; }
		template <class T1, class T2>
		friend bool operator!= (const myAlloc<T1>&, const myAlloc<T2>&) throw() { return false; }
		
	};
};


#endif