//
// Created by nova on 22/03/2019.
//

#define BOOST_TEST_MODULE test_variant
#define BOOST_TEST_MAIN
#define BOOST_TEST_STATIC_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <eg/future.hpp>
//using namespace eg;



BOOST_AUTO_TEST_SUITE(test_variant)

    BOOST_AUTO_TEST_CASE(test1) {
        eg::promise<int> p;
        p.get_future().then([](auto a){
            return 0;
        });

        p.set_value(1);
    }




BOOST_AUTO_TEST_SUITE_END()