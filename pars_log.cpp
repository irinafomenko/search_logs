//
// Created by ifomenko on 26.11.2019.
//
#include "pars_log.h"

using namespace std;

bool flag_not_found = false;

//ofstream result_logs_file;
string time_start;//начало времени
string time_end;//конец времени
int call_id_length;
ifstream theFile;//файл логов
extern ofstream result_logs_file;//результирующий файл из main.cpp
extern string number_slot;//номер слота из main.cpp
string call_id = "";//call-id инвайта
bool id_invite = false;//флаг для поиска id инвайта


void search_time(string line, int pos_time)
{
    //поиск времени, начиная с 13 поизиции строки. 8 это количество символов времени
    string time = line.substr(pos_time + 12, 8);
    //cout << time << endl;
    if(time_start.length() == 0) {time_start = time_end = time;}
    if(time < time_start) {time_start = time;}
    if(time > time_end) {time_end = time;}
}

void search_slot()//string file)
{
    theFile.seekg(0, ios::beg);
    while(!theFile.eof())
    {
        string line;
        getline(theFile, line);
        int pos_sid = line.find("sipcid:");
        int id = line.find(call_id);
        int pos_cid;
        if(id >= 0 && pos_sid >= 0)//если подстрока sipcid: и call_id инвайта найдено в одной строке, то ищем начало и конец строки с номером слота
        {
            //cout << line << endl;
            pos_sid = line.find("sid:");//начало подстроки с номером слота
            pos_cid = line.find("cid:");//конец подстроки с номером слота
            if(pos_sid >= 0)//если начало найдено
            {
                number_slot = line.substr(pos_sid, pos_cid - pos_sid - 1);//записываем строку, -1 без пробела
                //cout << line << endl;
                result_logs_file << line << endl;//запись строки полностью в файл
                break;
            }
        }
    }
}

void search_call_id(string line)
{
    int pos_call_id = line.find("Call-ID: ");//поиск строки с call-id
    if(pos_call_id >= 0)
    {
        call_id = line.substr(pos_call_id + 9, call_id_length);
        //search_slot();
        id_invite = false;
    }
    //cout << call_id << endl;
}

void write_result(string search_tags, string line)
{
    //cout << endl;
    //cout << search_tags << endl;
    //result_logs_file << value_sub_str << endl;
    //поиск времени
    result_logs_file << search_tags << endl;//запись тега в файл до искомой строки
    int pos_time = search_tags.find("@");
    if(pos_time >= 0) {search_time(search_tags, pos_time);}//поиск вермени звонка (начало и конец)
    //INVITE
    int pos_invite = search_tags.find("INVITE ");
    if(pos_invite >= 0) {id_invite = true;}//если это INVITE, то ищем call-id звонка
    if(id_invite == true) {search_call_id(search_tags);} //поиска call-id до найденной строки

    int pos_sign = line.find(">|");//поиск конца тега
    while(pos_sign < 0)// если не конец тега, то пишем все в файл
    {
        getline(theFile, line);
        //search_time(line);
        result_logs_file << line << endl;
        if(id_invite == true) {search_call_id(line);} //поиск call-id после искомой строки
        pos_sign = line.find(">|");
    }
    if(pos_invite >= 0)
    {
        //запомнить текущую позицию в файле
        int pos_thefile = theFile.tellg();
        search_slot();//поиск слота
        theFile.seekg(pos_thefile, ios::beg);//переходим на текущую позицию файла
    }

    flag_not_found = true;
}

void search_tag(string name_tag, string value_tag)
{
    int pos_name;//позиция в строке имени тега
    int pos_value;//позиция в строке значения тега
    string log_str, search_tags = "", sub_str;
    id_invite = false;//call_id invite не найден

    getline(theFile, log_str);
    int pos_sub_str;//позиции вхождений подстрок для поиска
    int sub_start = INVITE;
    int sub_end = SIP;
    while(sub_start <= sub_end) //поиск тега по возможным значениям
    {
        sub_str = enum_to_str(sub_start);
        if((pos_sub_str = log_str.find("<" + sub_str)) >= 0)//если одна из подстрок найдена, то записываем строку в переменную
        {
            search_tags += log_str;
            //cout << search_tags << endl;
            break;
        }
        else if((pos_sub_str = log_str.find("<^" + sub_str)) >= 0)//если одна из подстрок найдена, то записываем строку в переменную
        {
            search_tags += log_str;
            //cout << search_tags << endl;
            break;
        }
        sub_start++;
    }

    if(pos_sub_str >= 0)//если одна из подстрок найдена (если в предыдущем цикле ничего не найдено, ничего не происходило)
    {
        getline(theFile, log_str);
        search_tags += log_str;
        //cout << search_tags << endl;
        pos_name = log_str.find(name_tag);
        pos_value = log_str.find(value_tag);

        while(pos_name < 0 && pos_value < 0)//запись всех строк после открытого тега <
        {
            //search_tags += add_search_tags();
            //getline(theFile, log_str);
            getline(theFile, log_str);
            search_tags += log_str;
            pos_name = log_str.find(name_tag);
            pos_value = log_str.find(value_tag);
            //поиск длины call_id, чтоб правильно его записать
            int pos_call_id = log_str.find("Call-ID: ");//поиск строки с call-id
            if(pos_call_id >= 0) {call_id_length = log_str.length() - pos_call_id - 10;}
        }
        //cout << log_str.substr(0, pos_name + name_tag.length()) << endl;
        if(pos_name >= 0 && pos_value >= 0) {write_result(search_tags, log_str);}//при совпадении имени тега и его значении записываем в файл

    }

    //cout << search_tags << endl;

}



void open_log(string file, string name_tag, string value_tag)
{
    cout << "Parsing..." << endl;

    theFile.open(file, ios::in);
    if(theFile.is_open())
    {
        while(!theFile.eof())
        {
            search_tag(name_tag, value_tag);
        }
        if(flag_not_found == false) {cout << endl << "Not found!" << endl;}
        theFile.close();
    }
    else
    {
        cout << "Log file doesn't open!" << endl;
    }
    //if(call_id != "") {search_slot(file);}//если call-id найдено, ищем номер слота
    //cout << call_id << endl;
}

string pars_log(string file, string name_tag, string value_tag)
{
    string result_time = "";
    if(result_logs_file.is_open())
    {
        open_log(file, name_tag, value_tag);
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