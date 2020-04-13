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

        void insertByLength(MovieNode *nodeToAdd);

        void insertByRating(MovieNode *nodeToAdd);

        void deleteFromLength(MovieNode *nodeToDelete);

    public:
        MoviePlaitedList();

        MovieNode *getNameHead();

        MovieNode *getLengthHead();

        MovieNode *getRatingHead();

        void insertMovie(Movie *pMovie);

        bool deleteMovie(const string &movieName);

        virtual ~MoviePlaitedList();

    };
}


#endif //MOVIEPLAITERCLION_MOVIEPLAITEDLIST_H
