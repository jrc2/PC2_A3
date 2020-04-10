#ifndef MOVIEPLAITERCLION_MOVIENODE_H
#define MOVIEPLAITERCLION_MOVIENODE_H

#include <string>
#include "Movie.h"

using namespace model;
using namespace std;

namespace model
{

class MovieNode
{
private:
    Movie *movieInfo;
    string *nextName;
    int nextLength;
    int nextRating;

public:
    MovieNode(Movie *movieInfo, string *nextName, int nextLength, int nextRating);

    // getters
    Movie * getMovieInfo();
    string * getNextName();
    int getNextLength();
    int getNextRating();

    // setters
    void setNextName(string *nextName);
    void setNextLength(int nextLength);
    void setNextRating(int nextRating);

};
}

#endif //MOVIEPLAITERCLION_MOVIENODE_H
