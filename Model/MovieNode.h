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
    MovieNode *nextName;
    MovieNode *nextLength;
    MovieNode *nextRating;

public:
    virtual ~MovieNode();
    MovieNode(Movie *movieInfo);

    // getters
    Movie * getMovieInfo();
    MovieNode * getNextName();
    MovieNode * getNextLength();
    MovieNode * getNextRating();

    // setters
    void setNextName(MovieNode *nextName);
    void setNextLength(MovieNode *nextLength);
    void setNextRating(MovieNode *nextRating);

};
}

#endif //MOVIEPLAITERCLION_MOVIENODE_H
