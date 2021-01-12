

#include <iostream>
#include <string>

class Test
{
    public:

        Test() : value() {}
        const int& begin() const {return _value;}
    private:

        int value;
}