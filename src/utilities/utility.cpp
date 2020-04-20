#ifndef UTILITY_CPP
#define UTILITY_CPP

#include<sstream>

using namespace std;

std::string to_string (int Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

#endif