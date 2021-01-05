/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:14:05 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/05 17:12:36 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <vector>
#include <iostream>
#include "vector.hpp"

int main()
{
	ft::vector<int>base(5,10);
	ft::vector<int>::iterator it = base.begin();
	std::cout << "isEmpty ? " << base.empty() << std::endl;
	std::cout << "Size " << base.size() << std::endl;
	std::cout << "Capacity " << base.capacity() << std::endl;
	std::cout << "Vector base ";
	while (it != base.end()){
		std::cout << *it << " ";
		it++;
	}
	for (unsigned int i = 0; i < 7; i++)
	{
		base.push_back(30);
	}
	std::cout << "Size " << base.size() << std::endl;
	std::cout << "Capacity " << base.capacity() << std::endl;
}