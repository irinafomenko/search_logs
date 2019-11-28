//
// Created by ifomenko on 26.11.2019.
//
#include "pars_txt.h"

using namespace std;

bool flag_not_found_2 = false;

//ofstream result_logs_file;
string time_start;//начало времени
string time_end;
ifstream theFile;
string value_sub_str = "";// поиск значений после SIP/2.0
extern ofstream result_logs_file;
extern string number_sid;//номер слота
string call_id = "";
bool id_invite = false;

void search_time(string line, int pos_time)
{
    //int pos_time = line.find("Time: ");
    string time = line.substr(pos_time + 12, 8);
    //cout << time << endl;
    if(time_start.length() == 0) {time_start = time_end = time;}
    if(time < time_start) {time_start = time;}
    if(time > time_end) {time_end = time;}
}

void search_call_id(string line)
{
    int pos_call_id = line.find("Call-ID: ");
    if(pos_call_id >= 0) {call_id = line.substr(pos_call_id + 9, line.length() - pos_call_id - 10);}
}

void write_result(string search_tags, string line)
{
    //cout << endl;
    //cout << search_tags << endl;
    //result_logs_file << value_sub_str << endl;
    //время
    result_logs_file << search_tags << endl;
    int pos_time = search_tags.find("@");
    if(pos_time >= 0) {search_time(search_tags, pos_time);}
    //INVITE
    int pos_invite = search_tags.find("INVITE");
    if(pos_invite >= 0) {id_invite = true;}
    if(id_invite == true) {search_call_id(search_tags);}

    int pos_sign = line.find(">|");
    while(pos_sign < 0)
    {
        getline(theFile, line);
        //search_time(line);
        result_logs_file << line << endl;
        if(id_invite == true) {search_call_id(line);}
        pos_sign = line.find(">|");
    }
    /*

    */
    //cout << "123" << endl;
    flag_not_found_2 = true;
}

void search_tag(string name_tag, string value_tag)
{
    string log_str, search_tags = "", sub_str;
    id_invite = false;

    getline(theFile, log_str);
    int p1, p4;//позиции вхождений подстрок
    int sub_start = INVITE;
    int sub_end = SIP;
    while(sub_start <= sub_end) //поиск тега по возможным значениям
    {
        sub_str = enum_to_str(sub_start);
        p1 = log_str.find("<" + sub_str);
        p4 = log_str.find("<^" + sub_str);
        if(sub_start == SIP)
        {
            sub_str = "SIP.2.0";
            if(p4 >= 0)
            {
                value_sub_str = log_str.substr(p4 + sub_str.length() + 3);
                value_sub_str[value_sub_str.length() - 1] = 0;
            } //без пробела
            else if(p1 >= 0)
            {
                value_sub_str = log_str.substr(p1 + sub_str.length() + 2);
                value_sub_str[value_sub_str.length() - 1] = 0;
            }
            //cout << value_sub_str << endl;
        }
        if(p1 >= 0 || p4 >= 0)
        {
            search_tags += log_str;
            //cout << search_tags << endl;
            break;
        }
        sub_start++;
    }

    if(p1 >= 0 || p4 >= 0)
    {
        getline(theFile, log_str);
        search_tags += log_str;
        //cout << search_tags << endl;
        int pos_name = log_str.find(name_tag);
        int pos_value = log_str.find(value_tag);
        while(pos_name < 0 && pos_value < 0)
        {
            //search_tags += add_search_tags();
            //getline(theFile, log_str);
            getline(theFile, log_str);
            search_tags += log_str;
            pos_name = log_str.find(name_tag);
            pos_value = log_str.find(value_tag);
        }
        //cout << log_str.substr(0, pos_name + name_tag.length()) << endl;
        if(pos_name >= 0 && pos_value >= 0) {write_result(search_tags, log_str);}
    }

    //cout << search_tags << endl;

}

void search_slot(string file)
{
    theFile.open(file, ios::in);
    if(theFile.is_open())
    {
        //cout << call_id << endl;
        while(!theFile.eof())
        {
            string line;
            getline(theFile, line);
            int pos_sid = line.find("sipcid:");
            int id = line.find(call_id);
            int pos_cid;
            if(id >= 0 && pos_sid >= 0)
            {
                pos_sid = line.find("sid:");
                pos_cid = line.find("cid:");
                if(pos_sid >= 0)
                {
                    number_sid = line.substr(pos_sid, pos_cid - pos_sid - 1);//без пробела
                    //cout << number_sid << endl;
                    result_logs_file << line << endl;
                    break;
                }
            }
        }
        theFile.close();
    }
    else
    {
        cout << "Log file doesn't open!" << endl;
    }
}

void parsing_txt(string file, string name_tag, string value_tag)
{
    cout << "Parsing..." << endl;

    theFile.open(file, ios::in);
    if(theFile.is_open())
    {
        while(!theFile.eof())
        {
            search_tag(name_tag, value_tag);
        }
        if(flag_not_found_2 == false) {cout << endl << "Not found!" << endl;}
        theFile.close();
    }
    else
    {
        cout << "Log file doesn't open!" << endl;
    }
    if(call_id != "") {search_slot(file);}
    //cout << call_id << endl;
}

string pars_txt(string file, string name_tag, string value_tag)
{
    string result_time = "";
    //result_logs_file.open("results_search_logs.txt", ios::out);
    if(result_logs_file.is_open())
    {
        parsing_txt(file, name_tag, value_tag);
        //result_logs_file.close();
        //cout << endl << "start_time: " << time_start << endl;
        //cout << "end_time: " << time_end << endl;
        result_time = time_start + " " + time_end;
    }
    else
    {
        cout << "Output file doesn't open!" << endl;
    }
    return result_time;
}