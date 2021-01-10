/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:49:30 by hherin            #+#    #+#             */
/*   Updated: 2021/01/08 18:04:30 by hherin           ###   ########.fr       */
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


}
#endif