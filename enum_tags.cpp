//
// Created by ifomenko on 26.11.2019.
//
#include "enum_tags.h"

myTags str_to_enum(std::string str)
{
    myTags result;
    if(str == "INVITE") {result = INVITE;}
    else if(str == "CANCEL") {result = CANCEL;}
    else if(str == "BYE") {result = BYE;}
    else if(str == "ACK") {result = ACK;}
    else if(str == "PRACK") {result = PRACK;}
    else if(str == "SUBSCRIBE") {result = SUBSCRIBE;}
    else if(str == "NOTIFY") {result = NOTIFY;}
    else if(str == "REFER") {result = REFER;}
    else if(str == "OPTIONS") {result = OPTIONS;}
    else if(str == "INFO") {result = INFO;}
    else if(str == "PUBLISH") {result = PUBLISH;}
    else if(str == "UPDATE") {result = UPDATE;}
    else if(str == "SIP/2.0") {result = SIP;}
    return result;
}

std::string enum_to_str(int enm)
{
    std::string result;
    if(enm == INVITE) {result = "INVITE";}
    else if(enm == CANCEL) {result = "CANCEL";}
    else if(enm == BYE) {result = "BYE";}
    else if(enm == ACK) {result = "ACK";}
    else if(enm == PRACK) {result = "PRACK";}
    else if(enm == SUBSCRIBE) {result = "SUBSCRIBE";}
    else if(enm == NOTIFY) {result = "NOTIFY";}
    else if(enm == REFER) {result = "REFER";}
    else if(enm == OPTIONS) {result = "OPTIONS";}
    else if(enm == INFO) {result = "INFO";}
    else if(enm == PUBLISH) {result = "PUBLISH";}
    else if(enm == UPDATE) {result = "UPDATE";}
    else if(enm == SIP) {result = "SIP/2.0";}
    return result;
}