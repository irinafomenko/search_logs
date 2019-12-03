#include <iostream>
#include <string>
#include <cstring>
#include "pars_log.h"
#include "search_calls.h"

using namespace std;

ofstream result_logs_file("SM_SIP_result.txt", ios::out);
string number_slot;//номер слота
string path;

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        if(!strcmp(argv[1],".")) {path = "";}//текущая директория
        else {path = argv[1];}//введенная директория
    }
    else
    {
        path = "C:/Users/ifomenko/Desktop/prjct_logs/";//если ничего не вводили
    }
    string time;
    string name_tag, value_tag;
    cout << "Enter name tag: ";
    getline(cin, name_tag);
    cout << "Enter value tag: ";
    getline(cin, value_tag);

    for(int i=0; i<5; i++)
    {
        string file;
        if(i == 0) {file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log";}
        else {file = path + "opt/Avaya/ExperiencePortal/MPP/logs/process/SessMgr/SessionManager.log." + to_string(i);}
        cout << file << endl;
        //read_log_file(file);
        time = pars_log(file, name_tag, value_tag);
        //if(!number_slot.empty()) {break;}
    }
    cout << "Start time and end time: ";
    cout << time << endl;
    //cout << number_sid << endl;
    result_logs_file.close();
    /*---------------------------------------------*/
    //поиск номера слота
    //в строке содержится имя машины-id-номер слота
    //15 позиция номера слота после первого знака "-"
    number_slot = number_slot.substr(number_slot.find('-') + 15);
    /*
    char *s = new char[number_slot.size() + 1];
    strcpy(s, number_slot.c_str());
    char *p = strtok(s,"-");
    while (p != NULL)
    {
        number_slot = p;
        p = strtok(NULL, "-");
    }*/
#ifdef DEBUG
    cout << number_slot << endl;
#endif
    /*---------------------------------------------*/
    //поиск звонков в файлах
    search_calls(time, number_slot);
    /*---------------------------------------------*/

    return 0;
}