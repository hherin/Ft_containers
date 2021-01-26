/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:37:35 by hherin            #+#    #+#             */
/*   Updated: 2021/01/26 17:26:48 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../containers/vector.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "test_vector.hpp"
#include "valueGene.hpp"
#include <string>

std::ofstream stdFile;
std::ofstream ftFile;

void    CreateTestFiles()
{
    stdFile.open("result/std_vector.txt");
    ftFile.open("result/ft_vector.txt");
}

int main(void)
{
    geneClass<char> geneC( {-1, 0, 32, 33, 48,  36, 76, 117, 82, 21, 105, 72, 99, 111, 125, 122, 43, 50, 69, 88} );
    char *arrChar = ;
    CreateTestFiles();
    
    Test_constr<std::vector<int>, 1>();
    Test_constr<std::vector<std::string>, 1>();
    Test_constr<std::vector<char>, 1>();

    Test_constr<ft::vector<int>, 0>();
    Test_constr<ft::vector<std::string>, 0>();
    Test_constr<ft::vector<char>, 0>();


}