#include <stdexcept>
#include "Movie.h"
#include "Utils.h"

namespace model
{
    //
    // TODO: Document this
    //
    Movie::Movie(const string& name, const string& studio, int year, Rating rating, int length)
    {
        this->name = name;
        this->studio = studio;
        this->year = year;
        this->rating = rating;
        this->length = length;
    }

    const string& Movie::getName() const
    {
        return this->name;
    }

    const string& Movie::getStudio() const
    {
        return this->studio;
    }

    Movie::Rating Movie::getRating() const
    {
        return this->rating;
    }

    int Movie::getYear() const
    {
        return this->year;
    }

    int Movie::getLength() const
    {
        return this->length;
    }

    Movie::~Movie()
    {
        //dtor
    }

    /**
     * Returns the Rating enum corresponding with the given string
     *
     * @precondition rating is valid
     * @postcondition none
     *
     * @param rating the rating to parse to enum
     *
     * @return the Rating enum corresponding with the given string
     */
    Movie::Rating Movie::generateRatingFromString(const string &rating)
    {
        string uppercaseRating = toUpperCase(rating);
        if (uppercaseRating == "G")
        {
            return G;
        }
        else if (uppercaseRating == "PG")
        {
            return PG;
        }
        else if (uppercaseRating == "PG13")
        {
            return PG13;
        }
        else if (uppercaseRating == "R")
        {
            return R;
        }
        else {
            throw invalid_argument("Invalid rating");
        }
    }

}
