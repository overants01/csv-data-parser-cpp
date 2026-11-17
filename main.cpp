#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <expected>
#include <iomanip>
#include "stringpro.hpp"

using std::cout, std::cin, std::ofstream, std::ifstream, std::string, std::getline, std::map, std::vector, std::runtime_error, std::invalid_argument;
using namespace pro;

void clearCS(string &target)
{
    sub_str(target, ",");
    deleteEmpty(target);
}

bool IsHaveDay(const string &fileName, const string &day)
{
    string line;
    ifstream File(fileName);

    if (!File.is_open())
        throw runtime_error("Cannot Open File");
    while (getline(File, line))
    {
        if (start_with(line, "."))
            continue;
        string dayc = get_str_until(line, ",");
        clearCS(dayc);

        if (dayc == day)
        {
            File.close();
            return true;
        }
    }
    File.close();
    return false;
}

bool EditData(const string &FileName, string &DayOldAndTime, const string &NewData)
{
    bool res = false;
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return res;
    }
    string line;
    string Data = ".day, time, expenses, Income\n";

    while (getline(DataFile, line))
    {
        if (start_with(line, "."))
        {
            continue;
        }
        deleteEmpty(line);                     // line == day,time,expenses,Income
        deleteEmpty(DayOldAndTime);            // DayOldAndTime == day,time
        string day = get_str_until(line, ","); // day
        string TEI = sub_str_until(line, ","); // time,expenses,Income

        string Time = get_str_until(TEI, ",");                   // time
        string expenses = sub_str(line, day + "," + Time + ","); // expenses,Income
        expenses = get_str_until(expenses, ",");
        string Income = sub_str(line, day + "," + Time + "," + expenses + ",");
        if (day + "," + Time == DayOldAndTime)
        {
            Data += NewData + "\n";
            res = true;
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
        return res;
    }
    OutFile << Data;
    OutFile.close();
    return res;
}

string reverseDay(const string &Day)
{
    string clone = Day;
    string d = get_str_until(clone, "/");
    string my = sub_str(clone, d + "/");
    string m = get_str_until(my, "/");
    string y = sub_str_until(my, "/");

    string res = y + "/" + m + "/" + d;
    return res;
}

string getDataDays(const string &FileName, const string &StartDay, const string &EndDay, const bool &RawVactor = false)
{
    ifstream DataFile(FileName);
    if (!DataFile.is_open())
    {
        cout << "Cannot Open File: " << FileName << "!\n";
        return "";
    }
    string line;
    string Data = "";
    vector<string> dataVector;

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
            if (RawVactor == true)
            {
                continue;
            }
            Data += "\nDay: " + day + " Time: " + Time + " Expenses: " + expenses + " Income: " + Income + "\n";
        }
    }
    DataFile.close();
    if (RawVactor == true)
    {
        return "dataVector";
    }
    return Data;
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

class Record
{
private:
    string day;
    vector<string> time;
    vector<double> income;
    vector<double> expenses;
    string filename;

public:
    Record(const string &fileName, const string &day)
    {
        if (!IsHaveDay(fileName, day))
            throw runtime_error("Not Have Day In Data");
        ifstream DataFile(fileName);
        if (!DataFile.is_open())
            throw runtime_error("Cannot Open File!");

        string line;
        while (getline(DataFile, line))
        {
            if (start_with(line, "."))
                continue;

            string d = get_str_until(line, ",");
            clearCS(d);
            if (d != day)
                continue;
            string TIE = sub_str(line, d + ",");
            string Time = get_str_until(TIE, ",");
            clearCS(Time);

            string IE = sub_str(TIE, Time + ",");
            string Expenses = get_str_until(IE, ",");
            clearCS(Expenses);

            string Income = sub_str(IE, Expenses + ",");
            clearCS(Expenses);

            this->time.push_back(Time);
            this->income.push_back(std::stod(Income));
            this->expenses.push_back(std::stod(Expenses));
        }
        DataFile.close();
        this->filename = fileName;
        this->day = day;
    }
    void Edit(const string &time, const string &NewEI)
    {
        int ti = 0;
        bool IsHasSet = false;
        string DAT = this->day + "," + time;
        string NewData = DAT + "," + NewEI;
        for (const auto &t : this->time)
        {
            if (t == time)
            {
                string NewExpenses_str = get_str_until(NewEI, ",");
                clearCS(NewExpenses_str);
                string NewIncome_str = sub_str_until(NewEI, ",");
                clearCS(NewIncome_str);

                double NewIncome = std::stod(NewIncome_str);
                double NewExpenses = std::stod(NewExpenses_str);

                this->expenses[ti] = NewExpenses;
                this->income[ti] = NewIncome;
                IsHasSet = true;
            }
            ti++;
        }
        if (IsHasSet)
        {
            EditData(this->filename, DAT, NewData);
        }
        else
        {
            cout << "Cannot Edit File!\n";
        }
    }
    double get_income(const string &time = "All") const
    {
        int ti = 0;
        double res = 0;
        for (const auto &t : this->time)
        {
            if (time == "All")
            {
                res += this->income[ti];
            }
            if (t == time)
            {
                return this->income[ti];
            }
            ti++;
        }
        return res;
    }
    double get_expenses(const string &time = "All") const
    {
        int ti = 0;
        double res = 0;
        for (const auto &t : this->time)
        {
            if (time == "All")
            {
                res += this->expenses[ti];
            }
            if (t == time)
            {
                return this->expenses[ti];
            }
            ti++;
        }
        return res;
    }
    double get_balance() const
    {
        return get_income() - get_expenses();
    }
    void print_income(const string &time = "All")
    {
        for (const auto &t : this->time)
        {
            if (time == "All")
            {
                cout << t + " Income: " << get_income(t) << "\n";
                continue;
            }
            if (t == time)
            {
                cout << time + " Income: " << get_income(time) << "\n";
            }
        }
    }
    void print_expenses(const string &time = "All")
    {
        for (const auto &t : this->time)
        {
            if (time == "All")
            {
                cout << t + " Expenses: " << get_expenses(t) << "\n";
                continue;
            }
            if (t == time)
            {
                cout << time + " Expenses: " << get_expenses(time) << "\n";
            }
        }
    }
};

int main()
{
    // ========== NEW [Remake] ========== //
    Record t("data.csv", "25/10/69");
    t.print_income();
    t.print_expenses();

    double expenses = t.get_expenses("12:00"); // Only 12:00 Time
    double income = t.get_income("12:00");     // Only 12:00 Time

    cout << "EPXENSENE: " << expenses << "\nINCOME: " << income << "\n";

    // t.get_income(); OR t.get_expenses(); Will has already been calculated within the function

    cout << "Balance: " << t.get_balance() << "\n";

    t.Edit("12:00", "67.49,999.67");
    t.print_expenses();
    t.print_income();
    cout << "Balance: " << t.get_balance() << "\n";

    // ========== old [26/10/69 || 26/10/26] ========== //
    cout << getDataDays("data.csv", "25/10/69", "29/10/69") << "\n";
    cout << getData("data.csv") << "\n";

    // ========== Full Old Code In oldmain.cpp ========== //
    return 0;
}