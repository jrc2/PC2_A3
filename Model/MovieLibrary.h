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

public:
    void addMovie(Movie &movie);
    static void importFromCSV(string &csvContent);
    const vector<Movie> &getMovies() const;

};

}



#endif //MOVIEPLAITERCLION_MOVIELIBRARY_H
