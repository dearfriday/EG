//
// Created by nova on 07/04/2019.
//

#pragma once


#include <string>
#include <eg/variant/object.hpp>





namespace eg {


    struct object;


    struct any_map {
        any_map(const std::string &key, const object &obj);
    private:
        std::string key;
        std::shared_ptr<object>      value;
    };








}
