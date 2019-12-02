//
// Created by ifomenko on 26.11.2019.
//

#ifndef PROJECT_LOGS_SEARCH_CALLS_H
#define PROJECT_LOGS_SEARCH_CALLS_H

#include <iostream>
#include <fstream>
#include <iomanip>

int search_calls(std::string time, std::string number_slot);
void write_file(std::string slot);
void open_slots(std::string number_slot);
void open_cxi_slots(std::string number_slot);
void open_vb_slots(std::string number_slot);
void open_end_point_mgr(std::string number_slot);

#endif //PROJECT_LOGS_SEARCH_CALLS_H
