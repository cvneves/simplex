#ifndef PARSER_H
#define PARSER_H

#include "Model.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

Model ReadMps(std::string file_name);
std::vector<std::string> StringSplit(std::string);
std::string StringRemoveBorders(std::string);

#endif