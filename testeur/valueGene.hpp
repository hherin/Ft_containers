/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valueGene.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 16:55:31 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 17:27:09 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUEGENE_HPP
# define VALUEGENE_HPP

#include <string>

template <class T>
class geneClass
{
    public :
    geneClass(const static T &x) 
    {
        value = new T[n](); 
        for (int i = 0; i < 20; i++) 
            value[i] = x[i];
    }
    ~geneClass(){ delete[] value; }
    static const T* getValue() { return value; }
    
    protected:
    T *value;
};

// template <class T, class = void>
// struct valueGenerator
// { static geneClass<T> obj; const static void *value = obj.getValue(); };

// template <>
// struct valueGenerator<int>
// {
//     static geneClass<int> obj;
//     obj.add_value( {58966, 2147483647, 256, -2147483648, 0, -1, 2, 3, 4, 5, 6, 7, 7, 8, 54634152, 9, 10, 11, 56, 56465} );
//     static const int *value = obj.getValue();
// };

// template <>
// struct valueGenerator<std::string>
// { static const std::string value[20] = {"hello coco", "j'arrive", "oui-oui", "kafeolait", "jul d'ananas", "42", "gnou", "jura", "saperlipopette", "anticonstitutionnellement", "Pneumonoultramicroscopicsilicovolcanoconiosis", "Blue", "Red", "Orange", "Yellow"
//                             "boulette de viande hache"}; };// 16 words

// template <>
// struct valueGenerator<char>
// { static const char value[20] = {-1, 0, 32, 33, 48,  36, 76, 117, 82, 21, 105, 72, 99, 111, 125, 122, 43, 50, 69, 88}; };


#endif