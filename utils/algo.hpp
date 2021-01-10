/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:49:30 by hherin            #+#    #+#             */
/*   Updated: 2021/01/10 22:19:53 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_HPP
# define ALGO_HPP

#include "../containers/vector.hpp"

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