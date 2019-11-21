#include <iostream>
#include <string>
//#include "rapidxml-1.13/rapidxml.hpp"
//#include "rapidxml-1.13/rapidxml_print.hpp"
//#include "rapidxml_ext.h"
#include "enum_tags.h"
#include "class_XML.h"
#include "parser_xml.h"

using namespace rapidxml;
using namespace std;

XML create_xml;

void read_log_file(string file)
{
    bool flag_child;//флаг для создания дерева
    string log_str, sub_str;// = "SIP/2.0";
    ifstream log_file(file,ios::in);

    if(log_file.is_open())
    {
        //string line = "";
        while(!log_file.eof())
        {
            getline(log_file, log_str);
            int p1, p2, p4;//позиции вхождений подстрок
            int sub_start = INVITE;
            int sub_end = SIP;
            while(sub_start <= sub_end) //поиск тега по возможным значениям
            {
                sub_str = enum_to_str(sub_start);
                p1 = log_str.find("<" + sub_str);
                p4 = log_str.find("<^" + sub_str);
                if(sub_start == SIP) {sub_str = "SIP.2.0";}
                if(p1 >= 0 || p4 >= 0) {break;}
                sub_start++;
            }
            p2 = log_str.find(">|");
            if(p1 >= 0 || p4 >= 0)
            {
                /*---------------------------------------------*/
                flag_child = false;
                create_xml.add_child(flag_child, sub_str.c_str());
                /*---------------------------------------------*/
                //дата
                p1 = log_str.find('@');
                flag_child = true;
                create_xml.add_child(flag_child, "Date", log_str.substr(p1 + 1, 10));
                /*---------------------------------------------*/
                //время
                p1 = log_str.find(' ');
                create_xml.add_child(flag_child, "Time", log_str.substr(p1 + 1, 8));
                /*---------------------------------------------*/
                while(p2 < 0)
                {
                    getline(log_file, log_str);
                    p2 = log_str.find(">|");
                    if(p2 == 0) {break;}
                    int p3 = log_str.find(": ");//позиция вхождения подстроки
                    string value_log;
                    if(p3 < 0)
                    {
                        p3 = log_str.find('=');
                        value_log = log_str.substr(p3 + 1);//значение строки без знака =
                        value_log[value_log.length() - 1] = 0;
                        if(p3 < 0) { continue;}
                    }
                    else
                    {
                        value_log = log_str.substr(p3 + 2);//значение строки без знака : и пробела
                        value_log[value_log.length() - 1] = 0;
                    }
                    //cout << log_str.substr(0, p3) << endl;
                    /*---------------------------------------------*/
                    //flag_child = true;
                    create_xml.add_child(flag_child, log_str.substr(0, p3).c_str(), value_log);
                    /*---------------------------------------------*/
                }

            }
        }
        log_file.close();
    }
    else
    {
        cout << "Log_file doesn't open!" << endl;
    }
}

int main()
{
    string new_xml_file = "SessionManager.xml";
    /*---------------------------------------------*/
    create_xml.open_file(new_xml_file);
    create_xml.add_root();
    /*---------------------------------------------*/
    for(int i=0; i<5; i++)
    {
        string file;
        if(i == 0) {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log";}
        else {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log." + to_string(i);}
        cout << file << endl;
        read_log_file(file);
    }
    /*---------------------------------------------*/
    create_xml.close_file();
    /*---------------------------------------------*/
    pars_xml(new_xml_file);
    /*---------------------------------------------*/
    return 0;
}