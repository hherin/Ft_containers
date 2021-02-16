/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 14:28:27 by hherin            #+#    #+#             */
/*   Updated: 2021/02/16 15:29:25 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>
#include "containers/map.hpp"
#include <map>
// #include "utils/ABR/AVLtree.hpp"


int main(void)
{
	ft::map<int,int> m0;

	ft::pair<ft::map<int, int>::iterator, bool> ret = m0.insert(ft::pair<int, int>(1, 1));
}
