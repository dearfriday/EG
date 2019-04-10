//
// Created by nova on 07/04/2019.
//

#pragma once

#include <string>
#include <eg/variant/anyVar.hpp>



namespace eg {

    enum object_type {
        int64_type = 1,
        uint64_type,
        char_type,
        object_type,
        array_type,
        null_type
    };

    struct any_map;


    struct object {
        object();
        object(const object &obj);
        ~object();

        object(uint8_t v);
        object(uint16_t v);
        object(uint32_t v);
        object(uint64_t v);
        object(int8_t v);
        object(int16_t v);
        object(int32_t v);
        object(int64_t v);
        object(char c);
        object(const char *str);
        object(const std::string &str);
        object(const any_map &v);
    private:
        void *rel_value = nullptr;
        enum object_type _type;
    };



}
