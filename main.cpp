#include <iostream>
#include <string>
#include "pars_txt.h"
#include "class_XML.h"
#include "parser_xml.h"
#include "search_calls_in_slots.h"


using namespace rapidxml;
using namespace std;

XML create_xml;
//ofstream res_file("SessionManager.txt",ios::out);//попытка без xml
ofstream result_logs_file("results_search_logs.txt", ios::out);
string number_sid;//номер слота

int main()
{
    string new_xml_file = "SessionManager.xml";
    string time;
    string name_tag, value_tag;
    cout << "Enter name tag: ";
    getline(cin, name_tag);
    cout << "Enter value tag: ";
    getline(cin, value_tag);

    for(int i=0; i<5; i++)
    {
        string file;
        if(i == 0) {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log";}
        else {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log." + to_string(i);}
        cout << file << endl;
        //read_log_file(file);
        time = pars_txt(file, name_tag, value_tag);
        if(!number_sid.empty()) {break;}
    }
    cout << "Start time and end time: ";
    cout << time << endl;
    //cout << number_sid << endl;
    result_logs_file.close();
    /*---------------------------------------------*/
    //номер слота
    //number_sid = number_sid.substr(number_sid.find('-') + 15);
    char *s = new char[number_sid.size() + 1];
    strcpy(s, number_sid.c_str());
    char *p = strtok(s,"-");
    while (p != NULL)
    {
        number_sid = p;
        p = strtok(NULL, "-");
    }
    //cout << number_sid << endl;
    /*---------------------------------------------*/
    search_calls(time, number_sid);
    /*---------------------------------------------*/
    return 0;
}