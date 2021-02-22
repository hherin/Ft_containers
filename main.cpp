/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/02/22 16:37:13 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "containers/map.hpp"
#include <map>
// #include "utils/ABR/AVLtree.hpp"
// #include "utils/ABR/utilsTree.hpp"


int main(void)
{
	{
		{
			std::cout << "\n====================HOME================\n";
			ft::pair<int, std::string>pa1(58966, "hello coco");
			ft::pair<int, std::string>pa2(2147483647, "j'arrive");
			ft::pair<int, std::string>pa3(12, "DHGF");
			ft::pair<int, std::string>pa4(354, "THRGB");
			ft::pair<int, std::string>pa5(543, "HGD");
			ft::pair<int, std::string>pa6(463, "TGHTR");
			ft::pair<int, std::string>pa7(34, "RTHY");
			ft::map<int, std::string> x;
			std::cout << x.end().getCurrent() << "\n\n";
			x.insert(pa1);
			x.insert(pa2);
			x.insert(pa3);
			x.insert(pa4);
			x.insert(pa5);
			x.insert(pa6);
			x.insert(pa7);
			// x.printMap();
			// x.insert(x.end(), pa3);
			// ft::map<int, std::string>::iterator it = x.begin();
			
			// for (ft::map<int, std::string>::iterator it = x.begin(); it != x.end(); it++)
			// 	std::cout << (*it).first << "\n";
			
			// std::cout << "next\n";
			
			// for (ft::map<int, std::string>::iterator it = x.end(); it == x.begin(); ){
			// 	it--;
			// 	std::cout << (*it).first << "\n";
			// }
		}

		// x.insert(x.begin(), ft::pair<int, std::string>(535, "jojo"));
		{
		std::cout << "\n=======================STL====================\n";
		std::pair<int, std::string>pa1(58966, "hello coco");
		std::pair<int, std::string>pa2(2147483647, "j'arrive");
		std::pair<int, std::string>pa3(12, "j'12");
		std::pair<int, std::string>pa4(354, "THRGB");
		std::pair<int, std::string>pa5(543, "HGD");
		std::pair<int, std::string>pa6(463, "TGHTR");
		std::pair<int, std::string>pa7(34, "RTHY");
		std::map<int, std::string> x;
		x.insert(pa1);
		x.insert(pa2);
		x.insert(pa3);
		x.insert(pa4);
		x.insert(pa5);
		x.insert(pa6);
		x.insert(pa7);
		// x.insert(x.end(), pa3);
		
		for (std::map<int, std::string>::iterator it = x.begin(); it != x.end(); it++)
			std::cout << (*it).first << "\n";
		std::cout << "next\n";
		for (std::map<int, std::string>::iterator it = x.end(); it == x.begin(); ){
			it--;
			std::cout << (*it).first << "\n";
		}
		}
	}
}
