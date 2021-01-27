/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/01/27 15:29:48 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "containers/list.hpp"
#include"containers/stack.hpp"
#include"containers/vector.hpp"
#include <vector>
#include <stack>

class hehe;

void printVector(ft::vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " | ";
    std::cout << "\n";
}

void printVector(std::vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " | ";
    std::cout << "\n";
}

int main(void)
{
    std::cout << "FT CONTAINER\n";
    // ft::vector<int> v0;

    std::vector<int> v1;
    for (int i = 0; i < 4; i++)
        v1.push_back(i + 10);
    v1.erase(v1.begin(), v1.begin());
    printVector(v1);
}