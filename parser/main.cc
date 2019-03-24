#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main()
{
    std::ifstream f;
    f.open("p1.mps");
    std::string line;

   /* while (std::getline(f, line) && line.find("ROWS") == std::string::npos)
    {
        //
    }

    std::vector<std::vector<double>> tableau;
    tableau.push_back(std::vector<double>());

    int n_restrictions = 0;
    int n_artificial_vars = 0;
    std::vector<char> restriction_type;
    std::vector<std::string> restriction_names;


    while (std::getline(f, line) && line.find("COLUMNS"))
    {
        if (n_restrictions != 0)
        {
            tableau.push_back(std::vector<double>());
            if (line[1] == 'G')
            {
                n_artificial_vars++;
            }
            else if (line[1] == 'E')
            {
                n_artificial_vars++;
            }
            restriction_type.push_back(line[1]);
        }
        n_restrictions++;
    } */

}