#include "MovieLibrary.h"

#include <string>
#include <sstream>
#include <iostream>

#include "Utils.h"

using namespace std;

namespace model
{

    /**
    * Holds all movies and generates movie summary info
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
     * Deletes the given movie
     *
     * @precondition none
     * @postcondition none
     *
     * @param movieName the name of the movie to delete
     * @return true if the movie existed and was deleted, false if the movie did not exist
     */
    bool MovieLibrary::deleteMovie(const string &movieName)
    {
        return this->movies.deleteMovie(movieName);
    }

    /**
     * Generates the summary output, ordered by Movie name
     *
     * @precondition none
     * @postcondition none
     *
     * @param ascending set to true to sort ascending by name, false to sort descending
     * @return the summary output
     */
    string MovieLibrary::generateSummaryByName(bool ascending)
    {
        string output;
        MovieNode *currMovieNode = this->movies.getNameHead();
        this->addToSummaryByName(currMovieNode, output, ascending);

        return output;
    }

    void MovieLibrary::addToSummaryByName(MovieNode *node, string &output, bool ascending)
    {
        if (node == nullptr)
        {
            return;
        }

        if (ascending)
        {
            output += this->generateSingleMovieSummary(node);
        }

        this->addToSummaryByName(node->getNextName(), output, ascending);

        if (!ascending)
        {
            output += this->generateSingleMovieSummary(node);
        }
    }

    /**
     * Generates the summary output, ordered by Movie length
     *
     * @precondition none
     * @postcondition none
     *
     * @param ascending set to true to sort ascending by length, false to sort descending
     * @return the summary output
     */
    string MovieLibrary::generateSummaryByLength(bool ascending)
    {
        string output;
        MovieNode *currMovieNode = this->movies.getLengthHead();
        this->addToSummaryByLength(currMovieNode, output, ascending);

        return output;
    }

    void MovieLibrary::addToSummaryByLength(MovieNode *node, string &output, bool ascending)
    {
        if (node == nullptr)
        {
            return;
        }

        if (ascending)
        {
            output += this->generateSingleMovieSummary(node);
        }

        this->addToSummaryByLength(node->getNextLength(), output, ascending);

        if (!ascending)
        {
            output += this->generateSingleMovieSummary(node);
        }
    }

    string MovieLibrary::generateSingleMovieSummary(MovieNode *node) const
    {
        Movie *movie = node->getMovieInfo();
        const string &name = movie->getName();
        const string &studio = movie->getStudio();
        const string &year = to_string(movie->getYear());
        const string &rating = movie->getRatingString();
        const string &length = to_string(movie->getLength());
        const string &output =
                name + ", " + studio + ", " + year + ", " + rating + ", " + length +
                "\n"; //TODO format into even columns

        return output;
    }

}