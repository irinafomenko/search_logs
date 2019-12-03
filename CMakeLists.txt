cmake_minimum_required(VERSION 3.14)
project(project_logs)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_LIB search_calls.cpp pars_log.cpp enum_tags.cpp)
add_library(my_library STATIC ${SOURCE_LIB})

add_executable(project_logs main.cpp enum_tags search_calls pars_log)