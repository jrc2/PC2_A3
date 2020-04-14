#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Movie.h"

using namespace std;

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

const string toUpperCase(string text);

int toInt(const string &text, const char *errorMessage);

model::Movie::Rating returnRatingBasedOnString(string &rating);

#endif // UTILS_H
