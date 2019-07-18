


find_package(Boost 1.60 REQUIRED COMPONENTS
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

add_library(eg
        include/eg/future.hpp
        include/eg/task.hpp
        include/eg/type.hpp
        src/future.cpp)
target_include_directories(eg PUBLIC ${JSONCPP_INCLUDE_DIR})



add_subdirectory(tests)