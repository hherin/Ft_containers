/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_like.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:20:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/17 11:22:38 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_LIKE_HPP
#define STL_LIKE_HPP


namespace ft
{
    /**
    * ------------------------------------------------------------- *
    * ------------------------- FT::PAIR -------------------------- *
    *
    * Coplien form:
    * (constructor):        Construct pair
    * (destructor):         Pair destructor
    * operator=:            Assign content
    *
    * Public member variables:
    * T1:                   First pair's member variable.
    * T2:                   Second pair's member variable.
    * ------------------------------------------------------------- *
    */

    // template <typename T1, typename T2>
    // class pair
    // {
    //     public:
            
    //         /* ------------------------------------------------------------- */
    //         /* ------------------------ COPLIEN FORM ----------------------- */
            
    //         /**
    //         *   Default constructor, value initialized first and second.
    //         */
    //         pair() : first(), second() {};
            
    //         /**
    //         *   Initialization constructor.
    //         *
    //         *   @param a    Will initialize first.
    //         *   @param b    Will initialize second.
    //         */
    //         pair(const T1& a, const T2& b) : first(a), second(b) {};
            
    //         /**
    //         *   Copy constructor, creates a pair with the same member variables.
    //         *
    //         *   @param copy     The pair that will be copied.
    //         */
    //         pair(const pair& copy) : first(copy.first), second(copy.second) {};
            
    //         ~pair() {};
        
    //         /**
    //         *   Assigns a pair to this pair.
    //         *   
    //         *   @param assign   The pair that will be assigned.
    //         */
    //         pair& operator=(const pair& assign)
    //         {
    //             if (this != &assign)
    //             {
    //                 first = assign.first;
    //                 second = assign.second;
    //             }
    //             return (*this);
    //         }


    //         /* ------------------------------------------------------------- */
    //         /* ------------------ PUBLIC MEMBER VARIABLES ------------------ */
            
    //         T1 first;
    //         T2 second;
    // };
        
} // namespace ft

#endif