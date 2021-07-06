//
// Created by ifomenko on 26.11.2019.
//

#ifndef PROJECT_LOGS_PARS_LOG_H
#define PROJECT_LOGS_PARS_LOG_H

#include <iostream>
#include <fstream>
#include "enum_tags.h"

std::string pars_log(std::string file, std::string name_tag, std::string value_tag);
void open_log(std::string file, std::string name_tag, std::string value_tag);
void search_tag(std::string name_tag, std::string value_tag);
void search_slot();
void write_result(std::string search_tags, std::string line);
void search_time(std::string line, int pos_time);
void search_call_id(std::string line);

#endif //PROJECT_LOGS_PARS_LOG_H
