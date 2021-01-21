/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:35:17 by hherin            #+#    #+#             */
/*   Updated: 2021/01/19 15:40:51 by hherin           ###   ########.fr       */
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
	std::cout << std::endl;
}

class predicate
{
	public:
	predicate(){}
	// predicate(predicate const& d) {}
	~predicate(){}
	bool operator()(std::string s, std::string s2){ return (s2 == s);}
};

bool is_splce(std::string i)
{
	std::string s("1");
	return (i == s);
}
class hehe
{
    public :
    hehe(){std::cout << "const called\n";}
	hehe(const hehe&){std::cout << "copy called\n";}
    ~hehe(){std::cout << "dest called\n";}
hehe& operator=(const hehe& ){std::cout << "assign called\n"; return *this;}
};

template <class T>
void test_list()
{
	
	T lst;
	hehe J;
	std::cout << "PUSHBACK\n";
	lst.push_back(J);
	// lst.push_back(4);
	// lst.push_back(6);
	// lst.push_back(8);
	// lst.push_back(10);

	// T new_lst;
	// new_lst.push_back(5);
	// new_lst.push_back(1);
	// new_lst.push_back(7);
	// new_lst.push_back(3);
	// new_lst.push_back(9);
	// new_lst.push_back(0);
	// // predicate pred;
	// // lst.unique(pred);
	// // lst.merge(new_lst);
	
	// new_lst.swap(lst);
	// std::cout << "lst ";
	// printlist(lst);
	// std::cout << "newlst ";
	// printlist(new_lst);
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
		// T new_lst(6, "yoyo");
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

	
		// T new_lst;
		// new_lst.push_back("1");
		// new_lst.push_back("2");
		// new_lst.push_back("3");

		// std::cout << "\n\nnew lst ";
		// printlist(new_lst);

		// std::cout << "lst ";
		// printlist(lst);

		// std::cout << "new lst ";
		// std::cout << "new size " << new_lst.size() << "\n";
		// typename T::iterator it(new_lst.begin());
		// it++;
		
		// std::cout << "first splice all list\n";
		// new_lst.splice(it, lst);
		// printlist(new_lst);
		// printlist(lst);
		// lst.push_back("hey");
		// lst.push_back("lol");
		// typename T::iterator it2(lst.begin());

		// std::cout << "second splice 1 link\n";
		// new_lst.splice(it, lst, it2);
		// printlist(new_lst);
		// printlist(lst);
		// lst.push_back("splce1");
		// lst.push_back("splce2");
		// lst.push_back("splce3");
		// lst.push_back("splce4");
		// std::cout << "\nthird splice\n";
		// it--; it--;
		// new_lst.splice(it, lst, lst.begin(), lst.end());
		// printlist(new_lst);
		// printlist(lst);
	
		// std::cout << "\nREMOVE\n";
		// new_lst.remove("salut");
		// printlist(new_lst);

		// std::cout << "\n REMOVE if\n";
		// predicate pred("splce2");
		// new_lst.template remove_if<predicate>(pred);
		// printlist(new_lst);

}

#endif