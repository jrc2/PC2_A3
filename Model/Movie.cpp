#include <stdexcept>
#include "Movie.h"
#include "Utils.h"

namespace model
{
    //
    // TODO: Document everything public
    //
    Movie::Movie(const string &name, const string &studio, int year, Rating rating, int length)
    {
        this->name = name;
        this->studio = studio;
        this->year = year;
        this->rating = rating;
        this->length = length;
    }

    const string &Movie::getName() const
    {
        return this->name;
    }

    const string &Movie::getStudio() const
    {
        return this->studio;
    }

    Movie::Rating Movie::getRating() const
    {
        return this->rating;
    }

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

}
