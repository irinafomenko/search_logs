#include "search_calls.h"

using namespace std;

string start_t;
string end_t;
string prev_slot = "0";//для проверки
extern string path;
bool flag_find;

void write_file(string slot, string file, ofstream &result_file)
{
    ifstream slot_file(file,ios::in);

    string slot_str;
    if(slot_file.is_open())
    {
        while(!slot_file.eof())
        {
            if(prev_slot == slot) {break;}
            getline(slot_file, slot_str);
            //р1 - начало времени
            //р2 - конец времени
            int p1, p2 = -1;//позиции вхождений подстрок
            p1 = slot_str.find(start_t);
            if(p1 >= 0)//начало времени найдено, записываем все, пока не найден конец времени
            {
                result_file << "SessionSlot-" + slot << endl;
                result_file << slot_str << endl;
                while(p2 < 0)//записываем все, пока не найден конец времени
                {
                    getline(slot_file, slot_str);
                    string time = slot_str.substr(12, 8);
                    p2 = slot_str.find(end_t);
                    if((p2 < 0 && (start_t == end_t)) || (p2 < 0 && time > end_t)) {cout << slot_str << endl; break;}//если начальное и конечное время равны и в строке нет end_t, то выходим...иначе, все записывает в файл
                    result_file << slot_str << endl;
                }
                while(p2 >= 0)//запись строк до последнего равного времени (есть строки с одинаковым временем, что их тоже записать)
                {
                    getline(slot_file, slot_str);
                    p2 = slot_str.find(end_t);
                    //в файле VB есть строка между нужными строками без времени
                    //поэтому если нужного времени нет, то проверяем следующиую строку
                    if(p2 < 0)
                    {
                        string prev_str = slot_str;
                        getline(slot_file, slot_str);
                        p2 = slot_str.find(end_t);
                        if(p2 < 0) {break;}//если в следующей строке тоже нет, то выходим из цикла, если есть, то продолжаем писать
                        result_file << prev_str << endl;
                    }
                    result_file << slot_str << endl;
                }
                result_file << endl;
                prev_slot = slot;
                //cout << "SessionSlot-" << prev_slot << endl;
                flag_find = true;
            }
        }
        slot_file.close();
    }
    else
    {
        //cout << "Slot_file doesn't open!" << endl;
    }
}

void open_slots(string number_slot)
{
    ofstream result_file("SM_SessionSlot_result.txt",ios::out);
    string file;
    flag_find = false;
    //заполнение ведущими нулями
    std::ostringstream add_zeros;
    add_zeros << setfill('0') << setw(3) << number_slot;
    number_slot = add_zeros.str();
    for(int i=0; i<5; i++)
    {
        if(i == 0)
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log";
        }
        else
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log.1";
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_slot, file, result_file);
        if(flag_find == true) {break;}
    }
    if(flag_find == false) {cout << "Not found time in SessionSlot-" + number_slot + ".log" << endl;}
    result_file.close();
    prev_slot = "0";
}

void open_cxi_slots(string number_slot)
{
    ofstream result_file("CXI_SessionSlot_result.txt",ios::out);
    string file;
    flag_find = false;
    //заполнение ведущими нулями
    std::ostringstream add_zeros;
    add_zeros << setfill('0') << setw(3) << number_slot;
    number_slot = add_zeros.str();
    for(int i=0; i<5; i++)
    {
        if(i == 0)
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/CXI/CCXML-SessionSlot-" + number_slot + ".log";
        }
        else
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/CXI/CCXML-SessionSlot-" + number_slot + ".log.1";
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_slot, file, result_file);
        if(flag_find == true) {break;}
    }
    if(flag_find == false) {cout << "Not found time in CCXML-SessionSlot-" + number_slot + ".log" << endl;}
    result_file.close();
    prev_slot = "0";
}

void open_vb_slots(string number_slot)
{
    ofstream result_file("VB_SessionSlot_result.txt",ios::out);
    string file;
    flag_find = false;
    //заполнение ведущими нулями
    std::ostringstream add_zeros;
    add_zeros << setfill('0') << setw(3) << number_slot;
    number_slot = add_zeros.str();
    for(int i=0; i<5; i++)
    {
        if(i == 0)
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/VB/SessionSlot-" + number_slot + ".log";
        }
        else
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/VB/SessionSlot-" + number_slot + ".log.1";
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_slot, file, result_file);
        if(flag_find == true) {break;}
    }
    if(flag_find == false) {cout << "Not found time in VB/SessionSlot-" + number_slot + ".log" << endl;}
    result_file.close();
    prev_slot = "0";
}

void open_end_point_mgr(string number_slot)
{
    ofstream result_file("End_Point_Mgr_result.txt",ios::out);
    string file;
    flag_find = false;
    //заполнение ведущими нулями
    std::ostringstream add_zeros;
    add_zeros << setfill('0') << setw(3) << number_slot;
    number_slot = add_zeros.str();
    for(int i=0; i<10; i++)
    {
        if(i == 0)
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/MediaMgr/EndPointMgr.log";
        }
        else
        {
            file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/MediaMgr/EndPointMgr.log." + to_string(i);
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_slot, file, result_file);
        if(flag_find == true) {break;}
    }
    if(flag_find == false) {cout << "Not found time in MediaMgr/EndPointMgr.log" << endl;}
    result_file.close();
    prev_slot = "0";
}

int search_calls(string time, string number_slot)
{
    int pos_time = time.find(' ');
    start_t = time.substr(0,pos_time);
    end_t = time.substr(pos_time + 1);
    open_slots(number_slot);//SessMgr/SessionSlot
    open_cxi_slots(number_slot);//CXI/CCXML-SessionSlot
    open_vb_slots(number_slot);//VB/SessionSlot
    open_end_point_mgr(number_slot);//MediaMgr/EndPointMgr
    return 0;
}