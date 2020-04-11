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

public:
    void addMovie(Movie *pMovie);
    bool deleteMovie(const string &movieName);
    void importFromCSV(const string &csvContent);
    string generateSummaryByNameAscending();

};

}



#endif //MOVIEPLAITERCLION_MOVIELIBRARY_H
