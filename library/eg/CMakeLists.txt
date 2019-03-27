


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



set(SOURCES_HPP
        include/eg/variant/typename.hpp
        include/eg/reflect/reflect.hpp)

set(SOURCES_CPP
        src/variant/typename.cpp
        )

add_library(eg ${SOURCES_CPP} ${SOURCES_HPP})

target_link_libraries(eg ${JSONCPP_LIBRARY})
target_include_directories(eg PUBLIC ${JSONCPP_INCLUDE_DIR})

message(STATUS "find jsoncpp-lib : ${JSONCPP_INCLUDE_DIR}  --- ${JSONCPP_LIBRARY}")


add_subdirectory(tests)