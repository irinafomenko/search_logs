//
// Created by ifomenko on 20.11.2019.
//
#include "class_XML.h"

void XML::open_file(std::string file)
{
    xml_file.open(file, std::ios::out);
    //заголовок в файле
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);
}

void XML::add_root()
{
    root = doc.allocate_node(rapidxml::node_element, "SIP");
    doc.append_node(root);
}

void XML::add_child(bool flag_child, std::string name_str, std::string value_str)
{
    char * name = doc.allocate_string(name_str.c_str());
    char * value = doc.allocate_string(value_str.c_str());
    //
    if(flag_child == true)
    {
        rapidxml::xml_node<>* child_child = doc.allocate_node(rapidxml::node_element, name, value);
        child->append_node(child_child);
    } else
    {
        child = doc.allocate_node(rapidxml::node_element, name, value);
        if(name_str == "SIP.2.0") {child->append_attribute(doc.allocate_attribute("type", value));}
        root->append_node(child);
    }
}

void XML::close_file()
{
    xml_file << doc;
    doc.clear();
    xml_file.close();
}
