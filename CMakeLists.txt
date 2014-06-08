cmake_minimum_required(VERSION 2.8)

project(SET)

include_directories(${SET_SOURCE_DIR})

add_executable(set_testing
               set.cpp
	       set.hpp
	       iterator.cpp
	       node.hpp
	       node.cpp
	       set_testing.cpp
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++11 -pedantic")
endif()
 
target_link_libraries(set_testing -lpthread)
