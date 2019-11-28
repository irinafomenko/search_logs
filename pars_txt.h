//
// Created by ifomenko on 26.11.2019.
//

#ifndef PROJECT_LOGS_PARS_TXT_H
#define PROJECT_LOGS_PARS_TXT_H

#include <iostream>
#include <fstream>
#include "enum_tags.h"

std::string pars_txt(std::string file, std::string name_tag, std::string value_tag);
void parsing_txt(std::string file, std::string name_tag, std::string value_tag);
void search_tag(std::string name_tag, std::string value_tag);
void search_slot(std::string file);
void write_result(std::string search_tags, std::string line);
void search_time(std::string line, int pos_time);

#endif //PROJECT_LOGS_PARS_TXT_H
