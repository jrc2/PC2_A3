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
    int longestName;

    void insertByName(MovieNode *nodeToAdd);
    void insertByLength(MovieNode *nodeToAdd);
    void insertByRating(MovieNode *nodeToAdd);
    void addToSummaryByName(MovieNode *node, string &output, bool ascending);

public:
    //constructor
    MoviePlaitedList();

    void insertMovie(Movie *pMovie);
    bool deleteMovie(const string &movieName);
    string generateSummaryByName(bool ascending);

    // destructor
    virtual ~MoviePlaitedList();

};
}



#endif //MOVIEPLAITERCLION_MOVIEPLAITEDLIST_H
