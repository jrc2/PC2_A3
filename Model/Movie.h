#ifndef MOVIE_H
#define MOVIE_H

#include <string>

using namespace std;

namespace model
{

    class Movie
    {
    public:
        enum Rating
        {
            G, PG, PG13, R, NOT_RATED
        };

    private:
        string name;
        string studio;
        int year;
        Rating rating;
        int length;

    public:
        Movie(const string &name, const string &studio, int year, Rating rating, int length);

        const string &getName() const;

        const string &getStudio() const;

        Movie::Rating getRating() const;

        string getRatingString() const;

        int getYear();

        int getLength();

    };

}

#endif // MOVIE_H
