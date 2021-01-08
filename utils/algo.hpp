/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:49:30 by hherin            #+#    #+#             */
/*   Updated: 2021/01/08 17:59:03 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_HPP
# define ALGO_HPP

#include "../vector.hpp"

namespace ft
{
    template <typename T>
    bool is_max(T obj1, T obj2)
    {
        return obj1.size() > obj2.size();
    }

    template <typename T>
    T& max(T& obj1, T& obj2)
    {
        if (obj1.size() > obj2.size())
            return obj1;
        return obj2;
    }

    template <typename T>
    T& min(T& obj1, T& obj2)
    {
        if (obj1.size() < obj2.size())
            return obj1;
        return obj2;
    }
    
    // template <typename T>
    // void swapVector(T& min, T& max)
    // {
    //    T tmp = max;
    //     for (std::pair< typename T::iterator, typename T::iterator > it(max.begin(), min.begin()); it.second != min.end(); it.first++, it.second++)
    //         it.first = it.second;
    //     min._myAlloc.deallocate(min._vector, min._capacity);
    //     min._vector = min._myAlloc.allocate(max._capacity);
    //     for (std::pair< typename T::iterator, typename T::iterator > it(min.begin(), tmp.begin()); it.second != tmp.end(); it.first++, it.second++){
    //         // std::cout << *it.first << std::endl;
    //         // std::cout << *it.second << std::endl;
            
    //         it.first = it.second;
    //         // std::cout << *it.first << std::endl;
    //         }
    //     min._capacity = max._capacity;
    // }

}
#endif