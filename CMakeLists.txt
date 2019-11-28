cmake_minimum_required(VERSION 3.14)
project(project_logs)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_LIB class_XML.cpp parser_xml.cpp search_calls_in_slots.cpp pars_txt.cpp enum_tags.cpp)
add_library(my_library STATIC ${SOURCE_LIB})

add_executable(project_logs main.cpp rapidxml_ext.h enum_tags class_XML parser_xml search_calls_in_slots pars_txt)