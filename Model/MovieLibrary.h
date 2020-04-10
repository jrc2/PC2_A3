#ifndef MOVIEPLAITERCLION_MOVIELIBRARY_H
#define MOVIEPLAITERCLION_MOVIELIBRARY_H

#include <vector>
#include "Movie.h"

using namespace std;

namespace model
{

class MovieLibrary
{

private:
    vector<Movie> movies;

    void addMovie(Movie &movie);
    void addMovieFromString(string &movieInfo);

public:
    void importFromCSV(string &csvContent);
    const vector<Movie> &getMovies();

};

}



#endif //MOVIEPLAITERCLION_MOVIELIBRARY_H
