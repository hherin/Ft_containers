/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:35:17 by hherin            #+#    #+#             */
/*   Updated: 2021/01/17 13:01:28 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIST_HPP
# define TEST_LIST_HPP

# include <iostream>

template <class T>
void printlist(T &lst)
{
	for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << "| ";
	std::cout << std::endl << std::endl;
}


template <class T>
void test_list()
{
	T lst;

	lst.push_back("salut");
	// lst.push_back("cava");
	// lst.push_back("bien");

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
		T new_lst(6, "yoyo");
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		// typename T::iterator pos = new_lst.begin();
		// pos++; pos++;
		// new_lst.insert(pos, 3, "hehe");
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;


		// new_lst.insert(new_lst.begin(), lst.begin(), lst.end());

		// std::cout << "avant erase \n";
		// printlist(new_lst);

		// new_lst.erase(new_lst.begin());

		// std::cout << "apres erase \n";
		// printlist(new_lst);
		// pos = new_lst.begin();
		// pos++; pos++; pos++; pos++;

		// new_lst.erase(new_lst.begin(), pos);
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		// std::cout << "size main " << new_lst.size() << std::endl;

		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		// std::cout << "AVANT SWAP size lst =" << lst.size()
		// 		<< " et size new lst = " << new_lst.size() << std::endl;
		// new_lst.swap(lst);

		// std::cout << "size main after swap" << new_lst.size() << std::endl;


		// std::cout << "new lst ";
		// for (typename T::iterator it = new_lst.begin(); it != new_lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << std::endl;

		// std::cout << "lst ";
		// for (typename T::iterator it = lst.begin(); it != lst.end(); it++)
		// 	std::cout << *it << "| ";
		// std::cout << "ON EST ICI size: " << lst.size() << std::endl;
	}

	{
		T new_lst;
		new_lst.push_back("1");
		new_lst.push_back("2");
		new_lst.push_back("3");

		// std::cout << "\n\nnew lst ";
		// printlist(new_lst);

		// std::cout << "lst ";
		// printlist(lst);

		// std::cout << "new lst ";
		// std::cout << "new size " << new_lst.size() << "\n";
		typename T::iterator it(new_lst.begin());
		it++;
		// std::cout << "pos iterateur " << *it << "\n";
		new_lst.splice(it, lst);
		// printlist(new_lst);

	}

}

#endif