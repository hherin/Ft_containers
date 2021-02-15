/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/02/15 16:18:34 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
// #include "containers/map.hpp"
#include <map>
#include "utils/ABR/AVLtree.hpp"


int main(void)
{
	// std::map<int, std::string> mp0;
	// mp0.insert(std::pair<int, std::string>(20, "salut"));
	// mp0.insert(std::pair<int, std::string>(8, "cava"));
	// mp0.insert(std::pair<int, std::string>(12, "heyyo"));
	// mp0.insert(std::pair<int, std::string>(2, "bibibibi"));
	
	// std::map<int, std::string>::iterator b=mp0.begin();
	
	// std::cout << "iterator " << b->first << "\n";
	char c[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	s_abr<char, int> *a = createNewTree<char, int>(c[0], 2, NULL, NULL, NULL);
	// std::cout << "empty? " << empty<char>(a) << std::endl;
	insertNewNode<char, int>(&a, c[1], 2);  // 'b'
	insertNewNode(&a, c[2], 2);  // 'c'
	insertNewNode(&a, c[3], 2);  // 'd'
	insertNewNode(&a, c[4], 2);  // 'e'
	// insertNewNode(&a, c[5], 2);  // 'f'
	// insertNewNode(&a, c[6], 2);  // 'g'
	// insertNewNode(&a, c[7], 2);  // 'h'
	// insertNewNode(&a, c[8], 2);  // 'i'

	
	// std::cout << "PARENT MAIN " << a->left->left->parent->key << "\n";
	// std::cout << "empty? " << empty<char>(a) << std::endl;
	// std::cout << "HEIGHT " << getHeightTree<char>(a) <<std::endl;
	printTree(a);
	deleteNode<char>(&a, 'a');
	// std::cout << "RACINE " << a->p.first << "\n";
	// deleteNode<char>(&a, 'c');
	// deleteNode<char>(&a, 'b');

	std::cout << "\n===================================\n";
	// deleteNode<char>(&a, 'f');
	std::cout << "IN MAIN \n";
	// printTree(a);

}
