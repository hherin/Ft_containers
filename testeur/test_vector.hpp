/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:42:21 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 17:24:03 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_VECTOR_HPP
# define TEST_VECTOR_HPP

// # include "valueGene.hpp"

extern std::ofstream stdFile;
extern std::ofstream ftFile;

template <class T, bool B>
void printContainer(T &ctnr)
{
    for (typename T::iterator it = ctnr.begin(); it != ctnr.end(); it++)
        (B ? stdFile : ftFile) << *it << " | ";
    (B ? stdFile : ftFile) << "\n";
}


template <class T, bool B>
void Test_constr()
{
    (B ? stdFile : ftFile) << "================== Test_constr ==================\n";
    
    T v0;
    (B ? stdFile : ftFile) << "size()=\t" << v0.size() << "\n";
    (B ? stdFile : ftFile) << "capacity()=\t" << v0.capacity() << "\n";
    printContainer<T, B>(v0);
    
    (B ? stdFile : ftFile) << "-- push_back --\n";
    // for (int i = 3; i < 9; i++)
    //     v0.push_back(valueGenerator<T>::value[i]);
}

#endif