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
            else if (i == str.size() - 1)
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

    // ROWS

    int line_counter = 0;

    std::map<std::string, Constraint::ConstraintType> limits;
    std::pair<std::string, Objective::ObjectiveType> obj_func;

    while (std::getline(f, line))
    {
        if (line_counter == 0 || line_counter == 1)
        {
            line_counter++;
            continue;
        }

        if (line == "COLUMNS")
            break;

        auto str_vec = StringSplit(line);

        if (str_vec[0] == "N")
        {
            obj_func.first = str_vec[1];
            obj_func.second = Objective::maximize;
        }
        else if (str_vec[0] == "L")
        {
            limits[str_vec[1]] = Constraint::less_equal;
        }
        else if (str_vec[0] == "E")
        {
            limits[str_vec[1]] = Constraint::equal;
        }
        else if (str_vec[0] == "G")
        {
            limits[str_vec[1]] = Constraint::greater_equal;
        }

        line_counter++;
    }

    // COLUMNS

    line_counter = 0;

    std::map<std::string, std::map<std::string, double>> variables;

    while (std::getline(f, line))
    {
        if (line == "RHS")
            break;

        auto str_vec = StringSplit(line);

        for (int i = 1; i < str_vec.size() - 1; i += 2)
        {
            variables[str_vec[0]][str_vec[i]] = std::stod(str_vec[i + 1]);
        }
    }

    // RHS

    std::map<std::string, std::map<std::string, double>> rhs;

    while (std::getline(f, line))
    {
        if (line == "BOUNDS")
            break;

        auto str_vec = StringSplit(line);

        for (int i = 1; i < str_vec.size() - 1; i += 2)
        {
            rhs[str_vec[0]][str_vec[i]] = std::stod(str_vec[i + 1]);
        }

  
    }

    // BOUNDS

    std::map <std::string, std::pair<double, double>> bounds;

    for(auto v : variables)
    {
        bounds[v.first] = ;
    }

    while (std::getline(f, line))
    {
        if (line == "ENDATA")
            break;

        auto str_vec = StringSplit(line);




        std::cout << line << "\n";
    }

    return m;
}