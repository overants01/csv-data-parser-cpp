#include <iostream>
#include <string>
#include <fstream>
#include "stringpro.hpp"

using std::cout, std::cin, std::ofstream, std::ifstream, std::string, std::getline;
using namespace pro;

bool IsCorrectData(const string &Data)
{
    if (Data.empty())
    {
        return false;
    }
    int commaCount = 0;
    for (char c : Data)
    {
        if (c == ',')
        {
            commaCount++;
        }
    }
    if (commaCount == 3)
    {
        return true;
    }
    return false;
}

void NewData(const string &FileName, const string &Data)
{
    ofstream DataFile(FileName, std::ios::app);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return;
    }
    if (!IsCorrectData(Data))
    {
        cout << "Data is not correct!\n";
        return;
    }
    DataFile << Data << "\n";
    DataFile.close();
}

string reverseDay(const string &Day)
{
    string clone = Day;
    string result = "";
    for (int i = clone.length() - 1; i >= 0; i--)
    {
        result += clone[i];
    }
    return result;
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

string getDataDays(const string &FileName, const string &StartDay, const string &EndDay)
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
        string reversedDay = reverseDay(day);
        string reversedStartDay = reverseDay(StartDay);
        string reversedEndDay = reverseDay(EndDay);
        if (reversedDay >= reversedStartDay && reversedDay <= reversedEndDay)
        {
            Data = Data + "\nDay: " + day + " Time: " + Time + " Expenses: " + expenses + " Income: " + Income + "\n";
        }
    }
    DataFile.close();
    return Data;
}

double getALLexpenses(const string &FileName)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return 0;
    }
    string line;
    double expenses = 0;

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        // line == day, time, expenses, Income
        deleteEmpty(line);                                           // line == day,time,expenses,Income
        string day = get_str_until(line, ",");                       // day
        string Time = sub_str_until(line, ",");                      // time,expenses,Income
        Time = get_str_until(Time, ",");                             // time
        string expenses_str = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses_str = get_str_until(expenses_str, ",");
        expenses += std::stod(expenses_str);
    }
    DataFile.close();
    return expenses;
}

double getALLIncome(const string &FileName)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return 0;
    }
    string line;
    double Income = 0;

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        // line == day, time, expenses, Income
        deleteEmpty(line);                                           // line == day,time,expenses,Income
        string day = get_str_until(line, ",");                       // day
        string Time = sub_str_until(line, ",");                      // time,expenses,Income
        Time = get_str_until(Time, ",");                             // time
        string expenses_str = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses_str = get_str_until(expenses_str, ",");
        string Income_str = sub_str(line, day + "," + Time + "," + expenses_str + ",");
        Income += std::stod(Income_str);
    }
    DataFile.close();
    return Income;
}

void EditData(const string &FileName, string &DayOldAndTime, const string &NewData)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return;
    }
    if (!IsCorrectData(NewData))
    {
        cout << "Data is not correct!\n";
        return;
    }
    string line;
    string Data = ".day, time, expenses, Income\n";

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        // line == day, time, expenses, Income
        deleteEmpty(line);                                       // line == day,time,expenses,Income
        deleteEmpty(DayOldAndTime);                              // DayOldAndTime == day,time
        string day = get_str_until(line, ",");                   // day
        string Time = sub_str_until(line, ",");                  // time,expenses,Income
        Time = get_str_until(Time, ",");                         // time
        string expenses = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses = get_str_until(expenses, ",");
        string Income = sub_str(line, day + "," + Time + "," + expenses + ",");
        if (day + "," + Time == DayOldAndTime)
        {
            Data += NewData + "\n";
        }
        else
        {
            Data += line + "\n";
        }
    }
    DataFile.close();
    ofstream OutFile(FileName, std::ios::trunc);
    if (!OutFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return;
    }
    OutFile << Data;
    OutFile.close();
}

int main()
{

    cout << getDataDays("data.csv", "25/10/69", "29/10/69") << "\n";
    string DayOldAndTime = "25/10/69, 12:00";
    EditData("data.csv", DayOldAndTime, "25/10/69, 12:00, 100, 200");
    // cout << getALLexpenses("data.csv") << "\n";
    // cout << getALLIncome("data.csv") << "\n";
    // cout << getData("data.csv") << "\n";
    return 0;
}