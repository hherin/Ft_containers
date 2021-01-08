/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:14:05 by heleneherin       #+#    #+#             */
/*   Updated: 2021/01/08 13:14:53 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include <vector>
#include <iostream>
#include "vector.hpp"
#include <cstring>
#include <cstdlib>
#include <iterator>

int main()
{
	std::cout << "============= BASE VECTOR ================\n";
	ft::vector<int>base(0);
	std::cout << "\nSize: " << base.size() << "\t";
	std::cout << "Capacity: " << base.capacity() << std::endl;
	for (unsigned int i = 0; i < 10; i++)
		base.push_back(i);
	
	std::cout << "Vector base ";
	ft::vector<int>::iterator it = base.begin();
	while (it != base.end()){
		std::cout << *it << " ";
		it++;
	}
	std::cout << "\nSize: " << base.size() << "\t";
	std::cout << "Capacity: " << base.capacity() << std::endl;

	// std::cout << "\n============= COPY CONSTR ================\n";
	// ft::vector<int>vec2(base);
	// ft::vector<int>::iterator it2 = vec2.begin();
	// std::cout << "Vector vec2 ";
	// while (it2 != vec2.end()){
	// 	std::cout << *it2 << " ";
	// 	it2++;
	// }
	// std::cout << "\nSize: " << vec2.size() << "\t";
	// std::cout << "Capacity: " << vec2.capacity() << std::endl;
	// for (unsigned int i = 0; i < 7; i++)
	// 	vec2.push_back(30);
	// std::cout << "newVector ";
	// it2 = vec2.begin();
	// while (it2 != vec2.end()){
	// 	std::cout << *it2 << " ";
	// 	it2++;
	// }
	//std::cout << "\nnewSize: " << vec2.size() << "\t";
	// std::cout << "newCapacity: " << vec2.capacity() << std::endl;

	
	// std::cout << "\n============= OPERATOR= ================\n";
	// ft::vector<int>vec1;
	// vec1 = base;
	// ft::vector<int>::iterator it1 = vec1.begin();
	// std::cout << "Vector vec1 ";
	// while (it1 != vec1.end()){
	// 	std::cout << *it1 << " ";
	// 	it1++;
	// }
	// std::cout << "\nSize: " << vec1.size() << "\t";
	// std::cout << "Capacity: " << vec1.capacity() << std::endl;
	// for (unsigned int i = 0; i < 7; i++)
	// 	vec1.push_back(30);
	// std::cout << "newVector ";
	// it1 = vec1.begin();
	// while (it1 != vec1.end()){
	// 	std::cout << *it1 << " ";
	// 	it1++;
	// }
	// std::cout << "\nnewSize: " << vec1.size() << "\t";
	// std::cout << "newCapacity: " << vec1.capacity() << std::endl;

	std::cout << "\n==============ITERATORS OVERLOAD==========\n";
	it = base.begin();
	int nb = 2;
	std::cout << *(it + nb) << std::endl;

	// std::cout << "\n============= DESTRUCTORS=============\n";
	//check les leaks a revoir
// {
// 	char* str = strdup("salut");
// 	std::cout << str;
	
// 	int* tab = new int[4];
// 	tab[0] = 0;
// }
// {	ft::vector<char*> jo(10);
// 	jo.push_back(strdup("salut"));
// 	jo.push_back(strdup("ca va"));}
// 	system("leaks container");
}