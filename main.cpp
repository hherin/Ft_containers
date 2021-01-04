#include <iterator>
#include <vector>
#include <iostream>

int Foo()
{
	std::cout 
}

int main()
{
    int my_arr[100] = {0};
    std::vector<int, PreAllocator<int> > my_vec(PreAllocator<int>(&my_arr[0], 100));
    my_vec.push_back(1024);
    std::cout<<"My_Vec[0]: "<<my_vec[0]<<"\n";
    std::cout<<"My_Arr[0]: "<<my_arr[0]<<"\n";

    int* my_heap_ptr = new int[100]();
    std::vector<int, PreAllocator<int> > my_heap_vec(PreAllocator<int>(&my_heap_ptr[0], 100));
    my_heap_vec.push_back(1024);
    std::cout<<"My_Heap_Vec[0]: "<<my_heap_vec[0]<<"\n";
    std::cout<<"My_Heap_Ptr[0]: "<<my_heap_ptr[0]<<"\n";

    delete[] my_heap_ptr;
    my_heap_ptr = NULL;
}