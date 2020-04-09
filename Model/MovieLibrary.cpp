#include "MovieLibrary.h"

using namespace std;

namespace model
{

    /**
     * MovieLibrary hold all movies
     *
     * @author John Chittam
     */

    /**
     * Adds the movie to library
     *
     * @precondition none
     * @postcondition this->movies.size() == this-movies.size()@prev + 1
     *
     * @param movie the movie to add
     */
    void MovieLibrary::addMovie(Movie &movie) {
        this->movies.push_back(movie);
    }

    /**
     * Imports movies from the content of a CSV file
     *
     * @precondition none
     * @postcondition all movies from CSV added
     *
     * @param csvContent the string representation of content from the loaded CSV
     */
    void MovieLibrary::importFromCSV(string &csvContent) {

    }

    /**
     * Gets the movies in library
     *
     * @precondition none
     * @postcondition none
     *
     * @return the vector of movies in library
     */
    const vector<Movie> &MovieLibrary::getMovies() const {
        return this->movies;
    }
}