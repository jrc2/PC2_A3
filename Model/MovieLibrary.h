#ifndef MOVIEPLAITERCLION_MOVIELIBRARY_H
#define MOVIEPLAITERCLION_MOVIELIBRARY_H

#include <vector>
#include "Movie.h"
#include "MoviePlaitedList.h"

using namespace std;
using namespace model;

namespace model
{

    class MovieLibrary
    {

    private:
        MoviePlaitedList movies;

        void addMovieFromString(const string &movieInfo);

        void addToSummaryByName(MovieNode *node, string &output, bool ascending);

        void addToSummaryByLength(MovieNode *node, string &output, bool ascending);

        string generateSingleMovieSummary(MovieNode *node) const;

    public:
        void addMovie(Movie *pMovie);

        bool deleteMovie(const string &movieName);

        void importFromCSV(const string &csvContent);

        string generateSummaryByName(bool ascending);

        string generateSummaryByLength(bool ascending);

    };

}


#endif //MOVIEPLAITERCLION_MOVIELIBRARY_H
