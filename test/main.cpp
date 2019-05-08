#include <stdlib.h>
#include <iostream>
using namespace std;

struct test
{
    int m_i;
    test( int i ) : m_i(i){}
    test()
    {
        test(1);
    }
};



template <typename T, bool>
struct get_size;

template <typename T>
struct get_size<T, false>{
    union any{
        any(){}
        ~any(){}
        T t;
    } _value;
};


template <typename T>
struct get_size<T, true> : private T{

};


typedef  get_size<test, true>   true_size;
typedef  get_size<test, false>  true_size2;



int main()
{
    std::cout << sizeof(true_size) << std::endl;
    std::cout << sizeof(true_size2) << std::endl;

    return 0;
}