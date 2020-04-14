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
        int longestNameLength;
        int longestStudioLength;
        bool containsNotRated;

        void addMovieFromString(const string &movieInfo);

        void generateSummaryByName(MovieNode *node, string &output, bool ascending, bool forCSV);

        void generateSummaryByLength(MovieNode *node, string &output, bool ascending);

        void generateSummaryByRating(MovieNode *node, string &output, bool ascending);

        string generateSingleMovieSummary(MovieNode *node, bool forCSV) const;
    
        void generateColumnLengths();

    public:
        void addMovie(Movie *pMovie);

        bool deleteMovie(const string &movieName);

        string importFromCSV(const string &csvContent);

        string getSummaryByName(bool ascending, bool forCSV);

        string getSummaryByLength(bool ascending);

        string getSummaryByRating(bool ascending);
        
    };

}


#endif //MOVIEPLAITERCLION_MOVIELIBRARY_H
