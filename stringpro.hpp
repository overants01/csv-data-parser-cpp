#pragma once
#include <iostream>
#include <string>

namespace pro
{
    inline bool start_with(const std::string &str, const std::string &prefix)
    {
        return str.rfind(prefix, 0) == 0;
    }
    inline bool have_str(const std::string &str, const std::string &target)
    {
        return str.find(target) != std::string::npos;
    }

    inline std::string sub_str(std::string str, const std::string &target)
    {
        size_t pos = str.find(target);
        if (pos != std::string::npos)
        {
            str.erase(pos, target.length());
        }
        return str;
    }
    inline std::string get_str_until(const std::string str, const std::string &until_target)
    {
        if (until_target.empty() || until_target == " ")
        {
            size_t pos = str.find(' ');
            if (pos != std::string::npos)
            {
                return str.substr(0, pos);
            }
            return str;
        }

        size_t pos = str.find(until_target);
        if (pos != std::string::npos)
        {
            return str.substr(0, pos);
        }

        return str;
    }
    inline std::string deleteEmpty(std::string &word)
    {

        word.erase(remove(word.begin(), word.end(), ' '), word.end());
        return word;
    }
    inline std::string sub_str_until(std::string str, const std::string &until_target)
    {
        if (until_target.empty() || until_target == " ")
        {
            size_t pos = str.find(' ');
            if (pos != std::string::npos)
            {
                str.erase(0, pos + 1);
            }
            else
            {
                str.clear();
            }
            return str;
        }

        size_t pos = str.find(until_target);
        if (pos != std::string::npos)
        {
            str.erase(0, pos + until_target.length());
        }
        else
        {
            str.clear();
        }
        return str;
    }

    inline void lower(std::string &target)
    {
        for (auto &i : target)
        {
            if (i >= 'A' && i <= 'Z')
            {
                i += 32;
            }
        }
    }
    inline void upper(std::string &target)
    {
        for (auto &i : target)
        {
            if (i >= 'a' && i <= 'z')
            {
                i -= 32;
            }
        }
    }
}
