//
// Created by ifomenko on 20.11.2019.
//

#ifndef PROJECT_LOGS_CLASS_XML_H
#define PROJECT_LOGS_CLASS_XML_H
#include <iostream>
#include <fstream>
#include "rapidxml_ext.h"

class XML{
private:
    rapidxml::xml_document<> doc;
    rapidxml::xml_node<>* root;
    rapidxml::xml_node<>* child;
    std::ofstream xml_file;
public:
    void open_file(std::string file);
    void add_root();
    void add_child(bool flag_child, std::string name_str, std::string value_str = "");
    void close_file();
};

#endif //PROJECT_LOGS_CLASS_XML_H
