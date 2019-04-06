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
    f.open(file_name);
    std::string line;

    Model model;

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
            obj_func.second = Objective::minimize;
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

    int rhs_count = 0;
    while (std::getline(f, line))
    {
        if (line == "BOUNDS")
            break;

        auto str_vec = StringSplit(line);

        for (int i = 1; i < str_vec.size() - 1; i += 2)
        {
            rhs[str_vec[0]][str_vec[i]] = std::stod(str_vec[i + 1]);
        }
        rhs_count++;
    }

    if (rhs_count == 0)
    {
        for (auto l : limits)
        {
            rhs["R"][l.first] = 0;
        }
    }

    // BOUNDS

    std::map<std::string, std::pair<double *, double *>> bounds_p;
    std::vector<double *> bounds_to_delete;

    for (auto v : variables)
    {
        bounds_p[v.first] = std::pair<double *, double *>(NULL, NULL);
    }

    while (std::getline(f, line))
    {
        if (line == "ENDATA")
            break;

        auto str_vec = StringSplit(line);

        if (str_vec[0] == "UP")
        {
            double *d = new double;
            *d = std::stod(str_vec[3]);
            bounds_p[str_vec[2]].second = d;
            bounds_to_delete.push_back(d);
        }
        else if (str_vec[0] == "LO")
        {
            double *d = new double;
            *d = std::stod(str_vec[3]);
            bounds_p[str_vec[2]].first = d;
            bounds_to_delete.push_back(d);
        }
        else if (str_vec[0] == "FX")
        {
            double *d = new double;
            *d = std::stod(str_vec[3]);
            bounds_p[str_vec[2]].first = d;
            bounds_p[str_vec[2]].second = d;
            bounds_to_delete.push_back(d);
        }

        else if (str_vec[0] == "FR")
        {
            double *d1 = new double, *d2 = new double;
            *d1 = -std::numeric_limits<double>::infinity();
            *d2 = std::numeric_limits<double>::infinity();
            bounds_p[str_vec[2]].first = d1;
            bounds_p[str_vec[2]].second = d2;
            bounds_to_delete.push_back(d1);
            bounds_to_delete.push_back(d2);
        }
    }

    std::map<std::string, std::pair<double, double>> bounds;

    for (auto b : bounds_p)
    {
        if (b.second.first == NULL && b.second.second == NULL)
        {
            bounds[b.first].first = 0;
            bounds[b.first].second = std::numeric_limits<double>::infinity();
        }
        else if (b.second.first == NULL)
        {
            if (*(b.second.second) < 0)
            {
                bounds[b.first].first = -std::numeric_limits<double>::infinity();
                bounds[b.first].second = *(b.second.second);
                continue;
            }
            bounds[b.first].first = 0;
            bounds[b.first].second = *(b.second.second);
        }
        else if (b.second.second == NULL)
        {
            bounds[b.first].first = *(b.second.first);
            bounds[b.first].second = std::numeric_limits<double>::infinity();
        }
        else
        {
            bounds[b.first].first = *(b.second.first);
            bounds[b.first].second = *(b.second.second);
        }
    }

    for (auto b : bounds_to_delete)
    {
        delete b;
    }

    // Generate Model

    std::vector<Variable> vars;
    std::vector<Constraint> constr;
    Objective objective(obj_func.first, obj_func.second);

    for (auto b : bounds)
    {
        Variable v(b.first, b.second.first, b.second.second);
        vars.push_back(v);
    }

    for (auto l : limits)
    {
        Constraint c(l.first);
        c.constraint_type = l.second;
        constr.push_back(c);
    }

    for (auto &c : constr)
    {
        for (auto v : variables)
        {
            if (v.second.find(c.name) != v.second.end())
                c.column_value[v.first] = v.second[c.name];
        }
    }

    std::string first_rhs = (rhs.begin()->first);

    for (auto &c : constr)
    {
        c.rhs_value[first_rhs] = rhs[first_rhs][c.name];
        c.main_rhs_value = rhs[first_rhs][c.name];
    }

    for (auto v : variables)
    {
        if (v.second.find(obj_func.first) != v.second.end())
            objective.cost_value[v.first] = v.second[obj_func.first];
    }

    model.objective_function = objective;
    model.variables = vars;
    model.constraints = constr;

    return model;
}