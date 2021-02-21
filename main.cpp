/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/02/19 16:12:51 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "containers/map.hpp"
#include <map>
#include "utils/ABR/AVLtree.hpp"
#include "utils/ABR/utilsTree.hpp"


int main(void)
{
	// ft::map<int,int> m0;

	// ft::pair<ft::map<int, int>::iterator, bool> ret = m0.insert(ft::pair<int, int>(1, 1));
	// for(int i = 2; i < 11; i++)
	// 	ret = m0.insert(ft::pair<int, int>(i, 1));
	// // ret = m0.insert(ft::pair<int, int>(3, 1));
	// // ret = m0.insert(ft::pair<int, int>(4, 1));
	// std::cout << "main sie " << m0.size() << "\n";
	// ft::map<int, int>::iterator beg = m0.begin(); beg++;
	// ft::map<int, int>::iterator en = m0.end(); en--;
	// ft::map<int,int> m1(beg, en);
	
	// std::cout << "main sie " << m1.size() << "\n";
	// std::cout << (ret.second) << "\n";
	// m0.clear();

	{
		// s_abr<int, int> *root;
		// insertNewNode(&root, ft::pair<int, int>(1,1));
		// insertNewNode(&root, ft::pair<int, int>(2,1));
		// insertNewNode(&root, ft::pair<int, int>(13,1));
		// insertNewNode(&root, ft::pair<int, int>(4,1));
		// printTree(root);
		{
			std::cout << "\n====================HOME================\n";
			ft::pair<int, std::string>pa1(58966, "hello coco");
			ft::pair<int, std::string>pa2(2147483647, "j'arrive");
			ft::pair<int, std::string>pa3(12, "j'12");
			ft::map<int, std::string> x;
			std::cout << x.end().getCurrent() << "\n\n";
			x.insert(pa1);
			x.insert(pa2);
			x.insert(x.end(), pa3);
			// ft::map<int, std::string>::iterator it = x.begin();
			
			for (ft::map<int, std::string>::iterator it = x.begin(); it != x.end(); it++)
				std::cout << (*it).first << "\n";
			for (ft::map<int, std::string>::iterator it = x.end(); it != x.begin(); ){
			it++;
			std::cout << (*it).first << "\n";
			}
		}

		// x.insert(x.begin(), ft::pair<int, std::string>(535, "jojo"));
		{
		std::cout << "\n=======================STL====================\n";
		std::pair<int, std::string>pa1(58966, "hello coco");
		std::pair<int, std::string>pa2(2147483647, "j'arrive");
		std::pair<int, std::string>pa3(12, "j'12");
		std::map<int, std::string> x;
		x.insert(pa1);
		x.insert(pa2);
		x.insert(x.end(), pa3);
		
		for (std::map<int, std::string>::iterator it = x.begin(); it != x.end(); it++)
			std::cout << (*it).first << "\n";
		for (std::map<int, std::string>::iterator it = x.end(); it != x.begin(); ){
			it++;
			std::cout << (*it).first << "\n";
		}
		}
	}
}
