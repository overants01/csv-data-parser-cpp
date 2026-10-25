#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "stringpro.hpp"

using std::cout, std::cin, std::ofstream, std::ifstream, std::vector, std::string, std::getline;
using namespace pro;

void NewData(const string &FileName, const string &Data)
{
    ofstream DataFile(FileName, std::ios::app);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return;
    }
    DataFile << Data << "\n";
    DataFile.close();
}

string getData(const string &FileName)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return "";
    }
    string line;
    string Data = "";

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        // line == day, time, expenses, Income
        deleteEmpty(line);                                       // line == day,time,expenses,Income
        string day = get_str_until(line, ",");                   // day
        string Time = sub_str_until(line, ",");                  // time,expenses,Income
        Time = get_str_until(Time, ",");                         // time
        string expenses = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses = get_str_until(expenses, ",");
        string Income = sub_str(line, day + "," + Time + "," + expenses + ",");
        Data = Data + "\nDay: " + day + " Time: " + Time + " Expenses: " + expenses + " Income: " + Income + "\n";
    }
    DataFile.close();
    return Data;
}

string getDataDay(const string &FileName, const string &DayTarget)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return "";
    }
    string line;
    string Data = "";

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        // line == day, time, expenses, Income
        deleteEmpty(line);                                       // line == day,time,expenses,Income
        string day = get_str_until(line, ",");                   // day
        string Time = sub_str_until(line, ",");                  // time,expenses,Income
        Time = get_str_until(Time, ",");                         // time
        string expenses = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses = get_str_until(expenses, ",");
        string Income = sub_str(line, day + "," + Time + "," + expenses + ",");
        if (day == DayTarget)
        {
            Data = Data + "\nDay: " + day + " Time: " + Time + " Expenses: " + expenses + " Income: " + Income + "\n";
        }
    }
    DataFile.close();
    return Data;
}

int main()
{
    cout << getDataDay("data.csv", "25/10/69") << "\n";
    return 0;
}