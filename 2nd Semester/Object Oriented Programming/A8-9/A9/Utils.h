#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Utils {
public:
    void trimWhiteSpacesOfAString(std::string &stringToTrim);

    std::vector<std::string> tokenizeString(std::string &stringToTokenize, char delimiter);
};