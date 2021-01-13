/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/01/13 17:07:04 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
# include "containers/list.hpp"


int main(void)
{
    std::list<std::string> llist;
    
    llist.push_back(("salut"));
    llist.push_back(("cava"));
    llist.push_back(("bien"));
    std::list<std::string>::iterator it = llist.end();
    std::cout << *reinterpret_cast<size_t*>(&(*it)) << std::endl;

    ft::list<int> ll(3, 5);
    for (ft::list<int>::iterator it = ll.begin(); it != ll.end(); it++)
        std::cout << *it << "| ";
    std::cout << "\n"
    std::cout << ll.size() << std::endl;
}