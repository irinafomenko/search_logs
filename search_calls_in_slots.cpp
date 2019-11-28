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
                cout << "SessionSlot-" << prev_slot << endl;
            }
        }
        slot_file.close();
    }
    else
    {
        cout << "Slot_file doesn't open!" << endl;
    }
}

int search_calls(string time, string number_sid)
{
    int pos_time = time.find(' ');
    start_t = time.substr(0,pos_time);
    end_t = time.substr(pos_time + 1);
    string file;
    for(int i=0; i<2; i++)
    {
        if(i == 0)
        {
            if(number_sid.length() == 1) {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-00" + number_sid + ".log";}
            else if(number_sid.length() == 2){file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-0" + number_sid + ".log";}
            else {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_sid + ".log";}
        }
        else
        {
            if(number_sid.length() == 1) {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-00" + number_sid + ".log.1";}
            else if(number_sid.length() == 2){file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-0" + number_sid + ".log.1";}
            else {file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_sid + ".log.1";}
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_sid, file);
    }
    result_file.close();
    return 0;
}