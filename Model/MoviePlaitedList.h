#ifndef MOVIEPLAITERCLION_MOVIEPLAITEDLIST_H
#define MOVIEPLAITERCLION_MOVIEPLAITEDLIST_H

#include "Movie.h"
#include "MovieNode.h"

using namespace std;
using namespace model;

namespace model
{

class MoviePlaitedList
{
private:
    MovieNode *nameHead;
    MovieNode *lengthHead;
    MovieNode *ratingHead;

    void insertByName(MovieNode *nodeToAdd);
    void insertByLength(MovieNode *node);
    void insertByRating(MovieNode *node);

public:
    //constructor
    MoviePlaitedList();

    void insertMovie(Movie *pMovie);

    // destructor
    virtual ~MoviePlaitedList();

};
}



#endif //MOVIEPLAITERCLION_MOVIEPLAITEDLIST_H
