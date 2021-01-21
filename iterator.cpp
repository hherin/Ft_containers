#include <vector>
#include <iostream>

#include "containers/vector.hpp"
int main(void){
    int             arr1[5] = {1, 2, 3, 4, 5};
    // ft::vector<int> v1(arr1, arr1 + 5);

    // ft::vector<int>::reverse_iterator v1_it = v1.rbegin();
    // ft::vector<int>::reverse_iterator v1_end = v1.rend();

    // ft::vector<int>::iterator v11_it = v1.begin();
    // ft::vector<int>::iterator v11_end = v1.end();

    // v1_end + -2;
    // std::cout << "ft: " << *v1_end << "\n";
    // std::cout << v1_end - v1_it << std::endl;
    // std::cout << v11_end - v11_it << std::endl;

    std::cout << "\n================================================\n";

    std::vector<int> v2(arr1, arr1 + 5);

    std::vector<int>::reverse_iterator v2_it = v2.rbegin();
    std::vector<int>::reverse_iterator v2_end = v2.rend();

    std::vector<int>::iterator v22_it = v2.begin();
    std::vector<int>::iterator v22_end = v2.end();
    
    v2_end - 2;
    std::cout << "std: " << *v2_end << "\n";
    std::cout << v2_end - v2_it << std::endl;
    std::cout << v22_end - v22_it << std::endl;

}