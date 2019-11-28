//
// Created by ifomenko on 20.11.2019.
//

#ifndef PROJECT_LOGS_ENUM_TAGS_H
#define PROJECT_LOGS_ENUM_TAGS_H
#include <iostream>

enum myTags
{
    INVITE,
    CANCEL,
    BYE,
    ACK,
    PRACK,
    SUBSCRIBE,
    NOTIFY,
    REFER,
    OPTIONS,
    INFO,
    PUBLISH,
    UPDATE,
    SIP
};

myTags str_to_enum(std::string str);
std::string enum_to_str(int enm);
#endif //PROJECT_LOGS_ENUM_TAGS_H
