add_executable(test_variant test_variant.cpp )
target_link_libraries( test_variant  ${Boost_LIBRARIES} eg)
target_include_directories(test_variant
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${Boost_INCLUDE_DIRS}
        )