//
// Created by fri on 2019/3/25.
//

#pragma once


#include <cstdint>
#include <string>
#include <map>
#include <json/value.h>

#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/stringize.hpp>


namespace eg {


    template<typename T>
    struct reflect;

    template<typename T>
    struct jsonValue {
        static T get_value(const Json::Value &v) {
            T t;
            reflect<T>::from_json(v, t);
            return t;
        }
    };

    template<>
    struct jsonValue<int8_t> {
        static int8_t get_value(const Json::Value &v) { return (int8_t) v.asInt(); }
    };

    template<>
    struct jsonValue<int16_t> {
        static int16_t get_value(const Json::Value &v) { return (int16_t) v.asInt(); }
    };

    template<>
    struct jsonValue<int32_t> {
        static int32_t get_value(const Json::Value &v) { return v.asInt(); }
    };

    template<>
    struct jsonValue<int64_t> {
        static int64_t get_value(const Json::Value &v) { return v.asInt64(); }
    };


    template<>
    struct jsonValue<uint8_t> {
        static uint8_t get_value(const Json::Value &v) { return (uint8_t) v.asUInt(); }
    };

    template<>
    struct jsonValue<uint16_t> {
        static uint16_t get_value(const Json::Value &v) { return (uint16_t) v.asUInt(); }
    };

    template<>
    struct jsonValue<uint32_t> {
        static uint32_t get_value(const Json::Value &v) {
            return v.asUInt();
        }
    };

    template<>
    struct jsonValue<uint64_t> {
        static uint64_t get_value(const Json::Value &v) { return v.asUInt64(); }
    };

    template<>
    struct jsonValue<std::string> {
        static std::string get_value(const Json::Value &v) { return v.asString(); }
    };

    template<typename T>
    struct jsonValue<std::vector<T>> {
        static std::vector<T> get_value(const Json::Value &v) {
            std::vector<T> data;
            for(auto i = 0; i < v.size(); i++){
                data.push_back(jsonValue<T>::get_value(v[i]));
            }
            return data;
        }
    };


    template<typename T>
    void to_variant(const Json::Value &v, T &t) {
        reflect<T>::from_json(v, t);
    }

    template<typename T>
    void to_variant(const std::string &json, T &t){
        auto readerBuilder = Json::CharReaderBuilder();
        auto sreader = readerBuilder.newCharReader();
        Json::Value root;
        std::string errotStr;
        if (sreader->parse(json.c_str(), json.c_str() + json.size(), &root, &errotStr)) {
            to_variant(root, t);
        }
        else{
            std::cout << "TODO throw exception.\n";
        }
    }

}


#define EG_SET_VALUE(r, data, elem) \
    c.elem = jsonValue<decltype(data::elem)>::get_value(v[BOOST_PP_STRINGIZE(elem)]);

#define EG_SET_INHERIT_VALUE(r, data, elem) \
    to_variant<elem>(data, c);

#define EG_INHERIT_REFLECT(CLASS, INHERITS, MEMBERS) \
namespace eg{\
template<>\
    struct reflect<CLASS>{  \
        static void from_json(const Json::Value &v, CLASS &c){\
               BOOST_PP_SEQ_FOR_EACH(EG_SET_VALUE, CLASS, MEMBERS)\
               BOOST_PP_SEQ_FOR_EACH(EG_SET_INHERIT_VALUE, v, INHERITS)\
        }\
    };\
}

#define EG_REFLECT(CLASS, MEMBERS) \
    EG_INHERIT_REFLECT(CLASS, BOOST_PP_SEQ_NIL, MEMBERS)





