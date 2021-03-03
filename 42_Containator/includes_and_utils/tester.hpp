/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:27:13 by llefranc          #+#    #+#             */
/*   Updated: 2021/03/03 11:42:35 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

// Include the containers to test
#include "../../containers/vector.hpp"
#include "../../containers/list.hpp"
# include "../../containers/stack.hpp"
# include "../../containers/queue.hpp"
# include "../../containers/map.hpp"

// Needed for testing
#include "stl_like.hpp"
#include "utils.hpp"
#include "print_type.hpp"

void    testVector(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testList(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testStack(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testQueue(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testMap(const int (&arrInt)[20], const std::string (&arrString)[20]);

#endif