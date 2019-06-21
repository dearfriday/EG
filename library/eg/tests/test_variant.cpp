//
// Created by nova on 22/03/2019.
//
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test_variant
#define BOOST_TEST_MAIN
//#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <eg/future.hpp>
#include <tuple>
//using namespace eg;


//
BOOST_AUTO_TEST_SUITE(test_variant)

    BOOST_AUTO_TEST_CASE(test1) {
        eg::promise<int> p;

        p.get_future().then([](auto &&a) -> int{
            std::cout << std::get<0>(a) << std::endl;
//            std::cout << a << std::endl;
            std::cout << "xxx\n";
            return 0;
        }).then([](auto &&a) ->int{
            std::cout << std::get<0>(a) << std::endl;
            std::cout << "yyyy\n";
            return 1;
        });

        p.set_value(1);
    }




BOOST_AUTO_TEST_SUITE_END()