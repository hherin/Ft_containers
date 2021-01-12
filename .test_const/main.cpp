/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                 cl                                   +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                  clu                              +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 1<4:00:12 by hherin            #+#    #+#             */
/*   Updated: 2021/01/08 14:00:15 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Test
{
    public:

        Test(int *n) : value(n) {}
        const int& begin() const {return *value;}
    private:

        const int* value;
};

const int* func(int *n)
{
    return n;
}

const int& func2(int *n)
{
    return *n;
}

int& func3(int *n)
{
    return *n;
}


int main()
{
    int nb = 1;
    Test test(&nb);

    int t;

    t = test.begin();
    t = 5;
    std::cout << t << "\n";

   int *ok = 0;

   *ok = *func(&nb);
    // ok = 5;

    int &testi = func2(&nb);

    testi = func2(&nb);
    return (0);
}