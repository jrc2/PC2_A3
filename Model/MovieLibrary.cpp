#include "MovieLibrary.h"

#include <string>
#include <sstream>
#include <iostream>

#include "Utils.h"

using namespace std;

namespace model
{

    /**
     * MovieLibrary holds all movies
     *
     * @author John Chittam
     */

    /**
     * Adds the given Movie pointer to the library
     *
     * @precondition none
     * @postcondition this->movies.size()==this->movies.size()@prev-1
     *
     * @param pMovie the Movie pointer to add
     */
    void MovieLibrary::addMovie(Movie *pMovie)
    {
        this->movies.insertMovie(pMovie);
    }

    /**
     * Imports movies from the content of a CSV file
     *
     * @precondition none
     * @postcondition all movies from CSV added
     *
     * @param csvContent the string representation of content from the loaded CSV
     */
    void MovieLibrary::importFromCSV(const string &csvContent)
    {
        stringstream contentStream(csvContent);
        string line;

        while (getline(contentStream, line, '\n'))
        {
            this->addMovieFromString(line);
        }
    }

    void MovieLibrary::addMovieFromString(const string &movieInfo)
    {
        stringstream movieInfoStream(movieInfo);
        string movieInfoArray[5];
        string temp;

        int counter = 0;
        while (getline(movieInfoStream, temp, ','))
        {
            movieInfoArray[counter] = temp;
            counter++;
        }

        string title = movieInfoArray[0];
        string studio = movieInfoArray[1];
        int year = toInt(movieInfoArray[2], "Year field is not a number");
        Movie::Rating rating = returnRatingBasedOnString(movieInfoArray[3]);
        int length = toInt(movieInfoArray[4], "Length field is not a number");
        auto *pMovie = new Movie(title, studio, year, rating, length);
        this->addMovie(pMovie);
    }

    /**
     * TODO
     * @param pMovie
     */
    bool MovieLibrary::deleteMovie(const string &movieName)
    {
        return this->movies.deleteMovie(movieName);
    }

    //TODO doc
    string MovieLibrary::generateSummaryByName(bool ascending)
    {
        return this->movies.generateSummaryByName(ascending);
    }

}