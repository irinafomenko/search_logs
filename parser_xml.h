//
// Created by ifomenko on 21.11.2019.
//

#ifndef PROJECT_LOGS_PARSER_XML_H
#define PROJECT_LOGS_PARSER_XML_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
//#include <curl/curl.h>
//#include <queue>

void print_node(rapidxml::xml_node<> * node);
void print_result(rapidxml::xml_node<> * node);
void search_tag(rapidxml::xml_node<> * root_node, std::string name_tag = "", std::string value_tag = "");
void parsing_xml();
int pars_xml(std::string file);

#endif //PROJECT_LOGS_PARSER_XML_H
