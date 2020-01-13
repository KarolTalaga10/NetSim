cmake_minimum_required(VERSION 3.13)
project(NetSim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp
        #src/factory.cpp
        )


add_executable(main__debug ${SOURCE_FILES} main.cpp)

# == Unit testing using Google Testing Framework ==

set(SOURCES_FILES_TESTS
        #test/package_test.cpp
        #test/storage_tests.cpp
        #test/nodes_tests.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
        #test/test_Factory.cpp
        #test/test_factory_io.cpp
        )

add_executable(sol__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
target_compile_definitions(sol__test PUBLIC EXERCISE_ID=EXERCISE_ID_NODES)
target_include_directories(sol__test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        )

add_subdirectory(googletest-master googletest-master)

target_link_libraries(sol__test gmock)

