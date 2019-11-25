//#pragma comment(lib,"libcurl")
#include "parser_xml.h"
using namespace rapidxml;
using namespace std;

//объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
//static char errorBuffer[CURL_ERROR_SIZE];
//объялвяем буфер принимаемых данных
//static string buffer_xml;
//необходимые CURL объекты
//CURL *curl;
bool flag_not_found = false;
//xml file
xml_document<> doc;
std::ofstream logs_file;
string start_time;//начало времени
string end_time;

void search_time(xml_node<> * node)
{
    if(node->value() < start_time) {start_time = node->value();}
    if(node->value() > end_time) {end_time = node->value();}
}

void print_node(xml_node<> * node)
{
    logs_file << node->name() << ": " << node->value() << endl;
    string time = "Time";
    if(node->name() == time)
    {
        if(start_time.length() == 0) {start_time = end_time = node->value();}
        search_time(node);
    }
    cout << node->name() << ": " << node->value() << endl;
    for (xml_attribute<> * att = node->first_attribute(); att; att = att->next_attribute())
    {
        logs_file << "Name attribute: " << att->name() << endl;
        logs_file << "Value attribute: " << att->value() << endl;
        cout << "Name attribute: " << att->name() << endl;
        cout << "Value attribute: " << att->value() << endl;
    }
}

void print_result(xml_node<> * node)
{
    cout << endl;
    xml_node<> * parent = node->parent();
    //cout << parent->name() << endl;
    string sip = "SIP";
    if(parent->name() == sip)
    {
        string type = "SIP.2.0";
        if(parent->name() == type)
        {
            xml_attribute<> * att =  parent->first_attribute();
            logs_file << endl << "Name tag: " << node->name() << " " << att->value() << endl;
            cout << "Name tag: " << node->name() << " " << att->value() << endl;
        }
        else
        {
            logs_file << endl << "Name tag: " << node->name() << endl;
            cout << "Name tag: " << node->name() << endl;
        }
        for (xml_node<> * child_node = node->first_node(); child_node; child_node = child_node->next_sibling())
        {
            print_node(child_node);
        }
    }
    else
    {
        string type = "SIP.2.0";
        if(parent->name() == type)
        {
            xml_attribute<> * att =  parent->first_attribute();
            logs_file << endl << "Parent node: " << parent->name() << " " << att->value() << endl;
            cout << "Parent node: " << parent->name() << " " << att->value() << endl;
        }
        else
        {
            logs_file << endl << "Parent node: " << parent->name() << endl;
            cout << "Parent node: " << parent->name() << endl;
        }
        xml_node<> * child_node = parent->first_node();
        for (xml_node<> * child_node = parent->first_node(); child_node; child_node = child_node->next_sibling())
        {
             print_node(child_node);
        }
    }
    flag_not_found = true;
}

void search_tag(xml_node<> * root_node, string name_tag, string value_tag)
{
    for (root_node; root_node; root_node = root_node->next_sibling())
    {
        xml_node<> * child_node = root_node->first_node();
        if(name_tag.empty())
        {
            string sub_value_tag = root_node->value();
            int pos_sub_value_tag = sub_value_tag.find(value_tag);
            if(root_node->name() != name_tag && pos_sub_value_tag >= 0) {print_result(root_node);}
            search_tag(child_node, name_tag, value_tag);
        }
        else if(value_tag.empty())
        {
            if(root_node->name() == name_tag) {print_result(root_node);}
            search_tag(child_node, name_tag, value_tag);
        }
        else
        {
            string sub_value_tag = root_node->value();
            int pos_sub_value_tag = sub_value_tag.find(value_tag);
            if(root_node->name() == name_tag && pos_sub_value_tag >= 0) {print_result(root_node);}
            search_tag(child_node, name_tag, value_tag);
        }
    }
}

void parsing_xml(std::string file)
{
    string name_tag, value_tag;
    cout << "Enter name tag: ";
    getline(cin, name_tag);
    cout << "Enter value tag: ";
    getline(cin, value_tag);

    cout << "Parsing..." << endl;
    // Read the xml file into a vector
    ifstream theFile (file);
    //ifstream theFile ("C:/Users/ifomenko/CLionProjects/project_logs/cmake-build-debug/SessionManager.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    //buffer.push_back('\0');
    try
    {
        // Parse the buffer using the xml file parsing library into doc
        doc.parse<0>(&buffer[0]);
        xml_node<> * root_node = doc.first_node();
        search_tag(root_node, name_tag, value_tag);

        if(flag_not_found == false) {cout << endl << "Not found!" << endl;}
    }
    catch (const rapidxml::parse_error& e) //работает
    {
        cerr << "Parse error was: " << e.what() << std::endl;
    }
}

int pars_xml(std::string file)
{
    //download_xml();
    logs_file.open("results_search_logs.txt", ios::out);
    if(logs_file.is_open())
    {
        parsing_xml(file);
        logs_file.close();
        cout << "start_time: " << start_time << endl;
        cout << "end_time: " << end_time << endl;
    }
    else
    {
        cout << "Output file doesn't open!" << endl;
    }
    return 0;
}