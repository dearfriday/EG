//
// Created by nova on 22/03/2019.
//

#define BOOST_TEST_MODULE test_variant
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>

#include <json/json.h>
#include <eg/reflect/reflect.hpp>
//using namespace eg;

struct base_op {
    uint32_t a;
    int b;
    std::string c;
};


struct test_inherit : base_op {
    int32_t  d;
};

EG_REFLECT(base_op, (a)(b)(c))
EG_INHERIT_REFLECT(test_inherit, (base_op), (d))

struct test_has {
    int32_t  e;
    base_op  pp;
};


EG_REFLECT(test_has, (e)(pp))





BOOST_AUTO_TEST_SUITE(test_variant)

    BOOST_AUTO_TEST_CASE(test1) {
        Json::Value data;
        data["a"] = Json::Value(10);
        data["b"] = Json::Value(22);
        data["c"] = Json::Value("abcdef");
        base_op op;
        eg::reflect<base_op>::from_json(data, op);

        BOOST_CHECK_EQUAL(op.a, 10);
        BOOST_CHECK_EQUAL(op.b, 22);
        BOOST_CHECK_EQUAL(op.c, "abcdef");
    }


    BOOST_AUTO_TEST_CASE(test2) {
        Json::Value data;
        data["a"] = Json::Value(10);
        data["b"] = Json::Value(22);
        data["c"] = Json::Value("abcdef");
        data["d"] = Json::Value(-10);
        test_inherit op;
        eg::reflect<test_inherit>::from_json(data, op);

        BOOST_CHECK_EQUAL(op.a, 10);
        BOOST_CHECK_EQUAL(op.b, 22);
        BOOST_CHECK_EQUAL(op.c, "abcdef");
        BOOST_CHECK_EQUAL(op.d, -10);


    }

    BOOST_AUTO_TEST_CASE(test3) {
        Json::Value data;
        data["a"] = Json::Value(10);
        data["b"] = Json::Value(22);
        data["c"] = Json::Value("abcdef");

        Json::Value vv;
        vv["e"] = Json::Value(15);
        vv["pp"] = data;
        test_has op;
        eg::reflect<test_has>::from_json(vv, op);

        BOOST_CHECK_EQUAL(op.e, 15);
        BOOST_CHECK_EQUAL(op.pp.a, 10);
        BOOST_CHECK_EQUAL(op.pp.b, 22);
        BOOST_CHECK_EQUAL(op.pp.c, "abcdef");
    }



    BOOST_AUTO_TEST_CASE(json_test1) {
        const char *str = "{\"jsonrpc\": \"2.0\",\"method\": \"find\",\"params\": [\"1 \"]}";
        auto readerBuilder = Json::CharReaderBuilder();
        auto sreader = readerBuilder.newCharReader();
        Json::Value root;
        std::string errotStr;
        if (sreader->parse(str, str + strlen(str), &root, &errotStr)) {
            std::string version = root["jsonrpc"].asString();
        }
    }




BOOST_AUTO_TEST_SUITE_END()