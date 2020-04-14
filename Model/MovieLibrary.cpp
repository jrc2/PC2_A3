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
    *
    * @return a message indicating the file was loaded and containing any errors
    */
    string MovieLibrary::importFromCSV(const string &csvContent)
    {
        stringstream contentStream(csvContent);
        string line;
        string returnMessages = "File loaded";

        while (getline(contentStream, line, '\n'))
        {
            try
            {
                this->addMovieFromString(line);
            }
            catch (const invalid_argument &error)
            {
                returnMessages += "\n\n" + string(error.what()) + " Movie skipped.";
            }
        }
        
        return returnMessages;
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
        int year = toInt(movieInfoArray[2], ("Error for movie \"" + title + "\":\nYear field is not a number.").c_str());
        Movie::Rating rating = returnRatingBasedOnString(movieInfoArray[3]);
        int length = toInt(movieInfoArray[4], ("Error for movie \"" + title + "\":\nLength field is not a number.").c_str());
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
     *
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
     *
     * @return the summary output
     */
    string MovieLibrary::getSummaryByName(bool ascending, bool forCSV)
    {
        this->generateColumnLengths();
        string output;
        MovieNode *currMovieNode = this->movies.getNameHead();
        this->generateSummaryByName(currMovieNode, output, ascending, forCSV);

        return output;
    }

    void MovieLibrary::generateSummaryByName(MovieNode *node, string &output, bool ascending, bool forCSV)
    {
        if (node == nullptr)
        {
            return;
        }

        if (ascending)
        {
            output += this->generateSingleMovieSummary(node, forCSV);
        }
    
        this->generateSummaryByName(node->getNextName(), output, ascending, forCSV);

        if (!ascending)
        {
            output += this->generateSingleMovieSummary(node, forCSV);
        }
    }

    /**
     * Generates the summary output, ordered by Movie length
     *
     * @precondition none
     * @postcondition none
     *
     * @param ascending set to true to sort ascending by length, false to sort descending
     *
     * @return the summary output
     */
    string MovieLibrary::getSummaryByLength(bool ascending)
    {
        this->generateColumnLengths();
        string output;
        MovieNode *currMovieNode = this->movies.getLengthHead();
        this->generateSummaryByLength(currMovieNode, output, ascending);

        return output;
    }

    void MovieLibrary::generateSummaryByLength(MovieNode *node, string &output, bool ascending)
    {
        if (node == nullptr)
        {
            return;
        }

        if (ascending)
        {
            output += this->generateSingleMovieSummary(node, false);
        }
    
        this->generateSummaryByLength(node->getNextLength(), output, ascending);

        if (!ascending)
        {
            output += this->generateSingleMovieSummary(node, false);
        }
    }

    /**
     * Generates the summary output, ordered by Movie rating
     *
     * @precondition none
     * @postcondition none
     *
     * @param ascending set to true to sort ascending by rating, false to sort descending
     *
     * @return the summary output
     */
    string MovieLibrary::getSummaryByRating(bool ascending)
    {
        this->generateColumnLengths();
        string output;
        MovieNode *currMovieNode = this->movies.getRatingHead();
        this->generateSummaryByRating(currMovieNode, output, ascending);

        return output;
    }

    void MovieLibrary::generateSummaryByRating(MovieNode *node, string &output, bool ascending)
    {
        if (node == nullptr)
        {
            return;
        }

        if (ascending)
        {
            output += this->generateSingleMovieSummary(node, false);
        }
    
        this->generateSummaryByRating(node->getNextRating(), output, ascending);

        if (!ascending)
        {
            output += this->generateSingleMovieSummary(node, false);
        }
    }

    string MovieLibrary::generateSingleMovieSummary(MovieNode *node, bool forCSV) const
    {
        Movie *movie = node->getMovieInfo();
        string name = movie->getName();
        string studio = movie->getStudio();
        string year = to_string(movie->getYear());
        string rating = movie->getRatingString();
        string length = to_string(movie->getLength());
        
        if (forCSV)
        {
            return name + "," + studio + "," + year + "," + rating + "," + length + "\n";
        }
        
        string nameAndYear = name + "-" + year;
        nameAndYear.resize(this->longestNameLength + 6, ' ');
        studio.resize(this->longestStudioLength + 1, ' ');
        this->containsNotRated ? rating.resize(10, ' ') : rating.resize(5, ' ');

        return nameAndYear + studio + rating + length + "\n";
    }
    
    void MovieLibrary::generateColumnLengths()
    {
        MovieNode *current = this->movies.getNameHead();
        this->longestNameLength = 0;
        this->longestStudioLength = 0;
        this->containsNotRated = false;
        
        while (current != nullptr)
        {
            int currentNameLength = current->getMovieInfo()->getName().length();
            if (currentNameLength > this->longestNameLength)
            {
                this->longestNameLength = currentNameLength;
            }
            
            int currentStudioLength = current->getMovieInfo()->getStudio().length();
            if (currentStudioLength > this->longestStudioLength)
            {
                this->longestStudioLength = currentStudioLength;
            }
            
            if (current->getMovieInfo()->getRating() == Movie::NOT_RATED)
            {
                this->containsNotRated = true;
            }
            
            current = current->getNextName();
        }
    }
    
}