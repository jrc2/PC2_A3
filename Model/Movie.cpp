#include <stdexcept>
#include "Movie.h"
#include "Utils.h"

namespace model
{
    /**
     * Holds information about one movie
     *
     * @author Duane Yoder, John Chittam
     */

    /**
     * Constructs a new movie
     *
     * @precondition !name.empty() AND !studio.empty() AND year>=0 AND year<=9999 AND length>=1
     * @postcondition getName()==name AND getStudio()==studio AND getRating()==rating
     *                AND getYear()==year AND getLength()==length
     *
     * @param name the movie's name
     * @param studio the studio that produced the movie
     * @param year the movie's release year
     * @param rating the movie's rating (G, PG, etc.)
     * @param length the movie's length in minutes
     */
    Movie::Movie(const string &name, const string &studio, int year, Rating rating, int length)
    {
        if (name.empty())
        {
            throw invalid_argument("Movie name cannot be empty");
        }
        if (studio.empty())
        {
            throw invalid_argument("Movie \"" +name + "\" studio cannot be empty");
        }
        if (year < 0 || year > 9999)
        {
            throw invalid_argument("Movie \"" +name + "\" year must be >= 0 AND <= 9999");
        }
        if (length < 1)
        {
            throw invalid_argument("Movie \"" +name + "\" length must be at least one");
        }

        this->name = name;
        this->studio = studio;
        this->year = year;
        this->rating = rating;
        this->length = length;
    }

    /**
     * Gets movie name
     *
     * @precondition none
     * @postcondition none
     *
     * @return the movie name
     */
    const string &Movie::getName() const
    {
        return this->name;
    }

    /**
     * Gets movie studio
     *
     * @precondition none
     * @postcondition none
     *
     * @return the movie studio
     */
    const string &Movie::getStudio() const
    {
        return this->studio;
    }

    /**
     * Gets movie rating
     *
     * @precondition none
     * @postcondition none
     *
     * @return the movie rating
     */
    Movie::Rating Movie::getRating() const
    {
        return this->rating;
    }

    /**
     * Gets the string form of the movie rating
     *
     * @precondition none
     * @postcondition none
     *
     * @return the string form of the movie rating
     */
    string Movie::getRatingString() const
    {
        if (this->rating == G)
        {
            return "G";
        }
        if (this->rating == PG)
        {
            return "PG";
        }
        if (this->rating == PG13)
        {
            return "PG13";
        }
        if (this->rating == R)
        {
            return "R";
        }

        return "NOT RATED";
    }

    /**
     * Gets the movie release year
     *
     * @precondition none
     * @postcondition none
     *
     * @return the movie release year
     */
    int Movie::getYear()
    {
        return this->year;
    }

    /**
     * Gets the movie length in minutes
     *
     * @precondition none
     * @postcondition none
     *
     * @return the movie length in minutes
     */
    int Movie::getLength()
    {
        return this->length;
    }

    /**
     * Movie destructor
     */
    Movie::~Movie()
    {
        //TODO
    }

}
