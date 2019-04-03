#include "Parser.h"

std::string StringRemoveBorders(std::string str)
{
    while (str[0] == ' ')
    {
        str.erase(str.begin());
    }
    while (*(str.end() - 1) == ' ')
    {
        str.erase(str.end() - 1);
    }

    return str;
}

std::vector<std::string> StringSplit(std::string str)
{
    std::vector<std::string> str_vec;
    str = StringRemoveBorders(str);

    while (str.size() != 0)
    {
        int i = 0;
        for (char c : str)
        {
            if (c == ' ')
            {
                str_vec.push_back(std::string(str.begin(), str.begin() + i));
                i++;
                break;
            }
            else if(i == str.size() - 1)
            {
                str_vec.push_back(std::string(str.begin(), str.begin() + i + 1));
                i++;
                break;
            }
            i++;
        }
        str = std::string(str.begin() + i, str.end());
        str = StringRemoveBorders(str);
        }

    return str_vec;
}

Model ReadMps(std::string file_name)
{
    std::ifstream f;
    Model m;
    f.open(file_name);

    std::string line;

    int line_counter = 0;
    while (std::getline(f, line))
    {
        /*if (line_counter == 0 || line_counter == 1)
        {
            line_counter++;
            continue;
        }

        if (line == "COLUMNS")
            break; */
        

        for(auto str : StringSplit(line))
        {
            std::cout << "[" << str << "] ";
        }
        std::cout << "\n";

        line_counter++;
    }

    return m;
}