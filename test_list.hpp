/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:35:17 by hherin            #+#    #+#             */
/*   Updated: 2021/01/16 15:14:16 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIST_HPP
# define TEST_LIST_HPP

# include <iostream>

template <class T>
void test_list()
{
	T lst;
		
	lst.push_back("salut");
	lst.push_back("cava");
	lst.push_back("bien");

	// lst.push_back(1);
	// lst.push_back(2);
	// lst.push_back(3);

	// for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
	// 	std::cout << *it << "| ";
	// std::cout << std::endl;
	// 	// lst.insert(lst.begin(), 2, "hehe");
	// 	// 	for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
	// 	// std::cout << *it << "| ";
	// {
	// 	T new_lst(5, "yo");
	// 	for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
	// 		std::cout << *it << "| ";
	// 	std::cout << std::endl;
	// }

	// {
	// 	T new_lst(lst.begin(), lst.end());
	// 	for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
	// 		std::cout << *it << "| ";
	// 	std::cout << std::endl;
	// }

	// {
	// 	T new_lst(lst);
	// 	new_lst.pop_back();
	// 	new_lst.pop_front();
	// 	for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
	// 		std::cout << *it << "| ";
	// 	std::cout << std::endl;
	// }
	
	{
		T new_lst = lst;
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		std::cout << std::endl;

		typename T::iterator pos = new_lst.begin();
		pos++; pos++;
		new_lst.insert(pos, 3, "hehe");
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		new_lst.insert(new_lst.begin(), lst.begin(), lst.end());
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		new_lst.erase(lst.begin());
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
		pos = new_lst.begin();
		pos++; pos++; pos++; pos++;

		new_lst.erase(new_lst.begin(), pos);
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
		
		// std::cout << "size main " << new_lst.size() << std::endl;
		
		new_lst.swap(lst);
		
		// std::cout << "size main after swap" << new_lst.size() << std::endl;
		
		
		std::cout << "new lst ";
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;

		std::cout << "lst ";
		for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
		
		// lst.resize()
	}
	
}

#endif