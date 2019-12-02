#include "search_calls_in_slots.h"

using namespace std;

string start_t;
string end_t;
//ofstream result_file("SM_SessionSlot_result.txt",ios::out);
string prev_slot = "0";

void write_file(string slot, string file, string res_file)
{
    ifstream slot_file(file,ios::in);
    ofstream result_file(res_file,ios::out);
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
        result_file.close();
    }
    else
    {
        cout << "Slot_file doesn't open!" << endl;
    }
}

void open_slots(string number_slot)
{
    string file, result_file = "SM_SessionSlot_result.txt";
    std::ostringstream add_zeros;
    add_zeros << setfill('0') << setw(3) << number_slot;
    number_slot = add_zeros.str();

    for(int i=0; i<2; i++)
    {
        if(i == 0)
        {
            file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log";
        }
        else
        {
            file = "C:/Users/ifomenko/Desktop/prjct_logs/opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionSlot-" + number_slot + ".log.1";
        }
        //cout << file << endl;
        //search_slot(file);
        write_file(number_slot, file, result_file);
    }
}

int search_calls(string time, string number_slot)
{
    int pos_time = time.find(' ');
    start_t = time.substr(0,pos_time);
    end_t = time.substr(pos_time + 1);
    open_slots(number_slot);


    return 0;
}