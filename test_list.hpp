/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:35:17 by hherin            #+#    #+#             */
/*   Updated: 2021/01/16 13:29:33 by hherin           ###   ########.fr       */
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

	for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << "| ";
	std::cout << std::endl;
		// lst.insert(lst.begin(), 2, "hehe");
		// 	for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
		// std::cout << *it << "| ";
	{
		T new_lst(5, "yo");
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
	}

	{
		T new_lst(lst.begin(), lst.end());
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
	}

	{
		T new_lst(lst);
		new_lst.pop_back();
		new_lst.pop_front();
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
	}
	
	{
		T new_lst = lst;
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
		typename T::iterator pos = new_lst.begin();
		pos++; pos++;
		new_lst.insert(pos, 3, "hehe");
		for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
			std::cout << *it << "| ";
		std::cout << std::endl;
		std::cout << new_lst.back() << std::endl;
	}
	
}

#endif