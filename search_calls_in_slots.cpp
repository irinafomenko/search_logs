#include "search_calls_in_slots.h"

using namespace std;

string start_t;
string end_t;
ofstream result_file("SessionSlot_result.txt",ios::out);
string prev_slot = "0";

void write_file(string slot, string file)
{
    ifstream slot_file(file,ios::in);
    string slot_str;
    if(slot_file.is_open())
    {
        while(!slot_file.eof())
        {
            if(prev_slot == slot) {break;}
            getline(slot_file, slot_str);
            int p1, p2 = -1;//позиции вхождений подстрок
            p1 = slot_str.find(start_t);
            if(p1 >= 0)
            {
                result_file << "SessionSlot-" + slot << endl;
                result_file << slot_str << endl;
                while(p2 < 0)
                {
                    getline(slot_file, slot_str);
                    result_file << slot_str << endl;
                    p2 = slot_str.find(end_t);
                }
                result_file << endl;
                prev_slot = slot;
            }

        }
        slot_file.close();
    }
    else
    {
        cout << "Slot_file doesn't open!" << endl;
    }
}

void search_slot(string file)
{
    string log_str, sub_str;
    string value_sub_str = "";// = "SIP/2.0";
    ifstream log_file(file,ios::in);

    if(log_file.is_open())
    {
        //string line = "";
        while(!log_file.eof())
        {
            getline(log_file, log_str);
            int p1;//позиции вхождений подстрок
            string sub_str = "[SessionSlot";
            p1 = log_str.find(sub_str);
            if(p1 >= 0)
            {
                string number_slot = log_str.substr(p1 + sub_str.length() + 1,3);
                //cout << number_slot << endl;
                for(int i=0; i<2; i++)
                {
                    string file_slot;
                    if(i == 0) {file_slot = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log";}
                    else {file_slot = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log.1";}
                    write_file(number_slot, file_slot);
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

int search_calls(string time)
{
    int pos_time = time.find(' ');
    start_t = time.substr(0,pos_time);
    end_t = time.substr(pos_time + 1);
    string new_xml_file = "SessionManager.xml";
    for(int i=0; i<5; i++)
    {
        string file;
        if(i == 0) {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log";}
        else {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log." + to_string(i);}
        cout << file << endl;
        search_slot(file);
    }
    result_file.close();
    return 0;
}