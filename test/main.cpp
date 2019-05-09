#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <functional>
using namespace std;

//template <typename R, typename T>
//struct tuple_to_function;

//template <typename R, typename T>
struct tuple_to_function{

    template <typename TU, std::size_t t>
    struct call{
        template <typename Func>
        static void exe(size_t all_size, Func f, TU tup){
            call<TU, t - 1>::exe(all_size, f, tup, std::get<t - 1>(tup));
        }

        template <typename Func, typename ...ARGS>
        static void exe(Func f, TU tup, ARGS ...args){
            call<TU, t-1>::exe(f, tup, std::get< t - 1>(tup), args...);
        }
    };


    template <typename TU>
    struct call<TU, 0>{

        template <typename Func, typename ...ARGS>
        static void exe(Func f, TU tup, ARGS ...args){
            f(args...);
        }
    };

    template <typename R, typename T>
    void go(T t, R r){
        call<T, std::tuple_size<decltype(t)>::value>::exe(r, t);
    }

};


int main()
{

    tuple_to_function test;

    auto r = std::tuple<int, int, int>(1, 2, 3);
    test.go(r, [](int a, int b, int c) -> int{
        std::cout << "a " << a << std::endl;
        std::cout << "b " << b << std::endl;
        std::cout << "c " << c << std::endl;
        return 1;
    });






    return 0;
}