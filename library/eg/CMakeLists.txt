
project(eg)


find_package(Boost 1.67 REQUIRED COMPONENTS
        thread
        date_time
        system
        filesystem
        program_options
        signals
        serialization
        chrono
        unit_test_framework
        context
        locale
        iostreams)

#include(CMakeModules/Findjsoncpp.cmake)
find_package(jsoncpp REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES_HPP
        include/eg/variant/typename.hpp
        include/eg/variant/anyVar.hpp
        include/eg/variant/object.hpp
        include/eg/reflect/reflect.hpp

        )

set(SOURCES_CPP
        src/variant/typename.cpp
        src/variant/anyVar.cpp
        src/variant/object.cpp
        )

add_library(eg ${SOURCES_CPP} ${SOURCES_HPP})

target_link_libraries(eg ${JSONCPP_LIBRARY})
target_include_directories(eg PUBLIC ${JSONCPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

message(STATUS "find jsoncpp-lib : ${JSONCPP_INCLUDE_DIR}  --- ${JSONCPP_LIBRARY}")


add_subdirectory(tests)