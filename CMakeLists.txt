cmake_minimum_required(VERSION 3.12)
project(Egame)

set(CMAKE_CXX_STANDARD 17)



#find_package(Boost 1.67 REQUIRED COMPONENTS
#        thread
#        date_time
#        system
#        filesystem
#        program_options
#        signals
#        serialization
#        chrono
#        unit_test_framework
#        context
#        locale
#        iostreams)

add_subdirectory(library)
add_subdirectory(test)