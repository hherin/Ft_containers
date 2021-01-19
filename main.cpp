/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/01/19 17:24:19 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "containers/list.hpp"
#include "test_list.hpp"
#include"containers/stack.hpp"
#include"containers/vector.hpp"
#include <vector>
#include <stack>

class hehe;


int main(void)
{
    std::vector<int> v0 (5, 3);
    std::stack<int, std::vector<int> > s0(v0);
    
    std::cout << "stack size " << s0.size() << "\n Push\n";
    s0.push(7);
    std::cout << "stack size " << s0.size() << "\n";
    std::cout << "TOP " << s0.top() << "\n";

    std::cout <<"\n\n";
    ft::vector<int> v1 (5, 3);
    ft::stack<int, ft::vector<int> > s1(v1);
    
    std::cout << "stack size " << s1.size() << "\n Push\n";
    s1.push(7);
    std::cout << "stack size " << s1.size() << "\n";
    std::cout << "TOP " << s1.top() << "\n";
    // std::list<int> ls;
    
    // test_list<std::list<hehe> >();
    // std::cout << std::endl;
    // test_list<ft::list<hehe> >();
}